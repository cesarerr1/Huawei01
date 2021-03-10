using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using ClienteHuawei.Huawei;
using NLog;
using System.Windows.Forms;
using Com.Huawei.Device.ServiceModel;
using ClienteHuawei.Comm;

namespace ClienteHuawei
{

    /**
    *   Eventos relacionados con la interface de IPCC
    */
    delegate void OnInitializeResultHanlder(string callId, AgentInfo agentInfo,
        Dictionary<string, string> settings, bool flag, int errorCode);
    delegate void OnUnInitializeResultHandler(string callId, bool flag, int errorCode);

    delegate void OnAgentStatusChangeHandler(string callId, AgentInfo agentInfo);
    delegate void OnPhoneAlertingHandler(string callId, DeviceType callerType, string callerNumber, 
        DeviceType calleeType, string calleeNumber);
    delegate void OnPhoneHungupHandler(string callId, DialContent dialContent);
    delegate void OnDialResultHandler(string callId, DialContent dialContent, bool flag, int errorCode);
    delegate void OnNewCallResultHandler(string callId, DeviceType callerType, string callerNumber, 
        DeviceType calleeType, string calleeNumber);

    /**
    *   Eventos relacionados con las operaciones en segundo plano del dialogo
    */
    delegate void OnCierreOperacionHanlder(int campos);
        
    public partial class MainForm : Form
    {
        protected Logger logger = LogManager.GetCurrentClassLogger();
        ArchivoConfiguracion conf;
        protected ConfiguracionForm configuracion;
        Dictionary<DatosConexion, String> datosConexion;
        SocketServer servidor;
        InterfaceHuawei cliente;

        /**
        *  Elementos asociados con la interface del IPCC  
        */
        event OnInitializeResultHandler OnInitializeResult;
        event OnUnInitializeResultHandler OnUnInitializeResult;
        event OnAgentStatusChangeHandler OnAgentStatusChangeResult;
        event OnPhoneAlertingHandler OnPhoneAlertingResult;
        event OnPhoneHungupHandler OnPhoneHungupResult;
        event OnDialResultHandler OnDialResult;
        event OnNewCallResultHandler OnNewCallResult;
        
        /**
        *   Banderas para el control de los campos
        */
        protected const int CAMPOS_AGENTE_INACTIVOS = 0x0001;
        protected const int CAMPOS_AGENTE_ACTIVOS = 0x0100;
        protected const int CAMPOS_TELEFONIA_INACTIVOS = 0x0002;
        protected const int CAMPOS_TELEFONIA_ACTIVOS = 0x0200;

        public MainForm()
        {
            InitializeComponent();

            // Se carga la configuración por default de la interface
            datosConexion = new Dictionary<DatosConexion, string>();
            datosConexion.Add(DatosConexion.mainIPCC, "172.17.102.1");
            datosConexion.Add(DatosConexion.backupIPCC, "172.17.102.1");
            datosConexion.Add(DatosConexion.timeOut, "5000");
            datosConexion.Add(DatosConexion.webServiceURL, "https://172.17.102.2:8643/eds/services/ECUWebService");
            datosConexion.Add(DatosConexion.backupServiceURL, "https://172.17.102.2:8643/eds/services/ECUWebService");
            datosConexion.Add(DatosConexion.accessCode1, "90001");
            datosConexion.Add(DatosConexion.accessCode2, "90002");
            datosConexion.Add(DatosConexion.transferCode, "30007");
            datosConexion.Add(DatosConexion.outboundPrefix, "");
            datosConexion.Add(DatosConexion.extensionPrefix, "");
            datosConexion.Add(DatosConexion.extensionLenght, "8");

            // Se cargan los datos de conexión con el WS de Promad
            datosConexion.Add(DatosConexion.urlPromad, "http://192.168.56.1:8080/ModuloIPCC/spring-ws/EventosTelefonia.wsdl");
            datosConexion.Add(DatosConexion.timeOutPromad, "5000");

            // Se intenta cargar los dato de configuración
            conf = new ArchivoConfiguracion(System.IO.Path.GetDirectoryName(Application.ExecutablePath));
            conf.LeerArchivoConfiguracion(datosConexion);

            // Se genera el dialogo de configuración
            configuracion = new ConfiguracionForm(datosConexion, conf);

            // Se genera la interface de conexión
            cliente = new InterfaceHuawei();
            cliente.inicializarDatosConexion(
                datosConexion[DatosConexion.mainIPCC],
                datosConexion[DatosConexion.backupIPCC],
                Int16.Parse(datosConexion[DatosConexion.timeOut]),
                datosConexion[DatosConexion.webServiceURL],
                datosConexion[DatosConexion.backupServiceURL],
                datosConexion[DatosConexion.accessCode1],
                datosConexion[DatosConexion.accessCode2],
                datosConexion[DatosConexion.outboundPrefix],
                datosConexion[DatosConexion.extensionPrefix],
                Int16.Parse(datosConexion[DatosConexion.extensionLenght]),
                datosConexion[DatosConexion.transferCode],
                this);

            textIDAgente.Text = "106";
            textExtension.Text = "10006";
            toolStripStatusConexion.Text = "Sin inicializar";

            // Se inicializa la interface de comunicaciones
            servidor = new SocketServer(cliente, 
                datosConexion[DatosConexion.urlPromad],
                Int16.Parse(datosConexion[DatosConexion.timeOutPromad]));
            servidor.AbrirPuerto("0.0.0.0", 8889);
        }

