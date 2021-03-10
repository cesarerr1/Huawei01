// DialogoIVS.cpp: archivo de implementación
//

#include "stdafx.h"
#include "BrokerCCTV.h"
#include "DialogoIVS.h"
#include "afxdialogex.h"
#include "resource.h"

#define BUTTON_DLG_IZQUIERDA	WM_APP + 10001
#define BUTTON_DLG_DERECHA		WM_APP + 10002
#define BUTTON_DLG_ARRIBA		WM_APP + 10003
#define BUTTON_DLG_ABAJO		WM_APP + 10004
#define BUTTON_DLG_CENTRO		WM_APP + 10005

#define BUTTON_DLG_ZOOMIN		WM_APP + 10006
#define BUTTON_DLG_ZOOMOUT		WM_APP + 10007
#define BUTTON_DLG_TILTIN		WM_APP + 10008
#define BUTTON_DLG_TILTOUT		WM_APP + 10009

// Cuadro de diálogo de CDialogoIVS

IMPLEMENT_DYNAMIC(CDialogoIVS, CDialogEx)

CDialogoIVS::CDialogoIVS(CConfiguracion *conf,CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_IVS_DIALOG, pParent)
{
	pLogger = Logger::getInstance();
	configuracion = conf;
	login = false;
}

CDialogoIVS::~CDialogoIVS()
{
}

void CDialogoIVS::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IVS_OCXPLAYERCTRL3, m_IVSControl);
	DDX_Control(pDX, IDC_SLIDER_PAN, m_sliderPan);
	DDX_Control(pDX, IDC_CUSTOM_CENTER, m_botonCentro);
	DDX_Control(pDX, IDC_CUSTOM_ZOOMOUT, m_botonZoomOut);
	DDX_Control(pDX, IDC_CUSTOM_ZOOMIN, m_botonZoomIn);
	DDX_Control(pDX, IDC_CUSTOM_TILTOUT, m_botonTiltOut);
	DDX_Control(pDX, IDC_CUSTOM_TILTIN, m_botonTiltIn);
	DDX_Control(pDX, IDC_SLIDER_ZOOM, m_sliderZoom);
	DDX_Control(pDX, IDC_SLIDER_TILT, m_sliderTilt);
}


BEGIN_MESSAGE_MAP(CDialogoIVS, CDialogEx)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_PAN, &CDialogoIVS::OnNMReleasedcaptureSliderPan)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_ZOOM, &CDialogoIVS::OnNMReleasedcaptureSliderZoom)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_TILT, &CDialogoIVS::OnNMReleasedcaptureSliderTilt)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// Controladores de mensajes de CDialogoIVS

void CDialogoIVS::DesplegarCamara(char *camara) {
	char buffer[1024];

	// Se marca la operación a ejecutar
	sprintf_s(buffer, 1024, "Se solicita desplegar la cámara: %s\n", camara);
	pLogger->info(buffer);
	OutputDebugStringA(buffer);
	strcpy_s((char *)this->camara, 1024, camara);

	if (login) {

		sprintf_s(buffer, 1024, "Intentando detener la reproducción del video.");
		OutputDebugStringA(buffer);
		pLogger->info(buffer);
		IVS_INT32 iRet = IVS_SDK_StopRealPlay(sessionID, playerHandler);
		if (IVS_SUCCEED == iRet) {
			sprintf_s(buffer, 1024, "Error al intentar  detener la reproducción del video. %d", iRet);
			OutputDebugStringA(buffer);
			pLogger->info(buffer);
		}

		sprintf_s(buffer, 1024, "Intentando mostrar el stream de la cámara: %s\n", (char *)camara);
		pLogger->info(buffer);
		OutputDebugStringA(buffer);
		IVS_REALPLAY_PARAM playerRequest = { 0 };
		playerRequest.uiProtocolType = 1;
		playerRequest.uiStreamType = STREAM_TYPE_MAIN;
		iRet = IVS_SDK_StartRealPlay(sessionID,
			&playerRequest, camara, m_IVSControl.GetSafeHwnd(), &playerHandler);
		if (IVS_SUCCEED == iRet)
		{
			strcpy_s(this->camara, 1024, camara);
			sprintf_s(buffer, 1024, "%s - Se logro completar el request de la cámara.",
				"BrokerCCTVDlg");
			pLogger->info(buffer);
			strcat_s(buffer, 1024, "\n");
			OutputDebugStringA(buffer);
		}
		else
		{
			sprintf_s(buffer, 1024, "%s - Error en la invocación de la cámara. [%d]",
				"BrokerCCTVDlg", iRet);
			pLogger->error(buffer);
			strcat_s(buffer, 1024, "\n");
			OutputDebugStringA(buffer);
		}
	}
}

