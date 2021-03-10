#pragma once
#include "Logger.h"
#include <stdio.h>
#include <WS2tcpip.h>
#include <WinSock2.h>

using namespace CPlusPlusLogging;

class ClienteTCP
{
public:
	int enviar(char *buffer);
	void iniciarAtencion();
	bool isClienteActivo();
	char *getDireccionIP();
	int getPuerto();
	ClienteTCP(SOCKET socket, Logger *logger);
	~ClienteTCP();

protected:
	void atencion(char *msg);
	static DWORD WINAPI procesoCliente(LPVOID param);

protected:
	SOCKET socket;
	HANDLE evtFin;
	HANDLE evtInicio;
	HANDLE hProceso;
	Logger *pLogger;
	char ipAddr[100];
	int port;
	int timeOut;
	bool activo;
};

