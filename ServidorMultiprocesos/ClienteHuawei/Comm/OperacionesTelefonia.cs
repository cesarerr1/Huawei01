using ClienteHuawei.Huawei;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace ClienteHuawei.Comm
{
    class OperacionesTelefonia : SocketCliente
    {
        protected static InterfaceHuawei clienteHuawey;

        public OperacionesTelefonia(Socket socket, InterfaceHuawei cliente)
            : base(socket)
        {
            try
            {
                clienteHuawey = cliente;
            }
            catch (Exception err)
            {
                // Se detecto un error en el procedimiento
                errMsg = "EXCEPCION: " + err.Message;
                logger.Error("Error en la generación del objeto. " + err.Message);
            }
        }

        protected override void ProcesaRespuesta(string operacion)
        {
            try
            {
                logger.Trace("Se procesara un mensaje.");

                // Se intenta procesar la petición recibida
                Dictionary<string, object> oper = JsonConvert.
                    DeserializeObject<Dictionary<string, object>>(operacion);
                logger.Trace("Operación solicitada:  " + oper["operacion"]);
                Dictionary<string, string> param = JsonConvert.
                    DeserializeObject<Dictionary<string, string>>(oper["params"].ToString());

                // Se busca la operación solicitada
                Dictionary<string, string> respuesta;
                switch(oper["operacion"].ToString())
                {
                    case "asociaAgente":
                        respuesta = asociaAgente(
                            param["numeroAgente"], 
                            param["numeroExtension"], 
                            param["direccionIP"]);
                        break;

                    case "desasociaAgente":
                        respuesta = desasociaAgente(
                            param["numeroAgente"],
                            param["numeroExtension"],
                            param["direccionIP"]);
                        break;

                    case "cambioEstadoAgente":
                        respuesta = cambioEstadoAgente(
                            param["numeroAgente"],
                            param["numeroExtension"],
                            param["direccionIP"],
                            param["banderaDisponibilidad"]);
                        break;

                    case "solicitaContestarTel":
                        respuesta = solicitaContestarTel(
                            param["numeroAgente"],
                            param["numeroExtension"],
                            param["direccionIP"]);
                        break;

                    case "solicitaColgarTel":
                        respuesta = solicitaColgarTel(
                            param["numeroAgente"],
                            param["numeroExtension"],
                            param["direccionIP"]);
                        break;

                    case "solicitaLlamadaCallBack":
                        respuesta = solicitaLlamadaCallBack(
                            param["numeroAgente"],
                            param["numeroExtension"],
                            param["direccionIP"],
                            param["numeroTelefonico"]);
                        break;

                    default:
                        errMsg = "No se reconocio la operación solicitada: " + oper["operacion"];
                        logger.Error(errMsg);
                        respuesta = new Dictionary<string, string>();
                        respuesta.Add("errCode", "1002");
                        respuesta.Add("errMsg", errMsg);
                        break;
                }

                // Se envia la respuesta de la invocación
                string resp = JsonConvert.SerializeObject(respuesta);
                if (Enviar(resp) != 0)
                {
                    errMsg = "Error en el envio de la respuesta. " + errMsg;
                    logger.Error(errMsg);
                }
            }
            catch (Exception err)
            {
                // Se detecto un error en el procedimiento
                errMsg = "EXCEPCION: " + err.Message;
                logger.Error("Error en el procesamiento del mensaje." + err.Message);
            }
        }

        protected Dictionary<string, string> asociaAgente(string numeroAgente, string numeroExtension,
            string direccionIP)
        {
            Dictionary<string, string> respuesta = new Dictionary<string, string>();
            try
            {
                errMsg = "";

                // Se marca la operación solicitada
                logger.Trace(string.Format("asociarAgente agente:{0} extension:{1} ip:{2}", numeroAgente,
                    numeroExtension, direccionIP));
                if (clienteHuawey.asociarAgente(numeroAgente, numeroExtension, "", direccionIP) != 0)
                {
                    // Se detecto un error en la operación
                    errMsg = "Error al intentar asociar el agente. " + clienteHuawey.errMsg;
                    logger.Error(errMsg);
                    respuesta.Add("errCode", "0040");
                    respuesta.Add("errMsg", errMsg);
                    return respuesta;
                }

                // Se devuelve la respuesta a la operación
                respuesta.Add("errCode", "0000");
                respuesta.Add("errMsg", "OK");
                return respuesta;
            }
            catch (Exception err)
            {
                // Se detecto un error en el procedimiento
                errMsg = "EXCEPCION: " + err.Message;
                logger.Error("Error en la operacion " + err.Message);
                respuesta.Add("errCode", "1002");
                respuesta.Add("errMsg", errMsg);
                return respuesta;
            }
        }

        protected Dictionary<string, string> desasociaAgente(string numeroAgente, string numeroExtension, 
            string direccionIP)
        {
            Dictionary<string, string> respuesta = new Dictionary<string, string>();
            try
            {
                errMsg = "";

                // Se marca la operación solicitada
                logger.Trace(string.Format("desasociaAgente agente:{0} extension:{1} ip:{2}", numeroAgente,
                    numeroExtension, direccionIP));
                if (clienteHuawey.desasociarAgente() != 0)
                {
                    // Se detecto un error en la operación
                    errMsg = "Error al intentar desasociar el agente. " + clienteHuawey.errMsg;
                    logger.Error(errMsg);
                    respuesta.Add("errCode", "0040");
                    respuesta.Add("errMsg", errMsg);
                    return respuesta;
                }

                // Se devuelve la respuesta a la operación
                respuesta.Add("errCode", "0000");
                respuesta.Add("errMsg", "OK");
                return respuesta;
            }
            catch (Exception err)
            {
                // Se detecto un error en el procedimiento
                errMsg = "EXCEPCION: " + err.Message;
                logger.Error("Error en la operacion " + err.Message);
                respuesta.Add("errCode", "1002");
                respuesta.Add("errMsg", errMsg);
                return respuesta;
            }
        }

        protected Dictionary<string, string> cambioEstadoAgente(string numeroAgente, string numeroExtension,
            string direccionIP, string disponibilidad)
        {
            Dictionary<string, string> respuesta = new Dictionary<string, string>();
            try
            {
                errMsg = "";

                // Se marca la operación solicitada
                logger.Trace(string.Format("cambioEstadoAgente agente:{0} extension:{1} ip:{2} disponibilidad:{3}",
                    numeroAgente, numeroExtension, direccionIP, disponibilidad));
                if (clienteHuawey.cambiarStatus(disponibilidad) != 0)
                {
                    // Se detecto un error en la operación
                    errMsg = "Error al intentar cambiar el status del agente. " + clienteHuawey.errMsg;
                    logger.Error(errMsg);
                    respuesta.Add("errCode", "0040");
                    respuesta.Add("errMsg", errMsg);
                    return respuesta;
                }

                // Se devuelve la respuesta a la operación
                respuesta.Add("errCode", "0000");
                respuesta.Add("errMsg", "OK");
                return respuesta;
            }
            catch (Exception err)
            {
                // Se detecto un error en el procedimiento
                errMsg = "EXCEPCION: " + err.Message;
                logger.Error("Error en la operacion " + err.Message);
                respuesta.Add("errCode", "1002");
                respuesta.Add("errMsg", errMsg);
                return respuesta;
            }
        }

        protected Dictionary<string, string> solicitaContestarTel(string numeroAgente, string numeroExtension,
            string direccionIP)
        {
            Dictionary<string, string> respuesta = new Dictionary<string, string>();
            try
            {
                errMsg = "";

                // Se marca la operación solicitada
                logger.Trace(string.Format("solicitaContestarTel agente:{0} extension:{1} ip:{2}", numeroAgente,
                    numeroExtension, direccionIP));
                if (clienteHuawey.contestarTelefono() != 0)
                {
                    // Se detecto un error en la operación
                    errMsg = "Error al intentar contestar el teléfono del agente. " + clienteHuawey.errMsg;
                    logger.Error(errMsg);
                    respuesta.Add("errCode", "0040");
                    respuesta.Add("errMsg", errMsg);
                    return respuesta;
                }

                // Se devuelve la respuesta a la operación
                respuesta.Add("errCode", "0000");
                respuesta.Add("errMsg", "OK");
                return respuesta;
            }
            catch (Exception err)
            {
                // Se detecto un error en el procedimiento
                errMsg = "EXCEPCION: " + err.Message;
                logger.Error("Error en la operacion " + err.Message);
                respuesta.Add("errCode", "1002");
                respuesta.Add("errMsg", errMsg);
                return respuesta;
            }
        }

        protected Dictionary<string, string> solicitaColgarTel(string numeroAgente, string numeroExtension, 
            string direccionIP)
        {
            Dictionary<string, string> respuesta = new Dictionary<string, string>();
            try
            {
                errMsg = "";

                // Se marca la operación solicitada
                logger.Trace(string.Format("solicitaColgarTel agente:{0} extension:{1} ip:{2}", numeroAgente,
                    numeroExtension, direccionIP));
                if (clienteHuawey.colgarTelefono() != 0)
                {
                    // Se detecto un error en la operación
                    errMsg = "Error al intentar colgar el teléfono del agente. " + clienteHuawey.errMsg;
                    logger.Error(errMsg);
                    respuesta.Add("errCode", "0040");
                    respuesta.Add("errMsg", errMsg);
                    return respuesta;
                }

                // Se devuelve la respuesta a la operación
                respuesta.Add("errCode", "0000");
                respuesta.Add("errMsg", "OK");
                return respuesta;
            }
            catch (Exception err)
            {
                // Se detecto un error en el procedimiento
                errMsg = "EXCEPCION: " + err.Message;
                logger.Error("Error en la operacion " + err.Message);
                respuesta.Add("errCode", "1002");
                respuesta.Add("errMsg", errMsg);
                return respuesta;
            }
        }

        protected Dictionary<string, string> solicitaLlamadaCallBack(string numeroAgente, string numeroExtension, 
            string direccionIP, string numero)
        {
            Dictionary<string, string> respuesta = new Dictionary<string, string>();
            try
            {
                errMsg = "";

                // Se marca la operación solicitada
                logger.Trace(string.Format("asociarAgente agente:{0} extension:{1} ip:{2} numero:{3}", 
                    numeroAgente, numeroExtension, direccionIP, numero));
                if (clienteHuawey.marcarTelefono(numero) != 0)
                {
                    // Se detecto un error en la operación
                    errMsg = "Error al intentar marcar un teléfono. " + clienteHuawey.errMsg;
                    logger.Error(errMsg);
                    respuesta.Add("errCode", "0040");
                    respuesta.Add("errMsg", errMsg);
                    return respuesta;
                }

                // Se devuelve la respuesta a la operación
                respuesta.Add("errCode", "0000");
                respuesta.Add("errMsg", "OK");
                return respuesta;
            }
            catch (Exception err)
            {
                // Se detecto un error en el procedimiento
                errMsg = "EXCEPCION: " + err.Message;
                logger.Error("Error en la operacion " + err.Message);
                respuesta.Add("errCode", "1002");
                respuesta.Add("errMsg", errMsg);
                return respuesta;
            }
        }
    }
}
