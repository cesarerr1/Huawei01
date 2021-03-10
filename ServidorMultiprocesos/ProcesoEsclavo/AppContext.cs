using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.IO.Pipes;
using System.Threading;
using NLog;

namespace ProcesoEsclavo
{
    class AppContext : ApplicationContext
    {
        public const int BUFFER_SIZE = 1024 * 2;

        protected string mID;
        protected Logger logger = LogManager.GetCurrentClassLogger();
        protected NamedPipeClientStream mPipeClientStream;
        System.Timers.Timer mKeepAliveTime = new System.Timers.Timer(2000);

        public AppContext(string paramID)
        {
            try
            {
                logger.Trace("Construccion del contexto de la aplicacion: {0}", paramID);
                Application.ApplicationExit += new EventHandler(ApplicationExit);
                mID = paramID;
                mKeepAliveTime.Elapsed += new System.Timers.ElapsedEventHandler(KeepAliveTimerElapsed);
                mKeepAliveTime.Interval = 2000;
                mKeepAliveTime.Start();
                StartIPC();
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                logger.Error("Error en la construccion del contexto: {0}", ex.Message, ex);
            }
        }

        void KeepAliveTimerElapsed(object sender, System.Timers.ElapsedEventArgs e)
        {
            try
            {
                if (mPipeClientStream.IsConnected)
                {
                    StreamWriter sw = new StreamWriter(mPipeClientStream);
                    sw.WriteLine("KeepAlive" + mID);
                    sw.Flush();
                    //logger.Trace("KeepAlive fue enviado por {0}", mID);
                }
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                logger.Error("Cliente pipe esta desconectado {0} error:{1}", mID, ex.Message, ex);
                Application.Exit();
            }
        }

        void ApplicationExit(object sender, EventArgs e)
        {
            logger.Trace("Salida de la aplicacion {0}", mID);
        }

        void StartIPC()
        {
            logger.Trace("Arrancando cliente IPC {0}", mID);
            mPipeClientStream = new NamedPipeClientStream(".",
                mID,
                PipeDirection.InOut,
                PipeOptions.Asynchronous);
            try
            {
                mPipeClientStream.Connect(3000);
                logger.Trace("Conectado al servidor IPC {0}", mID);
            }
            catch (Exception ex)
            {
                logger.Trace("Error en el arranque del cliente {0}", ex.Message, ex);
            }

            // Se inicia el proceso de recepción
            bool retRead = true;
            logger.Trace(string.Format("Se completo la conexion con el servidor {0}", this.mID));
            while (retRead)
            {
                retRead = StartAsyncReceive();
                Thread.Sleep(100);
            }
        }

        bool StartAsyncReceive()
        {
            try
            {
                StreamReader sr = new StreamReader(mPipeClientStream);
                try
                {
                    // Se intenta leer una linea del proceso
                    char[] buffer = new char[BUFFER_SIZE];
                    int size = sr.Read(buffer, 0, BUFFER_SIZE);
                    if (size <= 0)
                        return false;
                    string msg = new string(buffer, 0, size);
                    OnMessage(msg);
                }
                catch (Exception ex)
                {
                    // Se detecto un error en el procedimiento
                    logger.Error("Error en el proceso de lectura del cliente {0} error:{1}",
                        this.mID, ex.Message, ex);
                }
                return true;
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                logger.Error("Error en el proceso de recepcion del cliente {0} error:{1}",
                    this.mID, ex.Message, ex);
                return false;
            }
        }

        protected virtual void OnMessage(string message)
        {
            try
            {
                logger.Trace(string.Format("{0} Mensaje recibido {1}", mID, message));
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                logger.Error("Error en el procesamiento del mensaje. {0} - {1}",
                    mID, ex.Message, ex);
            }
        }
    }
}
