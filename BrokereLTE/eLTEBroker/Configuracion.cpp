#include "stdafx.h"
#include "Configuracion.h"
#include <plog\Log.h>
#include <iostream>
#include <fstream>

// Configuración por default para la publicación del servidor de peticiones
#define SERVIDOR_IP_DEFAULT		 "localhost"
#define	SERVIDOR_PORT_DEFAULT	 "8030"
#define SERVIDOR_TIMEOUT_DEFAULT "3000"

// Configuración por default para la conexión con el servidor IVS
#define ELTE_IP_DEFAULT			"192.168.3.30"
#define ELTE_PORT_DEFAULT		"5060"
#define ELTE_USER_DEFAULT		"promad"
#define ELTE_PWD_DEFAULT		"promad123"

// Configuración por default de las bitácoras
#define LOG_LEVEL_DEFAULT		"ERROR"
#define LOG_SIZE_DEFAULT		"10000000"
#define LOG_NUMFILES_DEFAULT	"5"

// Configuración del número máximo de ventanas de reproducción
#define MAX_NUM_CAMARAS			"3"
#define ST_LISTA_CAMARAS		"TRUE"
#define ST_TIME_CAMARAS			"5"
#define ST_LOCAL_IP				"172.21.100.254"

// Definición de las llaves que corresponden a los parametros de configuración
#define CONF_IPADDR_HTTP		"host"
#define CONF_PORTADDR_HTTP		"port"
#define CONF_TIMEOUT_HTTP		"timeout"

#define CONF_SERVIDOR_ELTE		"host"
#define CONF_PORT_ELTE			"port"
#define CONF_USUARIO_ELTE		"usuario"
#define CONF_CLAVE_ELTE			"clave"

#define CONF_NIVEL_LOG			"nivel"
#define CONF_SIZE_LOG			"size"
#define CONF_NUM_LOG			"numero"

#define CONF_CAMARA_MAX			"camaras"
#define CONF_LISTA_CAM			"lista"
#define CONF_TIEMPO_CAM			"tiempo"
#define	CONF_LOCAL_IP			"localip"

const string Configuracion::HTTP_HOST = "HTTP_HOST";
const string Configuracion::HTTP_PORT = "HTTP_PORT";
const string Configuracion::HTTP_TIMEOUT = "HTTP_TIMEOUT";

const string Configuracion::ELTE_HOST = "ELTE_HOST";
const string Configuracion::ELTE_PORT = "ELTE_PORT";
const string Configuracion::ELTE_USER = "ELTE_USER";
const string Configuracion::ELTE_PWD = "ELTE_PWD";

const string Configuracion::LOG_LEVEL = "LOG_LEVEL";
const string Configuracion::LOG_SIZE = "LOG_SIZE";
const string Configuracion::LOG_NUMBER = "LOG_NUMBER";

const string Configuracion::MAX_CAMARAS = "MAX_CAMARAS";
const string Configuracion::LISTA_CAMARAS = "LISTA_CAMARAS";
const string Configuracion::TIEMPO_CAMARAS = "TIEMPO_CAMARAS";
const string Configuracion::LOCAL_IP = "LOCAL_IP";

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

	LOGD << "Archivo de configuración a ser validado: " << path.c_str();
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
	node["elte"][CONF_SERVIDOR_ELTE] = ELTE_IP_DEFAULT;
	node["elte"][CONF_PORT_ELTE] = ELTE_PORT_DEFAULT;
	node["elte"][CONF_USUARIO_ELTE] = ELTE_USER_DEFAULT;
	node["elte"][CONF_CLAVE_ELTE] = ELTE_PWD_DEFAULT;

	// Carga de la configuración por default de las bitácoras
	node["logs"][CONF_NIVEL_LOG] = LOG_LEVEL_DEFAULT;
	node["logs"][CONF_SIZE_LOG] = LOG_SIZE_DEFAULT;
	node["logs"][CONF_NUM_LOG] = LOG_NUMFILES_DEFAULT;

	// Carga de los máximos permitidos por la aplicación
	node["max"][CONF_CAMARA_MAX] = MAX_NUM_CAMARAS;
	node["conf"][CONF_LISTA_CAM] = ST_LISTA_CAMARAS;
	node["conf"][CONF_TIEMPO_CAM] = ST_TIME_CAMARAS;
	node["conf"][CONF_LOCAL_IP] = ST_LOCAL_IP;

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

	m_Configuracion[Configuracion::ELTE_HOST] = config["elte"][CONF_SERVIDOR_ELTE].as<string>();
	LOGD << "ivs.host: " << m_Configuracion[Configuracion::ELTE_HOST].c_str();
	m_Configuracion[Configuracion::ELTE_PORT] = config["elte"][CONF_PORT_ELTE].as<string>();
	LOGD << "ivs.port: " << m_Configuracion[Configuracion::ELTE_PORT].c_str();
	m_Configuracion[Configuracion::ELTE_USER] = config["elte"][CONF_USUARIO_ELTE].as<string>();
	LOGD << "ivs.usr: " << m_Configuracion[Configuracion::ELTE_USER].c_str();
	m_Configuracion[Configuracion::ELTE_PWD] = config["elte"][CONF_CLAVE_ELTE].as<string>();
	LOGD << "ivs.pwd: " << m_Configuracion[Configuracion::ELTE_PWD].c_str();

	m_Configuracion[Configuracion::LOG_LEVEL] = config["logs"][CONF_NIVEL_LOG].as<string>();
	LOGD << "logs.level: " << m_Configuracion[Configuracion::LOG_LEVEL].c_str();
	m_Configuracion[Configuracion::LOG_SIZE] = config["logs"][CONF_SIZE_LOG].as<string>();
	LOGD << "logs.size: " << m_Configuracion[Configuracion::LOG_SIZE].c_str();
	m_Configuracion[Configuracion::LOG_NUMBER] = config["logs"][CONF_NUM_LOG].as<string>();
	LOGD << "logs.number: " << m_Configuracion[Configuracion::LOG_NUMBER].c_str();

	m_Configuracion[Configuracion::MAX_CAMARAS] = config["max"][CONF_CAMARA_MAX].as<string>();
	LOGD << "max.camaras: " << m_Configuracion[Configuracion::MAX_CAMARAS].c_str();
	m_Configuracion[Configuracion::LISTA_CAMARAS] = config["conf"][CONF_LISTA_CAM].as<string>();
	LOGD << "conf.listaCamaras: " << m_Configuracion[Configuracion::LISTA_CAMARAS].c_str();
	m_Configuracion[Configuracion::TIEMPO_CAMARAS] = config["conf"][CONF_TIEMPO_CAM].as<string>();
	LOGD << "conf.tiempoCamara: " << m_Configuracion[Configuracion::TIEMPO_CAMARAS].c_str();
	m_Configuracion[Configuracion::LOCAL_IP] = config["conf"][CONF_LOCAL_IP].as<string>();
	LOGD << "conf.localip: " << m_Configuracion[Configuracion::LOCAL_IP].c_str();

	return 0;
}

string Configuracion::consultaParametro(string key)
{
	LOGD << "Se solicita consultar un parámetro: " << key.c_str();
	if (m_Configuracion.count(key.c_str()))
		return m_Configuracion[key];
	return "";
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