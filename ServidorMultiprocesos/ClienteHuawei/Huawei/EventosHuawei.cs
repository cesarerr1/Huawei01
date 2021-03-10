using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Com.Huawei.Device;
using Com.Huawei.Device.ServiceModel;
using NLog;

namespace ClienteHuawei.Huawei
{
    class EventosHuawei : IDeviceEventsAdapter
    {
        // Respuestas a los métodos invocados
        public delegate void OnInitializeResultHandler(string callId, AgentInfo agentInfo, 
            Dictionary<string, string> settings, bool flag, int errorCode);
        public delegate void OnUnInitializeResultHandler(string callId, bool flag, int errorCode);
        public delegate void OnSetBusyResultHandler(string callId, OpStatus status, bool flag, int errorCode);
        public delegate void OnSetIdleResultHandler(string callId, OpStatus status, bool flag, int errorCode);
        public delegate void OnPhoneHungupHandler(string callId, DialContent dialContent);
        public delegate void OnDialResultHandler(string callId, DialContent dialContent, bool flag, int errorCode);
        public delegate void OnAnswerCallResultHandler(string callId, DialContent dialContent, bool flag, int errorCode);
        public delegate void OnHangUpResultHandler(string callId, bool flag, int errorCode);

        // Eventos que se pueden presentar en la interface de telefonía
        public delegate void OnAgentStatusChangeHandler(string callId, AgentInfo agentInfo);
        public delegate void OnPhoneAlertingHandler(string callId, DeviceType callerType, 
            string callerNumber, DeviceType calleeType, string calleeNumber);
        public delegate void OnPhoneAlertOtherHungupHandler(string callId, DialContent dialContent);
        public delegate void OnNewCallResultHandler(string callId, DeviceType callerType, 
            string callerNumber, DeviceType calleeType, string calleeNumber);
        
        // Respuesta a los métodos invocados
        public static event OnInitializeResultHandler ReceiveInitializeResult;
        public static event OnUnInitializeResultHandler ReceiveUnInitializeResult;
        public static event OnSetBusyResultHandler ReceiveSetBusyResult;
        public static event OnSetIdleResultHandler ReceiveSetIdleResult;
        public static event OnPhoneHungupHandler ReceivePhoneHungupHandler;
        public static event OnDialResultHandler ReceiveDialResult;
        public static event OnAnswerCallResultHandler ReceiveAnswerCallResult;
        public static event OnHangUpResultHandler ReceiveHangUpResult;

        // Eventos que se pueden presentar en la interface de telefonía
        public static event OnAgentStatusChangeHandler ReceiveAgentStatusChangeResult;
        public static event OnPhoneAlertingHandler ReceivePhoneAlertingHandle;
        public static event OnPhoneAlertOtherHungupHandler ReceivePhoneAlertOtherHungupHandler;
        public static event OnNewCallResultHandler ReceiveNewCallResult;

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
            if (ReceiveInitializeResult != null)
                ReceiveInitializeResult(callId, agentInfo, settings, flag, errorCode);
        }

        public override void OnUnInitializeResult(string callId, bool flag, int errorCode)
        {
            if (ReceiveUnInitializeResult != null)
                ReceiveUnInitializeResult(callId, flag, errorCode);
        }

        public override void OnSetBusyResult(string callId, OpStatus status, bool flag, int errorCode)
        {
            if (ReceiveSetBusyResult != null)
                ReceiveSetBusyResult(callId, status, flag, errorCode);
        }

        public override void OnSetIdleResult(string callId, OpStatus status, bool flag, int errorCode)
        {
            if (ReceiveSetIdleResult != null)
                ReceiveSetIdleResult(callId, status, flag, errorCode);
        }

        public override void OnAgentStatusChange(string callId, AgentInfo agentInfo)
        {
            if (ReceiveAgentStatusChangeResult != null)
                ReceiveAgentStatusChangeResult(callId, agentInfo);
        }

        public override void OnPhoneAlerting(string callId, DeviceType callerType, string callerNumber, 
            DeviceType calleeType, string calleeNumber)
        {
            if (ReceivePhoneAlertingHandle != null)
                ReceivePhoneAlertingHandle(calleeNumber, callerType, callerNumber, calleeType, calleeNumber);
        }

        public override void OnPhoneAlertOtherHungup(string callId, DialContent dialContent)
        {
            if (ReceivePhoneAlertOtherHungupHandler != null)
                ReceivePhoneAlertOtherHungupHandler(callId, dialContent);
        }

        public override void OnPhoneHungup(string callId, DialContent dialContent)
        {
            if (ReceivePhoneHungupHandler != null)
                ReceivePhoneHungupHandler(callId, dialContent);
        }

        public override void OnDialResult(string callId, DialContent dialContent, bool flag, int errorCode)
        {
            if (ReceiveDialResult != null)
                ReceiveDialResult(callId, dialContent, flag, errorCode);
        }

        public override void OnNewCall(string callId, DeviceType callerType, string callerNumber, 
            DeviceType calleeType, string calleeNumber)
        {
            if (ReceiveNewCallResult != null)
                ReceiveNewCallResult(callId, callerType, callerNumber, calleeType, calleeNumber);
        }
        
        public override void OnAnswerCallResult(string callId, DialContent dialContent, bool flag, int errorCode)
        {
            if (ReceiveAnswerCallResult != null)
                ReceiveAnswerCallResult(callId, dialContent, flag, errorCode);
        }

        public override void OnHangUpResult(string callId, bool flag, int errorCode)
        {
            if (ReceiveHangUpResult != null)
                ReceiveHangUpResult(callId, flag, errorCode);
        }
    }
}
