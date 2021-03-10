using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NLog;
using Newtonsoft.Json;

namespace ServidorMultiproceso
{
    class InterfaceHuawei : Proceso
    {
        protected string errMsg;
        protected Dictionary<string, object> conexion;
        protected enum Comandos
        {
            inicializaInterface, asociaAgente
        };

        public InterfaceHuawei()
        {
            try
            {
                errMsg = "";
                conexion = null;
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                logger.Error("Error en la generacion de la interfase {0}", ex.Message, ex);
            }
        }

        public string getErrMsg()
        {
            return errMsg;
        }

        protected override void InicializaInterface()
        {
            try
            {
                logger.Trace("Inicializacion interna de la interfase {0}.", mPipeID);

                if (conexion != null)
                {
                    logger.Trace("Se intentara hacer el envio de los datos de conexion a la interfase {0}", mPipeID);
                    EnviarComando(Comandos.inicializaInterface.ToString(), conexion);
                }
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                logger.Error("Error en la inicializacion interna de la interfase {0} {1}",
                    mPipeID, ex.Message, ex);
            }
        }

        public int InicializarDatosConexion(string mainIPCC, string backIPCC, int timeOut,
            string mainIPCCWS, string backIPCCWS, string accessCode1, string accessCode2,
            string outboundPrefix, string extensionPrefix, int extensionLength,
            string transferAccessCode)
        {
            try
            {
                errMsg = "";

                logger.Trace("Inicializando los datos de conexion.");
                logger.Trace("mainIPCC: {0}", mainIPCC);
                logger.Trace("backupIPCC: {0}", backIPCC);
                logger.Trace("timeOut: {0}", timeOut);
                logger.Trace("mainIPCCWS: {0}", mainIPCCWS);
                logger.Trace("backupIPCCWS: {0}", backIPCCWS);
                logger.Trace("accessCode1: {0}", accessCode1);
                logger.Trace("accessCode2: {0}", accessCode2);
                logger.Trace("outboundPrefix: {0}", outboundPrefix);
                logger.Trace("extensionPrefix: {0}", extensionPrefix);
                logger.Trace("extensionLength: {0}", extensionLength);
                logger.Trace("transferAccessCode: {0}", transferAccessCode);

                Dictionary<string, object> param = new Dictionary<string, object>();
                param.Add("mainIPCC", mainIPCC);
                param.Add("backupIPCC", backIPCC);
                param.Add("timeOut", timeOut);
                param.Add("mainIPCCWS", mainIPCCWS);
                param.Add("backupIPCCWS", backIPCCWS);
                param.Add("accessCode1", accessCode1);
                param.Add("accessCode2", accessCode2);
                param.Add("outboundPrefix", outboundPrefix);
                param.Add("extensionPrefix", extensionPrefix);
                param.Add("extensionLength", extensionLength);
                param.Add("transferAccessCode", transferAccessCode);
                if (mPripeServerStream.IsConnected)
                    EnviarComando(Comandos.inicializaInterface.ToString(), param);
                conexion = param;

                return 0;
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                errMsg = string.Format("Error en la inicializacion de los datos de conexion. {0}", ex.Message);
                logger.Error("Error en la inicializacion de los datos de conexion. {0}", ex.Message, ex);
                return -1;
            }
        }

        public int AsociarAgente(string idAgente, string extension, string clave)
        {
            try
            {
                errMsg = "";

                logger.Trace("Se solicita asociar un agente {0} - {1}", idAgente, extension);
                Dictionary<string, object> param = new Dictionary<string, object>();
                param.Add("idAgente", idAgente);
                param.Add("extension", extension);
                param.Add("clave", clave);
                EnviarComando(Comandos.asociaAgente.ToString(), param);

                return 0;
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                errMsg = string.Format("Error en el procedimiento de asociacion. {0}", ex.Message);
                logger.Error("{0} Error en el procedimiento de asociacion. {1}",
                    mPipeID, ex.Message, ex);
                return -1;
            }
        }

        protected int EnviarComando(string operacion, Dictionary<string, object> parametros)
        {
            try
            {
                errMsg = "";

                // Se genera la estructura de comunicación con el cliente
                StringBuilder stringb = new StringBuilder();
                StringWriter stringw = new StringWriter(stringb);

                using (JsonWriter writer = new JsonTextWriter(stringw))
                {
                    writer.Formatting = Formatting.Indented;
                    writer.WriteStartObject();
                    writer.WritePropertyName("operacion");
                    writer.WriteValue(operacion);

                    writer.WritePropertyName("parametros");
                    writer.WriteStartObject();
                    foreach (KeyValuePair<string, object> item in parametros)
                    {
                        writer.WritePropertyName(item.Key);
                        writer.WriteValue(item.Value);
                    }                    
                    writer.WriteEndObject();

                    writer.WriteEndObject();
                }
                logger.Trace("Comando a ser enviado: {0}", stringb.ToString());

                // Se intenta hacer el envio de la estructura 
                if (mPripeServerStream.IsConnected)
                {
                    StreamWriter streamw = new StreamWriter(mPripeServerStream);
                    streamw.WriteLine(stringb.ToString());
                    streamw.Flush();
                }
                else
                {
                    // Se detecto que el cliente no esta conectado
                    errMsg = string.Format("El cliente {0} no esta conectado.", mPipeID);
                    logger.Error("El cliente {0} no esta conectado.", mPipeID);
                    return -1;
                }

                return 0;
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                errMsg = string.Format("Error en el envio del comando {0}", ex.Message);
                logger.Error("Error en el envio del comando {0}, {1}", operacion, ex.Message, ex);
                return -1;
            }
        }

    }
}
