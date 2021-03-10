using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Com.Huawei.Device;
using Com.Huawei.Device.Contract;
using Com.Huawei.Device.ServiceModel;
using NLog;

namespace ClienteHuawei.Huawei
{

    // Eventos relacionados a invocaciones de la interfase
    delegate void OnInitializeResultHandler(string callId, AgentInfo agentInfo,
            Dictionary<string, string> settings, bool flag, int errorCode);
    delegate void OnUnInitializeResultHandler(string callId, bool flag, int errorCode);
    delegate void OnAgentStatusChangeResultHandler(string callId, OpStatus status, bool flag, int errorCode);
    delegate void OnAnswerCallResultHandler(string callId, DialContent dialContent, bool flag, int errorCode);
    delegate void OnHangUpResultHandler(string callId, bool flag, int errorCode);
    delegate void OnDialResultHandler(string callId, DialContent dialContent, bool flag, int errorCode);

    // Eventos ajenos a invocaciones de la interfase
    delegate void OnAgentStatusChangeHandler(string callId, AgentInfo agentInfo);
    delegate void OnPhoneAlertingHandler(string callId, DeviceType callerType,
            string callerNumber, DeviceType calleeType, string calleeNumber);
    delegate void OnPhoneAlertOtherHungupHandler(string callId, DialContent dialContent);

    class InterfaceHuawei
    {
        protected int timeOut;
        protected Semaphore controlOperaciones = new Semaphore(1, 1);
        protected Queue<Dictionary<string, object>> operaciones = new Queue<Dictionary<string, object>>();
        
        protected AutoResetEvent waitInitializeResult = new AutoResetEvent(false);
        protected AutoResetEvent waitUninitializeResult = new AutoResetEvent(false);
        protected AutoResetEvent waitChangeStatusResult = new AutoResetEvent(false);
        protected AutoResetEvent waitPickupResult = new AutoResetEvent(false);
        protected AutoResetEvent waitHangupResult = new AutoResetEvent(false);
        protected AutoResetEvent waitDialResult = new AutoResetEvent(false);

        // Eventos relacionados a invocaciones de la interfase
        public event OnInitializeResultHandler OnInitializeResult;
        public event OnUnInitializeResultHandler OnUnInitializeResult;
        public event OnAgentStatusChangeResultHandler OnAgentStatusChangeResult;
        public event OnAnswerCallResultHandler OnAnswerCallResult;
        public event OnHangUpResultHandler OnHangupResult;
        public event OnDialResultHandler OnDialResult;

        // Eventos ajenos a invocaciones de la interfase
        public event OnAgentStatusChangeHandler OnAgentStatusChange;
        public event OnPhoneAlertingHandler OnPhoneAlerting;
        public event OnPhoneAlertOtherHungupHandler OnPhoneAlertOtherHungup;
        
        protected Dictionary<string, string> settings;
        protected IDevice device = null;
        protected Logger logger = LogManager.GetCurrentClassLogger();
        public string errMsg { get; protected set; }
        public bool statusAsociacion { get; protected set; }
        public OpStatus statusOperacion { get; protected set; }
        public AgentInfo datosAgente { get; protected set; }
        public String ipAddr { get; protected set; }
        protected bool stPendiente = false;
        protected string statusPendiente;

        public InterfaceHuawei()
        {
        }

