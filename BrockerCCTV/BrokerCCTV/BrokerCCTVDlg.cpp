
// BrokerCCTVDlg.cpp: archivo de implementaci�n
//

#include "stdafx.h"
#include "BrokerCCTV.h"
#include "BrokerCCTVDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include "include/IVS_SDK.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cuadro de di�logo CAboutDlg utilizado para el comando Acerca de

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Datos del cuadro de di�logo
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX/DDV

// Implementaci�n
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cuadro de di�logo de CBrokerCCTVDlg



CBrokerCCTVDlg::CBrokerCCTVDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_BROKERCCTV_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	dlgIVS = NULL;
}

void CBrokerCCTVDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBrokerCCTVDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_IVS, &CBrokerCCTVDlg::OnBnClickedButtonIvs)
END_MESSAGE_MAP()


// Controladores de mensaje de CBrokerCCTVDlg

BOOL CBrokerCCTVDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Agregar el elemento de men� "Acerca de..." al men� del sistema.

	// IDM_ABOUTBOX debe estar en el intervalo de comandos del sistema.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Establecer el icono para este cuadro de di�logo.  El marco de trabajo realiza esta operaci�n
	//  autom�ticamente cuando la ventana principal de la aplicaci�n no es un cuadro de di�logo
	SetIcon(m_hIcon, TRUE);			// Establecer icono grande
	SetIcon(m_hIcon, FALSE);		// Establecer icono peque�o

	// TODO: agregar aqu� inicializaci�n adicional
	
	// Inicializaci�n del logger
	char buffer[1024];
	pLogger = Logger::getInstance();
	pLogger->enableConsoleLogging();
	pLogger->enableFileLogging();

	// Carga de la configuraci�n
	configuracion = new CConfiguracion(pLogger);
	configuracion->cargarConfiguracion();

	// Configuraci�n del servidor TCP
	servidorTCP = new ServidorTCP(pLogger);
	string item = configuracion->obtenerConfiguracion(CONF_PORTADDRTCP);
	int puerto = atoi(item.c_str());
	item = configuracion->obtenerConfiguracion(CONF_TIMEOUTTCP);
	int timeOut = atoi(item.c_str());
	item = configuracion->obtenerConfiguracion(CONF_IPADDRTCP);
	strcpy_s(buffer, 1024, item.c_str());
	servidorTCP->escuchar(buffer, puerto, timeOut);

	pLogger->always("Inicio de carga de modulos.");
	sprintf_s(buffer, 1024, "%s - Arrancando proceso de inicializaci�n de la interfase.", "BrokerCCTVDlg");
	pLogger->info(buffer);
	strcat_s(buffer, 1024, "\n");
	OutputDebugStringA(buffer);

	// Inicializaci�n de la interface relacionada con el IVS
	IVS_INT32 iRet = IVS_SDK_Init();
	if (IVS_SUCCEED == iRet) {
		sprintf_s(buffer, 1024, "%s - Se logro inicializar la interfase con el IVS.", "BrokerCCTVDlg");
		pLogger->info(buffer);
		strcat_s(buffer, 1024, "\n");
		OutputDebugStringA(buffer);
	}
	else {
		sprintf_s(buffer, 1024, "%s - Error en la inicializaci�n de la interface con el IVS [%d]",
			"BrokerCCTVDlg", iRet);
		pLogger->error(buffer);
		strcat_s(buffer, 1024, "\n");
		OutputDebugStringA(buffer);
	}
			
	return TRUE;  // Devuelve TRUE  a menos que establezca el foco en un control
}

void CBrokerCCTVDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// Si agrega un bot�n Minimizar al cuadro de di�logo, necesitar� el siguiente c�digo
//  para dibujar el icono.  Para aplicaciones MFC que utilicen el modelo de documentos y vistas,
//  esta operaci�n la realiza autom�ticamente el marco de trabajo.

void CBrokerCCTVDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Contexto de dispositivo para dibujo

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Centrar icono en el rect�ngulo de cliente
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Dibujar el icono
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// El sistema llama a esta funci�n para obtener el cursor que se muestra mientras el usuario arrastra
//  la ventana minimizada.
HCURSOR CBrokerCCTVDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CBrokerCCTVDlg::OnBnClickedButtonIvs()
{
	// TODO: Agregue aqu� su c�digo de controlador de notificaci�n de control
	DesplegarCamara("09569040000000000101#b6bfedbd2bb84861913ac25d21d88241");
}

void CBrokerCCTVDlg::DesplegarCamara(char *idCamara) {
	char buffer[1024];

	// Se solicita desplegar una c�mara
	sprintf_s(buffer, 1024, "Se solicita desplegar una c�mara: %s\n", idCamara);
	pLogger->info(buffer);
	OutputDebugStringA(buffer);

	if (dlgIVS == NULL) {
		dlgIVS = new CDialogoIVS(configuracion, this);
		dlgIVS->DesplegarCamara(idCamara);
		dlgIVS->DoModal();
		dlgIVS->DestroyWindow();
		delete(dlgIVS);
		dlgIVS = NULL;
	}
	else
		dlgIVS->DesplegarCamara(idCamara);

}

BOOL CBrokerCCTVDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Agregue aqu� su c�digo especializado o llame a la clase base
	char buff[1024];
	switch (pMsg->message) {

	case WM_COMM_DESPLIEGA_CAMARA:

		// Se despliega la informaci�n de la petici�n
		sprintf_s(buff, 1024, "----Se recibio una petici�n de abrir una c�mara: %s----\n", 
			(char *)pMsg->lParam);
		pLogger->info(buff);
		OutputDebugStringA(buff);
		strcpy_s(buff, 1024, (char *)pMsg->lParam);
		free((void *)pMsg->lParam);
		DesplegarCamara(buff);
		return true;

	default:
		break;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CBrokerCCTVDlg::PostNcDestroy()
{
	// TODO: Agregue aqu� su c�digo especializado o llame a la clase base
	OutputDebugStringA("Cierre de la aplicaci�n.\n");
	delete(configuracion);
	servidorTCP->cerrar();
	delete(servidorTCP);
	pLogger->disableLog();
	
	CDialogEx::PostNcDestroy();
}
