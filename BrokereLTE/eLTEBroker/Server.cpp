#include "stdafx.h"
#include "Server.h"
#include <plog\Log.h>

using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

Server::Server(utility::string_t url, eLTESession *pLTE, Configuracion *pConfiguracion) : m_listener(url)
{
	m_errMsg = "";
	m_status = 0;
	
	LOGD << "Inicializando servidor en: " << url.c_str();

	m_listener.support(methods::GET, std::bind(&Server::handle_get, this, std::placeholders::_1));
	m_listener.support(methods::POST, std::bind(&Server::handle_post, this, std::placeholders::_1));

	p_LTESession = pLTE;
	p_Configuracion = pConfiguracion;
	p_dlgServer = NULL;
}

void Server::setRestServer(CeLTEBrokerDlg *pDlg)
{
	LOGD << "Se asigna la referencia al dialogo del servidor REST.";
	p_dlgServer = pDlg;
}

string Server::getErrMsg()
{
	return m_errMsg;
}

bool Server::isActivo()
{
	m_errMsg = "";
	LOGD << "Se solicita consultar el status del servidor. " << m_status;
	return m_status == 0 ? false : true;
}

int Server::open() 
{
	m_errMsg = "";
	LOGD << "Solicitando habilitar el servidor REST.";

	try 
	{
		m_listener.open().wait();
		m_status = 1;
	}
	catch (http_exception ex) 
	{
		m_errMsg = ex.what();
		LOGE << "Error en la apertura del end point. " << m_errMsg;
		return -1;
	}

	return 0;
}

int Server::close() 
{
	m_errMsg = "";
	LOGD << "Solicitando deshabilitar el servidor REST.";

	try 
	{
		m_status = 0;
		m_listener.close().wait();
	}
	catch (http_exception ex)
	{
		m_errMsg = ex.what();
		LOGE << "Error en el cierre del end point. " << m_errMsg;
		return -1;
	}
	
	return 0;
}

void Server::handle_get(http_request message) 
{
	auto relative = message.relative_uri();
	string_t path = relative.path();
	LOGD << "Se recibio una petición GET. " << path;
	
	if (path.compare(_T("version")) == 0)
	{
		LOGD << "Se solicita consultar la versión y status del broker.";
		value response = json::value::object();
		response[_T("version")] = json::value::string(_T("1.0.1"));
		response[_T("status")] = json::value::string(_T("ready!"));
		response[_T("broker")] = json::value::string(_T("eLTE Sesion Broker."));
		message.reply(status_codes::OK, response);
		return;
	}

	else if (path.compare(_T("status")) == 0)
	{
		LOGD << "REQ Se solicita consultar el status de la sesión eLTE Service.";
		message.reply(status_codes::OK, consultarStatusSesion());
		return;
	}

	else if (path.compare(_T("usuarios")) == 0)
	{
		LOGD << "REQ Se solicita listar los usuarios registrados en la plataforma.";
		message.reply(status_codes::OK, listarUsuarios());
		return;
	}

	else if (path.compare(_T("grupos")) == 0)
	{
		LOGD << "REQ Se solicita listar los grupos registrados en la plataforma.";
		message.reply(status_codes::OK, listarGrupos());
		return;
	}
	
	LOGE << "GET - no se reconocio el path solicitado: " << path;
	message.reply(status_codes::NotFound);
}

