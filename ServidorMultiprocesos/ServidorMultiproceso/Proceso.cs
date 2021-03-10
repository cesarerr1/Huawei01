using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;
using System.IO;
using System.IO.Pipes;
using System.Threading;
using NLog;

namespace ServidorMultiproceso
{
    class ReceivedEventArg : EventArgs
    {
        public string data;

        public ReceivedEventArg(string paramData)
        {
            this.data = paramData;
        }
    }

    class Proceso : IDisposable
    {
        public const int BUFFER_SIZE = 1024 * 2;

        protected string mPipeID;
        protected Process mChildProcess;
        protected NamedPipeServerStream mPripeServerStream;
        protected bool mIsDisposing;
        protected Thread mPipeMessagingThread;
        protected Logger logger = LogManager.GetCurrentClassLogger();

        public Proceso()
        {

        }

        public bool Start(string paramUID)
        {
            try
            {
                mPipeID = paramUID;

                // Se genera el soporte de la mensajeria
                mPipeMessagingThread = new Thread(new ThreadStart(StartIPCServer));
                mPipeMessagingThread.Name = this.GetType().Name + ".PipeMessagingThread";
                mPipeMessagingThread.IsBackground = true;
                mPipeMessagingThread.Start();

                // Se intenta lanzar el proceso
                logger.Trace(string.Format("Intentando lanzar el proceso {0}", paramUID));
                ProcessStartInfo processInfo = new ProcessStartInfo("ProcesoEsclavo", this.mPipeID);
                mChildProcess = Process.Start(processInfo);

                return true;
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                logger.Error("Error en el lanzamiento del proceso: {0} error:{1}", 
                    paramUID, ex.Message);
                return false;
            }
        }

        public bool Send(string paramData)
        {
            return true;
        }

        void StartIPCServer()
        {
            try
            {
                // Se valida si se debe generar el canal de comunicación
                if (mPripeServerStream == null)
                    mPripeServerStream = new NamedPipeServerStream(mPipeID,
                        PipeDirection.InOut,
                        1,
                        PipeTransmissionMode.Byte,
                        PipeOptions.Asynchronous,
                        BUFFER_SIZE,
                        BUFFER_SIZE);
                logger.Trace(string.Format("{0}:Esperando conexion del proceso esclavo...", mPipeID));
                try
                {
                    // Espera conexión del proceso esclavo
                    mPripeServerStream.WaitForConnection();
                    logger.Trace(string.Format("Proceso esclavo {0} esta conectado.", mPipeID));
                }
                catch (ObjectDisposedException ex)
                {
                    // Se detecto un error en el procedimiento
                    logger.Error("StartIPCServer para proceso {0} error:{1}", this.mPipeID, ex.Message);
                }
                catch (IOException ex)
                {
                    // Se detecto un error en el procedimiento
                    logger.Error("StartIPCServer para proceso {0} error:{1}", this.mPipeID, ex.Message);
                }

                // Se inicia el proceso de recepción
                bool retRead = true;
                logger.Trace(string.Format("Se completo la apertura del canal con el cliente {0}", this.mPipeID));
                InicializaInterface();
                while (retRead && !mIsDisposing)
                {
                    retRead = StartAsyncReceive();
                    Thread.Sleep(100);
                }
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                logger.Error("Error al arrancar el modulo de comunicacion con el cliente {0} error: {1}",
                    this.mPipeID, ex.Message);
            }
        }

        bool StartAsyncReceive()
        {
            try
            {
                StreamReader sr = new StreamReader(mPripeServerStream);
                try
                {
                    // Se intenta leer una linea del proceso
                    string str = sr.ReadLine();
                    if (string.IsNullOrEmpty(str))
                        return false;
                    logger.Trace(string.Format("{0} recibido: [{1}] (Hilo {2})",
                        mPipeID, str, Thread.CurrentThread.ManagedThreadId));
                }
                catch (Exception ex)
                {
                    // Se detecto un error en el procedimiento
                    logger.Error("Error en el proceso de lectura del cliente {0} error:{1}",
                        this.mPipeID, ex.Message);
                }
                return true;
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                logger.Error("Error en el proceso de recepcion del cliente {0} error:{1}",
                    this.mPipeID, ex.Message);
                return false;
            }
        }

        void DisposeClientProcess()
        {
            try
            {
                mIsDisposing = true;
                try
                {
                    mChildProcess.Kill();
                }
                catch { }
                mPripeServerStream.Dispose();
                logger.Trace(string.Format("El proceso {0} esta cerrado.", mPipeID));
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                logger.Error("El proceso {0} esta cerrado error: {1}", this.mPipeID, ex.Message);
            }
        }

        public void Dispose()
        {
            DisposeClientProcess();
        }

        protected virtual void InicializaInterface()
        {
            try
            {
                logger.Trace("Proceso de inicializacion interno de la interfase {0}.", mPipeID);
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                logger.Error("Error en el proceso de inicializacion interno de la interfase {0}.", ex.Message);
            }
        }
    }
}
