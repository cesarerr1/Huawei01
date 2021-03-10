#pragma once
#include <map>
#include <cassert>
#include "EnumParser.h"
#include "Logger.h"

// Configuración por default para la publicación del servidor de peticiones
#define SERVIDOR_TCP_IP_DEFAULT		"127.0.0.1"
#define	SERVIDOR_TCP_PORT_DEFAULT	"8020"
#define SERVIDOR_TCP_TIMEOUT_DEFAULT "3000"

// Configuración por default para la conexión con el servidor IVS
#define SERVIDOR_IVS_IP_DEFAULT		"172.17.101.2"
#define SERVIDOR_IVS_USER_DEFAULT	"promad"
#define SERVIDOR_IVS_PWD_DEFAULT	"Huawer123"

// Definición de las llaves que corresponden a los parametros de configuración
#define CONF_IPADDRTCP		"ipAddr"
#define CONF_PORTADDRTCP	"portAddr"
#define CONF_TIMEOUTTCP		"timeOutTcp"

#define CONF_SERVIDORIVS	"servidorIVS"
#define CONF_USUARIOIVS		"usuarioIVS"
#define CONF_CLAVEIVS		"claveIVS"

using namespace CPlusPlusLogging;

class CConfiguracion
{
public:
	CConfiguracion(Logger *logger);
	~CConfiguracion();
	int cargarConfiguracion();
	std::string obtenerConfiguracion(char *llave);

protected:
	Logger *pLogger;
	FILE *generarConfiguracion(CString pathFile);
	int leerConfiguracion(CString pathFile);
	std::map<std::string, std::string> buffer;

};

enum ItemsConfiguracion
{
	// Datos de publicación del servidor de peticiones
	ipAddr,
	portAddr,
	timeOutTcp,

	// Datos de conexión con el servidor IVS
	servidorIVS, 
	usuarioIVS, 
	claveIVS
};

EnumParser<ItemsConfiguracion>::EnumParser() 
{
	enumMap[CONF_IPADDRTCP] = ipAddr;
	enumMap[CONF_PORTADDRTCP] = portAddr;
	enumMap[CONF_TIMEOUTTCP] = timeOutTcp;
	enumMap[CONF_SERVIDORIVS] = servidorIVS;
	enumMap[CONF_USUARIOIVS] = usuarioIVS;
	enumMap[CONF_CLAVEIVS] = claveIVS;
}