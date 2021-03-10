#include "stdafx.h"
#include "ServidorTCP.h"
#include "ClienteTCP.h"
#include <list>

#define BUFFER_SIZE		2048

ServidorTCP::ServidorTCP(Logger *logger)
{
	pLogger = logger;
	activo = false;
	socketSrv = INVALID_SOCKET;
	hProceso = NULL;
	evtInicio = NULL;
	evtFin = NULL;
}

ServidorTCP::~ServidorTCP()
{
}

int ServidorTCP::escuchar(char *ipAddr, int port, int timeOut) {

	char buffer[1024];

	// Se marca la operación a ejecutar
	sprintf_s(buffer, 1024, "Se solicita la apertura de la dirección %s:%d - %d\n",
		ipAddr, port, timeOut);
	pLogger->info(buffer);
	OutputDebugStringA(buffer);

	// Se arranca el proceso auxiliar
	strcpy_s(this->ipAddr, 100, ipAddr);
	this->port = port;
	this->timeOut = timeOut;
	evtInicio = CreateEvent(NULL, TRUE, FALSE, TEXT("Evento inicialización."));
	evtFin = CreateEvent(NULL, TRUE, FALSE, TEXT("Evento de conclusión."));
	DWORD idProceso;
	hProceso = CreateThread(NULL, 0, ServidorTCP::procesoServidor, this, 0, &idProceso);
	
	// Se espera la señal de un correcto arranque del proceso
	DWORD evt = WaitForSingleObject(evtInicio, 3000);
	if (evt != 0) {
		sprintf_s(buffer, 1024, "Error en la espera de arranque del proceso.\n");
		pLogger->error(buffer);
		OutputDebugStringA(buffer);
		return -1;
	}

	// Se completo correctamente el proceso de apertura del puerto
	sprintf_s(buffer, 1024, "Se recibio de manera correcta el evento de apertura de socket.\n");
	pLogger->info(buffer);
	OutputDebugStringA(buffer);

	return 0;
}

int ServidorTCP::cerrar() {

	char buffer[1024];

	// Se marca la opeción a ejecutar
	sprintf_s(buffer, 1024, "Se solicita liberar los recursos asociados al socket %s:%d\n",
		ipAddr, port);
	pLogger->info(buffer);
	OutputDebugStringA(buffer);

	// Se espera por la señal de cierre
	activo = false;
	DWORD evt = WaitForSingleObject(evtFin, 3000);
	if (evt != 0) {
		sprintf_s(buffer, 1024, "Error en la espera de cierre del proceso.\n");
		pLogger->error(buffer);
		OutputDebugStringA(buffer);
		return -1;
	}

	return 0;
}

DWORD WINAPI ServidorTCP::procesoServidor(LPVOID param) {

	// Se obtiene el apuntador al servidor
	ServidorTCP *srv = (ServidorTCP *)param;

	// Se valida el estatus del servidor
	char buffer[BUFFER_SIZE];
	if (srv->activo) {
		sprintf_s(buffer, BUFFER_SIZE, "El servidor ya esta activo.");
		srv->pLogger->error(buffer);
		OutputDebugStringA(buffer);
		return 1;
	}

	// Se marca el inicio del proceso auxiliar
	sprintf_s(buffer, BUFFER_SIZE, "Se inicia el proceso auxiliar del servidor %s:%d - %d\n",
		srv->ipAddr, srv->port, srv->timeOut);
	srv->pLogger->info(buffer);
	OutputDebugStringA(buffer);		

	// Inicialización de los sockets
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{	// Error en la inicialización de la interfase de sockets
		sprintf_s(buffer, BUFFER_SIZE, "WSAStartup error: %d\n", iResult);
		srv->pLogger->error(buffer);
		OutputDebugStringA(buffer);
		return 1;
	}
	
	// Se genera el socket para la recepción de peticiones
	struct addrinfo *result = NULL, *ptr = NULL, hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;
	_itoa_s(srv->port, buffer, 10);
	iResult = getaddrinfo(srv->ipAddr, buffer, &hints, &result);
	if (iResult != 0)
	{	// Error en la inicialización de la interfase de sockets
		sprintf_s(buffer, BUFFER_SIZE, "Error en la inicialización del socket: %d\n", iResult);
		srv->pLogger->error(buffer);
		OutputDebugStringA(buffer);
		WSACleanup();
		return 1;
	}
	srv->socketSrv = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (srv->socketSrv == INVALID_SOCKET) {
		sprintf_s(buffer, BUFFER_SIZE, "Error en la generación del socket: %ld\n", WSAGetLastError());
		srv->pLogger->error(buffer);
		OutputDebugStringA(buffer);
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}
	DWORD timeOut = srv->timeOut;
	iResult = setsockopt(srv->socketSrv, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeOut, sizeof(timeOut));
	if (iResult != 0) {
		sprintf_s(buffer, BUFFER_SIZE, "Error en la configuración del socket: %ld\n", WSAGetLastError());
		srv->pLogger->error(buffer);
		OutputDebugStringA(buffer);
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	// Preparación del socket para la escucha
	iResult = bind(srv->socketSrv, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		sprintf_s(buffer, BUFFER_SIZE, "Error en la vinculación del socket: %d\n", WSAGetLastError());
		srv->pLogger->error(buffer);
		OutputDebugStringA(buffer);
		freeaddrinfo(result);
		closesocket(srv->socketSrv);
		WSACleanup();
		return 1;
	}

	if (listen(srv->socketSrv, 10) == SOCKET_ERROR) {
		sprintf_s(buffer, BUFFER_SIZE, "Error al intentar escuchar en el socket: %ld\n", WSAGetLastError());
		srv->pLogger->error(buffer);
		OutputDebugStringA(buffer);
		closesocket(srv->socketSrv);
		WSACleanup();
		return 1;
	}

	// Se envia el aviso de una correcta inicialización
	sprintf_s(buffer, BUFFER_SIZE, "Se completo la inicialización del socket.\n");
	srv->pLogger->info(buffer);
	OutputDebugStringA(buffer);
	SetEvent(srv->evtInicio);
	
	// Se inicia el loop para aceptar conexiones
	srv->activo = true;
	std::list<ClienteTCP *> clientes;
	do {
		sprintf_s(buffer, BUFFER_SIZE, "Iniciando la espera de una conexión.\n");
		srv->pLogger->info(buffer);
		OutputDebugStringA(buffer);

		SOCKET cliente = accept(srv->socketSrv, NULL, NULL);
		if (cliente == INVALID_SOCKET) {
			sprintf_s(buffer, BUFFER_SIZE, "Error al intentar aceptar un cliente.\n");
			srv->pLogger->error(buffer);
			OutputDebugStringA(buffer);
		}
		else {
			sprintf_s(buffer, BUFFER_SIZE, "Se logro aceptar la petición de conexión del cliente.\n");
			srv->pLogger->error(buffer);
			OutputDebugStringA(buffer);

			// Se genera una interface de atención alterna
			ClienteTCP *local = new ClienteTCP(cliente, srv->pLogger);
			clientes.push_front(local);
			local->iniciarAtencion();
		}

		// Se hace el barrido de las interfaces con los clientes disponibles
		for (std::list<ClienteTCP *>::iterator it = clientes.begin(); it != clientes.end(); ++it) {
			if (!((ClienteTCP *)*it)->isClienteActivo())
			{
				
			}
		}
		

	} while (srv->activo);

	// Se envia el aviso de que se concluyo el proceso
	SetEvent(srv->evtFin);

	return 0;
}