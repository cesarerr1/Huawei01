using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Com.Huawei.Device;
using Com.Huawei.Device.Contract;
using Com.Huawei.Device.ServiceModel;
using NLog;

namespace ProcesoEsclavo.Huawei
{

    delegate void OnInitializeResultHandler(string id, string phone, int errorCode);
    delegate void OnUnInitializeResultHandler(string callId, bool flag, int errorCode);

    class InterfaceHuawei
    {
        event OnInitializeResultHandler OnInitializeResult;
        event OnUnInitializeResultHandler OnUnInitializeResult;

        protected Dictionary<string, string> settings;
        protected IDevice device;
        protected Logger logger = LogManager.GetCurrentClassLogger();

        public int inicializarDatosConexion(string mainIPCC, string backIPCC, int timeOut,
            string mainIPCCWS, string backIPCCWS, string accessCode1, string accessCode2,
            string outboundPrefix, string extensionPrefix, int extensionLength,
            string transferAccessCode)
        {
            try
            {
                logger.Info("Carga de los valores de conexión.");
                settings = new Dictionary<string, string>();
                settings.Add("HuaweiCTIServerIP", mainIPCC);
                settings.Add("HuaweiBackupCTIServerIP", backIPCC);
                settings.Add("HuaweiTimeout", timeOut.ToString());

                settings.Add("HuaweiWebServiceUrl", mainIPCCWS);
                settings.Add("HuaweiBackupWebServiceUrl", backIPCCWS);
                settings.Add("HuaweiAccessCode1", accessCode1);
                settings.Add("HuaweiAccessCode2", accessCode2);
                settings.Add("HuaweiOutboundPrefix", outboundPrefix);
                settings.Add("HuaweiExtensionPrefix", extensionPrefix);
                settings.Add("HuaweiExtensionLength", extensionLength.ToString());
                settings.Add("HuaweiTransferAccessCode", transferAccessCode);

                return 0;
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                logger.Error("Error en la carga de los valores de conexión. {0}", 
                    ex.Message, ex);
                return -1;
            }
        }

        public int asociarAgente(string idAgente, string extension, string clave)
        {
            try
            {
                logger.Info("Generación de la interface con el IPCC idAgente:{0} extension:{1}",
                    idAgente, extension);
                this.device = IDeviceProvider.GetIDevice(EventosHuawei.getMainEvtHuawei(this)) as IDevice;
                if (this.device == null)
                {
                    logger.Error("No se obtuvo el acceso a la interface. agentID:{0} extension:{1}",
                        idAgente, extension);
                    return -1;
                }

                logger.Trace("Carga de los datos de telefonista idAgente:{0} extension:{1}",
                    idAgente, extension);
                AgentInfo agentInfo = new AgentInfo();
                agentInfo.AgentId = idAgente;
                agentInfo.PhoneNumber = extension;
                agentInfo.PassWord = clave;

                logger.Trace("Intento de conexión idAgente:{0} extension {1}", idAgente, extension);
                this.device.Initialize(agentInfo, settings);
                EventosHuawei.ReceiveInitializeResult += ReceiveInitializeResult;
                EventosHuawei.ReceiveUnInitializeResult += ReceiveUnInitializeResult;

                return 0;
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                logger.Error("Error en el intento de conexión idAgente:{0} extension:{1} error:{2}",
                    idAgente, extension, ex.Message, ex);
                return -1;
            }
        }


        public void ReceiveInitializeResult(string callId, AgentInfo agentInfo, Dictionary<string, string> settings, 
            bool flag, int errorCode)
        {
            try
            {
                logger.Trace("Resultado inicializacion callID:{0} agentInfo:{1} flag:{2} errCode:{3}",
                    callId, agentInfo.AgentId, flag, errorCode);
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                logger.Error("Error en el procesamiento de la inicializacion: {0}", ex.Message, ex);
            }
        }

        public void ReceiveUnInitializeResult(string callId, bool flag, int errorCode)
        {
            try
            {
                logger.Trace("Des-inicializacion callerID:{0} flag:{1} errCode:{2}", callId, flag, errorCode);
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                logger.Error("Error en el procedimiento de des-inicializacion: {0}", ex.Message, ex);
            }
        }
    }
}
