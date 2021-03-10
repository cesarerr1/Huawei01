
// ModuloCCTVDlg.cpp: archivo de implementación
//

#include "stdafx.h"
#include "ModuloCCTV.h"
#include "ModuloCCTVDlg.h"
#include "afxdialogex.h"
#include <list>
#include "include/IVS_SDK.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Cuadro de diálogo CAboutDlg utilizado para el comando Acerca de

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Datos del cuadro de diálogo
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX/DDV

// Implementación
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


// Cuadro de diálogo de CModuloCCTVDlg

CModuloCCTVDlg::CModuloCCTVDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MODULOCCTV_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CModuloCCTVDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IVS_OCXPLAYERCTRLMAIN, cMainPlayer);
}

BEGIN_MESSAGE_MAP(CModuloCCTVDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CModuloCCTVDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// Controladores de mensaje de CModuloCCTVDlg

BOOL CModuloCCTVDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Agregar el elemento de menú "Acerca de..." al menú del sistema.

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

	// Establecer el icono para este cuadro de diálogo.  El marco de trabajo realiza esta operación
	//  automáticamente cuando la ventana principal de la aplicación no es un cuadro de diálogo
	SetIcon(m_hIcon, TRUE);			// Establecer icono grande
	SetIcon(m_hIcon, FALSE);		// Establecer icono pequeño

	// TODO: agregar aquí inicialización adicional
	pLogger = Logger::getInstance();
	pLogger->enableConsoleLogging();
	pLogger->enableFileLogging();
	char buffer[1024];
	pLogger->always("Inicio del procedimiento.");
	sprintf_s(buffer, 1024, "%s - Arrancando proceso de inicialización de la interfase.", "ModuloCCTVDlg");
	pLogger->info(buffer);
	
	// Inicialización de la interface relacionada con el IVS
	IVS_INT32 iRet = IVS_SDK_Init();
	if (IVS_SUCCEED == iRet) {
		sprintf_s(buffer, 1024, "%s - Se logro inicializar la interfase con el IVS.", "ModuloCCTVDlg");
		pLogger->info(buffer);
	}		
	else {
		sprintf_s(buffer, 1024, "%s - Error en la inicialización de la interface con el IVS [%d]",
			"ModuloCCTVDlg", iRet);
		pLogger->error(buffer);
	}
	
	return TRUE;  // Devuelve TRUE  a menos que establezca el foco en un control
}

void CModuloCCTVDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// Si agrega un botón Minimizar al cuadro de diálogo, necesitará el siguiente código
//  para dibujar el icono.  Para aplicaciones MFC que utilicen el modelo de documentos y vistas,
//  esta operación la realiza automáticamente el marco de trabajo.

void CModuloCCTVDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Contexto de dispositivo para dibujo

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Centrar icono en el rectángulo de cliente
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

// El sistema llama a esta función para obtener el cursor que se muestra mientras el usuario arrastra
//  la ventana minimizada.
HCURSOR CModuloCCTVDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CModuloCCTVDlg::OnBnClickedOk()
{
	// Se intenta logear el sistema en el IVS
	IVS_LOGIN_INFO loginData = { 0 };
	loginData.stIP.uiIPType = IP_V4;
	strncpy_s(loginData.stIP.cIP, "172.17.101.2", IVS_IP_LEN);
	loginData.uiPort = 9900;	
	strncpy_s(loginData.cUserName, "promad", IVS_NAME_LEN);
	strncpy_s(loginData.pPWD, "Huawei123", IVS_PWD_LEN);
	IVS_INT32 iRet = IVS_SDK_Login(&loginData, &sessionID);
	char buffer[1024];
	if (IVS_SUCCEED == iRet) {
		IVS_UINT32 uiReqNum = 10;		//Numero de camaras a ser solicitadas
		// Calculate the buffer size. IVS_CAMERA_BRIEF_INFO_LIST contains one IVS_CAMERA_BRIEF_INFO, so the multiplier is (uiReqNum-1)
		IVS_UINT32 uiRsqBufSize = sizeof(IVS_CAMERA_BRIEF_INFO_LIST) + (uiReqNum - 1) * sizeof(IVS_CAMERA_BRIEF_INFO);
		IVS_CAMERA_BRIEF_INFO_LIST* pCameraInfoList = (IVS_CAMERA_BRIEF_INFO_LIST*)(new IVS_CHAR[uiRsqBufSize]);
		if (pCameraInfoList == NULL)	//The pointer is null
			memset(pCameraInfoList, 0, uiRsqBufSize);
		IVS_INDEX_RANGE IndexRange = { 1, uiReqNum };	//Query 1-100 camera devices
		char camara[1024];
		
														// Se obtiene la lista de cámaras
		IVS_INT32 iRet = IVS_SDK_GetDeviceList(sessionID, DEVICE_TYPE_CAMERA, 
			&IndexRange, pCameraInfoList, uiRsqBufSize);
		if (IVS_SUCCEED == iRet)
		{
			IVS_UINT32 uiNum = (pCameraInfoList->stIndexRange.uiToIndex - pCameraInfoList->stIndexRange.uiFromIndex) + 1;
			uiNum = (uiNum > pCameraInfoList->uiTotal) ? pCameraInfoList->uiTotal : uiNum;

			for (IVS_UINT32 i = 0; i<uiNum; i++)
			{
				//Save the camera list
				if (pCameraInfoList->stCameraBriefInfo[i].uiStatus == DEV_STATUS_ONLINE)
					strncpy_s(camara, pCameraInfoList->stCameraBriefInfo[i].cCode, 1024);
				sprintf_s(buffer, 1024, "%s - Datos de la cámara. [%d][%d][%d][%s]",
					"ModuloCCTVDlg", i, 
					pCameraInfoList->stCameraBriefInfo[i].uiCameraStatus,
					pCameraInfoList->stCameraBriefInfo[i].uiStatus,
					pCameraInfoList->stCameraBriefInfo[i].cCode);
				pLogger->info(buffer);
			}

			// Release the memory
			delete[] pCameraInfoList;
			pCameraInfoList = NULL;
		}

		// Se intenta mostrar el stream de una cámara
		IVS_REALPLAY_PARAM playerRequest = { 0 };
		playerRequest.uiProtocolType = 1;
		playerRequest.uiStreamType = STREAM_TYPE_MAIN;
		IVS_ULONG playerHandler = 0;
		iRet = IVS_SDK_StartRealPlay(sessionID,
			&playerRequest, camara, cMainPlayer.GetSafeHwnd(), &playerHandler);
		if (IVS_SUCCEED == iRet)
		{
			sprintf_s(buffer, 1024, "%s - Se logro completar el request de la cámara.",
				"ModuloCCTVDlg");
			pLogger->info(buffer);
		}
		else 
		{
			sprintf_s(buffer, 1024, "%s - Error en la invocación de la cámara. [%d]", 
				"ModuloCCTVDlg", iRet);
			pLogger->error(buffer);
		}
	}
	else {
		sprintf_s(buffer, 1024, "%s - No se logro iniciar sesión en el IVS. [%d]",
			"ModuloCCTVDlg", iRet);
		pLogger->error(buffer);
	}
	
}
