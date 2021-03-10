using NLog;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace ClienteHuawei.Comm
{
    class SocketCliente
    {
        protected const int BUFFER_SIZE = 2048;
        protected byte[] buffer = new byte[BUFFER_SIZE];
        protected int timeOut = 3000;
        protected Logger logger = LogManager.GetCurrentClassLogger();
        public string errMsg { get; protected set; }
        public bool activo { get; protected set; }
        public Socket workSocket = null;
        public StringBuilder sb = new StringBuilder();

        public SocketCliente(Socket socket)
        {
            try
            {
                errMsg = "";
                workSocket = socket;
                AtenderPeticion();
            }
            catch (Exception err)
            {
                // Se detecto un error en el procedimiento
                errMsg = "EXCEPCION: " + err.Message;
                logger.Error("Se detecto un error en la generación del cliente. {0}",
                    err.Message, err);
            }
        }

        public void AtenderPeticion()
        {
            try
            {
                errMsg = "";

                // Se inicia con la recepción de la petición del canal
                logger.Trace("Inicio de la recepción de información del canal.");
                workSocket.BeginReceive(buffer, 0, BUFFER_SIZE, SocketFlags.None,
                    new AsyncCallback(RecepcionPeticion), this);
            }
            catch (Exception err)
            {
                // Se detecto un error en el procedimiento
                errMsg = "EXCEPCION: " + err.Message;
                logger.Error("Error la generación del hilo de atención de peticiones. {0}",
                    err.Message, err);
            }
        }

        protected void RecepcionPeticion(IAsyncResult res)
        {
            try
            {
                errMsg = "";

                logger.Trace("Se atiende la petición recibida.");
                SocketCliente state = (SocketCliente)res.AsyncState;
                Socket handler = state.workSocket;

                // Lectura de información desde el socket
                int bytesRead = handler.EndReceive(res);
                if (bytesRead > 0)
                {
                    // Se almacena la información y se procesa
                    string temp = Encoding.UTF8.GetString(state.buffer, 0, bytesRead);
                    logger.Trace("Paquete recibido: [{0}][{1}]", bytesRead, temp);
                    ProcesaRespuesta(temp);
                }
            }
            catch (Exception err)
            {
                // Se detecto un error en el procedimiento
                errMsg = "EXCEPCION: " + err.Message;
                logger.Error("Error en la atención de la petición recibida. {0}",
                    err.Message, err);
            }
        }

        public int Enviar(String data)
        {
            try
            {
                errMsg = "";

                logger.Trace("Se intentara enviar [{0}] al cliente.", data);
                byte[] byteData = Encoding.ASCII.GetBytes(data);

                // Begin sending the data to the remote device.
                workSocket.BeginSend(byteData, 0, byteData.Length, 0,
                    new AsyncCallback(EnviarRespuesta), workSocket);
                return 0;
            }
            catch (Exception err)
            {
                // Se detecto un error en el procedimiento
                logger.Error("Error en el envio de la información. {0}",
                    err.Message, err);
                return -1;
            }
        }

        protected void EnviarRespuesta(IAsyncResult res)
        {
            try
            {
                errMsg = "";

                logger.Trace("Retroalimentación de la operación de envio.");
                Socket handler = (Socket)res.AsyncState;
                int bytesSent = handler.EndSend(res);
                Console.WriteLine("Se enviaron {0} bytes al cliente.", bytesSent);

                handler.Shutdown(SocketShutdown.Both);
                handler.Close();
            }
            catch (Exception err)
            {
                // Se detecto un error en el procedimiento
                errMsg = "EXCEPCION: " + err.Message;
                logger.Error("Error en la operación de envio. {0}",
                    err.Message, err);
            }
        }

        protected virtual void ProcesaRespuesta(string operacion)
        {
            try
            {
                logger.Trace("Se procesara el siguiente mensaje: " + operacion);
            }
            catch (Exception err)
            {
                // Se detecto un error en el procedimiento
                errMsg = "EXCEPCION: " + err.Message;
                logger.Error("Error en el procesamiento del mensaje. " + err.Message);
            }
        }
    }
}