        public int inicializarDatosConexion(string mainIPCC, string backIPCC, int timeOut,
            string mainIPCCWS, string backIPCCWS, string accessCode1, string accessCode2,
            string outboundPrefix, string extensionPrefix, int extensionLength,
            string transferAccessCode, MainForm frm)
        {
            try
            {
                errMsg = "";
                logger.Info("Carga de los valores de conexión.");
                settings = new Dictionary<string, string>();
                settings.Add("HuaweiCTIServerIP", mainIPCC);
                settings.Add("HuaweiBackupCTIServerIP", backIPCC);
                settings.Add("HuaweiTimeout", timeOut.ToString());

                settings.Add("HuaweiWebServiceUrl", mainIPCCWS);
                settings.Add("HuaweiBackupWebServiceUrl", backIPCCWS);
                settings.Add("HuaweiAccessCode1", accessCode1);
                settings.Add("HuaweiAccessCode2", accessCode2);
                settings.Add("HuaweiOutboundPrefix", outboundPrefix);
                settings.Add("HuaweiExtensionPrefix", extensionPrefix);
                settings.Add("HuaweiExtensionLength", extensionLength.ToString());
                settings.Add("HuaweiTransferAccessCode", transferAccessCode);
                this.timeOut = timeOut;

                // Inicialización de los valores de status
                statusAsociacion = false;
                statusOperacion = OpStatus.Closed;

                // Se intenta generar la interface de conexión
                bool nuevo = false;
                if (this.device == null)
                {
                    this.device = IDeviceProvider.GetIDevice(EventosHuawei.getMainEvtHuawei(this)) as IDevice;
                    nuevo = true;
                }
                if (nuevo)
                {
                    // Se asocian los eventos con el control
                    EventosHuawei.ReceiveInitializeResult += ReceiveInitializeResult;
                    EventosHuawei.ReceiveUnInitializeResult += ReceiveUnInitializeResult;
                    EventosHuawei.ReceiveSetBusyResult += ReceiveAgentStatusChangeResult;
                    EventosHuawei.ReceiveSetIdleResult += ReceiveAgentStatusChangeResult;
                    EventosHuawei.ReceiveAnswerCallResult += ReceiveAnswerCallResult;
                    EventosHuawei.ReceiveHangUpResult += ReceiveHangUpResult;

                    EventosHuawei.ReceiveAgentStatusChangeResult += ReceiveAgentStatusChange;
                    EventosHuawei.ReceivePhoneAlertingHandle += ReceivePhoneAlerting;
                    EventosHuawei.ReceivePhoneAlertOtherHungupHandler += ReceivePhoneAlertOtherHungup;
                    
                    EventosHuawei.ReceiveInitializeResult += frm.OnInitializeResultCallback;
                    EventosHuawei.ReceiveUnInitializeResult += frm.OnUnInitializeResultCallback;
                    EventosHuawei.ReceiveAgentStatusChangeResult += frm.OnAgentStatusChange;
                    EventosHuawei.ReceivePhoneAlertingHandle += frm.OnPhoneAlerting;
                    EventosHuawei.ReceivePhoneHungupHandler += frm.OnPhoneHungup;
                }

                return 0;
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                errMsg = string.Format("Error en la carga de los valores de conexión. {0}", ex.Message);
                logger.Error("Error en la carga de los valores de conexión. {0}", 
                    ex.Message, ex);
                return -1;
            }
        }

        public int asociarAgente(string idAgente, string extension, string clave, string ipAddr)
        {
            bool bloqueado = false;
            try
            {
                errMsg = "";
                logger.Info("Generación de la interface con el IPCC idAgente:{0} extension:{1} / {2}",
                    idAgente, extension, statusAsociacion);
                this.ipAddr = ipAddr;

                // Se valida que no se cuente con otra operación pendiente
                logger.Trace("Se intenta obtener el control de la interface.");
                if (!controlOperaciones.WaitOne(timeOut))
                {
                    errMsg = "No se logro acceder a la interface de telefonía. BLOQUEADA";
                    logger.Error(errMsg);
                    return -1;
                }
                bloqueado = true;
                logger.Trace("Se bloqueo el control de la interface.");
                if (this.device == null)
                {
                    errMsg = string.Format("No se obtuvo el acceso a la interface. agentID:{0} extension:{1}",
                        idAgente, extension);
                    logger.Error("No se obtuvo el acceso a la interface. agentID:{0} extension:{1}",
                        idAgente, extension);
                    return -1;
                }

                // Se intenta ejecutar la operación solicitada
                logger.Trace("Carga de los datos de telefonista idAgente:{0} extension:{1}",
                    idAgente, extension);
                AgentInfo agentInfo = new AgentInfo();
                agentInfo.AgentId = idAgente;
                agentInfo.PhoneNumber = extension;
                agentInfo.PassWord = clave;
                operaciones.Clear();

                // Se genera la invocación en un hilo distinto
                new Thread(() =>
                {
                    try
                    {
                        logger.Trace("Datos del agente: {0}", agentInfo.AgentId);
                        device.Initialize(agentInfo, settings);
                    }
                    catch (Exception ex)
                    {
                        // Se detecto un error en el procedimiento
                        logger.Error("Error en la asociacion del agente. {0}", ex.Message, ex);
                    }
                }
                ).Start();
                

                // Se intenta esperar por los eventos
                logger.Trace("Inicio de la espera del evento de inicialización.");
                if (!waitInitializeResult.WaitOne(timeOut))
                {
                    errMsg = string.Format("No se logro obtener una respuesta en tiempo del " +
                        "procedimiento de asociacion agente. {0}-{1}", idAgente, extension);
                    logger.Error(errMsg);
                    return -1;
                }
                logger.Trace("Concluye la espera del evento de inicialización.");

                // Se obtiene la respuesta del método
                Dictionary<string, object> respuesta = operaciones.Dequeue();
                controlOperaciones.Release();
                bloqueado = false;
                int errCode = Convert.ToInt32(respuesta["errorCode"]);
                logger.Trace("Respuesta: {0}", errCode);                
                if (errCode == 0)
                {
                    logger.Trace("Se logro asociar al agente  {0}-{1}", idAgente, extension);
                    statusAsociacion = true;
                    return 0;
                }
                    

                // Se detecto un error en el procedimiento
                errMsg = "Error en la asociación del agente.";
                logger.Error(errMsg);
                return -1;
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                errMsg = string.Format("Error en el intento de conexión idAgente:{0} extension:{1} error:{2}",
                    idAgente, extension, ex.Message, ex);
                logger.Error("Error en el intento de conexión idAgente:{0} extension:{1} error:{2}",
                    idAgente, extension, ex.Message, ex);
                return -1;
            }
            finally
            {
                // Se valida que no este bloqueado el recurso
                if (bloqueado)
                    controlOperaciones.Release();
            }
        }