        public void OnInitializeResultCallback(string callId, AgentInfo agentInfo,
            Dictionary<string, string> settings, bool flag, int errorCode)
        {
            try
            {
                logger.Trace("Procesando la inicialización del agente. {0}-{1}",
                    agentInfo.AgentId, agentInfo.PhoneNumber);

                // Se valida el resultado de la operación
                if (errorCode != 0)
                    return;

                // Se valida si se trata de una operación segura para el dialogo
                if (this.InvokeRequired)
                {
                    OnInitializeResultHandler hand = new OnInitializeResultHandler(OnInitializeResultCallback);
                    this.Invoke(hand, new object[] { callId, agentInfo, settings,flag, errorCode });
                    return;
                }
                
                // Se continua el procesamiento del mensaje
                buttonAsociar.Text = "Desasociar Agente";
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                logger.Error("Error al procesar la inicialización del agente. {0}",
                    ex.Message, ex);
            }
        }

        public void OnUnInitializeResultCallback(string callId, bool flag, int errorCode)
        {
            try
            {
                logger.Trace("Procesando la desinicialización del agente.");

                // Se valida el resultado de la operación
                if (errorCode != 0)
                    return;

                // Se valida si se trata de una operación segura para el dialogo
                if (this.InvokeRequired)
                {
                    OnUnInitializeResultHandler hand = new OnUnInitializeResultHandler(OnUnInitializeResultCallback);
                    this.Invoke(hand, new object[] { callId, flag, errorCode });
                    return;
                }

                // Se continua el procesamiento del mensaje
                buttonAsociar.Text = "Asociar Agente";
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                logger.Error("Error al procesar la inicialización del agente. {0}",
                    ex.Message, ex);
            }
        }

        public void OnAgentStatusChange(string callId, AgentInfo agentInfo)
        {
            try
            {
                logger.Trace("Main cambio de status de agente {0} - {1}", agentInfo.AgentId,
                    agentInfo.AgentStatus);

                // Se valida si se trata de una operación segura para el dialogo
                if (this.InvokeRequired)
                {
                    OnAgentStatusChangeHandler hand = new OnAgentStatusChangeHandler(OnAgentStatusChange);
                    this.Invoke(hand, new object[] { callId, agentInfo });
                    return;
                }

                // Se continua el procesamiento del mensaje
                AgregarMensajeBitacora(string.Format("Cambio de status detectado: {0}/{1}",
                    agentInfo.AgentId, agentInfo.AgentStatus));
                toolStripStatusConexion.Text = string.Format("agentID:{0} status:{1}",
                    agentInfo.AgentId, agentInfo.AgentStatus);
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                logger.Error("Error en el cambio de status del agente. {0}", ex.Message, ex);
            }
        }

