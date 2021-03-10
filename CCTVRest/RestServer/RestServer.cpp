
// RestServer.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "RestServer.h"
#include "RestServerDlg.h"
#include "Server.h"
#include <plog\Log.h>
#include "include\IVS_SDK.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

std::unique_ptr<Server> p_Server;

// CRestServerApp

BEGIN_MESSAGE_MAP(CRestServerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CRestServerApp construction

CRestServerApp::CRestServerApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CRestServerApp object

CRestServerApp theApp;


// CRestServerApp initialization

BOOL CRestServerApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	InicializacionAuxiliares();

	CRestServerDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
	}


#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

void CRestServerApp::InicializacionAuxiliares()
{

	// Configuración inicial de la bitácora de la aplicación
	plog::init(plog::debug, "bitacora.log", 10000000, 5);
	LOGD << U("Inicio de la aplicación.");

	// Lectura de la configuración de la aplicación
	if (m_Configuracion.lecturaConfiguracion() != 0)
	{
		LOGE << "Error en la carga de la configuración del sistema.";
		return;
	}

	// Modificación del nivel de disparo de la bitácora
	string log = m_Configuracion.consultaParametro(Configuracion::LOG_LEVEL);
	if (log.compare("INFO") == 0)
		plog::get()->setMaxSeverity(plog::info);

	else if (log.compare("ERROR") == 0)
		plog::get()->setMaxSeverity(plog::error);


	// Publicación del servicio web
	string url = "http://";
	string host = m_Configuracion.consultaParametro(Configuracion::HTTP_HOST);
	string port = m_Configuracion.consultaParametro(Configuracion::HTTP_PORT);
	url.append(host).append(":").append(port);

	utility::string_t address(url.length(), L' ');
	copy(url.begin(), url.end(), address.begin());
	uri_builder uri(address);
	uri.append_path(U("server/broker/"));
	auto addr = uri.to_uri().to_string();
	p_Server = std::unique_ptr<Server>(new Server(addr));
	p_Server->open().wait();

	// Inicialización de la interface con el IVS
	IVS_INT32 iRes = IVS_SDK_Init();
	if (iRes == IVS_SUCCEED)
		LOGI << "Se logro inicializar el SDK del IVS.";
	else
		LOGE << "Error en la inicialización del SDK del IVS: " << iRes;

}