void Server::handle_post(http_request message)
{
	auto relative = message.relative_uri();
	string_t path = relative.path();

	LOGD << "Se recibio una petición POST. " << path;

	if (path.compare(_T("llamadaDirecta/generar")) == 0)
	{
		LOGD << "REQ Se solicita generar una llamada directa.";
		string_t recurso(_T(""));
		for (auto item : message.headers())
		{
			if (item.first.compare(_T("recurso")) == 0)
				recurso = item.second;
		}
		LOGD << "REQ Se solicita generar una llamada directa al recurso: " << recurso;
		string buffer = conversions::to_utf8string(recurso);
		message.reply(status_codes::OK, llamadaP2P(buffer));
		return;
	}

	else if (path.compare(_T("llamadaDirecta/liberar")) == 0)
	{
		LOGD << "REQ Se solicita liberar una llamada directa.";
		string_t recurso(_T(""));
		for (auto item : message.headers())
		{
			if (item.first.compare(_T("recurso")) == 0)
				recurso = item.second;
		}
		LOGD << "REQ Se solicita liberar una llamada directa al recurso: " << recurso;
		string buffer = conversions::to_utf8string(recurso);
		message.reply(status_codes::OK, liberarLlamadaP2P(buffer));
		return;
	}

	else if (path.compare(_T("llamadaGrupo/generar")) == 0)
	{
		LOGD << "REQ Se solicita generar una llamada de grupo.";
		string_t recurso(_T(""));
		for (auto item : message.headers())
		{
			if (item.first.compare(_T("recurso")) == 0)
				recurso = item.second;
		}
		LOGD << "REQ Se solicita generar una llamada de grupo al recurso: " << recurso;
		string buffer = conversions::to_utf8string(recurso);
		message.reply(status_codes::OK, llamadaGrupo(buffer));
		return;
	}

	else if (path.compare(_T("llamadaGrupo/liberar")) == 0)
	{
		LOGD << "REQ Se solicita liberar una llamada de grupo.";
		string_t recurso(_T(""));
		for (auto item : message.headers())
		{
			if (item.first.compare(_T("recurso")) == 0)
				recurso = item.second;
		}
		LOGD << "REQ Se solicita liberar una llamada de grupo al recurso: " << recurso;
		string buffer = conversions::to_utf8string(recurso);
		message.reply(status_codes::OK, liberarLlamadaGrupo(buffer));
		return;
	}

	else if (path.compare(_T("llamadaGrupo/cerrar")) == 0)
	{
		LOGD << "REQ Se solicita cerrar una llamada de grupo.";
		string_t recurso(_T(""));
		for (auto item : message.headers())
		{
			if (item.first.compare(_T("recurso")) == 0)
				recurso = item.second;
		}
		LOGD << "REQ Se solicita cerrar una llamada de grupo al recurso: " << recurso;
		string buffer = conversions::to_utf8string(recurso);
		message.reply(status_codes::OK, cerrarLlamadaGrupo(buffer));
		return;
	}

	else if (path.compare(_T("mensajeTexto")) == 0)
	{
		LOGD << "REQ Se solicita generar un mensaje de texto.";
		string_t recurso(_T(""));
		string_t cuerpo(_T(""));
		for (auto item : message.headers())
		{
			if (item.first.compare(_T("recurso")) == 0)
				recurso = item.second;
			else if (item.first.compare(_T("mensaje")) == 0)
				cuerpo = item.second;
		}
		LOGD << "REQ Se solicita generar un mensaje al recurso: " << recurso << "/" << cuerpo;
		string buffer = conversions::to_utf8string(recurso);
		string mensaje = conversions::to_utf8string(cuerpo);
		message.reply(status_codes::OK, enviarSMS(buffer, mensaje));
		return;
	}

	else if (path.compare(_T("llamadaVideo")) == 0) 
	{
		LOGD << "REQ Se solicita generar una llamada de video.";
		string_t recurso(_T(""));
		for (auto item : message.headers())
		{
			if (item.first.compare(_T("recurso")) == 0)
				recurso = item.second;
		}
		LOGD << "REQ Se solicita generar una llamada de video al recurso: " << recurso;
		string buffer = conversions::to_utf8string(recurso);
		message.reply(status_codes::OK, llamadaVideo(buffer));
		return;
	}

	LOGE << "POST - no se reconocio el path solicitado: " << path;
	message.reply(status_codes::NotFound);
}

value Server::consultarStatusSesion()
{
	LOGD << "Se solicita consultar el status de la conexión.";

	value response = json::value::object();
	
	if (p_LTESession == NULL)
	{
		response[_T("status")] = json::value::string(_T("ERROR"));
		response[_T("errMsg")] = json::value::string(_T("No se cuenta con referencia a la sesión del IVS."));
		response[_T("errCode")] = json::value::number(1L);
	}
	else if (!p_LTESession->isActivo())
	{
		response[_T("status")] = json::value::string(_T("DESCONECTADO"));
		response[_T("errMsg")] = json::value::string(_T("No se cuenta con una sesión válida en el IVS."));
		response[_T("errCode")] = json::value::number(2L);
	}
	else if (p_LTESession->isActivo())
	{
		response[_T("status")] = json::value::string(_T("CONECTADO"));
		response[_T("errMsg")] = json::value::string(_T("OK"));
		response[_T("errCode")] = json::value::number(0L);
	}
	else
	{
		response[_T("status")] = json::value::string(_T("DESCONOCIDO"));
		response[_T("errMsg")] = json::value::string(_T("No se contemplo este estado."));
		response[_T("errCode")] = json::value::number(999L);
	}

	return response;
}

