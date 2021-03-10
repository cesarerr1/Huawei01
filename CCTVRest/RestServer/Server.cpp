#include "stdafx.h"
#include "Server.h"
#include <plog\Log.h>

using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

Server::Server()
{
}


Server::Server(utility::string_t url) : m_listener(url)
{
	LOGD << "Inicializando servidor en: " << url.c_str();
	m_listener.support(methods::GET, std::bind(&Server::handle_get, this, std::placeholders::_1));
}

void Server::handle_get(http_request message) 
{
	LOGD << "Se recibio una petición GET\n" << message.to_string();
	message.reply(status_codes::OK);
}
