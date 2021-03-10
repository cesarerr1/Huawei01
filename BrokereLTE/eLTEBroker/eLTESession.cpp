#include "stdafx.h"
#include "eLTESession.h"
#include "plog\Log.h"
#include "tinyxml2.h"

eLTESession::eLTESession(string host, int port, string localip)
{
	LOGD << "Se solicita la inicialización de la sesión eLTE: " << host << ":" << port << " - " << localip;
	m_host = host;
	n_port = port;
	b_Activo = false;
	b_Inicializado = false;
	local_ip = localip;
}


eLTESession::~eLTESession()
{
}

bool eLTESession::isActivo()
{
	LOGD << "Se solicita consultar si a sesión esta activa.";
	return b_Activo;
}

string eLTESession::getErrorMessage()
{
	LOGD << "Se solicita consultar el último mensaje de error.";
	return errMsg;
}

ELTE_INT32 eLTESession::getErrorCode()
{
	LOGD << "Se solicita consultar el último código de error reportado.";
	return errCode;
}

int eLTESession::setStatus(bool status)
{
	LOGD << "Se detecto un cambio de status: " << status;
	b_Activo = status;
	return 0;
}

int eLTESession::beginSession(string user, string pwd)
{
	LOGD << "Se solicita el inicio de sesión: " << m_host << ":" << n_port << "/" << user << "/" << pwd << "/" << b_Inicializado;

	errCode = 0;
	errMsg = "";

	ELTE_INT32 res = ELTE_SDK_Init(0);
	if (res != 0)
	{
		identificarError(res);
		LOGE << "Error en la inicialización de la interfase eLTE para la sesión. " << errMsg;
		return res;
	}

	res = ELTE_SDK_SetEventCallBack(ELTE_EventCallBack, this);
	if (res != 0)
	{
		identificarError(res);
		LOGE << "Error en la asignación de la función callback. " << errMsg;
		return res;
	}

	LOGD << "IP Local configurada: " << local_ip;
	m_user = user;
	m_pwd = pwd;
	res = ELTE_SDK_Login(m_user.c_str(), m_pwd.c_str(), m_host.c_str(), local_ip.c_str(), n_port);
	if (res != 0)
	{
		identificarError(res);
		LOGE << "Se detecto un error en el login. " << errMsg;
		return -1;
	}
	LOGD << "Se logro acceder al servidor eLTE.";

	return 0;
}

int eLTESession::closeSession() 
{
	LOGD << "Se solicita el cierre de la sesión activa: " << m_user;

	ELTE_INT32 res = ELTE_SDK_Logout(m_user.c_str());
	if (res != 0)
	{
		identificarError(res);
		LOGE << "Error en el cierre de la sesión. " << errMsg;
		return -1;
	}

	return 0;
}

int eLTESession::reconnectSession()
{
	LOGD << "Se solicita la reconexión de la sesión activa.";
	return this->beginSession(m_user, m_pwd);
}

int eLTESession::releaseResources()
{
	LOGD << "Se solicta la liberación de los recursos asociados a la sesión eLTE.";
	ELTE_INT32 res = ELTE_SDK_Cleanup();
	if (res != 0)
	{
		identificarError(res);
		LOGE << "Error en la liberación de los recursos. " << errMsg;
		return -1;
	}

	return 0;
}

list<map<string, string>*>* eLTESession::listUsers()
{
	errMsg = "";
	LOGD << "Se solicita listar los usuarios registrados. " << m_user.c_str();

	ELTE_CHAR *pChar = NULL;
	ELTE_INT32 res = ELTE_SDK_GetDcUsers(m_user.c_str(), &pChar);
	if (res == 0)
	{
		LOGD << "Se logro obtener el listado de usuarios: \n" << pChar;
		list<map<string, string>*> *salida = parseoXML(pChar, "UserInfoList");
		ELTE_SDK_ReleaseBuffer(pChar);
		return salida;
	}
	else
	{
		identificarError(res);
		LOGE << "Error en el listado de los usuarios. " << errMsg;
		return NULL;
	}

	return NULL;
}

list<map<string, string>*>* eLTESession::listGroups()
{
	errMsg = "";
	LOGD << "Se solicita listar los grupos registrados." << m_user.c_str();

	ELTE_CHAR *pChar = NULL;
	ELTE_INT32 res = ELTE_SDK_GetDcGroups(m_user.c_str(), &pChar);
	if (res == 0)
	{
		LOGD << "Se logro obtener el listado de grupos: \n" << pChar;
		list<map<string, string>*> *salida = parseoXML(pChar, "GroupInfoList");
		ELTE_SDK_ReleaseBuffer(pChar);
		return salida;
	}
	else
	{
		identificarError(res);
		LOGE << "Error en el listado de grupos. " << errMsg;
		return NULL;
	}

	return NULL;
}