value Server::listarUsuarios()
{
	LOGD << "Se solicita listar los usuarios registrados en el sistema.";

	value response = json::value::object();

	if (p_LTESession == NULL)
	{
		LOGE << "No se cuenta con una referencia a la sesión del IVS.";
		response[_T("status")] = json::value::string(_T("ERROR"));
		response[_T("errMsg")] = json::value::string(_T("No se cuenta con referencia a la sesión del IVS."));
		response[_T("errCode")] = json::value::number(1L);
		return response;
	}

	list<map<string, string>*> *lista = p_LTESession->listUsers();
	if (lista == NULL)
	{
		LOGE << "Error al intentar listar los usuarios registrados en el sistema. " << p_LTESession->getErrorMessage();
		response[_T("status")] = json::value::string(_T("ERROR"));
		wstring buffer = CA2W(p_LTESession->getErrorMessage().c_str());
		response[_T("errMsg")] = json::value::string(buffer);
		response[_T("errCode")] = json::value::number(2L);
		return response;
	}

	vector<value> listado;
	listado.clear();
	for (list<map<string, string>*>::iterator it = lista->begin();
		it != lista->end(); it++)
	{
		value item = json::value::object();
		try
		{
			wstring buffer = CA2W(((**it)["UserID"]).c_str());
			item[_T("UserID")] = json::value::string(buffer);
			
			buffer = CA2W(((**it)["UserPriority"]).c_str());
			item[_T("UserPriority")] = json::value::string(buffer);

			buffer = CA2W(((**it)["UserName"]).c_str());
			item[_T("UserName")] = json::value::string(buffer);

			int value = stoi(((**it)["UserCategory"]), nullptr, 0);
			switch (value)
			{
			case 0: // DISPATCHER indicates a DC user.
				item[_T("UserCategory")] = json::value::string(_T("DISPATCHER"));
				break;
			case 4: // PLMNUSER indicates a PLMN user.
				item[_T("UserCategory")] = json::value::string(_T("PLMNUSER"));
				break;
			case 50: // ALLTYPEUSER indicates a user of any user type.
				item[_T("UserCategory")] = json::value::string(_T("ALLTYPEUSER"));
				break;
			case 255: // OTHERUSER indicates a user whose type is not defined.
				item[_T("UserCategory")] = json::value::string(_T("OTHERUSER"));
				break;
			case 1: // FIXEDCAMERA indicates a fixed camera.
				item[_T("UserCategory")] = json::value::string(_T("FIXEDCAMERA"));
				break;
			case 2: // PSTNUSER indicates a PSTN user.
				item[_T("UserCategory")] = json::value::string(_T("PSTNUSER"));
				break;
			case 3: // TETRAUSER indicates a TETRA user.
				item[_T("UserCategory")] = json::value::string(_T("TETRAUSER"));
				break;
			case 5: // EXTERNALPTT indicates an external PTT user.
				item[_T("UserCategory")] = json::value::string(_T("EXTERNALPTT"));
				break;
			case 9: // PTTUSER indicates a PTT user.
				item[_T("UserCategory")] = json::value::string(_T("PTTUSER"));
				break;
			case 6: // SDKUSER indicates an SDK gateway internal user.
				item[_T("UserCategory")] = json::value::string(_T("SDKUSER"));
				break;
			case 7: // APPUSER indicates an tAPP user.
				item[_T("UserCategory")] = json::value::string(_T("APPUSER"));
				break;
			case 8: // UELOGINUSER indicates a logged - in terminal user.
				item[_T("UserCategory")] = json::value::string(_T("UELOGINUSER"));
				break;
			default:
				item[_T("UserCategory")] = json::value::string(_T("UNKNONW"));
				break;
			}
			
			listado.push_back(item);
		}
		catch (invalid_argument ex)
		{
			LOGE << "Argumento invalido para la categoria. " << ((**it)["UserCategory"]) << "\n" << ex.what();
		}
		catch (out_of_range ex)
		{
			LOGE << "Argumento fuera de rango para la categoria. " << ((**it)["UserCategory"]) << "\n" << ex.what();
		}
		
		(*it)->clear();
		delete (*it);
	}

	lista->clear();
	delete lista;
	response[_T("usuarios")] = json::value::array(listado);

	return response;
}