BOOL CDialogoIVS::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	char buffer[1024];
	sprintf_s(buffer, 1024, "Se intenta desplegar el broker de CCTV.");
	pLogger->info(buffer);
	strcat_s(buffer, 1024, "\n");
	OutputDebugStringA(buffer);

	// Brush para el fondo del dialogo
	m_brush.CreateSolidBrush(RGB(64, 64, 64));

	// Se modifica el color de algunos de los controles
	CWnd *pWnd = this->GetDlgItem(IDC_STATIC_DESPLAZAMIENTO);
	pWnd->GetDC()->SetBkColor(RGB(64, 64, 64));
	pWnd->Invalidate();
	pWnd->UpdateWindow();

	// Se inicializan los botones y acciones asociadas
	m_botonCentro.SetButtonID(BUTTON_DLG_CENTRO, BUTTON_MODE_PTZ);
	m_botonCentro.RegistrarEventosActivos(MOUSE_LEFT_BUTTON_DOWN | MOUSE_LEFT_BUTTON_UP | WM_MOUSE_MOVE);	
	m_botonCentro.SetWindowPos(NULL, 0, 0, 120, 120, SWP_NOMOVE | SWP_NOZORDER);

	m_botonZoomIn.SetButtonID(BUTTON_DLG_ZOOMIN, BUTTON_MODE_NORMAL);
	m_botonZoomIn.SetButtonIcon(IDI_ICON_ZOOMIN, 32, 32, 24);
	m_botonZoomIn.RegistrarEventosActivos(MOUSE_LEFT_BUTTON_DOWN | MOUSE_LEFT_BUTTON_UP);
	m_botonZoomIn.SetWindowPos(NULL, 0, 0, 30, 30, SWP_NOMOVE | SWP_NOZORDER);

	m_botonZoomOut.SetButtonID(BUTTON_DLG_ZOOMOUT, BUTTON_MODE_NORMAL);
	m_botonZoomOut.SetButtonIcon(IDI_ICON_ZOOMOUT, 32, 32, 24);
	m_botonZoomOut.RegistrarEventosActivos(MOUSE_LEFT_BUTTON_DOWN | MOUSE_LEFT_BUTTON_UP);
	m_botonZoomOut.SetWindowPos(NULL, 0, 0, 30, 30, SWP_NOMOVE | SWP_NOZORDER);

	m_botonTiltIn.SetButtonID(BUTTON_DLG_TILTIN, BUTTON_MODE_NORMAL);
	m_botonTiltIn.SetButtonIcon(IDI_ICON_LENSIN, 32, 32, 24);
	m_botonTiltIn.RegistrarEventosActivos(MOUSE_LEFT_BUTTON_DOWN | MOUSE_LEFT_BUTTON_UP);
	m_botonTiltIn.SetWindowPos(NULL, 0, 0, 30, 30, SWP_NOMOVE | SWP_NOZORDER);

	m_botonTiltOut.SetButtonID(BUTTON_DLG_TILTOUT, BUTTON_MODE_NORMAL);
	m_botonTiltOut.SetButtonIcon(IDI_ICON_LENOUT1, 32, 32, 24);
	m_botonTiltOut.RegistrarEventosActivos(MOUSE_LEFT_BUTTON_DOWN | MOUSE_LEFT_BUTTON_UP);
	m_botonTiltOut.SetWindowPos(NULL, 0, 0, 30, 30, SWP_NOMOVE | SWP_NOZORDER);

	SetWindowTheme(GetDlgItem(IDC_STATIC_DESPLAZAMIENTO)->GetSafeHwnd(), L"", L"");
	GetDlgItem(IDC_STATIC_DESPLAZAMIENTO)->Invalidate();

	m_sliderPan.SetRange(0, 10);
	m_sliderPan.SetPos(5);
	sprintf_s(velocidadPan, 128, "5");

	m_sliderZoom.SetRange(0, 10);
	m_sliderZoom.SetPos(5);
	sprintf_s(velocidadZoom, 128, "5");

	m_sliderTilt.SetRange(0, 10);
	m_sliderTilt.SetPos(5);
	sprintf_s(velocidadTilt, 128, "5");

	IVS_LOGIN_INFO loginData = { 0 };
	loginData.stIP.uiIPType = IP_V4;
	pLogger->info("\nCargando los datos de conexión:\n");
	sprintf_s(buffer, 1024, "IP Servidor: %s\n",
		configuracion->obtenerConfiguracion(CONF_SERVIDORIVS).c_str());
	pLogger->info(buffer);
	strncpy_s(loginData.stIP.cIP, 
		configuracion->obtenerConfiguracion(CONF_SERVIDORIVS).c_str(), 
		IVS_IP_LEN);
	loginData.uiPort = 9900;
	sprintf_s(buffer, 1024, "Usuario: %s\n",
		configuracion->obtenerConfiguracion(CONF_USUARIOIVS).c_str());
	pLogger->info(buffer);
	sprintf_s(buffer, 10124, "Clave: %s\n",
		configuracion->obtenerConfiguracion(CONF_CLAVEIVS).c_str());
	pLogger->info(buffer);
	strncpy_s(loginData.cUserName, 
		configuracion->obtenerConfiguracion(CONF_USUARIOIVS).c_str(), 
		IVS_NAME_LEN);
	strncpy_s(loginData.pPWD, 
		configuracion->obtenerConfiguracion(CONF_CLAVEIVS).c_str(),
		IVS_PWD_LEN);
	OutputDebugStringA("Se intenta acceder al sistema de IVS.\n");
	IVS_INT32 iRet = IVS_SDK_Login(&loginData, &sessionID);
	login = false;
	if (IVS_SUCCEED == iRet) {
		
		// Se intenta mostrar el stream de una cámara
		login = true;
		sprintf_s(buffer, 1024, "Intentando mostrar el stream de la cámara: %s\n", (char *)camara);
		pLogger->info(buffer);
		OutputDebugStringA(buffer);
		IVS_REALPLAY_PARAM playerRequest = { 0 };
		playerRequest.uiProtocolType = 1;
		playerRequest.uiStreamType = STREAM_TYPE_MAIN;
		iRet = IVS_SDK_StartRealPlay(sessionID,
			&playerRequest, camara, m_IVSControl.GetSafeHwnd(), &playerHandler);
		if (IVS_SUCCEED == iRet)
		{
			strcpy_s(this->camara, 1024, camara);
			sprintf_s(buffer, 1024, "%s - Se logro completar el request de la cámara.",
				"BrokerCCTVDlg");
			pLogger->info(buffer);
			strcat_s(buffer, 1024, "\n");
			OutputDebugStringA(buffer);
		}
		else
		{
			sprintf_s(buffer, 1024, "%s - Error en la invocación de la cámara. [%d]",
				"BrokerCCTVDlg", iRet);
			pLogger->error(buffer);
			strcat_s(buffer, 1024, "\n");
			OutputDebugStringA(buffer);
		}

	}
	else {
		sprintf_s(buffer, 1024, "%s - No se logro iniciar sesión en el IVS. [%d]",
			"BrokerCCTVDlg", iRet);
		pLogger->error(buffer);
		strcat_s(buffer, 1024, "\n");
		OutputDebugStringA(buffer);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPCIÓN: las páginas de propiedades OCX deben devolver FALSE
}


