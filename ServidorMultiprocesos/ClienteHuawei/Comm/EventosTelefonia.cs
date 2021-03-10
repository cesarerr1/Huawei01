using NLog;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClienteHuawei.Comm
{
    class EventosTelefonia
    {

        public string url { get; protected set; }
        public int timeOut { get; protected set; }
        public string errMsg { get; protected set; }
        protected Logger logger = LogManager.GetCurrentClassLogger();

        public EventosTelefonia(string url, int timeOut)
        {
            try
            {
                // Se carga la información requerida para el funcionamiento del objeto
                errMsg = "";
                this.url = url;
                this.timeOut = timeOut;
            }
            catch (Exception err)
            {
                // Se detecto un error en el procedimiento
                errMsg = "EXCEPCION: " + err.Message;
                logger.Error("Error en la generación del cliente. {0}", err.Message, err);

            }
        }

        public int cambiarStatus(string ip, string numAgente, string numExtension, bool disponible)
        {
            try
            {
                errMsg = "";

                // Se genera la interface con el cliente
                EventosIPCC.EventosTelefoniaService serv = new EventosIPCC.EventosTelefoniaService();
                serv.Url = this.url;
                serv.Timeout = this.timeOut;

                // Se cargan los datos de invocación
                EventosIPCC.cambioEstadoAgenteRequest req = new EventosIPCC.cambioEstadoAgenteRequest();
                req.asociacionAgente = new EventosIPCC.asociacionAgente();
                req.asociacionAgente.ip = ip;
                req.asociacionAgente.numeroAgente = numAgente;
                req.asociacionAgente.numeroExtension = numExtension;
                req.disponibilidad = disponible ? EventosIPCC.EnumDisponibilidad.DISPONIBLE :
                    EventosIPCC.EnumDisponibilidad.NO_DISPONIBLE;
                
                // Se invoca la operación y se espera el resultado
                EventosIPCC.cambioEstadoAgenteResponse resp = serv.cambioEstadoAgente(req);
                if (resp == null)
                {
                    errMsg = "No se obtuvo respuesta del método.";
                    logger.Error("Error en la invocación. {0}", errMsg);
                    return -1;
                }
                int errCode = Int16.Parse(resp.codigoError);
                if (errCode == 0)
                    return 0;

                // Se detecto un error en el procedimiento remoto
                errMsg = resp.descripcion;
                return errCode;
            }
            catch (Exception err)
            {
                // Se detecto un error en el procedimiento
                errMsg = "EXCEPCION: " + err.Message;
                logger.Error("Error en la operación {0}", err.Message, err);
                return -1;
            }
        }

        public long RegistraRecepcionLlamada(string ip, string numAgente, string numExtension, string uniqueId,
            string callerId, string canal)
        {
            try
            {
                errMsg = "";

                // Se genera la interface con el cliente
                EventosIPCC.EventosTelefoniaService serv = new EventosIPCC.EventosTelefoniaService();
                serv.Url = this.url;
                serv.Timeout = this.timeOut;

                // Se cargan los datos de invocación
                EventosIPCC.registraRecepcionLlamadaRequest req = new EventosIPCC.registraRecepcionLlamadaRequest();
                req.asociacionAgente = new EventosIPCC.asociacionAgente();
                req.asociacionAgente.ip = ip;
                req.asociacionAgente.numeroAgente = numAgente;
                req.asociacionAgente.numeroExtension = numExtension;
                req.callerId = callerId;
                req.canal = canal;
                req.uniqueId = uniqueId;
                req.coordX = "";
                req.coordY = "";
                
                // Se invoca la operación y se espera el resultado
                EventosIPCC.registraRecepcionLlamadaResponse resp = serv.registraRecepcionLlamada(req);
                if (resp == null)
                {
                    errMsg = "No se obtuvo respuesta del método.";
                    logger.Error("Error en la invocación. {0}", errMsg);
                    return -1;
                }
                int errCode = Int16.Parse(resp.codigoError);
                if (errCode == 0)
                    return resp.uniqueID;

                // Se detecto un error en el procedimiento remoto
                errMsg = resp.descripcion;
                return -1;
            }
            catch (Exception err)
            {
                // Se detecto un error en el procedimiento
                errMsg = "EXCEPCION: " + err.Message;
                logger.Error("Error en la operación {0}", err.Message, err);
                return -1;
            }
        }

        public int RegistraAtencionLlamada(string ip, string numAgente, string numExtension, string uniqueId,
            string callerId, string canal)
        {
            try
            {
                errMsg = "";

                // Se genera la interface con el cliente
                EventosIPCC.EventosTelefoniaService serv = new EventosIPCC.EventosTelefoniaService();
                serv.Url = this.url;
                serv.Timeout = this.timeOut;

                // Se cargan los datos de invocación
                EventosIPCC.registraAtencionLlamadaRequest req = new EventosIPCC.registraAtencionLlamadaRequest();
                req.asociacionAgente = new EventosIPCC.asociacionAgente();
                req.asociacionAgente.ip = ip;
                req.asociacionAgente.numeroAgente = numAgente;
                req.asociacionAgente.numeroExtension = numExtension;
                req.callerId = callerId;
                req.canal = "1";
                req.uniqueId = "399";
                req.nombreArchivo = "X";
                req.urlArchivo = "Y";
                req.coordX = "";
                req.coordY = "";

                // Se invoca la operación y se espera el resultado
                EventosIPCC.registraAtencionLlamadaResponse resp = serv.registraAtencionLlamada(req);
                if (resp == null)
                {
                    errMsg = "No se obtuvo respuesta del método.";
                    logger.Error("Error en la invocación. {0}", errMsg);
                    return -1;
                }
                int errCode = Int16.Parse(resp.codigoError);
                if (errCode == 0)
                    return 0;

                // Se detecto un error en el procedimiento remoto
                errMsg = resp.descripcion;
                return errCode;
            }
            catch (Exception err)
            {
                // Se detecto un error en el procedimiento
                errMsg = "EXCEPCION: " + err.Message;
                logger.Error("Error en la operación {0}", err.Message, err);
                return -1;
            }
        }
    }
}