value Server::listarGrupos()
{
	LOGD << "Se solicita listar los grupos registrados en el sistema.";

	value response = json::value::object();

	if (p_LTESession == NULL)
	{
		LOGE << "No se cuenta con una referencia a la sesión del IVS.";
		response[_T("status")] = json::value::string(_T("ERROR"));
		response[_T("errMsg")] = json::value::string(_T("No se cuenta con referencia a la sesión del IVS."));
		response[_T("errCode")] = json::value::number(1L);
		return response;
	}

	list<map<string, string>*> *lista = p_LTESession->listGroups();
	if (lista == NULL)
	{
		LOGE << "Error al intentar listar los grupos registrados en el sistema. " << p_LTESession->getErrorMessage();
		response[_T("status")] = json::value::string(_T("ERROR"));
		wstring buffer = CA2W(p_LTESession->getErrorMessage().c_str());
		response[_T("errMsg")] = json::value::string(buffer);
		response[_T("errCode")] = json::value::number(2L);
		return response;
	}

	vector<value> listado;
	listado.clear();
	for (list<map<string, string>*>::iterator it = lista->begin();
		it != lista->end(); it++)
	{
		value item = json::value::object();
		try
		{
			wstring buffer = CA2W(((**it)["GroupID"]).c_str());
			item[_T("GroupID")] = json::value::string(buffer);

			buffer = CA2W(((**it)["GroupPriority"]).c_str());
			item[_T("GroupPriority")] = json::value::string(buffer);

			buffer = CA2W(((**it)["GroupName"]).c_str());
			item[_T("GroupName")] = json::value::string(buffer);

			int value = stoi(((**it)["GroupCategory"]), nullptr, 0);
			switch (value)
			{
			case 0: // GRP_ALLBROADCAST indicates a network - wide broadcast group.
				item[_T("GroupCategory")] = json::value::string(_T("GRP_ALLBROADCAST"));
				break;
			case 1: // GRP_GENERAL indicates a common group.
				item[_T("GroupCategory")] = json::value::string(_T("GRP_GENERAL"));
				break;
			case 2: // GRP_AREABROADCAST indicates a regional broadcast group.
				item[_T("GroupCategory")] = json::value::string(_T("GRP_AREABROADCAST"));
				break;
			case 8: // GRP_EXTERNAL indicates an external group.
				item[_T("GroupCategory")] = json::value::string(_T("GRP_EXTERNAL"));
				break;
			case 9: // GRP_DYNAMICGRP indicates a dynamic group.
				item[_T("GroupCategory")] = json::value::string(_T("GRP_DYNAMICGRP"));
				break;
			case 10: // GRP_ALLTYPE indicates a group of any type.
				item[_T("GroupCategory")] = json::value::string(_T("GRP_ALLTYPE"));
				break;
			default:
				item[_T("GroupCategory")] = json::value::string(_T("UNKNONW"));
				break;
			}

			listado.push_back(item);
		}
		catch (invalid_argument ex)
		{
			LOGE << "Argumento invalido para la categoria. " << ((**it)["GroupCategory"]) << "\n" << ex.what();
		}
		catch (out_of_range ex)
		{
			LOGE << "Argumento fuera de rango para la categoria. " << ((**it)["GroupCategory"]) << "\n" << ex.what();
		}

		(*it)->clear();
		delete (*it);
	}

	lista->clear();
	delete lista;
	response[_T("grupos")] = json::value::array(listado);

	return response;
}

