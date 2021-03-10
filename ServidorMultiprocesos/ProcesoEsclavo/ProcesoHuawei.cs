using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NLog;
using ProcesoEsclavo;
using Newtonsoft.Json;

namespace ProcesoEsclavo.Huawei
{
    class ProcesoHuawei : AppContext
    {
        protected InterfaceHuawei cliente;

        protected enum Comandos
        {
            inicializaInterface, asociaAgente
        };

        public ProcesoHuawei(string paramID)
            :base(paramID)
        {
            try
            {
                cliente = null;
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                logger.Error("{0} Error en la inicializacion de la interface. {1}",
                    mID, ex.Message, ex);
            }
        }

        protected override void OnMessage(string message)
        {
            try
            {
                logger.Trace("{0} Procesando el mensaje: {1}", this.mID, message);

                // Se intenta deserializar el contenido del mensaje
                Dictionary<string, object> root = JsonConvert.DeserializeObject<Dictionary<string, object>>(message);
                logger.Trace("{0} Operacion: {1}", this.mID, root["operacion"]);
                Dictionary<string, string> parametros = JsonConvert.DeserializeObject<Dictionary<string, string>>(
                    root["parametros"].ToString());
                
                switch (root["operacion"].ToString())
                {
                    case "inicializaInterface":
                        InicializaInterface(parametros);
                        break;

                    case "asociaAgente":
                        AsociarAgente(parametros);
                        break;

                    default:
                        break;
                }
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                logger.Error("{0} Error en el procesamiento del mensaje. {1}",
                    this.mID, ex.Message, ex);
            }
        }

        protected void InicializaInterface(Dictionary<string, string> parametros)
        {
            try
            {
                logger.Info("{0} Inicializacion de la interface.", mID);

                // Se genera la interface de comunicación con huawei
                cliente = new InterfaceHuawei();
                cliente.inicializarDatosConexion(
                    parametros["mainIPCC"],
                    parametros["backupIPCC"],
                    Int16.Parse(parametros["timeOut"]),
                    parametros["mainIPCCWS"],
                    parametros["backupIPCCWS"],
                    parametros["accessCode1"],
                    parametros["accessCode2"],
                    parametros["outboundPrefix"],
                    parametros["extensionPrefix"],
                    Int16.Parse(parametros["extensionLength"]),
                    parametros["transferAccessCode"]);
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                logger.Error("{0} Error en la inicializacion de la interface. {1}",
                    mID, ex.Message, ex);
            }
        }

        protected void AsociarAgente(Dictionary<string, string> parametros)
        {
            try
            {
                logger.Trace("Se solicita agregar un agente {0}", parametros["idAgente"]);

                // Se valida que la interface este inicializada
                if (cliente == null)
                {
                    logger.Error("{0} La interface con el IPCC no ha sido inicializada.", mID);
                    return;
                }

                // Se intenta completar la acción
                cliente.asociarAgente(parametros["idAgente"], parametros["extension"], 
                    parametros["clave"]);
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                logger.Error("{0} Error en la asociacion del agente. {1}",
                    mID, ex.Message, ex);
            }
        }

    }
}