BOOL CDialogoIVS::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Agregue aquí su código especializado o llame a la clase base
	IVS_INT32 iRet = 0;
	char buffer[1024];

	switch (pMsg->message)
	{
	case BUTTON_DLG_CENTRO:
		sprintf_s(buffer, 1024, "DialogoIVS INFO: Se selecciono en botón PTZ. [%02x]\n", pMsg->wParam);
		OutputDebugStringA(buffer);
		switch (pMsg->wParam & 0xF0)
		{
			// Se valida la zona en donde se detecto el click
			case 0x00:	// Botón centro
				OutputDebugStringA("DialogoIVS INFO: Se detecto la zona centro.\n");
				break;

			case 0x10:	// Botón arriba
				OutputDebugStringA("DialogoIVS INFO: Se detecto la zona arriba.\n");
				if ((pMsg->wParam & (WM_APP + 0x0F00)) == WM_MOUSE_LEFTBUTTON_DOWN) {
					OutputDebugStringA("DialogoIVS INFO: Se presiono el botón arriba.\n");
					iRet = IVS_SDK_PtzControl(sessionID, camara, PTZ_UP, "2", velocidadPan, &lock);
				}
				else if ((pMsg->wParam & (WM_APP + 0x0F00)) == WM_MOUSE_LEFTBUTTON_UP) {
					OutputDebugStringA("DialogoIVS INFO: Se libero el botón arriba.\n");
					iRet = IVS_SDK_PtzControl(sessionID, camara, PTZ_STOP, "2", velocidadPan, &lock);
				}
				break;

			case 0x20:	// Botón abajo
				OutputDebugStringA("DialogoIVS INFO: Se detecto la zona abajo.\n");
				if ((pMsg->wParam & (WM_APP + 0x0F00)) == WM_MOUSE_LEFTBUTTON_DOWN) {
					OutputDebugStringA("DialogoIVS INFO: Se presiono el botón abajo.\n");
					iRet = IVS_SDK_PtzControl(sessionID, camara, PTZ_DOWN, "2", velocidadPan, &lock);
				}
				else if ((pMsg->wParam & (WM_APP + 0x0F00)) == WM_MOUSE_LEFTBUTTON_UP) {
					OutputDebugStringA("DialogoIVS INFO: Se libero el botón abajo.\n");
					iRet = IVS_SDK_PtzControl(sessionID, camara, PTZ_STOP, "2", velocidadPan, &lock);
				}
				break;

			case 0x30:	// Botón izquierda
				OutputDebugStringA("DialogoIVS INFO: Se detecto la zona izquierda.\n");
				if ((pMsg->wParam & (WM_APP + 0x0F00)) == WM_MOUSE_LEFTBUTTON_DOWN) {
					OutputDebugStringA("DialogoIVS INFO: Se presiono el botón izquierda.\n");
					iRet = IVS_SDK_PtzControl(sessionID, camara, PTZ_LEFT, "2", velocidadPan, &lock);
				}
				else if ((pMsg->wParam & (WM_APP + 0x0F00)) == WM_MOUSE_LEFTBUTTON_UP) {
					OutputDebugStringA("DialogoIVS INFO: Se libero el botón izquierda.\n");
					iRet = IVS_SDK_PtzControl(sessionID, camara, PTZ_STOP, "2", velocidadPan, &lock);
				}
				break;

			case 0x40:	// Botón derecha
				OutputDebugStringA("DialogoIVS INFO: Se detecto la zona derecha.\n");
				if ((pMsg->wParam & (WM_APP + 0x0F00)) == WM_MOUSE_LEFTBUTTON_DOWN) {
					OutputDebugStringA("DialogoIVS INFO: Se presiono el botón derecha.\n");
					iRet = IVS_SDK_PtzControl(sessionID, camara, PTZ_RIGHT, "2", velocidadPan, &lock);
				}
				else if ((pMsg->wParam & (WM_APP + 0x0F00)) == WM_MOUSE_LEFTBUTTON_UP) {
					OutputDebugStringA("DialogoIVS INFO: Se libero el botón derecha.\n");
					iRet = IVS_SDK_PtzControl(sessionID, camara, PTZ_STOP, "2", velocidadPan, &lock);
				}
				break;
			default:
				break;
		}
		break;


	case BUTTON_DLG_ZOOMIN:
		if (pMsg->wParam == WM_MOUSE_LEFTBUTTON_DOWN) {
			OutputDebugStringA("DialogoIVS INFO: Se presiono el botón zoom in.\n");
			iRet = IVS_SDK_PtzControl(sessionID, camara, PTZ_LENS_ZOOM_IN, "2", velocidadZoom, &lock);
		}
		else if (pMsg->wParam == WM_MOUSE_LEFTBUTTON_UP) {
			OutputDebugStringA("DialogoIVS INFO: Se libero el botón zoom in.\n");
			iRet = IVS_SDK_PtzControl(sessionID, camara, PTZ_STOP, "2", velocidadZoom, &lock);
		}
		break;

	case BUTTON_DLG_ZOOMOUT:
		if (pMsg->wParam == WM_MOUSE_LEFTBUTTON_DOWN) {
			OutputDebugStringA("DialogoIVS INFO: Se presiono el botón zoom out.\n");
			iRet = IVS_SDK_PtzControl(sessionID, camara, PTZ_LENS_ZOOM_OUT, "2", velocidadZoom, &lock);
		}
		else if (pMsg->wParam == WM_MOUSE_LEFTBUTTON_UP) {
			OutputDebugStringA("DialogoIVS INFO: Se libero el botón zoom out.\n");
			iRet = IVS_SDK_PtzControl(sessionID, camara, PTZ_STOP, "2", velocidadZoom, &lock);
		}
		break;

	case BUTTON_DLG_TILTIN:
		if (pMsg->wParam == WM_MOUSE_LEFTBUTTON_DOWN) {
			OutputDebugStringA("DialogoIVS INFO: Se presiono el botón tilt in.\n");
			iRet = IVS_SDK_PtzControl(sessionID, camara, PTZ_LENS_FOCAL_NEAT, "2", velocidadTilt, &lock);
		}
		else if (pMsg->wParam == WM_MOUSE_LEFTBUTTON_UP) {
			OutputDebugStringA("DialogoIVS INFO: Se libero el botón tilt in.\n");
			iRet = IVS_SDK_PtzControl(sessionID, camara, PTZ_STOP, "2", velocidadTilt, &lock);
		}
		break;

	case BUTTON_DLG_TILTOUT:
		if (pMsg->wParam == WM_MOUSE_LEFTBUTTON_DOWN) {
			OutputDebugStringA("DialogoIVS INFO: Se presiono el botón tilt out.\n");
			iRet = IVS_SDK_PtzControl(sessionID, camara, PTZ_LENS_FOCAL_FAR, "2", velocidadTilt, &lock);
		}
		else if (pMsg->wParam == WM_MOUSE_LEFTBUTTON_UP) {
			OutputDebugStringA("DialogoIVS INFO: Se libero el botón tilt out.\n");
			iRet = IVS_SDK_PtzControl(sessionID, camara, PTZ_STOP, "2", velocidadTilt, &lock);
		}
		break;

	default:
		return CDialogEx::PreTranslateMessage(pMsg);
	}

	sprintf_s(buffer, 1024, "DialogoIVS INFO: Resultado de la operación: %d\n", iRet);
	OutputDebugStringA(buffer);
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CDialogoIVS::OnNMReleasedcaptureSliderPan(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Agregue aquí su código de controlador de notificación de control
	sprintf_s(velocidadPan, 128, "%d", m_sliderPan.GetPos());
	char buffer[1024];
	sprintf_s(buffer, 1024, "DialogoIVS INFO: Se modifico la velocidad de paneo: %d\n", m_sliderPan.GetPos());
	OutputDebugStringA(buffer);
	*pResult = 0;
}


