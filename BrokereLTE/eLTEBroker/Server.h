#pragma once

#include "cpprest/json.h"
#include "cpprest/http_listener.h"
#include "cpprest/uri.h"
#include "cpprest/asyncrt_utils.h"
#include <string>
#include "eLTESession.h"
#include "Configuracion.h"
#include "eLTEBrokerDlg.h"

using namespace std;
using namespace web;
using namespace http;
using namespace utility;
using namespace web::json;
using namespace http::experimental::listener;

#define EVT_SERVER	(WM_APP | 0x110)

#define COM_DESPLIEGA_CAMARA	0x01

class Server
{
public:
	Server(utility::string_t url, eLTESession *pLTE, Configuracion *pConfiguracion);
	void setRestServer(CeLTEBrokerDlg *pDlg);
	bool isActivo();
	string getErrMsg();
	int open();
	int close();

protected:
	void handle_post(http_request message);
	void handle_get(http_request message);

	value llamadaVideo(string recurso);
	value enviarSMS(string recurso, string mensaje);
	value cerrarLlamadaGrupo(string recurso);
	value liberarLlamadaGrupo(string recurso);
	value llamadaGrupo(string recurso);
	value liberarLlamadaP2P(string recurso);
	value llamadaP2P(string recurso);
	value listarGrupos();
	value listarUsuarios();
	value consultarStatusSesion();

	CeLTEBrokerDlg *p_dlgServer;
	Configuracion *p_Configuracion;
	eLTESession *p_LTESession;
	UINT m_status;
	string m_errMsg;
	http_listener m_listener;
};

