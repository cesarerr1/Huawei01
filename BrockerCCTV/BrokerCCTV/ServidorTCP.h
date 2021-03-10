#pragma once
#include "Logger.h"
#include "Configuracion.h"
#include <stdio.h>
#include <WS2tcpip.h>
#include <WinSock2.h>

// Definición de los mensajes que pueden ser enviados por la interfase
#define WM_COMM_DESPLIEGA_CAMARA	WM_APP + 0x0100

using namespace CPlusPlusLogging;

class ServidorTCP
{
public:
	int cerrar();
	void atencion(SOCKET cliente, char *mensaje);
	int escuchar(char *ipAddr, int port, int timeOut);
	ServidorTCP(Logger *logger);
	~ServidorTCP();

protected:
	static DWORD WINAPI procesoServidor(LPVOID param);

protected:
	SOCKET socketSrv;
	HANDLE evtFin;
	HANDLE evtInicio;
	HANDLE hProceso;
	Logger *pLogger;

	char ipAddr[100];
	int port;
	int timeOut;
	bool activo;
};