        public int desasociarAgente()
        {
            bool bloqueado = false;
            try
            {
                errMsg = "";
                logger.Info("Se intentara desasociar el agente.");

                // Se valida que no se cuente con otra operación pendiente
                logger.Trace("Se intenta obtener el control de la interface.");
                if (!controlOperaciones.WaitOne(timeOut))
                {
                    errMsg = "No se logro acceder a la interface de telefonía. BLOQUEADA";
                    logger.Error(errMsg);
                    return -1;
                }
                bloqueado = true;
                logger.Trace("Se bloqueo el control de la interface.");
                if (this.device == null)
                {
                    errMsg = "No se obtuvo el acceso a la interface.";
                    logger.Error(errMsg);
                    return -1;
                }

                // Se genera la invocación en un hilo distinto
                new Thread(() =>
                {
                    try
                    {
                        logger.Trace("Solicitud de desasociacion del agente.");
                        this.device.UnInitialize();
                    }
                    catch (Exception ex)
                    {
                        // Se detecto un error en el procedimiento
                        logger.Error("Error en la asociacion del agente. {0}", ex.Message, ex);
                    }
                }
                ).Start();


                // Se intenta esperar por los eventos
                logger.Trace("Inicio de la espera del evento de desinicializacion.");
                if (!waitUninitializeResult.WaitOne(timeOut))
                {
                    errMsg = "No se logro obtener una respuesta en tiempo del procedimiento de " +
                        "desasociacion agente.";
                    logger.Error(errMsg);
                    return -1;
                }
                logger.Trace("Concluye la espera del evento de desasociacion.");

                // Se obtiene la respuesta del método
                Dictionary<string, object> respuesta = operaciones.Dequeue();
                controlOperaciones.Release();
                bloqueado = false;
                int errCode = Convert.ToInt32(respuesta["errorCode"]);
                logger.Trace("Respuesta: {0}", errCode);
                if (errCode == 0)
                {
                    logger.Trace("Se logro desasociar al agente");
                    statusAsociacion = true;
                    return 0;
                }

                // Se detecto un error en el procedimiento
                errMsg = "Error en la desasociacion del agente.";
                logger.Error(errMsg);
                return -1;
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                errMsg = string.Format("Error en el intento de desasociar el agente. {0}", ex.Message);
                logger.Error("Error en el intento de desasociar el agente. {0}", ex.Message, ex);
                return -1;
            }
            finally
            {
                // Se valida que no este bloqueado el recurso
                if (bloqueado)
                    controlOperaciones.Release();
            }
        }

