using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NLog;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using ClienteHuawei.Huawei;
using Com.Huawei.Device.ServiceModel;

namespace ClienteHuawei.Comm
{
    public delegate void OnAgentStatusChangeHandler(string callId, AgentInfo agentInfo);
    public delegate void OnPhoneAlertingHandler(string callId, DeviceType callerType,
            string callerNumber, DeviceType calleeType, string calleeNumber);

    class SocketServer
    {
        protected Logger logger = LogManager.GetCurrentClassLogger();
        public string errMsg { get; protected  set; }
        public bool activo { get; protected set; }
        protected Socket listener;
        public string callerId { get; protected set; }
        public string uniqueId { get; protected set; }
        protected ManualResetEvent eventoInicializa = new ManualResetEvent(false);
        protected ManualResetEvent eventoCaptura = new ManualResetEvent(false);
        protected InterfaceHuawei clienteHuawei;

        // Datos de conexión con la interface Promad
        public string urlPromad { get; protected set; }
        public int timeOutPromad { get; protected set; }

        // Eventos ajenos a invocaciones de la interfase
        public event OnAgentStatusChangeHandler OnAgentStatusChange;
        public event OnPhoneAlertingHandler OnPhoneAlerting;

        public SocketServer(InterfaceHuawei cliente, string urlPromad, int timeOutPromad)
        {
            try
            {
                errMsg = "";
                activo = false;
                this.clienteHuawei = cliente;
                this.urlPromad = urlPromad;
                this.timeOutPromad = timeOutPromad;
            }
            catch (Exception err)
            {
                // Se detecto un error en el procedimiento
                errMsg = "EXCEPCION: " + err.Message;
                logger.Error("Error en la construcción del objeto. {0}", err.Message, err);
            }
        }

        public int AbrirPuerto(string addr, int puerto)
        {
            try
            {
                errMsg = "";

                // Se valida que el servidor no este activo
                if (activo)
                {
                    errMsg = "Ya se cuenta con un servicio activo.";
                    logger.Error(errMsg);
                    return -1;
                }

                // Se intenta vincular la dirección solicitada con el socket
                logger.Trace("Intentando abrir el la dirección {0}:{1}", addr, puerto);
                IPAddress ipAddress = null;
                if (addr.CompareTo("0.0.0.0") == 0)
                    ipAddress = IPAddress.Any;
                else
                {
                    // Se intenta vincular la interface con una dirección especifica
                    IPHostEntry ipHostInfo = Dns.GetHostEntry(addr);
                    ipAddress =ipHostInfo.AddressList[0];
                }
                IPEndPoint localEndPoint = new IPEndPoint(ipAddress, puerto);
                listener = new Socket(AddressFamily.InterNetwork, 
                    SocketType.Stream, ProtocolType.Tcp);

                // Se lanza el proceso del socket en segundo plano
                eventoInicializa.Reset();
                new Thread(() =>
                {
                    try
                    {
                        errMsg = "";

                        // Se intenta vincular el socket al end point
                        listener.Bind(localEndPoint);
                        listener.Listen(100);
                        eventoInicializa.Set();
                        activo = true;
                        logger.Trace("Se inicia el proceso de espera de conexiones.");
                        while (activo)
                        {
                            // Se resetea el evento de captura
                            eventoCaptura.Reset();

                            // Start an asynchronous socket to listen for connections.
                            listener.BeginAccept(
                                new AsyncCallback(AceptarCliente), this);

                            // Wait until a connection is made before continuing.
                            eventoCaptura.WaitOne(1000);
                        }
                    }
                    catch (Exception err)
                    {
                        // Se detecto un error en el procedimiento
                        errMsg = "EXCEPCION: " + err.Message;
                        logger.Error("Error en el procedimiento del socket. {0}", err.Message,
                            err);
                    }
                    finally
                    {
                        activo = false;
                    }
                }).Start();

                // Se vinculan los eventos a atender en la interfase
                clienteHuawei.OnAgentStatusChange += this.ReceiveAgentStatusChange;
                clienteHuawei.OnPhoneAlerting += this.ReceivePhoneAlerting;

                // Se espera la confirmación del evento de inicialización
                if (!eventoInicializa.WaitOne(1000))
                {
                    logger.Error("Error en la apertura del puerto solicitado.");
                    return -1;
                }

                logger.Trace("Se logro abrir el puerto solicitado.");
                return 0;
            }
            catch (Exception err)
            {
                // Se detecto un error en el procedimiento
                errMsg = "EXCEPCION: " + err.Message;
                logger.Error("Error en la apertura del puerto {0}.", err.Message, err);
                return -1;
            }
        }

