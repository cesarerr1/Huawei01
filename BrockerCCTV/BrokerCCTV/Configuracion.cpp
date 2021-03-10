#include "stdafx.h"
#include "Configuracion.h"


CConfiguracion::CConfiguracion(Logger *logger)
{
	this->pLogger = logger;
}


CConfiguracion::~CConfiguracion()
{
}

int CConfiguracion::cargarConfiguracion()
{
	// Se elimina cualquier contenido del buffer de configuración
	buffer.clear();

	// Se intenta obtener el path de ejecución
	CString path;
	AfxGetModuleFileName(AfxGetInstanceHandle(), path);
	path = path.Left(path.ReverseFind('\\') + 1);
	CString properties;
	properties = path + CString("configuracion.properties");
	CW2A str(properties, CP_UTF8);
	char buff[1024];
	sprintf_s(buff, 1024, "Path de configuración: %s", str);
	pLogger->always(buff);
	pLogger->always(buff);

	// Se valida que exista el archivo de configuración
	FILE *file;
	errno_t error = fopen_s(&file, str, "r");
	if (error != NO_ERROR) {
		// Hay un problema con el archivo de configuración
		if ((file = generarConfiguracion(properties)) == NULL) {
			pLogger->always("Error en la generación del archivo de configuración.");
			return -1;
		}
	}
	else {
		// Se puede leer el archivo de configuración
		fclose(file);
		if (leerConfiguracion(properties) != 0) {
			pLogger->always("Error en la lectura de la configuración.");
			return -1;
		}
	}

	pLogger->always("\nConfiguración reconocida.\n");
	std::string buf = "Servidor IVS: " + buffer[CONF_SERVIDORIVS] + "\n";
	pLogger->always(buf.c_str());
	buf = "Usuario  IVS: " + buffer[CONF_USUARIOIVS] + "\n";
	pLogger->always(buf.c_str());

	return 0;
}

FILE *CConfiguracion::generarConfiguracion(CString pathFile)
{
	// Se intenta generar el archivo de configuración por default
	FILE *file;
	CW2A str(pathFile, CP_UTF8);
	fopen_s(&file, str, "w");
	if (file == NULL) {
		pLogger->always("Error en la generación del archivo de configuración.");
		return NULL;
	}
	pLogger->always("Se logro generar el archivo de configuración.");

	// Se carga el default en el archivo de configuración
	char buffer[1024];
	sprintf_s(buffer, 1024, "%s=%s\n", CONF_IPADDRTCP, SERVIDOR_TCP_IP_DEFAULT);
	fputs(buffer, file);
	sprintf_s(buffer, 1024, "%s=%s\n", CONF_PORTADDRTCP, SERVIDOR_TCP_PORT_DEFAULT);
	fputs(buffer, file);
	sprintf_s(buffer, 1024, "%s=%s\n", CONF_TIMEOUTTCP, SERVIDOR_TCP_TIMEOUT_DEFAULT);
	fputs(buffer, file);
	sprintf_s(buffer, 1024, "%s=%s\n", CONF_SERVIDORIVS, SERVIDOR_IVS_IP_DEFAULT);
	fputs(buffer, file);
	sprintf_s(buffer, 1024, "%s=%s\n", CONF_USUARIOIVS, SERVIDOR_IVS_USER_DEFAULT);
	fputs(buffer, file);
	sprintf_s(buffer, 1024, "%s=%s\n", CONF_CLAVEIVS, SERVIDOR_IVS_PWD_DEFAULT);
	fputs(buffer, file);

	// Se cierra la interface con el archivo
	fclose(file);
	
	return file;
}

int CConfiguracion::leerConfiguracion(CString pathFile) {

	// Se abre el archivo para su lectura
	FILE *file;
	CW2A str(pathFile, CP_UTF8);
	errno_t error = fopen_s(&file, str, "r");
	if (error != NO_ERROR) {
		pLogger->always("Error en la reapertura del archivo de configuración.");
		return -1;
	}

	// Se obtiene el tamaño del archivo
	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	rewind(file);

	// Se inicia con la lectura del archivo
	char *buffer = (char*)malloc(sizeof(char) * size);
	if (buffer == NULL) {
		pLogger->always("Error en la asignación de memoria para la lectura de la configuración.");
		return -1;
	}
	long res = fread(buffer, sizeof(char), size, file);
	if (res <= 0) {
		pLogger->always("Error en la lectura del archivo de configuración.");
		return -1;
	}

	// Se cierra la interfase con el archivo
	fclose(file);
	string temp(buffer, res);
	free(buffer);

	// Se inicia con la carga de las propiedades de configuración
	this->buffer.clear();
	int inicio = 0, index;
	do {
		index = temp.find('\n', inicio + 1);
		if (index < 0)
			break;
		string linea = temp.substr(inicio == 0 ? inicio : inicio + 1, 
			index - (inicio == 0 ? 0 : inicio + 1));
		this->buffer.insert_or_assign(linea.substr(0, linea.find('=')),
			linea.substr(linea.find('=') + 1, linea.size()));
		inicio = index;
	} while (index > 0);

	return 0;
}

std::string CConfiguracion::obtenerConfiguracion(char *llave) 
{
	return buffer[llave].c_str();
}