        public int cambiarStatus(string status)
        {
            bool bloqueado = false;
            try
            {
                errMsg = "";
                logger.Info("Se intentara cambiar el status del agente {0}", status);

                // Se valida que el agente no este ocupado
                if (statusOperacion == OpStatus.Talking)
                {
                    logger.Info("Se intentara asignar el status en la siguiente operación. {0}", status);
                    stPendiente = true;
                    statusPendiente = status;
                    return 0;
                }

                // Se valida que no se cuente con otra operación pendiente
                logger.Trace("Se intenta obtener el control de la interface.");
                if (!controlOperaciones.WaitOne(timeOut))
                {
                    errMsg = "No se logro acceder a la interface de telefonía. BLOQUEADA";
                    logger.Error(errMsg);
                    return -1;
                }
                bloqueado = true;
                logger.Trace("Se bloqueo el control de la interface.");
                if (this.device == null)
                {
                    errMsg = "No se obtuvo el acceso a la interface.";
                    logger.Error(errMsg);
                    return -1;
                }

                // Se genera la invocación en un hilo distinto
                new Thread(() =>
                {
                    try
                    {
                        logger.Trace("Solicitud de cambio de status del agente {0}", status);
                        if (status.CompareTo("ACTIVO") == 0 || status.CompareTo("DISPONIBLE") == 0)
                            this.device.SetIdle();
                        else
                            this.device.SetBusy();
                    }
                    catch (Exception ex)
                    {
                        // Se detecto un error en el procedimiento
                        logger.Error("Error en la asociacion del agente. {0}", ex.Message, ex);
                    }
                }
                ).Start();


                // Se intenta esperar por los eventos
                logger.Trace("Inicio de la espera de respuesta del evento de cambio estado agente.");
                if (!waitChangeStatusResult.WaitOne(timeOut))
                {
                    errMsg = "No se logro obtener una respuesta en tiempo del procedimiento de " +
                        "cambio estado agente.";
                    logger.Error(errMsg);
                    return -1;
                }
                logger.Trace("Concluye la espera del evento de cambio estado agente.");

                // Se obtiene la respuesta del método
                Dictionary<string, object> respuesta = operaciones.Dequeue();
                controlOperaciones.Release();
                bloqueado = false;
                int errCode = Convert.ToInt32(respuesta["errorCode"]);
                logger.Trace("Respuesta: {0}", errCode);
                if (errCode == 0)
                {
                    logger.Trace("Se logro cambiar el status al agente");
                    return 0;
                }

                // Se detecto un error en el procedimiento
                errMsg = "Error en el cambio de status del agente.";
                logger.Error(errMsg);
                return -1;
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                errMsg = string.Format("Error en el cambio de status del agente. {0}", ex.Message);
                logger.Error("Error en el cambio de status del agente. {0}", ex.Message, ex);
                return -1;
            }
            finally
            {
                // Se valida que no este bloqueado el recurso
                if (bloqueado)
                    controlOperaciones.Release();
            }
        }

        public int contestarTelefono()
        {
            bool bloqueado = false;
            try
            {
                errMsg = "";
                logger.Info("Se intentara contestar el telefono.");

                // Se valida que no se cuente con otra operación pendiente
                logger.Trace("Se intenta obtener el control de la interface.");
                if (!controlOperaciones.WaitOne(timeOut))
                {
                    errMsg = "No se logro acceder a la interface de telefonía. BLOQUEADA";
                    logger.Error(errMsg);
                    return -1;
                }
                bloqueado = true;
                logger.Trace("Se bloqueo el control de la interface.");
                if (this.device == null)
                {
                    errMsg = "No se obtuvo el acceso a la interface.";
                    logger.Error(errMsg);
                    return -1;
                }

                // Se genera la invocación en un hilo distinto
                new Thread(() =>
                {
                    try
                    {
                        logger.Trace("Solicitud de contestar el teléfono.");
                        this.device.Pickup();
                    }
                    catch (Exception ex)
                    {
                        // Se detecto un error en el procedimiento
                        logger.Error("Error en el intento de contestar el teléfono. {0}", ex.Message, ex);
                    }
                }
                ).Start();


                // Se intenta esperar por los eventos
                logger.Trace("Inicio de la espera de respuesta del evento de contestar teléfono.");
                if (!waitPickupResult.WaitOne(timeOut))
                {
                    errMsg = "No se logro obtener una respuesta en tiempo del procedimiento de " +
                        "contestar telefono.";
                    logger.Error(errMsg);
                    return -1;
                }
                logger.Trace("Concluye la espera del evento de contestar telefono.");

                // Se obtiene la respuesta del método
                Dictionary<string, object> respuesta = operaciones.Dequeue();
                controlOperaciones.Release();
                bloqueado = false;
                int errCode = Convert.ToInt32(respuesta["errorCode"]);
                logger.Trace("Respuesta: {0}", errCode);
                if (errCode == 0)
                {
                    logger.Trace("Se logro contestar el teléfono.");
                    return 0;
                }

                // Se detecto un error en el procedimiento
                errMsg = "Error al intentar contestar el teléfono.";
                logger.Error(errMsg);
                return -1;
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                errMsg = string.Format("Error el intento de contestar el teléfono. {0}", ex.Message);
                logger.Error("Error en el intento de contestar el teléfono. {0}", ex.Message, ex);
                return -1;
            }
            finally
            {
                // Se valida que no este bloqueado el recurso
                if (bloqueado)
                    controlOperaciones.Release();
            }
        }