int eLTESession::generarLlamadaP2P(string resourceID)
{
	LOGD << "Se solicita generar una llamada P2P: " << resourceID;

	ELTE_INT32 res = ELTE_SDK_P2PDial(resourceID.c_str());
	if (res != 0)
	{
		identificarError(res);
		LOGE << "Error en la generación de la llamada. " << errMsg;
		return -1;
	}

	return 0;
}

int eLTESession::liberarLlamadaP2P(string resourceID)
{
	LOGD << "Se solicita liberar una llamada P2P: " << resourceID;

	ELTE_INT32 res = ELTE_SDK_P2PHangup(resourceID.c_str());
	if (res != 0)
	{
		identificarError(res);
		LOGE << "Error en la generación de la llamada. " << errMsg;
		return -1;
	}

	return 0;
}

int eLTESession::generarLlamadaGrupo(string groupID)
{
	LOGD << "Se solicita generar una llamada de grupo: " << groupID;

	ELTE_INT32 res = 0;
	if (m_grupos.count(groupID) <= 0)
	{
		LOGI << "Se inicia la vinculación del broker con el grupo: " << groupID;
		res = ELTE_SDK_SubJoinGroup(groupID.c_str());
		if (res != 0)
		{
			identificarError(res);
			LOGE << "Error en el join al sub grupo. " << errMsg;
			return -1;
		}
		m_grupos[groupID] = "llamada";
	}
	else
	{
		LOGD << "Ya se cuenta con un status del grupo " << groupID << m_grupos[groupID];
	}
	
	LOGD << "Se solicita abrir el canal al grupo: " << groupID;
	res = ELTE_SDK_PTTDial(groupID.c_str());
	if (res != 0)
	{
		identificarError(res);
		LOGE << "Error en la generación de la llamada. " << errMsg;
		return -1;
	}

	return 0;
}

int eLTESession::liberarLlamadaGrupo(string groupID)
{
	LOGD << "Se solicita liberar una llamada de grupo: " << groupID;

	ELTE_INT32 res = ELTE_SDK_PTTRelease(groupID.c_str());
	if (res != 0)
	{
		identificarError(res);
		LOGE << "Error en la generación de la llamada. " << errMsg;
		return -1;
	}

	return 0;
}

int eLTESession::cerrarLlamadaGrupo(string groupID)
{
	LOGD << "Se solicita cerrar una llamada de grupo: " << groupID;

	if (m_grupos.count(groupID) <= 0)
	{
		LOGI << "Se inicia la des-vinculación del broker con el grupo: " << groupID;
		m_grupos.erase(groupID);
	}
	else
	{
		LOGD << "NO se cuenta con un status del grupo " << groupID;
	}

	
	ELTE_INT32 res = ELTE_SDK_PTTDial(groupID.c_str());
	if (res != 0)
	{
		identificarError(res);
		LOGE << "Error en la petición de apertura de canal del grupo. " << errMsg;
	}
		
	res = ELTE_SDK_PTTHangup(groupID.c_str());
	if (res != 0)
	{
		identificarError(res);
		LOGE << "Error en la liberación del PTT del sub grupo. " << errMsg;
	}

	res = ELTE_SDK_UnSubscribeGroup(groupID.c_str());
	if (res != 0)
	{
		identificarError(res);
		LOGE << "Error en la desuscripcion del PTT del sub grupo. " << errMsg;
	}

	return 0;
}

int eLTESession::enviarMensaje(int tipoMensaje, string destino, string mensaje, string path)
{
	LOGD << "Se solicita enviar un mensaje: " << tipoMensaje << "/" << mensaje << "/" << path;

	stringstream buffer;
	buffer << "<Content>" << 
		"<SDSType>" << (tipoMensaje == ELTE_MENSAJE_SMS ? "0001" : "0004") << "</SDSType>" << 
		"<MsgBody>" << mensaje << "</MsgBody>" <<
		"<Receiver>" << destino << "</Receiver>" <<
		"<AttachFileList>" << 
			"<AttachFile>" << path << "</AttachFile>" << 
		"</AttachFileList>" <<
		"</Content>";

	LOGD << "Se solicitara el envio de la siguiente estructura: "<< 
		m_user << "\n" << buffer.str();
	ELTE_INT32 res = ELTE_SDK_SDSSendMessage(m_user.c_str(), buffer.str().c_str());
	if (res != 0)
	{
		identificarError(res);
		LOGE << "Error en el envio del mensaje. " << errMsg;
		return -1;
	}

	return 0;
}