void CDialogoIVS::OnNMReleasedcaptureSliderZoom(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Agregue aquí su código de controlador de notificación de control
	sprintf_s(velocidadZoom, 128, "%d", m_sliderZoom.GetPos());
	char buffer[1024];
	sprintf_s(buffer, 1024, "DialogoIVS INFO: Se modifico la velocidad de Zoom: %d\n", m_sliderZoom.GetPos());
	OutputDebugStringA(buffer);
	*pResult = 0;
}


void CDialogoIVS::OnNMReleasedcaptureSliderTilt(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Agregue aquí su código de controlador de notificación de control
	sprintf_s(velocidadTilt, 128, "%d", m_sliderTilt.GetPos());
	char buffer[1024];
	sprintf_s(buffer, 1024, "DialogoIVS INFO: Se modifico la velocidad de Tilt: %d\n", m_sliderTilt.GetPos());
	OutputDebugStringA(buffer);
	*pResult = 0;
}


BOOL CDialogoIVS::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Agregue aquí su código de controlador de mensajes o llame al valor predeterminado
	CRect rectPage;
	GetClientRect(rectPage.operator LPRECT());
	pDC->FillRect(rectPage.operator LPRECT(), &m_brush);
	
	return TRUE;
}


HBRUSH CDialogoIVS::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Cambie aquí los atributos de DC necesarios
	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_STATIC_DESPLAZAMIENTO:
	case IDC_SLIDER_PAN:
	case IDC_SLIDER_TILT:
	case IDC_SLIDER_ZOOM:
		pDC->SetBkColor(RGB(64, 64, 64));
		pDC->SetTextColor(RGB(255, 255, 255));
		return m_brush;

	default:
		break;
	}

	// TODO:  Devuelve un pincel diferente si no se desea el predeterminado
	return hbr;
}
