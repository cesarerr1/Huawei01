#pragma once

#include <string>
#include <list>
#include <map>
#include "include\eLTE_SDK.h"
#include "include\eLTE_Types.h"

#define ELTE_EVT_MSG WM_APP | 0x1000

#define ELTE_LOGIN		0x00001

#define ELTE_Event_NotifyUserStatus				0	// (Device Status Change Notification)
#define ELTE_Event_NotifyP2pvideocallStatus		1	// (Real - time Video Event Notification)
#define ELTE_Event_NotifyResourceStatus			2	// (Group Relationship Change Notification)
#define ELTE_Event_NotifyProvisionChange		3	// (Device Attribute Configuration Change Notification)
#define ELTE_Event_NotifyProvisionAllResync		4	// (Configuration Data Automatic Download Notification)
#define ELTE_Event_NotifyP2pcallStatus			5	// (P2P Call Status Change Notification)
#define ELTE_Event_NotifyGroupStatus			6	// (Group Call Status Change Notification)
#define ELTE_Event_NotifyModuleStatus			7	// (Module Status Change Notification)
#define ELTE_Event_NotifyGISReport				8	// (GIS Information Notification)
#define ELTE_Event_NotifyGISStatus				9	// (GIS Status Notification)
#define ELTE_Event_NotifySDSReport				10	// (Short / Multimedia Message Reception Notification)
#define ELTE_Event_NotifySDSSendStatus			11	// (Short / Multimedia Message Sending Status Notification)

#define ELTE_MENSAJE_SMS	0
#define ELTE_MENSAJE_MMS	1

#define ELTE_VIDEO_CIF		0
#define ELTE_VIDEO_QCIF		1
#define ELTE_VIDEO_D1		2
#define ELTE_VIDEO_720P		3
#define ELTE_VIDEO_1080P	4

#define ELTE_CAMERA_FRONT	0
#define ELTE_CAMERA_BACK	1

#define ELTE_CAM_CONF_NREQ	0
#define ELTE_CAM_CONF_REQ	1

#define ELTE_CAM_SND_REQ	0
#define ELTE_CAM_SND_NREQ	1

#define	P2Pvideocall_IND_STATUS_INITIATED		3001
#define P2Pvideocall_IND_STATUS_RECEIVED		3002	//The upper-layer application receives a P2P call as a callee. Handling this event is not required.
#define	P2Pvideocall_IND_STATUS_ANSWERED		3003	//The upper-layer application initiates a P2P call as a caller and the callee has answered the call. In this case, the media is played based on the returned parameter.
#define P2Pvideocall_IND_STATUS_PROCEEDING		3004	//The upper-layer application attempts to initiate a P2P call as a caller.
#define P2Pvideocall_IND_STATUS_RINGING			3005	//The upper-layer application successfully initiates a P2P call as a caller and the callee is ringing.
#define	P2Pvideocall_IND_STATUS_ACKED			3006	//The upper-layer application is a callee.
#define P2Pvideocall_IND_STATUS_RELEASED		3007
#define P2Pvideocall_IND_STATUS_HANGUPED		3008
#define P2Pvideocall_IND_STATUS_HANGUPED_ACTIVE	3009
#define P2Pvideocall_IND_STATUS_CANCELLED		3010
#define P2Pvideocall_IND_STATUS_MONITOR			3011	//The upper-layer application receives a video upload request. Handling this event is not required.
#define	P2Pvideocall_IND_STATUS_PREMPTED		3012
#define P2Pvideocall_IND_STATUS_RELEASED_BUSY	3013
#define P2Pvideocall_IND_STATUS_PROHIBITED		3014
#define P2Pvideocall_IND_STATUS_REMOTE_NOANSWER	3015
#define P2Pvideocall_IND_STATUS_REMOTE_NOTFOUND	3016
#define P2Pvideocall_IND_STATUS_LICENSE_LIMIT	3017
#define	P2Pvideocall_IND_STATUS_EMERGENCY		3018
#define P2Pvideocall_IND_STATUS_ACKED_MEDIAPLANE_ERROR	 3019	//Creating the video RTP flow failed.
#define P2Pvideocall_IND_STATUS_ACKED_MEDIAPLANE_NOAUDIO 3020	//Creating the audio flow for the video failed.
#define P2Pvideocall_IND_STATUS_REMOTE_NOTCONNECTED	3021
#define P2Pvideocall_IND_STATUS_REMOTE_NOTSUPPORTED	3022
#define	P2Pvideocall_IND_STATUS_SIGNAL_ERROR		3023	//The SIP in gateway mode is incorrect,
#define P2Pvideocall_IND_STATUS_VIDEO_CONTROL		3024	//PTZ control in gateway mode
#define P2Pvideocall_IND_STATUS_PICKEDUP			3040	//The local end accepts the video from the terminal.

using namespace std;

class eLTESession
{
public:
	string identificarStatusVideo(int value);
	string identificarCategoriaGrupo(int value);
	string identificarCategoriaUsuario(int value);
	string identificarStatus(int value);
	CStringW identificarUltimoError();
	list<map<string, string> *>* parseoXML(char *xml, string nodo);
	map<string, string>* parseoXML(char *xml);
	int detenerVideo(string recurso);
	int asignarRecursoVideo(string recurso, ELTE_VOID *wnd);
	int iniciarVideo(string recurso, int videoFrm, int camType, int confReq, int sndType);
	int enviarMensaje(int tipoMensaje, string destino, string mensaje, string path);
	int cerrarLlamadaGrupo(string groupID);
	int liberarLlamadaGrupo(string groupID);
	int generarLlamadaGrupo(string groupID);
	int liberarLlamadaP2P(string resourceID);
	int generarLlamadaP2P(string resourceID);
	list<map<string, string>*>* listGroups();
	list<map<string, string>*>* listUsers();
	int triggerStatusReport();
	ELTE_INT32 getErrorCode();
	string getErrorMessage();
	int setStatus(bool status);
	bool isActivo();
	int releaseResources();
	int reconnectSession();
	int closeSession();
	int beginSession(string user, string pwd);

	static ELTE_VOID __SDK_CALL ELTE_EventCallBack(ELTE_INT32 iEventType,
		ELTE_VOID* pEventBuf, ELTE_UINT32 uiBufSize, ELTE_VOID* pUserData);

	eLTESession(string host, int port, string localip);
	~eLTESession();

protected:
	void identificarError(ELTE_INT32 errCode);

	map<string, string> m_grupos;
	ELTE_INT32 errCode;
	string errMsg;
	string m_user;
	string m_pwd;
	string local_ip;
	int n_port;
	string m_host;
	bool b_Activo;
	bool b_Inicializado;
};

