using Newtonsoft.Json;
using NLog;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClienteHuawei
{
    public enum DatosConexion
    {
        mainIPCC, backupIPCC, timeOut, webServiceURL, backupServiceURL, accessCode1, accessCode2, transferCode,
        outboundPrefix, extensionPrefix, extensionLenght, urlPromad, timeOutPromad
    }
    public class ArchivoConfiguracion
    {
        public string path { get; protected set; }
        protected const string nombreArchivo = "Configuracion.ini";
        protected Logger logger = LogManager.GetCurrentClassLogger();
        public string errMsg { get; protected set; }
        
        public ArchivoConfiguracion(string path)
        {
            try
            {
                this.path = path;
                logger.Trace("Se ubicara el archivo de configuración en: {0}\\{1}", path, nombreArchivo);
            }
            catch (Exception err)
            {
                // Se detecto un error en el procedimiento
                logger.Error("Error en la generación de la interfase. {0}", err.Message, err);
            }
        }

        public int LeerArchivoConfiguracion(Dictionary<DatosConexion, string> configuracion)
        {
            try
            {
                errMsg = "";

                // Se valida si existe el archivo de configuración
                string path = string.Format("{0}\\{1}", this.path, nombreArchivo);
                if (!File.Exists(path))
                {
                    logger.Trace("Se intentara generar un archivo de configuración con los datos default.");
                    return ActualizarArchivoConfiguracion(configuracion);
                }

                // Se trata de leer el contenido del archivo de configuración
                string buffer = File.ReadAllText(path, Encoding.UTF8);
                Dictionary<DatosConexion, string> oper = JsonConvert.
                    DeserializeObject<Dictionary<DatosConexion, string>>(buffer);

                // Se actualiza el diccionario de configuración
                for (int i = 0; i < configuracion.Count; i++)
                {
                    KeyValuePair<DatosConexion, string> item = configuracion.ElementAt(i);
                    if (oper[item.Key] != null)
                        configuracion[item.Key] = oper[item.Key];
                }

                ActualizarArchivoConfiguracion(configuracion);

                return 0;
            }
            catch (Exception err)
            {
                // Se detecto un error en el procedimiento
                errMsg = "EXCEPCION: " + err.Message;
                logger.Error("Error en la lectura del archivo de configuración. {0}", 
                    err.Message, err);
                return -1;
            }
        }

        public int ActualizarArchivoConfiguracion(Dictionary<DatosConexion, string> configuracion)
        {
            try
            {
                errMsg = "";

                // Se genera el contenido JSON del diccionario
                string path = string.Format("{0}\\{1}", this.path, nombreArchivo);
                string buffer = JsonConvert.SerializeObject(configuracion, Formatting.Indented);
                File.WriteAllText(path, buffer);
                  
                return 0;
            }
            catch (Exception err)
            {
                // Se detecto un error en el procedimiento
                errMsg = "EXCEPCION: " + err.Message;
                logger.Error("Error en la generación del archivo de configuración. {0}",
                    err.Message, err);
                return -1;
            }
        }
    }
}