        public int colgarTelefono()
        {
            bool bloqueado = false;
            try
            {
                errMsg = "";
                logger.Info("Se intentara colgar el teléfono.");

                // Se valida que no se cuente con otra operación pendiente
                logger.Trace("Se intenta obtener el control de la interface.");
                if (!controlOperaciones.WaitOne(timeOut))
                {
                    errMsg = "No se logro acceder a la interface de telefonía. BLOQUEADA";
                    logger.Error(errMsg);
                    return -1;
                }
                bloqueado = true;
                logger.Trace("Se bloqueo el control de la interface.");
                if (this.device == null)
                {
                    errMsg = "No se obtuvo el acceso a la interface.";
                    logger.Error(errMsg);
                    return -1;
                }

                // Se genera la invocación en un hilo distinto
                new Thread(() =>
                {
                    try
                    {
                        logger.Trace("Solicitud de colgar el teléfono.");
                        this.device.Hangup();
                    }
                    catch (Exception ex)
                    {
                        // Se detecto un error en el procedimiento
                        logger.Error("Error en el intento de colgar el teléfono. {0}", ex.Message, ex);
                    }
                }
                ).Start();


                // Se intenta esperar por los eventos
                logger.Trace("Inicio de la espera de respuesta del evento de colgar teléfono.");
                if (!waitHangupResult.WaitOne(timeOut))
                {
                    errMsg = "No se logro obtener una respuesta en tiempo del procedimiento de " +
                        "colgar el teléfono.";
                    logger.Error(errMsg);
                    return -1;
                }
                logger.Trace("Concluye la espera del evento de colgar el teléfono.");

                // Se obtiene la respuesta del método
                Dictionary<string, object> respuesta = operaciones.Dequeue();
                controlOperaciones.Release();
                bloqueado = false;
                int errCode = Convert.ToInt32(respuesta["errorCode"]);
                logger.Trace("Respuesta: {0}", errCode);
                if (errCode == 0)
                {
                    logger.Trace("Se logro colgar el teléfono.");
                    return 0;
                }

                // Se detecto un error en el procedimiento
                errMsg = "Error al intentar colgar el teléfono.";
                logger.Error(errMsg);
                return -1;
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                errMsg = string.Format("Error el intento de colgar el teléfono. {0}", ex.Message);
                logger.Error("Error en el intento de colgar el teléfono. {0}", ex.Message, ex);
                return -1;
            }
            finally
            {
                // Se valida que no este bloqueado el recurso
                if (bloqueado)
                    controlOperaciones.Release();
            }
        }