int eLTESession::iniciarVideo(string recurso, int videoFrm, int camType, int confReq, int sndType)
{
	string vFrm = "Desconocido";
	switch (videoFrm) {
	case ELTE_VIDEO_CIF:
		vFrm = "CIF";
		break;
	case ELTE_VIDEO_QCIF:
		vFrm = "QCIF";
		break;
	case ELTE_VIDEO_D1:
		vFrm = "D1";
		break;
	case ELTE_VIDEO_720P:
		vFrm = "720P";
		break;
	case ELTE_VIDEO_1080P:
		vFrm = "1080P";
		break;
	default:
		LOGE << "Formato de video no reconocido: " << vFrm;
		videoFrm = ELTE_VIDEO_CIF;
		vFrm = "CIF";
		break;
	}
	LOGD << "Se envia la petición para solicitar el video de un recurso: " << recurso <<
		" videoFrm: " << vFrm <<
		" camType: " << (camType == ELTE_CAMERA_FRONT ? "FRONT" : "REAR" ) <<
		" confReq: " << (confReq == ELTE_CAM_CONF_NREQ ? "NOT_REQUIRED" : "REQUIRED" ) <<
		" sndType: " << (sndType == ELTE_CAM_SND_REQ ? "REQUIRED" : "NOT_REQUIRED" );

	stringstream buffer;

	buffer << "<Content>" << "<VideoParam>" <<
		"<VideoFormat>" << vFrm << "</VideoFormat>" <<
		"<CameraType>" << camType << "</CameraType>" <<
		"<UserConfirmType>" << confReq << "</UserConfirmType>" <<
		"<MuteType>" << sndType << "</MuteType>" <<
		"</VideoParam></Content>";

	LOGD << "Estructura a ser enviada: \n" << buffer.str();

	ELTE_INT32 res = ELTE_SDK_StartRealPlay(recurso.c_str(), buffer.str().c_str());
	if (res != 0)
	{
		identificarError(res);
		LOGE << "Error en la petición del video. " << errMsg;
		return -1;
	}

	return 0;
}

int eLTESession::asignarRecursoVideo(string recurso, ELTE_VOID *hWnd)
{
	LOGD << "Se solicita la asignación del video a una ventana: " << recurso;

	ELTE_INT32 res = ELTE_SDK_SetPlayWindow(recurso.c_str(), hWnd);
	if (res != 0)
	{
		identificarError(res);
		LOGE << "Error en la asignación del video a uno de los recursos: " << errMsg;
		return -1;
	}
	return 0;
}

int eLTESession::detenerVideo(string recurso)
{
	LOGD << "Se solicita detener la reproducción del video: " << recurso;

	ELTE_INT32 res = ELTE_SDK_StopRealPlay(recurso.c_str());
	if (res != 0)
	{
		identificarError(res);
		LOGE << "Error en la solicitud de detener el stream de video de un recurso. " << errMsg;
		return -1;
	}
	return 0;
}

int eLTESession::triggerStatusReport()
{
	errMsg = "";
	LOGD << "Se solicita habilitar el reporte de status.";

	ELTE_INT32 res = ELTE_SDK_TriggerStatusReport(1);
	if (res != 0)
	{
		identificarError(res);
		LOGE << "Se detecto un error al intentar habilitar el reporte de status. " << errMsg;
		return -1;
	}
	return 0;
}

map<string, string>* eLTESession::parseoXML(char *xml)
{
	string local(xml);
	errMsg = "";
	errCode = 0;
	LOGD << "Se solicita parsear la siguiente cadena:\n" << local;

	tinyxml2::XMLDocument doc;
	int res = doc.Parse(local.c_str());

	tinyxml2::XMLNode *root = doc.FirstChild();
	if (root == NULL)
	{
		errCode = 1001;
		errMsg = "No se logro completar la lectura de la estructura XML.";
		LOGE << errMsg << "\n" << local;			
		return NULL;
	}

	tinyxml2::XMLElement *nodo = root->FirstChildElement();
	LOGD << "Se encontro el nodo raiz: " << root->Value();

	map<string, string>* salida = new map<string, string>();
	while (nodo != NULL)
	{
		LOGD << "Nodo: " << nodo->Value() << "/" << nodo->GetText();
		(*salida)[nodo->Value()] = nodo->GetText() == NULL ? "NULL" : nodo->GetText();
		nodo = nodo->NextSiblingElement();
	}
	
	return salida;
}

