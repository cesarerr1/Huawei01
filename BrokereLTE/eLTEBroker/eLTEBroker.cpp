
// eLTEBroker.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "eLTEBroker.h"
#include "eLTEBrokerDlg.h"
#include "plog\Log.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

// CeLTEBrokerApp

BEGIN_MESSAGE_MAP(CeLTEBrokerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CeLTEBrokerApp construction

CeLTEBrokerApp::CeLTEBrokerApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CeLTEBrokerApp object

CeLTEBrokerApp theApp;


// CeLTEBrokerApp initialization

BOOL CeLTEBrokerApp::InitInstance()
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

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Activate "Windows Native" visual manager for enabling themes in MFC controls
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	InicializacionAuxiliares();
	LOGD << "Intentando generar el dialogo principal de la aplicación.";

	CeLTEBrokerDlg dlg;
	m_pMainWnd = &dlg;
	dlg.seteLTESesion(p_Session);
	dlg.setConfiguracion(&m_Configuracion);
	INT_PTR nResponse = dlg.DoModal();

	LOGD << "Solicitando el cierre de los procesos auxiliares.";
	CierreAuxiliares();

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
		TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}

	// Delete the shell manager created above.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

void CeLTEBrokerApp::InicializacionAuxiliares()
{
	// Configuraión inicial de la bitácora de la aplicacion
	plog::init(plog::debug, "bitacora.log", 10000000, 5);
	LOGD << "Inicio de la aplicación.";

	// Lectura del archivo de configuración
	if (m_Configuracion.lecturaConfiguracion() != 0)
	{
		LOGE << "Error en la lectura de la configuración del sistema.";
		return;
	}

	// Modificación del nivel de disparo de la bitácora
	string log = m_Configuracion.consultaParametro(Configuracion::LOG_LEVEL);
	if (log.compare("INFO") == 0)
		plog::get()->setMaxSeverity(plog::info);
	else if (log.compare("ERROR") == 0)
		plog::get()->setMaxSeverity(plog::error);

	string hostLTE = m_Configuracion.consultaParametro(Configuracion::ELTE_HOST);
	string portLTE = m_Configuracion.consultaParametro(Configuracion::ELTE_PORT);
	string localIP = m_Configuracion.consultaParametro(Configuracion::LOCAL_IP);
	string userLTE = m_Configuracion.consultaParametro(Configuracion::ELTE_USER);
	string pwdLTE = m_Configuracion.consultaParametro(Configuracion::ELTE_PWD);
	int port = 5060;

	try
	{
		port = stoi(portLTE, nullptr, 0);
		LOGD << "Se detecto la configuración del puerto: " << port;
	}
	catch (invalid_argument ex)
	{
		LOGE << "Argumento invalido para el puerto eLTE. " << portLTE << "\n" << ex.what();
		stringstream buffer;
		buffer << "Argumento invalido para el puerto eLTE: " << portLTE << "\n" << ex.what() << endl;
		CStringW msg(buffer.str().c_str());
		AfxMessageBox(msg);
	}
	catch (out_of_range ex)
	{
		LOGE << "Argumento fuera de rango para el puerto eLTE. " << portLTE << "\n" << ex.what();
		stringstream buffer;
		buffer << "Argumento fuera de rango para el puerto eLTE: " << portLTE << "\n" << ex.what() << endl;
		CStringW msg(buffer.str().c_str());
		AfxMessageBox(msg);
	}

	p_Session = new eLTESession(hostLTE, port, localIP);
	
	// Publicación del servicio web
	string url = "http://";
	string host = m_Configuracion.consultaParametro(Configuracion::HTTP_HOST);
	string portS = m_Configuracion.consultaParametro(Configuracion::HTTP_PORT);
	url.append(host).append(":").append(portS);
	LOGI << "Publicando interface REST en: " << url;

	// Preparación de la url de publicación
	utility::string_t address(url.length(), L' ');
	copy(url.begin(), url.end(), address.begin());
	uri_builder uri(address);
	uri.append_path(U("server/broker/"));
	auto addr = uri.to_uri().to_string();

	p_Server = std::unique_ptr<Server>(new Server(addr, p_Session, &m_Configuracion));
	int resp = p_Server->open();
	if (resp != 0)
	{
		LOGE << "Error en la inicialización del servidor REST. " << p_Server->getErrMsg();
		UINT dlgType = MB_APPLMODAL | MB_OK | MB_ICONSTOP;
		CStringW wmsg(p_Server->getErrMsg().c_str());
		AfxMessageBox(wmsg);
		return;
	}
}

void CeLTEBrokerApp::CierreAuxiliares()
{

}