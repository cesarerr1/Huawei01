#include "stdafx.h"
#include "ClienteTCP.h"
#include "json\json.h"
#include "DialogoIVS.h"
#include "ServidorTCP.h"
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE		2048

ClienteTCP::ClienteTCP(SOCKET socket, Logger *logger)
{
	this->socket = socket;
	pLogger = logger;
	activo = false;
	socket = INVALID_SOCKET;
	hProceso = NULL;
	evtInicio = NULL;
	evtFin = NULL;
}


ClienteTCP::~ClienteTCP()
{
}

bool ClienteTCP::isClienteActivo()
{
	return activo;
}

char *ClienteTCP::getDireccionIP()
{
	return ipAddr;
}

int ClienteTCP::getPuerto()
{
	return port;
}

void ClienteTCP::iniciarAtencion()
{
	char buffer[1024];

	// Se obtiene la información del cliente remoto
	struct sockaddr name; 
	socklen_t len = sizeof(name);
	getpeername(this->socket, &name, &len);
	inet_ntop(AF_INET, &name, buffer, 1024);
	strcpy_s(this->ipAddr, 100, buffer);

	// Se marca el inicio de las operaciones
	sprintf_s(buffer, 1024, "Se intenta arrancar el proceso de atención del cliente.\n");
	pLogger->info(buffer);
	OutputDebugStringA(buffer);

	// Se inicia la generación del hilo de atención de peticiones
	evtInicio = CreateEvent(NULL, TRUE, FALSE, TEXT("Evento inicialización cliente."));
	evtFin = CreateEvent(NULL, TRUE, FALSE, TEXT("Evento de conclusión cliente."));
	DWORD idProceso;
	hProceso = CreateThread(NULL, 0, ClienteTCP::procesoCliente, this, 0, &idProceso);

	// Se espera la señal de un correcto arranque del proceso
	DWORD evt = WaitForSingleObject(evtInicio, 3000);
	if (evt != 0) {
		sprintf_s(buffer, 1024, "Error en la espera de arranque del proceso.\n");
		pLogger->error(buffer);
		OutputDebugStringA(buffer);
		return;
	}

	// Se completo correctamente el proceso de apertura del puerto
	sprintf_s(buffer, 1024, "Se logro iniciar el proceso de atención del cliente.\n");
	pLogger->info(buffer);
	OutputDebugStringA(buffer);
}

DWORD WINAPI ClienteTCP::procesoCliente(LPVOID param) 
{
	ClienteTCP *cliente = (ClienteTCP *)param;
	char buffer[BUFFER_SIZE];
	cliente->activo = true;

	// Se marca el inicio del proceso de atención
	sprintf_s(buffer, BUFFER_SIZE, "Inicio del proceso de atención por cliente.\n");
	cliente->pLogger->info(buffer);
	OutputDebugStringA(buffer);

	// Se intenta leer el paquete enviado por el cliente
	char temp[BUFFER_SIZE];
	int data = recv(cliente->socket, temp, BUFFER_SIZE, 0);
	temp[data] = '\0';
	
	// Se evalua la recepción de información del cliente
	if (data > 0) {
		// Se atiende la petición recibida
		cliente->atencion(temp);
	}
	else {
		sprintf_s(buffer, BUFFER_SIZE, "Error en la recepción de la información.\n");
		cliente->pLogger->error(buffer);
		OutputDebugStringA(buffer);
	}

	// Se marca el cierre del proceso de atención
	sprintf_s(buffer, BUFFER_SIZE, "Cierre del proceso de atención del cliente.\n");
	cliente->pLogger->info(buffer);
	OutputDebugStringA(buffer);
	cliente->activo = false;

	return 0;
}

void ClienteTCP::atencion(char *msg)
{
	char buffer[BUFFER_SIZE];

	// Se marca el paquete recibido
	sprintf_s(buffer, BUFFER_SIZE, "Se recibio la siguiente cadena: [%s]\n", msg);
	pLogger->info(buffer);
	OutputDebugStringA(buffer);

	// Se intenta procesar el paquete recibido
	Json::Value root;
	Json::Reader reader;
	bool status = reader.parse(msg, root, false);
	if (!status) {
		// Se detecto un error en el procedimiento de parseo
		sprintf_s(buffer, BUFFER_SIZE, "Se detecto un error en el parseo del paquete.\n");
		pLogger->error(buffer);
		OutputDebugStringA(buffer);
		return;
	}

	// Se procesa la instrucción
	Json::Value operacion = root["operacion"];
	Json::Value params = root["parametros"];
	sprintf_s(buffer, 1024, "Se recibio la siguiente instrucción: %s\n", operacion.asString().c_str());
	pLogger->info(buffer);
	OutputDebugStringA(buffer);

	// Se hace el switch de la instrucción
	if (strcmp(operacion.asString().c_str(), "despliegaCamara") == 0) {

		// Se genera la cadena de respuesta
		Json::Value resp;
		Json::StyledWriter writer;
		resp["operacion"] = "despliegaCamara";
		resp["errCode"] = "0000";
		resp["errMsg"] = "OK";
		std::string cadena = writer.write(resp);
		sprintf_s(buffer, 1024, "Cadena a ser enviada: %s", cadena.c_str());
		pLogger->info(buffer);
		OutputDebugStringA(buffer);
		sprintf_s(buffer, 1024, cadena.c_str());
		enviar(buffer);

		// Se marca la operación solicitada
		sprintf_s(buffer, 1024, "Se solicita desplegar una cámara: %s\n", params["camara"].asString().c_str());
		pLogger->info(buffer);
		OutputDebugStringA(buffer);
		char *mem = (char *)malloc(512);
		strcpy_s(mem, 512, params["camara"].asString().c_str());
		AfxGetApp()->GetMainWnd()->PostMessageW(WM_COMM_DESPLIEGA_CAMARA, 0, (LPARAM)mem);

		return;
	}	
}

int ClienteTCP::enviar(char *buffer) {

	char buff[1024];

	// Se marca la operación a ser ejecutada
	sprintf_s(buff, 1024, "Se intentara enviar la siguiente cadena por el canal: %s\n", buffer);
	pLogger->info(buff);
	OutputDebugStringA(buff);

	// Se intenta enviar el buffer por el canal
	int res = send(socket, buffer, (int) strlen(buffer) + 1, 0);
	sprintf_s(buff, 1024, "Se envio el paquete con respuesta[%d]-%d\n", res,
		res >= 0 ? 0 : WSAGetLastError());
	pLogger->info(buff);
	OutputDebugStringA(buff);

	return 0;
}