list<map<string, string> *>* eLTESession::parseoXML(char *xml, string busqueda)
{
	string local(xml);
	LOGD << "Se solicita parsear el nodo " << busqueda << " de la siguiente estructura.\n" << local;

	tinyxml2::XMLDocument doc;
	int res = doc.Parse(local.c_str());

	tinyxml2::XMLNode *root = doc.FirstChild();
	if (root == NULL)
	{
		errCode = 1001;
		errMsg = "No se logro completar la lectura de la estructura XML.";
		LOGE << errMsg << "\n" << local;
		return NULL;
	}

	tinyxml2::XMLElement *lista = root->FirstChildElement(busqueda.c_str());
	if (lista != NULL)
		LOGD << "Se encontro el nodo lista: " << lista->Value();
	else
	{
		stringstream buff;
		buff << "No se encontro el nodo lista: " << busqueda;
		errMsg = buff.str();
		LOGE << errMsg;
		return NULL;
	}

	list<map<string, string> *> *salida = new list<map<string, string> *>();
	tinyxml2::XMLElement *nodo = lista->FirstChildElement();
	string itemV = "";
	if (nodo != NULL)
		itemV = nodo->Value();
	while (nodo != NULL)
	{
		LOGD << "Se encontro el nodo item: " << itemV;
		map<string, string>* local = new map<string, string>();
		tinyxml2::XMLElement *nodoE = nodo->FirstChildElement();
		while (nodoE != NULL)
		{
			LOGD << "Nodo: " << nodoE->Value() << "/" << nodoE->GetText();
			(*local)[nodoE->Value()] = nodoE->GetText() == NULL ? "NULL" : nodoE->GetText();
			nodoE = nodoE->NextSiblingElement();
		}
		salida->push_back(local);
		LOGD << "Buscando el siguiente elemento del tipo: " << itemV;
		nodo = nodo->NextSiblingElement(itemV.c_str());
	}

	return salida;
}

CStringW eLTESession::identificarUltimoError()
{
	wchar_t buf[256];
	FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buf, sizeof(buf), NULL);
	return CStringW(buf);
}

ELTE_VOID __SDK_CALL eLTESession::ELTE_EventCallBack(ELTE_INT32 iEventType, ELTE_VOID* pEventBuf,
	ELTE_UINT32 uiBufSize, ELTE_VOID* pUserData)
{

	LOGD << "Recepción de notificación de la sesión eLTE. " << iEventType;

	void *ptr = malloc(uiBufSize);
	memcpy(ptr, pEventBuf, uiBufSize);

	switch (iEventType)
	{
	case ELTE_Event_NotifyUserStatus:
		LOGD << "Device Status Change Notification.";
		break;
	case ELTE_Event_NotifyP2pvideocallStatus:
		LOGD << "Real - time Video Event Notification.";
		LOGD << (char *)ptr;
		break;
	case ELTE_Event_NotifyResourceStatus:
		LOGD << "Group Relationship Change Notification.";
		break;
	case ELTE_Event_NotifyProvisionChange:
		LOGD << "Device Attribute Configuration Change Notification.";
		break;
	case ELTE_Event_NotifyProvisionAllResync:
		LOGD << "Configuration Data Automatic Download Notification.";
		break;
	case ELTE_Event_NotifyP2pcallStatus:
		LOGD << "P2P Call Status Change Notification.";
		break;
	case ELTE_Event_NotifyGroupStatus:
		LOGD << "Group Call Status Change Notification.";
		break;
	case ELTE_Event_NotifyModuleStatus:
		LOGD << "Module Status Change Notification.";
		LOGD << (char *)pEventBuf;
		break;
	case ELTE_Event_NotifyGISReport:
		LOGD << "GIS Information Notification.";
		LOGD << (char *)ptr;
		break;
	case ELTE_Event_NotifyGISStatus:
		LOGD << "GIS Status Notification.";
		LOGD << (char *)ptr;
		break;
	case ELTE_Event_NotifySDSReport:
		LOGD << "Short / Multimedia Message Reception Notification.";
		LOGD << (char *)ptr;
		break;
	case ELTE_Event_NotifySDSSendStatus:
		LOGD << "Short / Multimedia Message Sending Status Notification.";
		LOGD << (char *)ptr;
		break;

	default:
		break;
	}

	CWinApp *app = AfxGetApp();
	if (app != NULL 
		&& (iEventType == ELTE_Event_NotifyResourceStatus
		|| iEventType == ELTE_Event_NotifyP2pvideocallStatus))
		app->PostThreadMessageW(ELTE_EVT_MSG, iEventType, (LPARAM)ptr);
	else
		free(ptr);
}