        public void OnPhoneAlerting(string callId, DeviceType callerType, string callerNumber,
            DeviceType calleeType, string calleeNumber)
        {
            try
            {
                logger.Trace("Main phone alerting device:{0} callerNumber:{1} device:{2} calleeNumber:{3}",
                    callerType.ToString(), callerNumber, calleeType.ToString(), calleeNumber);

                // Se valida que sea una operación segura para el dialogo
                if (this.InvokeRequired)
                {
                    OnPhoneAlertingHandler hand = new OnPhoneAlertingHandler(OnPhoneAlerting);
                    this.Invoke(hand, new object[] { callId, callerType, callerNumber, calleeType, calleeNumber });
                    return;
                }

                // Se continua con el procesamiento normal de la función
                AgregarMensajeBitacora(string.Format("Llamada entrante: {0} -> {1}",
                    callerNumber, calleeNumber));
                
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                logger.Error("Error en la captura de llamada entrante. {0}", ex.Message, ex);
            }
        }

        public void OnPhoneHungup(string callId, DialContent dialContent)
        {
            try
            {
                logger.Trace("Main phone hungup dial:{0}", dialContent.PhoneNumber);
                // Se valida que sea una operación segura para el dialogo
                if (this.InvokeRequired)
                {
                    OnPhoneHungupHandler hand = new OnPhoneHungupHandler(OnPhoneHungup);
                    this.Invoke(hand, new object[] { callId, dialContent });
                    return;
                }

                // Se continua con el procesamiento normal de la función
                AgregarMensajeBitacora(string.Format("Se colgo la bocina: {0}", dialContent.PhoneNumber));
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                logger.Error("Error en el procesamiento de colgado de la bocina. {0}", ex.Message, ex);
            }
        }
        

        private void OperacionActiva(string operacion)
        {
            try
            {
                // Se marca el control en status de espera
                toolStripProgressBarConexion.Style = ProgressBarStyle.Marquee;                                
                buttonAsociar.Enabled = false;
                buttonColgar.Enabled = false;
                buttonCSActiva.Enabled = false;
                buttonCSInactiva.Enabled = false;
                buttonDescolgar.Enabled = false;
                buttonLlamar.Enabled = false;
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                logger.Error("Error en la deshabilitación de los controles. {0}", ex.Message, ex);
            }
        }

        private void CierreOperacionActiva(int campos)
        {
            try
            {
                // Se valida que sea una operación segura para el dialogo
                if (this.InvokeRequired)
                {
                    OnCierreOperacionHanlder hand = new OnCierreOperacionHanlder(CierreOperacionActiva);
                    this.Invoke(hand, new object[] { campos });
                    return;
                }

                // Se marca el control en status de activo
                toolStripProgressBarConexion.Style = ProgressBarStyle.Blocks;
                buttonAsociar.Enabled = true;
                
                // Se valida si se debe habilitar los campos asociados con el agente
                if ((campos & CAMPOS_AGENTE_ACTIVOS) == CAMPOS_AGENTE_ACTIVOS)
                {
                    textIDAgente.ReadOnly = false;
                    textExtension.ReadOnly = false;
                }
                else if ((campos & CAMPOS_AGENTE_INACTIVOS) == CAMPOS_AGENTE_INACTIVOS)
                {
                    textIDAgente.ReadOnly = true;
                    textExtension.ReadOnly = true;
                }

                if ((campos & CAMPOS_TELEFONIA_ACTIVOS) == CAMPOS_TELEFONIA_ACTIVOS)
                {
                    textBoxLlamada.ReadOnly = false;
                    buttonColgar.Enabled = true;
                    buttonCSActiva.Enabled = true;
                    buttonCSInactiva.Enabled = true;
                    buttonDescolgar.Enabled = true;
                    buttonLlamar.Enabled = true;
                }
                else if ((campos & CAMPOS_TELEFONIA_INACTIVOS) == CAMPOS_TELEFONIA_INACTIVOS)
                {
                    textBoxLlamada.ReadOnly = true;
                    buttonColgar.Enabled = false;
                    buttonCSActiva.Enabled = false;
                    buttonCSInactiva.Enabled = false;
                    buttonDescolgar.Enabled = false;
                    buttonLlamar.Enabled = false;
                }
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                logger.Error("Error en el cierre de la operacion. {0}", ex.Message, ex);
            }
        }

