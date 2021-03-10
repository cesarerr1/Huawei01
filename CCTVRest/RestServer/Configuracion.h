#pragma once

#include <yaml-cpp\yaml.h>
#include <string>

using namespace std;

class Configuracion
{
public:
	Configuracion();
	~Configuracion();
	int lecturaConfiguracion();
	string consultaParametro(string key);

	static const string HTTP_HOST;
	static const string HTTP_PORT;
	static const string HTTP_TIMEOUT;

	static const string IVS_HOST;
	static const string IVS_USER;
	static const string IVS_PWD;

	static const string LOG_LEVEL;
	static const string LOG_SIZE;
	static const string LOG_NUMBER;

private:
	int lecturaArchivo(string path);
	YAML::Node prepararContenido();
	int lecturaContenido(YAML::Node config);
	int escrituraArchivo(string path, string content);

	map<string, string> m_Configuracion;
};

