using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Com.Huawei.Device;
using Com.Huawei.Device.ServiceModel;
using NLog;

namespace ProcesoEsclavo.Huawei
{
    class EventosHuawei : IDeviceEventsAdapter
    {
        public delegate void OnInitializeResultHandler(string callId, AgentInfo agentInfo, Dictionary<string, string> settings, bool flag, int errorCode);
        public delegate void OnUnInitializeResultHandler(string callId, bool flag, int errorCode);

        public static event OnInitializeResultHandler ReceiveInitializeResult;
        public static event OnUnInitializeResultHandler ReceiveUnInitializeResult;

        static InterfaceHuawei main = null;
        static EventosHuawei evtHuawei = null;
        static Logger logger = LogManager.GetCurrentClassLogger();

        public static EventosHuawei getMainEvtHuawei(InterfaceHuawei frmmain)
        {
            try
            {
                if (evtHuawei == null)
                {
                    evtHuawei = new EventosHuawei();
                    frmmain = main;
                }
                return evtHuawei;
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                logger.Error("Error en la carga de la interface. {0}", ex.Message);
                return null;
            }
        }

        public override void OnInitializeResult(string callId, AgentInfo agentInfo,
            Dictionary<string, string> settings, bool flag, int errorCode)
        {
            logger.Trace("Resultado inicializacion: callerID:{0} agentInfo:{1} flag:{2} errCode:{3}",
                callId, agentInfo.AgentId, flag, errorCode);
            if (ReceiveInitializeResult != null)
                ReceiveInitializeResult(callId, agentInfo, settings, flag, errorCode);
        }

        public override void OnUnInitializeResult(string callId, bool flag, int errorCode)
        {
            logger.Trace("Resultado des-inicializacion: callerID:{0} flag:{2} errCode:{3}",
                callId, flag, errorCode);
            if (ReceiveUnInitializeResult != null)
                ReceiveUnInitializeResult(callId, flag, errorCode);
        }
    }
}