value Server::llamadaP2P(string recurso)
{
	LOGD << "Se solicita hacer una llamada P2P: " << recurso;

	value response = json::value::object();

	if (p_LTESession == NULL)
	{
		LOGE << "No se cuenta con una referencia a la sesión del IVS.";
		response[_T("status")] = json::value::string(_T("ERROR"));
		response[_T("errMsg")] = json::value::string(_T("No se cuenta con referencia a la sesión del IVS."));
		response[_T("errCode")] = json::value::number(1L);
		return response;
	}

	int res = p_LTESession->generarLlamadaP2P(recurso);
	if (res != 0) {
		LOGE << "Error en la generación de la llamada P2P. " << recurso << p_LTESession->getErrorMessage();
		response[_T("status")] = json::value::string(_T("ERROR"));
		wstring buffer = CA2W(p_LTESession->getErrorMessage().c_str());
		response[_T("errMsg")] = json::value::string(buffer);
		response[_T("errCode")] = json::value::number(1001L);
		return response;
	}

	LOGD << "Se logro generar la llamada P2P.";
	response[_T("status")] = json::value::string(_T("OK"));
	response[_T("errMsg")] = json::value::string(_T(""));
	response[_T("errCode")] = json::value::number(0L);
	return response;
}

value Server::liberarLlamadaP2P(string recurso)
{
	LOGD << "Se solicita liberar una llamada P2P: " << recurso;

	value response = json::value::object();

	if (p_LTESession == NULL)
	{
		LOGE << "No se cuenta con una referencia a la sesión del IVS.";
		response[_T("status")] = json::value::string(_T("ERROR"));
		response[_T("errMsg")] = json::value::string(_T("No se cuenta con referencia a la sesión del IVS."));
		response[_T("errCode")] = json::value::number(1L);
		return response;
	}

	int res = p_LTESession->liberarLlamadaP2P(recurso);
	if (res != 0) {
		LOGE << "Error en la liberación de la llamada P2P. " << recurso << p_LTESession->getErrorMessage();
		response[_T("status")] = json::value::string(_T("ERROR"));
		wstring buffer = CA2W(p_LTESession->getErrorMessage().c_str());
		response[_T("errMsg")] = json::value::string(buffer);
		response[_T("errCode")] = json::value::number(1001L);
		return response;
	}

	LOGD << "Se logro liberar la llamada P2P.";
	response[_T("status")] = json::value::string(_T("OK"));
	response[_T("errMsg")] = json::value::string(_T(""));
	response[_T("errCode")] = json::value::number(0L);
	return response;
}

value Server::llamadaGrupo(string recurso)
{
	LOGD << "Se solicita hacer una llamada de grupo: " << recurso;

	value response = json::value::object();

	if (p_LTESession == NULL)
	{
		LOGE << "No se cuenta con una referencia a la sesión del IVS.";
		response[_T("status")] = json::value::string(_T("ERROR"));
		response[_T("errMsg")] = json::value::string(_T("No se cuenta con referencia a la sesión del IVS."));
		response[_T("errCode")] = json::value::number(1L);
		return response;
	}

	int res = p_LTESession->generarLlamadaGrupo(recurso);
	if (res != 0) {
		LOGE << "Error en la generación de la llamada grupo. " << recurso << p_LTESession->getErrorMessage();
		response[_T("status")] = json::value::string(_T("ERROR"));
		wstring buffer = CA2W(p_LTESession->getErrorMessage().c_str());
		response[_T("errMsg")] = json::value::string(buffer);
		response[_T("errCode")] = json::value::number(1001L);
		return response;
	}

	LOGD << "Se logro generar la llamada grupo.";
	response[_T("status")] = json::value::string(_T("OK"));
	response[_T("errMsg")] = json::value::string(_T(""));
	response[_T("errCode")] = json::value::number(0L);
	return response;
}

value Server::liberarLlamadaGrupo(string recurso)
{
	LOGD << "Se solicita liberar una llamada de grupo: " << recurso;

	value response = json::value::object();

	if (p_LTESession == NULL)
	{
		LOGE << "No se cuenta con una referencia a la sesión del IVS.";
		response[_T("status")] = json::value::string(_T("ERROR"));
		response[_T("errMsg")] = json::value::string(_T("No se cuenta con referencia a la sesión del IVS."));
		response[_T("errCode")] = json::value::number(1L);
		return response;
	}

	int res = p_LTESession->liberarLlamadaGrupo(recurso);
	if (res != 0) {
		LOGE << "Error en la liberación de la llamada grupo. " << recurso << p_LTESession->getErrorMessage();
		response[_T("status")] = json::value::string(_T("ERROR"));
		wstring buffer = CA2W(p_LTESession->getErrorMessage().c_str());
		response[_T("errMsg")] = json::value::string(buffer);
		response[_T("errCode")] = json::value::number(1001L);
		return response;
	}

	LOGD << "Se logro liberar la llamada grupo.";
	response[_T("status")] = json::value::string(_T("OK"));
	response[_T("errMsg")] = json::value::string(_T(""));
	response[_T("errCode")] = json::value::number(0L);
	return response;
}