        private void AgregarMensajeBitacora(string mensaje)
        {
            try
            {
                // Se agrega la operación a la bitácora
                DateTime time = DateTime.Now;
                String buffer = textBitacora.Text;
                String msg = string.Format("{0:hh:mm:ss.ffff} {1}", time, mensaje);
                textBitacora.Text = string.Format("{0}\r\n{1}", msg, buffer);
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                logger.Error("Error en el procesamiento del mensaje bitácora. {0}", ex.Message, ex);
            }
        }

        private void OnMenuConfiguracion(object sender, EventArgs e)
        {
            try
            {
                if (configuracion == null)
                    configuracion = new ConfiguracionForm(datosConexion, conf);
                configuracion.ShowDialog();
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                logger.Error("Error en el despliegue del menu de configuración. {0}",
                    ex.Message, ex);
            }
        }

        private void OnButtonAsociar(object sender, EventArgs e)
        {
            try
            {
                // Se valida el status del cliente
                if (!cliente.statusAsociacion)
                {
                    OperacionActiva("Intentando asociar al agente.");
                    textIDAgente.ReadOnly = true;
                    textExtension.ReadOnly = true;
                    AgregarMensajeBitacora(string.Format("Intentando asociar al agente {0} con la extensión {1}",
                        textIDAgente.Text, textExtension.Text));

                    // Se invoca en segundo plano la operación
                    new Thread(() =>
                    {
                        try {
                            logger.Trace("Invocacion en segundo plano de la asociacion agente. {0}-{1}",
                                textIDAgente.Text, textExtension.Text);
                            if (cliente.asociarAgente(textIDAgente.Text, textExtension.Text, "", "") == 0)
                            {
                                logger.Trace("Se logro asociar al agente con la extensión.");
                                CierreOperacionActiva(CAMPOS_AGENTE_INACTIVOS|CAMPOS_TELEFONIA_ACTIVOS);
                            }
                            else
                            {
                                logger.Error("Error en la asociación del agente con la extensión. {0}", 
                                    cliente.errMsg);
                                CierreOperacionActiva(CAMPOS_AGENTE_ACTIVOS|CAMPOS_TELEFONIA_INACTIVOS);
                                MessageBox.Show(string.Format("Error en la asociación del agente con la " +
                                    "extensión. {0}", cliente.errMsg), "Asociar Agente",
                                    MessageBoxButtons.OK, MessageBoxIcon.Error);
                            }
                        }
                        catch (Exception ex)
                        {
                            // Se detecto un error en el procedimiento
                            logger.Error("Se detecto un error en la asociacion del agente segundo plano. {0}",
                                ex.Message, ex);
                        }
                    }).Start();
                }
                else
                {
                    OperacionActiva("Intentando desasociar al agente.");
                    textIDAgente.ReadOnly = true;
                    textExtension.ReadOnly = true;
                    AgregarMensajeBitacora(string.Format("Intentando desasociar al agente {0}", textIDAgente.Text));

                    // Se invoca en segundo plano la operación
                    new Thread(() =>
                    {
                        try
                        {
                            logger.Trace("Invocacion en segundo plano de la desasociacion agente. {0}", textIDAgente.Text);
                            if (cliente.desasociarAgente() == 0)
                            {
                                logger.Trace("Se logro desasociar al agente con la extensión.");
                                CierreOperacionActiva(CAMPOS_AGENTE_ACTIVOS|CAMPOS_TELEFONIA_INACTIVOS);
                            }
                            else
                            {
                                logger.Error("Error en la desasociación del agente con la extensión. {0}",
                                    cliente.errMsg);
                                CierreOperacionActiva(CAMPOS_AGENTE_ACTIVOS|CAMPOS_TELEFONIA_INACTIVOS);
                                MessageBox.Show(string.Format("Error en la desasociación del agente con la " +
                                    "extensión. {0}", cliente.errMsg), "Desasociar Agente",
                                    MessageBoxButtons.OK, MessageBoxIcon.Error);
                            }
                        }
                        catch (Exception ex)
                        {
                            // Se detecto un error en el procedimiento
                            logger.Error("Se detecto un error en la desasociacion del agente segundo plano. {0}",
                                ex.Message, ex);
                        }
                    }).Start();

                }
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                logger.Error("Error en el intento de asociacion/desasociación al IPCC.{0}",
                    ex.Message, ex);
            }
        }