string eLTESession::identificarStatus(int value)
{
	LOGD << "Se solicita identificar el status: " << value;

	switch (value)
	{
	case 4000: 
		return "Indicates an unknown state, which is RESOURCE_STATUS_UNKNOWN.";
	case 4001: 
		return "The resource is selected, which is STATUS_SELECTED.";
	case 4002: 
		return "The resource is unselected, which is STATUS_UNSELECTED.";
	case 4003: 
		return "The resource is assigned, which is STATUS_ASSIGNED.";
	case 4004:
		return "The resource is not assigned, which is STATUS_ASSIGNED.";
	case 4005: 
		return "The resource is listening, which is STATUS_LISTENING.";
	case 4006: 
		return "The resource stops listening, which is STATUS_LISTENEND.";
	case 4007:
		return "The resource is being recorded, which is STATUS_LOGGING.";
	case 4008: 
		return "The resource is not recorded, which is STATUS_NOLOGGING.";
	case 4009: 
		return "The resource is in a patch, which is STATUS_INPATCH.";
	case 4010: 
		return "The resource is not in a patch, which is STATUS_OUTPATCH.";
	case 4011: 
		return "The resource registration succeeds, which is STATUS_REGOK.";
	case 4012: 
		return "The resource registration fails, which is STATUS_REGFAIL.";
	case 4013: 
		return "The resource is unauthorized, which is STATUS_FORBIDEN.";
	case 4014: 
		return "The resource does not exist, which is STATUS_NOT_FOUND.";
	case 4015:
		return "The resource is unavailable, which is STATUS_TEMP_UNAVAILABLE.";
	case 4016:
		return "Indicates a resource conflict, which is STATUS_RES_CONFILCT.";
	case 4017: 
		return "The resource is unauthenticated, which is STATUS_UNAUTHORIZED.";
	case 4018:
		return "The license is insufficient, which is STATUS_LICENSE_LIMIT.";
	case 4019: 
		return "The password is incorrect, which is STATUS_PASSWORD_WRONG.";
	case 4020: 
		return "The resource is in a call, which is STATUS_INVITING.";
	case 4021: 
		return "The resource is ringing, which is STATUS_RINGING.";
	case 4022: 
		return "The resource is in a call or a call forwarding, which is STATUS_TXMTING.";
	case 4023:
		return "The resource is in the idle state, which is STATUS_TXMTIDLE.";
	case 4024: 
		return "Dynamic regrouping for the resource succeeds, which is STATUS_DGNAOK.";
	case 4025: 
		return "Dynamic regrouping for the resource fails, which is STATUS_DGNAFAIL.";
	case 4026:
		return "Dynamic regrouping for one UE fail, which is STATUS_DGNA_UEFAIL.";
	case 4027:
		return "The resource group is activated, which is STATUS_GROUP_ACTIVATED.";
	case 4028: 
		return "The resource group is deactivated, which is STATUS_GROUP_DEACTIVATED.";
	case 4031:
		return "Creating a patch group succeeds, which is STATUS_GRPPATCH_CREATEOK.";
	case 4032:
		return "Creating a patch group fails, which is STATUS_GRPPATCH_CREATEFAIL.";
	case 4033:
		return "Canceling the patch group creation succeeds, which is STATUS_GRPPATCH_CANCELOK.";
	case 4034:
		return "Canceling the patch group creation fails, which is STATUS_GRPPATCH_CANCELFAIL.";
	case 4035:
		return "Adding members to a patch group succeeds, which is STATUS_GRPPATCH_ADDOK.";
	case 4036: 
		return "Adding members to a patch group fails, which is STATUS_GRPPATCH_ADDFAIL.";
	case 4037:
		return "Deleting members from a patch group succeeds, which is STATUS_GRPPATCH_DELOK.";
	case 4038:
		return "Deleting members from a patch group fails, which is STATUS_GRPPATCH_DELFAIL.";
	default:
		return "Unknown.";
	}
}

string eLTESession::identificarCategoriaUsuario(int value)
{
	LOGD << "Se solicita identificar la catégoria del usuario: " << value;

	switch (value)
	{
	case 0:	// DISPATCHER indicates a DC user.
		return "DISPATCHER";
	case 1: // FIXEDCAMERA indicates a fixed camera.
		return "FIXEDCAMERA";
	case 2: // PSTNUSER indicates a PSTN user.
		return "PSTNUSER";
	case 3: // TETRAUSER indicates a TETRA user.
		return "TETRAUSER";
	case 4: // PLMNUSER indicates a PLMN user.
		return "PLMNUSER";
	case 5: // EXTERNALPTT indicates an external PTT user.
		return "EXTERNALPTT";
	case 6: // SDKUSER indicates an SDK gateway internal user.
		return "SDKUSER";
	case 7: // APPUSER indicates an tAPP user.
		return "APPUSER";
	case 8: // UELOGINUSER indicates a logged - in terminal user.
		return "UELOGINUSER";
	case 9: // PTTUSER indicates a PTT user.
		return "PTTUSER";
	case 50: // ALLTYPEUSER indicates a user of any user type.
		return "ALLTYPEUSER";
	case 255: // OTHERUSER indicates a user whose type is not defined.
		return "OTHERUSER";
	default:
		return "UNKNOWN";
	}
}