        protected void AceptarCliente(IAsyncResult res)
        {
            try
            {
                errMsg = "";

                logger.Trace("Se inicia el proceso de recepción del cliente.");
                eventoCaptura.Set();

                // Se obtiene el socket que atendera al cliente
                SocketServer server = (SocketServer)res.AsyncState;
                Socket handler = server.listener.EndAccept(res);

                // Create the state object.
                OperacionesTelefonia cliente = new OperacionesTelefonia(handler, 
                    server.clienteHuawei);
            }
            catch (Exception err)
            {
                // Se detecto un error en el procedimiento
                errMsg = "EXCEPCION: " + err.Message;
                logger.Error("Error en la recepción del cliente. {0}", err.Message, err);
            }
        }

        public int CerrarPuerto()
        {
            try
            {
                errMsg = "";

                // Se señaliza el cierre del puerto
                if (activo)
                    activo = false;
                listener.Shutdown(SocketShutdown.Both);

                return 0;
            }
            catch (Exception err)
            {
                // Se detecto un error en el procedimiento
                errMsg = "EXCEPCION: " + err.Message;
                logger.Error("Error en el cierre del procedimiento. {0}", err.Message, err);
                return -1;
            }
        }

        public void ReceiveAgentStatusChange(string callId, AgentInfo agentInfo)
        {
            try
            {
                // Se marca la operacion
                logger.Trace("Se detecto el cambio de status del agente:[{0}]",
                    agentInfo.AgentStatus);

                // Se envia la información de la invocación
                EventosTelefonia eventos = new EventosTelefonia(urlPromad, timeOutPromad);
                if (agentInfo.AgentStatus == OpStatus.Talking)
                {
                    logger.Trace("Se marca la atención del número: {0}/{1}", this.uniqueId, this.callerId);
                    if (eventos.RegistraAtencionLlamada(clienteHuawei.ipAddr, agentInfo.AgentId, 
                        agentInfo.PhoneNumber, this.uniqueId, this.callerId, "0") != 0)
                        logger.Error("Error en el envio de la invocación. {0}", eventos.errMsg);
                }
                else
                {
                    if (eventos.cambiarStatus(clienteHuawei.ipAddr, agentInfo.AgentId, agentInfo.PhoneNumber,
                        agentInfo.AgentStatus == OpStatus.Idle ? true : false) != 0)
                            logger.Error("Error en el envio de la invocación. {0}", eventos.errMsg);
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

                // Se envia la información de la invocación
                EventosTelefonia eventos = new EventosTelefonia(urlPromad, timeOutPromad);
                logger.Trace("Se inicia la atención del número: {0}", callerNumber);
                this.callerId = callerNumber;
                long unique = eventos.RegistraRecepcionLlamada(clienteHuawei.ipAddr,
                    clienteHuawei.datosAgente.AgentId, clienteHuawei.datosAgente.PhoneNumber,
                    "0", callerNumber, "0");

                if (unique <= 0)
                    logger.Error("Error en el envio de la invocación. {0}", eventos.errMsg);

                // Se cargan los dato de la llamada
                this.uniqueId = unique.ToString();
                logger.Trace("Se carga el tag para las peticiones de la llamada: {0}", this.uniqueId);
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                logger.Error("Error en el método de recepción de llamadas1 {0}", ex.Message, ex);
            }
        }
    }
}