        private void OnButtonSTActiva(object sender, EventArgs e)
        {
            try
            {
                logger.Trace("Se solicita el cambio de stats a activa.");

                // Se invoca en segundo plano la operación
                new Thread(() =>
                {
                    try
                    {
                        logger.Trace("Invocacion en segundo plano del cambio de status Activa.");
                        if (cliente.cambiarStatus("ACTIVO") == 0)
                        {
                            logger.Trace("Se logro cambiar el status del agente.");
                            CierreOperacionActiva(CAMPOS_AGENTE_INACTIVOS|CAMPOS_TELEFONIA_ACTIVOS);
                        }
                        else
                        {
                            logger.Error("Error en el cambio de status del agente. {0}",
                                cliente.errMsg);
                            CierreOperacionActiva(CAMPOS_AGENTE_INACTIVOS|CAMPOS_TELEFONIA_ACTIVOS);
                            MessageBox.Show(string.Format("Error en el cambio del status del agente. {0}", 
                                cliente.errMsg), "Cambio Estado Agente",
                                MessageBoxButtons.OK, MessageBoxIcon.Error);
                        }
                    }
                    catch (Exception ex)
                    {
                        // Se detecto un error en el procedimiento
                        logger.Error("Se detecto un error en el cambio de status del en agente segundo plano. {0}",
                            ex.Message, ex);
                    }
                }).Start();
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                logger.Error("Error en el intento de cambiar el status de operación Activa  {0}",
                    ex.Message, ex);
            }
        }

        private void OnButtonSTInactiva(object sender, EventArgs e)
        {
            try
            {
                logger.Trace("Se solicita el cambio de stats a inactiva.");

                // Se invoca en segundo plano la operación
                new Thread(() =>
                {
                    try
                    {
                        logger.Trace("Invocacion en segundo plano del cambio de status Inactiva.");
                        if (cliente.cambiarStatus("INACTIVO") == 0)
                        {
                            logger.Trace("Se logro cambiar el status del agente.");
                            CierreOperacionActiva(CAMPOS_AGENTE_INACTIVOS | CAMPOS_TELEFONIA_ACTIVOS);
                        }
                        else
                        {
                            logger.Error("Error en en el cambio de status del agente. {0}",
                                cliente.errMsg);
                            CierreOperacionActiva(CAMPOS_AGENTE_INACTIVOS | CAMPOS_TELEFONIA_ACTIVOS);
                            MessageBox.Show(string.Format("Error en el cambio de status del agente. {0}",
                                cliente.errMsg), "Cambio Status Agente",
                                MessageBoxButtons.OK, MessageBoxIcon.Error);
                        }
                    }
                    catch (Exception ex)
                    {
                        // Se detecto un error en el procedimiento
                        logger.Error("Se detecto un error en el cambio de status del agente segundo plano. {0}",
                            ex.Message, ex);
                    }
                }).Start();
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                logger.Error("Error en el intento de cambiar el status de operación Inactiva  {0}",
                    ex.Message, ex);
            }
        }