string eLTESession::identificarStatusVideo(int value)
{
	LOGD << "Se solicita identificar el status de video para: " << value;

	switch (value)
	{
	case P2Pvideocall_IND_STATUS_INITIATED:
		return "P2Pvideocall_IND_STATUS_INITIATED";
	case P2Pvideocall_IND_STATUS_RECEIVED:
		return "The upper-layer application receives a P2P call as a callee.";
	case P2Pvideocall_IND_STATUS_ANSWERED:
		return "The upper-layer application initiates a P2P call as a caller and the callee has answered the call. In this case, the media is played based on the returned parameter.";
	case P2Pvideocall_IND_STATUS_PROCEEDING:
		return "The upper-layer application attempts to initiate a P2P call as a caller.";
	case P2Pvideocall_IND_STATUS_RINGING:
		return "The upper-layer application successfully initiates a P2P call as a caller and the callee is ringing.";
	case P2Pvideocall_IND_STATUS_ACKED:
		return "The upper-layer application is a callee.";
	case P2Pvideocall_IND_STATUS_RELEASED:
		return "P2Pvideocall_IND_STATUS_RELEASED";
	case P2Pvideocall_IND_STATUS_HANGUPED:
		return "P2Pvideocall_IND_STATUS_HANGUPED";
	case P2Pvideocall_IND_STATUS_HANGUPED_ACTIVE:
		return "P2Pvideocall_IND_STATUS_HANGUPED_ACTIVE";
	case P2Pvideocall_IND_STATUS_CANCELLED:
		return "P2Pvideocall_IND_STATUS_CANCELLED";
	case P2Pvideocall_IND_STATUS_MONITOR:
		return "The upper-layer application receives a video upload request.";
	case P2Pvideocall_IND_STATUS_PREMPTED:
		return "P2Pvideocall_IND_STATUS_PREMPTED";
	case P2Pvideocall_IND_STATUS_RELEASED_BUSY:
		return "P2Pvideocall_IND_STATUS_RELEASED_BUSY";
	case P2Pvideocall_IND_STATUS_PROHIBITED:
		return "P2Pvideocall_IND_STATUS_PROHIBITED";
	case P2Pvideocall_IND_STATUS_REMOTE_NOANSWER:
		return "P2Pvideocall_IND_STATUS_REMOTE_NOANSWER";
	case P2Pvideocall_IND_STATUS_REMOTE_NOTFOUND:
		return "P2Pvideocall_IND_STATUS_REMOTE_NOTFOUND";
	case P2Pvideocall_IND_STATUS_LICENSE_LIMIT:
		return "P2Pvideocall_IND_STATUS_LICENSE_LIMIT";
	case P2Pvideocall_IND_STATUS_EMERGENCY:
		return "P2Pvideocall_IND_STATUS_EMERGENCY";
	case P2Pvideocall_IND_STATUS_ACKED_MEDIAPLANE_ERROR:
		return "Creating the video RTP flow failed.";
	case P2Pvideocall_IND_STATUS_ACKED_MEDIAPLANE_NOAUDIO:
		return "Creating the audio flow for the video failed.";
	case P2Pvideocall_IND_STATUS_REMOTE_NOTCONNECTED:
		return "P2Pvideocall_IND_STATUS_REMOTE_NOTCONNECTED";
	case P2Pvideocall_IND_STATUS_REMOTE_NOTSUPPORTED:
		return "P2Pvideocall_IND_STATUS_REMOTE_NOTSUPPORTED";
	case P2Pvideocall_IND_STATUS_SIGNAL_ERROR:
		return "The SIP in gateway mode is incorrect.";
	case P2Pvideocall_IND_STATUS_VIDEO_CONTROL:
		return "PTZ control in gateway mode.";
	case P2Pvideocall_IND_STATUS_PICKEDUP:
		return "The local end accepts the video from the terminal.";
	default:
		return "UNKNOWN";
	}
}

