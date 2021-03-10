#include "stdafx.h"
#include "Configuracion.h"
#include <plog\Log.h>
#include <iostream>
#include <fstream>

// Configuración por default para la publicación del servidor de peticiones
#define SERVIDOR_IP_DEFAULT		 "127.0.0.1"
#define	SERVIDOR_PORT_DEFAULT	 "8020"
#define SERVIDOR_TIMEOUT_DEFAULT "3000"

// Configuración por default para la conexión con el servidor IVS
#define IVS_IP_DEFAULT		  "172.17.101.2"
#define IVS_USER_DEFAULT	  "promad"
#define IVS_PWD_DEFAULT		  "Huawei123"

// Configuración por default de las bitácoras
#define LOG_LEVEL_DEFAULT		"ERROR"
#define LOG_SIZE_DEFAULT		"10000000"
#define LOG_NUMFILES_DEFAULT	"5"

// Definición de las llaves que corresponden a los parametros de configuración
#define CONF_IPADDR_HTTP	"host"
#define CONF_PORTADDR_HTTP	"port"
#define CONF_TIMEOUT_HTTP	"timeout"

#define CONF_SERVIDOR_IVS	"host"
#define CONF_USUARIO_IVS	"usuario"
#define CONF_CLAVE_IVS		"clave"

#define CONF_NIVEL_LOG		"nivel"
#define CONF_SIZE_LOG		"size"
#define CONF_NUM_LOG		"numero"

const string Configuracion::HTTP_HOST = "HTTP_HOST";
const string Configuracion::HTTP_PORT = "HTTP_PORT";
const string Configuracion::HTTP_TIMEOUT = "HTTP_TIMEOUT";

const string Configuracion::IVS_HOST = "IVS_HOST";
const string Configuracion::IVS_USER = "IVS_USER";
const string Configuracion::IVS_PWD = "IVS_PWD";

const string Configuracion::LOG_LEVEL = "LOG_LEVEL";
const string Configuracion::LOG_SIZE = "LOG_SIZE";
const string Configuracion::LOG_NUMBER = "LOG_NUMBER";

Configuracion::Configuracion()
{
}

Configuracion::~Configuracion()
{
}

int Configuracion::lecturaConfiguracion() 
{
	LOGD << "Solicitando la lectura del archivo de configuración.";

	lecturaArchivo("configuracion.yml");

	return 0;

}

int Configuracion::lecturaArchivo(string path)
{
	string buff = "Solicitando la lectura del archivo: ";
	buff.append(path.c_str());
	LOGI << buff;

	ifstream file(path.c_str());
	if (file.is_open())
	{
		LOGD << "Inicio de la lectura del archivo de configuración.";
		file.close();

		YAML::Node config = YAML::LoadFile(path.c_str());
		lecturaContenido(config);
	}
	else 
	{
		LOGE << "Error en la apertura del archivo de configuración.";
		LOGD << "Se intentara generar el archivo de configuración.";
		
		YAML::Node conf = prepararContenido();
		ofstream fout(path.c_str());
		fout << conf;
		lecturaContenido(conf);

		return 0;
	}
	LOGD << "Se logro cargar el archivo de configuración.";

	return 0;
}

YAML::Node Configuracion::prepararContenido()
{

	LOGD << "Se preparará el contenido predeterminado del archivo de configuración.";

	YAML::Node node;

	// Carga de la configuración por default del servidor
	node["server"][CONF_IPADDR_HTTP] = SERVIDOR_IP_DEFAULT;
	node["server"][CONF_PORTADDR_HTTP] = SERVIDOR_PORT_DEFAULT;
	node["server"][CONF_TIMEOUT_HTTP] = SERVIDOR_TIMEOUT_DEFAULT;

	// Carga de la configuración por default de la conectividad con el IVS
	node["ivs"][CONF_SERVIDOR_IVS] = IVS_IP_DEFAULT;
	node["ivs"][CONF_USUARIO_IVS] = IVS_USER_DEFAULT;
	node["ivs"][CONF_CLAVE_IVS] = IVS_PWD_DEFAULT;

	// Carga de la configuración por default de las bitácoras
	node["logs"][CONF_NIVEL_LOG] = LOG_LEVEL_DEFAULT;
	node["logs"][CONF_SIZE_LOG] = LOG_SIZE_DEFAULT;
	node["logs"][CONF_NUM_LOG] = LOG_NUMFILES_DEFAULT;

	return node;
}

int Configuracion::lecturaContenido(YAML::Node config)
{
	LOGD << "Iniciando la lectura de la configuración proporcionada.";

	m_Configuracion.clear();

	m_Configuracion[Configuracion::HTTP_HOST] = config["server"][CONF_IPADDR_HTTP].as<string>();
	LOGD << "server.host: " << m_Configuracion[Configuracion::HTTP_HOST].c_str();
	m_Configuracion[Configuracion::HTTP_PORT] = config["server"][CONF_PORTADDR_HTTP].as<string>();
	LOGD << "server.port: " << m_Configuracion[Configuracion::HTTP_PORT].c_str();
	m_Configuracion[Configuracion::HTTP_TIMEOUT] = config["server"][CONF_TIMEOUT_HTTP].as<string>();
	LOGD << "server.timeout: " << m_Configuracion[Configuracion::HTTP_TIMEOUT].c_str();

	m_Configuracion[Configuracion::IVS_HOST] = config["ivs"][CONF_SERVIDOR_IVS].as<string>();
	LOGD << "ivs.host: " << m_Configuracion[Configuracion::IVS_HOST].c_str();
	m_Configuracion[Configuracion::IVS_USER] = config["ivs"][CONF_USUARIO_IVS].as<string>();
	LOGD << "ivs.usr: " << m_Configuracion[Configuracion::IVS_USER].c_str();
	m_Configuracion[Configuracion::IVS_PWD] = config["ivs"][CONF_CLAVE_IVS].as<string>();
	LOGD << "ivs.pwd: " << m_Configuracion[Configuracion::IVS_PWD].c_str();

	m_Configuracion[Configuracion::LOG_LEVEL] = config["logs"][CONF_NIVEL_LOG].as<string>();
	LOGD << "logs.level: " << m_Configuracion[Configuracion::LOG_LEVEL].c_str();
	m_Configuracion[Configuracion::LOG_SIZE] = config["logs"][CONF_SIZE_LOG].as<string>();
	LOGD << "logs.size: " << m_Configuracion[Configuracion::LOG_SIZE].c_str();
	m_Configuracion[Configuracion::LOG_NUMBER] = config["logs"][CONF_NUM_LOG].as<string>();
	LOGD << "logs.number: " << m_Configuracion[Configuracion::LOG_NUMBER].c_str();

	return 0;
}

string Configuracion::consultaParametro(string key)
{
	LOGD << "Se solicita consultar un parámetro: " << key.c_str();
	return m_Configuracion[key];
}

int Configuracion::escrituraArchivo(string path, string content)
{

	string buff = "Iniciando el almacenamiento del arhivo de configuración. ";
	buff.append(path);
	LOGI << buff.c_str();

	ofstream file(path);
	if (file.is_open())
	{
		file << content.c_str();
		file.close();
	}
	else
	{
		LOGE << "Error en la generación del archivo de configuración.";
		return -1;
	}

	return 0;
}