        public int marcarTelefono(string telefono)
        {
            bool bloqueado = false;
            try
            {
                errMsg = "";
                logger.Info("Se intentara marcar el teléfono: {0}", telefono);

                // Se valida que no se cuente con otra operación pendiente
                logger.Trace("Se intenta obtener el control de la interface.");
                if (!controlOperaciones.WaitOne(timeOut))
                {
                    errMsg = "No se logro acceder a la interface de telefonía. BLOQUEADA";
                    logger.Error(errMsg);
                    return -1;
                }
                bloqueado = true;
                logger.Trace("Se bloqueo el control de la interface.");
                if (this.device == null)
                {
                    errMsg = "No se obtuvo el acceso a la interface.";
                    logger.Error(errMsg);
                    return -1;
                }

                // Se genera la invocación en un hilo distinto
                new Thread(() =>
                {
                    try
                    {
                        logger.Trace("Solicitud de marcar el teléfono: {0}", telefono);
                        DialContent dial = new DialContent();
                        dial.PhoneNumber = telefono;
                        dial.PhoneType = DeviceType.Phone;
                        dial.CallType = DeviceCallType.ConventionCall;
                        this.device.Dial(dial);
                    }
                    catch (Exception ex)
                    {
                        // Se detecto un error en el procedimiento
                        logger.Error("Error en el intento de marcar el teléfono. {0}", ex.Message, ex);
                    }
                }
                ).Start();


                // Se intenta esperar por los eventos
                logger.Trace("Inicio de la espera de respuesta del evento de marcar teléfono.");
                if (!waitDialResult.WaitOne(timeOut))
                {
                    errMsg = "No se logro obtener una respuesta en tiempo del procedimiento de " +
                        "marcar el teléfono.";
                    logger.Error(errMsg);
                    return -1;
                }
                logger.Trace("Concluye la espera del evento de marcar el teléfono.");

                // Se obtiene la respuesta del método
                Dictionary<string, object> respuesta = operaciones.Dequeue();
                controlOperaciones.Release();
                bloqueado = false;
                int errCode = Convert.ToInt32(respuesta["errorCode"]);
                logger.Trace("Respuesta: {0}", errCode);
                if (errCode == 0)
                {
                    logger.Trace("Se logro marcar el teléfono.");
                    return 0;
                }

                // Se detecto un error en el procedimiento
                errMsg = "Error al intentar marcar el teléfono.";
                logger.Error(errMsg);
                return -1;
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                errMsg = string.Format("Error el intento de marcar el teléfono. {0}", ex.Message);
                logger.Error("Error en el intento de marcar el teléfono. {0}", ex.Message, ex);
                return -1;
            }
            finally
            {
                // Se valida que no este bloqueado el recurso
                if (bloqueado)
                    controlOperaciones.Release();
            }
        }


        public void ReceiveInitializeResult(string callId, AgentInfo agentInfo, Dictionary<string, string> settings, 
            bool flag, int errorCode)
        {
            try
            {
                // Se reporta el resultado de la operación
                Dictionary<string, object> salida = new Dictionary<string, object>();
                salida.Add("callId", callId);
                salida.Add("agentInfo", agentInfo);
                salida.Add("settings", settings);
                salida.Add("flag", flag);
                salida.Add("errorCode", errorCode);
                operaciones.Enqueue(salida);
                waitInitializeResult.Set();

                // Se muestra el resultado de la operación
                logger.Trace("Recepcion initialize result [{0}] {1} / {2}.",
                    errorCode, agentInfo.AgentId, agentInfo.PhoneNumber);

                // Se valida el resultado de la operación
                if (errorCode != 0)
                    return;

                // Se procesa el cambio de status
                this.statusAsociacion = true;
                this.datosAgente = agentInfo;
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                logger.Error("Error en el procesamiento de la inicializacion: {0}", ex.Message, ex);
            }
        }

        public void ReceiveUnInitializeResult(string callId, bool flag, int errorCode)
        {
            try
            {
                // Se reporta el resultado de la operación
                Dictionary<string, object> salida = new Dictionary<string, object>();
                salida.Add("callId", callId);
                salida.Add("flag", flag);
                salida.Add("errorCode", errorCode);
                operaciones.Enqueue(salida);
                waitUninitializeResult.Set();

                // Se muestra el resultado de la operación
                logger.Trace("Recepcion uninitialize result [{0}]", errorCode);

                // Se procesa el cambio de status
                this.statusAsociacion = false;
                this.datosAgente = null;

                // Se valida el resultado de la operación
                if (errorCode != 0)
                    return;
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                logger.Error("Error en el procedimiento de des-inicializacion: {0}", ex.Message, ex);
            }
        }

        public void ReceiveAgentStatusChangeResult(string callId, OpStatus status, bool flag, int errorCode)
        {
            try
            {
                // Se reporta el resultado de la operación
                Dictionary<string, object> salida = new Dictionary<string, object>();
                salida.Add("callId", callId);
                salida.Add("opStatus", status);
                salida.Add("flag", flag);
                salida.Add("errorCode", errorCode);
                operaciones.Enqueue(salida);
                waitChangeStatusResult.Set();

                // Se muestra el resultado de la operación
                logger.Trace("Change status result [{0}]", errorCode);

                // Se valida el resultado de la operación
                if (errorCode != 0)
                    return;
                
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                logger.Error("Error en el procedimiento de cambio de status. {0} {1}", callId,
                    ex.Message, ex);
            }
        }