string eLTESession::identificarCategoriaGrupo(int value)
{
	LOGD << "Se solicita identificar la catégoria del grupo: " << value;

	switch (value)
	{
	case 0: // GRP_ALLBROADCAST indicates a network - wide broadcast group.
		return "GRP_ALLBROADCAST";
	case 1: // GRP_GENERAL indicates a common group.
		return "GRP_GENERAL";
	case 2: // GRP_AREABROADCAST indicates a regional broadcast group.
		return "GRP_AREABROADCAST";
	case 8: // GRP_EXTERNAL indicates an external group.
		return "GRP_EXTERNAL";
	case 9: // GRP_DYNAMICGRP indicates a dynamic group.
		return "GRP_DYNAMICGRP";
	case 10: // GRP_ALLTYPE indicates a group of any type.
		return "GRP_ALLTYPE";
	default:
		return "UNKNOWN";
	}
}

void eLTESession::identificarError(ELTE_INT32 code)
{
	LOGD << "Se solicita identificar el error: " << code;
	errCode = code;

	switch (code)
	{
	case 2135102001:
		errMsg = "Failed";
		break;
	case 2135102002:
		errMsg = "Invalid parameter";
		break;
	case 2135102003:
		errMsg = "Null pointer error";
		break;
	case 2135102004:
		errMsg = "Creating object failed.";
		break;
	case 2135102005:
		errMsg = "Creating the directory failed.";
		break;
	case 2135102006:
		errMsg = "Log module initialization failed.";
		break;
	case 2135102101:
		errMsg = "Initializing the socket dynamic library failed.";
		break;
	case 2135102102:
		errMsg = "Connecting to the server failed.";
		break;
	case 2135102103:
		errMsg = "SSL connection failed.";
		break;
	case 2135102104:
		errMsg = "Sending data failed.";
		break;
	case 2135102105:
		errMsg = "Waiting timeout.";
		break;
	case 2135102106:
		errMsg = "The service is not running.";
		break;
	case 2135102201:
		errMsg = "Loading the .ini configuration file failed.";
		break;
	case 2135102202:
		errMsg = "Reading the .ini configuration file failed.";
		break;
	case 2135102203:
		errMsg = "Writing the .ini configuration file failed.";
		break;
	case 2135102301:
		errMsg = "Constructing the XML character string failed.";
		break;
	case 2135102302:
		errMsg = "Parsing the XML character string failed.";
		break;
	case 2135102303:
		errMsg = "Finding the XML node failed.";
		break;
	case 2135102304:
		errMsg = "Obtaining the XML node failed.";
		break;

	case 2135103001:
		errMsg = "Failed";
		break;
	case 2135103002:
		errMsg = "Invalid parameter.";
		break;
	case 2135103003:
		errMsg = "Null pointer error";
		break;
	case 2135103004:
		errMsg = "Not logged in";
		break;
	case 2135103005:
		errMsg = "Waiting for the login result.An exit indicates a login failure.";
		break;
	case 2135103006:
		errMsg = "Memory request error";
		break;
	case 2135103007:
		errMsg = "Obtaining the session ID failed.";
		break;
	case 2135103008:
		errMsg = "Invalid session ID";
		break;
	case 2135103009:
		errMsg = "The service expires.The client must restart the service.";
		break;
	case 2135103010:
		errMsg = "Incorrect password";
		break;
	case 2135103101:
		errMsg = "Initializing the network socket failed.";
		break;
	case 2135103102:
		errMsg = "Receiving the network socket failed.";
		break;
	case 2135103103:
		errMsg = "Sending the network socket failed.";
		break;
	case 2135103201:
		errMsg = "Loading the.ini configuration file failed.";
		break;
	case 2135103202:
		errMsg = "Reading the.ini configuration file failed.";
		break;
	case 2135103203:
		errMsg = "Writing the.ini configuration file failed.";
		break;
	case 2135103301:
		errMsg = "Constructing the XML character string failed.";
		break;
	case 2135103302:
		errMsg = "Parsing the XML character string failed.";
		break;
	case 2135103303:
		errMsg = "Finding the XML node failed.";
		break;
	case 2135103304:
		errMsg = "Obtaining the XML node failed.";
		break;

	case 999115400:
		errMsg = "Obtaining the channel failed.";
		break;
	case 999115401:
		errMsg = "All ports are occupied.";
		break;
	case 999115402:
		errMsg = "Starting the socket DLL library failed.";
		break;
	case 999115403:
		errMsg = "Creating the socket connection failed.";
		break;
	case 999115404:
		errMsg = "Memory allocation failed.";
		break;
	case 999115405:
		errMsg = "Data flow error";
		break;
	case 999115406:
		errMsg = "Connection timeout";
		break;
	case 999115407:
		errMsg = "Creating the thread failed.";
		break;
	case 999115408:
		errMsg = "Creating the decoder failed.";
		break;
	case 999115409:
		errMsg = "Incorrect invoking sequence";
		break;
	case 999115410:
		errMsg = "Decoding failed.";
		break;
	case 999115411:
		errMsg = "Normal watermark data";
		break;
	case 999115412:
		errMsg = "Watermark data tampering";
		break;
	case 999115413:
		errMsg = "The current version does not support this operation.";
		break;
	case 999115414:
		errMsg = "The buffer area is full.";
		break;
	case 999115415:
		errMsg = "Obtaining the handle of the RTSP failed.";
		break;
	case 999115416:
		errMsg = "Sending the setup request of the RTSP failed.";
		break;
	case 999115417:
		errMsg = "Sending the play request of the RTSP failed.";
		break;
	case 999115418:
		errMsg = "Sending the pause request of the RTSP failed.";
		break;
	case 999115419:
		errMsg = "Sending the teardown request of the RTSP failed.";
		break;
	case 999115420:
		errMsg = "The RTSP connection ends normally.";
		break;
	case 999115421:
		errMsg = "The RTSP connection ends abnormally.";
		break;
	case 999115422:
		errMsg = "The RTSP stream does not meet the requirements.";
		break;
	case 999115423:
		errMsg = "The RTSP stream is disconnected.";
		break;
	case 999115424:
		errMsg = "The NetSource failed to open the network stream.";
		break;
	case 999115425:
		errMsg = "The MP failed to open the network stream.";
		break;
	case 999115426:
		errMsg = "The MP failed to start playback.";
		break;
	case 999115427:
		errMsg = "The NetSource failed to start stream collection.";
		break;
	case 999115428:
		errMsg = "Failed to initialize the NetSource.";
		break;
	case 999115429:
		errMsg = "Failed to initialize the MP.";
		break;
	case 999115430:
		errMsg = "Error in accessing the file or directory.";
		break;
	case 999115431:
		errMsg = "Full disk space.";
		break;
	case 999115432:
		errMsg = "Audio mixer state error.";
		break;
	case 999115433:
		errMsg = "Audio mixer operation error.";
		break;
	case 999115434:
		errMsg = "Incorrect voice intercom state.";
		break;
	case 999115435:
		errMsg = "Playing the voice broadcast file ends.";
		break;
	case 999115436:
		errMsg = "Incorrect voice broadcast file format.";
		break;
	case 999115437:
		errMsg = "Failed to read the voice broadcast file.";
		break;
	case 999115438:
		errMsg = "Failed to obtain the mode of opening data streams.";
		break;
	case 999115439:
		errMsg = "Failed to obtain the volume.";
		break;
	case 999115440:
		errMsg = "Failed to enable audio output.";
		break;
	case 999115441:
		errMsg = "Incorrect audio collection status.";
		break;
	case 999115442:
		errMsg = "Failed to enable audio input.";
		break;
	case 999115443:
		errMsg = "The audio device is not found.";
		break;
	case 999115444:
		errMsg = "Unsupported media type.";
		break;
	case 999115445:
		errMsg = "Incorrect voice broadcast state.";
		break;
	case 999115446:
		errMsg = "The channel does not exist.";
		break;
	case 999115447:
		errMsg = "The connection handle does not exist.";
		break;
	case 999115448:
		errMsg = "Connection Failures";
		break;
	case 999115449:
		errMsg = "Incorrect response message.";
		break;
	case 999115450:
		errMsg = "The response timed out.";
		break;
	case 999115451:
		errMsg = "The link is abnormal.";
		break;
	case 999115452:
		errMsg = "Sending error.";
		break;
	case 999115453:
		errMsg = "Receiving error.";
		break;
	case 999115454:
		errMsg = "Error in the parameter check.";
		break;
	case 999115455:
		errMsg = "Normal end.The ANNOUNCE ended the request normally.";
		break;
	case 999115456:
		errMsg = "Abnormal end.The ANNOUNCE ended the request abnormally.";
		break;
	case 999115457:
		errMsg = "Common system error.";
		break;
	case 999115458:
		errMsg = "Port binding failure.";
		break;
	case 999115459:
		errMsg = "Server 500 response.";
		break;
	case 999115460:
		errMsg = "Service unavailable.";
		break;
	case 999115461:
		errMsg = "Failed to write the recording.Check the permission on the folder.";
		break;
	case 999115462:
		errMsg = "The recording file does not exist.";
		break;
	case 999115463:
		errMsg = "The voice talk had started.";
		break;
	case 999115464:
		errMsg = "The media server bandwidth is insufficient.";
		break;

	default:
		errMsg = "Unknown error.";
		break;
	}
}