        private void OnButtonLlamar(object sender, EventArgs e)
        {
            try
            {
                logger.Trace("Se solicita marcar el teléfono.");

                // Se invoca en segundo plano la operación
                new Thread(() =>
                {
                    try
                    {
                        logger.Trace("Invocacion en segundo plano de marcar el teléfono.");
                        if (cliente.marcarTelefono(textBoxLlamada.Text) == 0)
                        {
                            logger.Trace("Se intentara marcar el telefono.");
                            CierreOperacionActiva(CAMPOS_AGENTE_INACTIVOS | CAMPOS_TELEFONIA_ACTIVOS);
                        }
                        else
                        {
                            logger.Error("Error en el intento de marcar el teléfono. {0}",
                                cliente.errMsg);
                            CierreOperacionActiva(CAMPOS_AGENTE_INACTIVOS | CAMPOS_TELEFONIA_ACTIVOS);
                            MessageBox.Show(string.Format("Error en el intento de marcar el teléfono. {0}",
                                cliente.errMsg), "Marcar Teléfono",
                                MessageBoxButtons.OK, MessageBoxIcon.Error);
                        }
                    }
                    catch (Exception ex)
                    {
                        // Se detecto un error en el procedimiento
                        logger.Error("Se detecto un error en el intento de marcar el teléfono en segundo plano. {0}",
                            ex.Message, ex);
                    }
                }).Start();
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                logger.Error("Error en el intento de marcar el teléfono {0}",
                    ex.Message, ex);
            }
        }

        private void OnButtonDescolgar(object sender, EventArgs e)
        {
            try
            {
                logger.Trace("Se solicita contestar el teléfono.");

                // Se invoca en segundo plano la operación
                new Thread(() =>
                {
                    try
                    {
                        logger.Trace("Invocacion en segundo plano de contesta el teléfono.");
                        if (cliente.contestarTelefono() == 0)
                        {
                            logger.Trace("Se intetara contestar el telefono.");
                            CierreOperacionActiva(CAMPOS_AGENTE_INACTIVOS | CAMPOS_TELEFONIA_ACTIVOS);
                        }
                        else
                        {
                            logger.Error("Error en el intento de contestar el teléfono. {0}",
                                cliente.errMsg);
                            CierreOperacionActiva(CAMPOS_AGENTE_INACTIVOS | CAMPOS_TELEFONIA_ACTIVOS);
                            MessageBox.Show(string.Format("Error en el intento de contestar el teléfono. {0}",
                                cliente.errMsg), "Contestar Teléfono",
                                MessageBoxButtons.OK, MessageBoxIcon.Error);
                        }
                    }
                    catch (Exception ex)
                    {
                        // Se detecto un error en el procedimiento
                        logger.Error("Se detecto un error en el intento de contestar el teléfono en segundo plano. {0}",
                            ex.Message, ex);
                    }
                }).Start();
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                logger.Error("Error en el intento de contestar el teléfono {0}",
                    ex.Message, ex);
            }
        }

        private void OnButtonColgar(object sender, EventArgs e)
        {
            try
            {
                logger.Trace("Se solicita colgar el teléfono.");

                // Se invoca en segundo plano la operación
                new Thread(() =>
                {
                    try
                    {
                        logger.Trace("Invocacion en segundo plano de colgar el teléfono.");
                        if (cliente.colgarTelefono() == 0)
                        {
                            logger.Trace("Se intentara colgar el telefono.");
                            CierreOperacionActiva(CAMPOS_AGENTE_INACTIVOS | CAMPOS_TELEFONIA_ACTIVOS);
                        }
                        else
                        {
                            logger.Error("Error en el intento de colgar el teléfono. {0}",
                                cliente.errMsg);
                            CierreOperacionActiva(CAMPOS_AGENTE_INACTIVOS | CAMPOS_TELEFONIA_ACTIVOS);
                            MessageBox.Show(string.Format("Error en el intento de colgar el teléfono. {0}",
                                cliente.errMsg), "Colgar Teléfono",
                                MessageBoxButtons.OK, MessageBoxIcon.Error);
                        }
                    }
                    catch (Exception ex)
                    {
                        // Se detecto un error en el procedimiento
                        logger.Error("Se detecto un error en el intento de colgar el teléfono en segundo plano. {0}",
                            ex.Message, ex);
                    }
                }).Start();
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                logger.Error("Error en el intento de colgar el teléfono {0}",
                    ex.Message, ex);
            }
        }
        
        private void OnDialogoLeave(object sender, FormClosingEventArgs e)
        {
            try
            {
                logger.Trace("Saliendo del dialogo.");
                cliente.desasociarAgente();
                servidor.CerrarPuerto();
            }
            catch (Exception err)
            {
                // Se detecto un error en el procedimiento
                logger.Error("Error en el proceso de cierre del dialogo. {0}", err.Message, err);
            }
        }
    }    
}