        public void ReceiveAnswerCallResult(string callId, DialContent dialContent, bool flag, int errorCode)
        {
            try
            {
                // Se reporta el resultado de la operación
                Dictionary<string, object> salida = new Dictionary<string, object>();
                salida.Add("callId", callId);
                salida.Add("dialContent", dialContent);
                salida.Add("flag", flag);
                salida.Add("errorCode", errorCode);
                operaciones.Enqueue(salida);
                waitPickupResult.Set();

                // Se muestra el resultado de la operación
                logger.Trace("Aswer call result [{0}]", errorCode);

                // Se valida el resultado de la operación
                if (errorCode != 0)
                    return;

            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                logger.Error("Error en el procedimiento de contestar el teléfono. {0} {1}", callId,
                    ex.Message, ex);
            }
        }

        public void ReceiveHangUpResult(string callId, bool flag, int errorCode)
        {
            try
            {
                // Se reporta el resultado de la operación
                Dictionary<string, object> salida = new Dictionary<string, object>();
                salida.Add("callId", callId);
                salida.Add("flag", flag);
                salida.Add("errorCode", errorCode);
                operaciones.Enqueue(salida);
                waitHangupResult.Set();

                // Se muestra el resultado de la operación
                logger.Trace("Hangup call result [{0}]", errorCode);

                // Se valida el resultado de la operación
                if (errorCode != 0)
                    return;

            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                logger.Error("Error en el procedimiento de colgar el teléfono. {0} {1}", callId,
                    ex.Message, ex);
            }
        }

        public void ReceiveDialResult(string callId, DialContent dialContent, bool flag,
            int errorCode)
        {
            try
            {
                // Se reporta el resultado de la operación
                Dictionary<string, object> salida = new Dictionary<string, object>();
                salida.Add("callId", callId);
                salida.Add("dialContent", dialContent);
                salida.Add("flag", flag);
                salida.Add("errorCode", errorCode);
                operaciones.Enqueue(salida);
                waitDialResult.Set();

                // Se muestra el resultado de la operación
                logger.Trace("Dial result [{0}]", errorCode);

                // Se valida el resultado de la operación
                if (errorCode != 0)
                    return;

            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                logger.Error("Error en el procedimiento de marcar el teléfono. {0} {1}", callId,
                    ex.Message, ex);
            }
        }

        public void ReceiveAgentStatusChange(string callId, AgentInfo agentInfo)
        {
            try
            {
                // Se marca la operacion
                logger.Trace("Se detecto el cambio de status del agente:[{0}]",
                    agentInfo.AgentStatus);

                // Se valida el status previo de la interface
                if (this.statusOperacion == OpStatus.Talking && this.stPendiente)
                {
                    this.statusOperacion = agentInfo.AgentStatus;
                    logger.Info("Se tiene pendiente la asignación de un status a la interface. {0}", this.statusPendiente);
                    this.stPendiente = false;
                    cambiarStatus(this.statusPendiente);
                    if (OnAgentStatusChange != null)
                        OnAgentStatusChange(callId, agentInfo);
                }
                else
                {
                    this.statusOperacion = agentInfo.AgentStatus;
                    if (OnAgentStatusChange != null)
                        OnAgentStatusChange(callId, agentInfo);
                }
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                logger.Error("Error en el método de recepción de llamadas1 {0}", ex.Message, ex);
            }
        }

        public void ReceivePhoneAlerting(string callId, DeviceType callerType, string callerNumber, 
            DeviceType calleeType, string calleeNumber)
        {
            try
            {
                // Se marca la operacion
                logger.Trace("Se detecto la recepción de una llamada. desde:[{0}] hacia:[{1}]",
                    callerNumber, calleeNumber);
                if (OnPhoneAlerting != null)
                    OnPhoneAlerting(callId, callerType, callerNumber, calleeType, calleeNumber);
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                logger.Error("Error en el método de recepción de llamadas {0}", ex.Message, ex);
            }
        }

        public void ReceivePhoneAlertOtherHungup(string callId, DialContent dialContent)
        {
            try
            {
                // Se marca la operación
                logger.Trace("Se detecto el cambio de status en una llamada: {0}/{1}/{2}", dialContent.CallId,
                    dialContent.DeviceId, dialContent.PhoneNumber);
                if (OnPhoneAlertOtherHungup != null)
                    OnPhoneAlertOtherHungup(callId, dialContent);

                // Se intenta regresar el status del agente a Idle
                cambiarStatus("DISPONIBLE");
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                logger.Error("Error en el método de notificación de llamadas  {0}", ex.Message, ex);
            }
        }
    }
}