value Server::cerrarLlamadaGrupo(string recurso)
{
	LOGD << "Se solicita cerrar una llamada de grupo: " << recurso;

	value response = json::value::object();

	if (p_LTESession == NULL)
	{
		LOGE << "No se cuenta con una referencia a la sesión del IVS.";
		response[_T("status")] = json::value::string(_T("ERROR"));
		response[_T("errMsg")] = json::value::string(_T("No se cuenta con referencia a la sesión del IVS."));
		response[_T("errCode")] = json::value::number(1L);
		return response;
	}

	int res = p_LTESession->cerrarLlamadaGrupo(recurso);
	if (res != 0) {
		LOGE << "Error en el cierre de la llamada grupo. " << recurso << p_LTESession->getErrorMessage();
		response[_T("status")] = json::value::string(_T("ERROR"));
		wstring buffer = CA2W(p_LTESession->getErrorMessage().c_str());
		response[_T("errMsg")] = json::value::string(buffer);
		response[_T("errCode")] = json::value::number(1001L);
		return response;
	}

	LOGD << "Se logro cerrar la llamada grupo.";
	response[_T("status")] = json::value::string(_T("OK"));
	response[_T("errMsg")] = json::value::string(_T(""));
	response[_T("errCode")] = json::value::number(0L);
	return response;
}

value Server::enviarSMS(string recurso, string mensaje)
{
	LOGD << "Se solicita enviar un SMS: " << recurso << "/" << mensaje;

	value response = json::value::object();

	if (p_LTESession == NULL)
	{
		LOGE << "No se cuenta con una referencia a la sesión del IVS.";
		response[_T("status")] = json::value::string(_T("ERROR"));
		response[_T("errMsg")] = json::value::string(_T("No se cuenta con referencia a la sesión del IVS."));
		response[_T("errCode")] = json::value::number(1L);
		return response;
	}

	int res = p_LTESession->enviarMensaje(ELTE_MENSAJE_SMS, recurso, mensaje, "");
	if (res != 0) {
		LOGE << "Error en la generación del mensaje. " << recurso << p_LTESession->getErrorMessage();
		response[_T("status")] = json::value::string(_T("ERROR"));
		wstring buffer = CA2W(p_LTESession->getErrorMessage().c_str());
		response[_T("errMsg")] = json::value::string(buffer);
		response[_T("errCode")] = json::value::number(1001L);
		return response;
	}

	LOGD << "Se logro generar el mensaje.";
	response[_T("status")] = json::value::string(_T("OK"));
	response[_T("errMsg")] = json::value::string(_T(""));
	response[_T("errCode")] = json::value::number(0L);
	return response;
}

value Server::llamadaVideo(string recurso)
{
	LOGD << "Se solicita generar una llamada de video al recuros: " << recurso;

	value response = json::value::object();

	if (p_LTESession == NULL)
	{
		LOGE << "No se cuenta con una referencia a la sesión del IVS.";
		response[_T("status")] = json::value::string(_T("ERROR"));
		response[_T("errMsg")] = json::value::string(_T("No se cuenta con referencia a la sesión del IVS."));
		response[_T("errCode")] = json::value::number(1L);
		return response;
	}

	int res = p_LTESession->iniciarVideo(recurso,
		ELTE_VIDEO_D1,
		ELTE_CAMERA_BACK,
		ELTE_CAM_CONF_NREQ,
		ELTE_CAM_SND_NREQ);

	if (res != 0) {
		LOGE << "Error en la generación de la llamada. " << recurso << p_LTESession->getErrorMessage();
		response[_T("status")] = json::value::string(_T("ERROR"));
		wstring buffer = CA2W(p_LTESession->getErrorMessage().c_str());
		response[_T("errMsg")] = json::value::string(buffer);
		response[_T("errCode")] = json::value::number(1001L);
		return response;
	}

	LOGD << "Se logro solicitar la llamada de video.";
	response[_T("status")] = json::value::string(_T("OK"));
	response[_T("errMsg")] = json::value::string(_T(""));
	response[_T("errCode")] = json::value::number(0L);
	return response;
}