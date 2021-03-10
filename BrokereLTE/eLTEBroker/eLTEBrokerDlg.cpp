
// eLTEBrokerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "eLTEBroker.h"
#include "eLTEBrokerDlg.h"
#include "afxdialogex.h"
#include "plog\Log.h"
#include "DialogLlamada.h"
#include "DialogMensaje.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define ICONO_USUARIO	0
#define ICONO_TELEFONO	1
#define ICONO_RADIO		2
#define ICONO_CAMARA	3
#define ICONO_BROWSER	4
#define ICONO_GRUPO		5

#define POST_INIT_DLG	WM_APP | 0x8000

#define VIDEO_REQ_READY	(WM_USER+101)

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
//	virtual void OnOK();
//	virtual void OnCancel();
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


// CeLTEBrokerDlg dialog



CeLTEBrokerDlg::CeLTEBrokerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ELTEBROKER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	p_Configuracion = NULL;
	p_Session = NULL;
	pl_Usuarios = NULL;
	pl_Grupos = NULL;
}

void CeLTEBrokerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DISPOSITIVOS, c_dispositivos);
	DDX_Control(pDX, IDC_BUTTON_LISTADO, b_Listado);
	DDX_Control(pDX, IDC_BUTTON_SESION, b_Sesion);
	DDX_Control(pDX, IDC_STATIC_STATUSSESION, s_Status);
	DDX_Control(pDX, IDC_COMBO_RECURSOS, c_TRecruso);
}

BEGIN_MESSAGE_MAP(CeLTEBrokerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_WM_DESTROY()
ON_NOTIFY(NM_RCLICK, IDC_LIST_DISPOSITIVOS, &CeLTEBrokerDlg::OnRclickListDispositivos)
ON_CBN_SELCHANGE(IDC_COMBO_RECURSOS, &CeLTEBrokerDlg::OnSelchangeComboRecursos)
ON_BN_CLICKED(IDC_BUTTON_LISTADO, &CeLTEBrokerDlg::OnBnClickedButtonListado)
ON_BN_CLICKED(IDC_BUTTON_SESION, &CeLTEBrokerDlg::OnBnClickedButtonSesion)
ON_MESSAGE(VIDEO_REQ_READY, &CeLTEBrokerDlg::OnVideoReqReady)
END_MESSAGE_MAP()


// CeLTEBrokerDlg message handlers

BOOL CeLTEBrokerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	d_Video = NULL;

	initListViewColumn();
	c_TRecruso.SetCurSel(1);
	PostMessageW(POST_INIT_DLG);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CeLTEBrokerDlg::postInitView()
{
	LOGD << "Se solicita la inicialiación del dialogo postInit.";

	if (p_Configuracion)
	{
		LOGD << "Inicialización de la sesión eLTE asociada.";

		s_Status.SetWindowTextW(_T("Intentando logear..."));
		string hostLTE = p_Configuracion->consultaParametro(Configuracion::ELTE_HOST);
		string portLTE = p_Configuracion->consultaParametro(Configuracion::ELTE_PORT);
		string localIP = p_Configuracion->consultaParametro(Configuracion::LOCAL_IP);
		string userLTE = p_Configuracion->consultaParametro(Configuracion::ELTE_USER);
		string pwdLTE = p_Configuracion->consultaParametro(Configuracion::ELTE_PWD);
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

		if (p_Session != NULL && p_Session->beginSession(userLTE, pwdLTE) == 0)
		{
			LOGD << "Se logro enviar el inicio de sesión.";
		}
		else {
			LOGE << "Error en el inicio de sesión." << p_Session->getErrorMessage();
			stringstream buffer;
			buffer << "Error en el inicio de sesión.\n" << p_Session->getErrorMessage() << endl;
			CStringW msg(buffer.str().c_str());
			s_Status.SetWindowTextW(_T("Error conexión"));
			AfxMessageBox(msg);

			c_dispositivos.InsertItem(0, _T("Prueba"), 1);
		}
	}
	else
	{
		s_Status.SetWindowTextW(_T("Error conexión"));
		LOGE << "No se cuenta con una configuración válida.";
		stringstream buffer;
		buffer << "No se cuenta con una configuración válida." << endl;
		CStringW msg(buffer.str().c_str());
		AfxMessageBox(msg);
	}
}

void CeLTEBrokerDlg::initListViewColumn()
{
	LOGD << "Solicitando modificar las columnas del listado de dispositivos.";

	HWND listWnd = c_dispositivos.GetSafeHwnd();

	LVCOLUMN lvc;
	WCHAR szText[256];
	
	for (int iCol = 0; iCol < 4; iCol++)
	{
		lvc.iSubItem = iCol;
		lvc.pszText = szText;
		lvc.cx = 100;
		lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

		switch (iCol)
		{
		case 0:
			lvc.fmt = LVCFMT_LEFT;
			lvc.mask = lvc.mask | LVCF_IMAGE;
			wcscpy_s(szText, _T("Type"));
			lvc.cx = 200;
			break;

		case 1:
			lvc.fmt = LVCFMT_LEFT;
			wcscpy_s(szText, _T("ID"));
			break;

		case 2:
			lvc.fmt = LVCFMT_LEFT;
			lvc.mask = lvc.mask | LVCF_IMAGE;
			wcscpy_s(szText, _T("Status"));
			break;

		case 3:
			lvc.fmt = LVCFMT_LEFT;
			wcscpy_s(szText, _T("Name"));
			lvc.cx = 200;
			break;

		default:
			lvc.fmt = LVCFMT_LEFT;
			wcscpy_s(szText, _T("Prueba"));
			break;
		}
		ListView_InsertColumn(listWnd, iCol, &lvc);
	}

	LOGD << "Cargando el listado de imagenes disponibles para el listado de usuarios.";

	l_iconos.Create(24, 24, ILC_COLOR, 2, 2);
	l_iconos.Add(AfxGetApp()->LoadIconW(IDI_ICON_USER));
	l_iconos.Add(AfxGetApp()->LoadIconW(IDI_ICON_PHONEUSER));
	l_iconos.Add(AfxGetApp()->LoadIconW(IDI_ICON_RADIO));
	l_iconos.Add(AfxGetApp()->LoadIconW(IDI_ICON_CAMERA));
	l_iconos.Add(AfxGetApp()->LoadIconW(IDI_ICON_BROWSER));
	l_iconos.Add(AfxGetApp()->LoadIconW(IDI_ICON_GROUP));

	c_dispositivos.SetImageList(&l_iconos, LVSIL_SMALL);
}

void CeLTEBrokerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CeLTEBrokerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CeLTEBrokerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CeLTEBrokerDlg::setConfiguracion(Configuracion* configuracion)
{
	LOGD << "Se carga la configuración de la aplicación.";
	p_Configuracion = configuracion;
}

void CeLTEBrokerDlg::seteLTESesion(eLTESession *pSesion)
{
	LOGD << "Se carga la interface con la sesión eLTE.";
	p_Session = pSesion;
}

BOOL CeLTEBrokerDlg::DestroyWindow()
{
	LOGD << "Se detecto el cierre del dialogo principal.";

	if (p_Session != NULL)
	{
		LOGD << "Solicitando la liberación de los recursos asociados al dialogo.";
		p_Session->closeSession();
		p_Session->releaseResources();
		delete p_Session;
	}
	liberarListaRecursos(-1);

	return CDialogEx::DestroyWindow();
}


BOOL CeLTEBrokerDlg::PreTranslateMessage(MSG* pMsg)
{
	switch (pMsg->message)
	{
	case POST_INIT_DLG:
		postInitView();
		break;

	case ELTE_EVT_MSG:
		LOGD << "Se tiene una notificación de la sesión eLTE: " << pMsg->wParam << "\n" << 
			(pMsg->lParam != NULL ? (char *)pMsg->lParam : "ERROR / sin mensaje.");
		if (pMsg->lParam != NULL)
		{
			map<string, string> *info = p_Session->parseoXML((char *)pMsg->lParam);
			if (info == NULL)
			{
				LOGE << "Error en el parseo de la estructura XML. " << p_Session->getErrorMessage();
			}
			else
			{
				mensajeSesioneLTE(pMsg->wParam, info);
				info->clear();
				delete(info);
			}
		}
		else
			LOGE << "No se recibio la estructura con la información del status.";

		if (pMsg->lParam != NULL)
			free((void *)pMsg->lParam);
		break;

	default:
		break;
	}

	
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CeLTEBrokerDlg::mensajeSesioneLTE(WPARAM message, map<string, string> *info)
{
	LOGD << "Se atiende el mensaje recibido de la sesión eLTE. " << message;

	switch (message)
	{
	case ELTE_Event_NotifyProvisionAllResync:
		break;

	case ELTE_Event_NotifyModuleStatus:
		return statusModulo(info);

	case ELTE_Event_NotifyResourceStatus:
		return statusRecurso(info);

	case ELTE_Event_NotifyP2pvideocallStatus:
		LOGD << "Notificación de video.";
		LOGD << "CallStatus: " << (*info)["CallStatus"];
		LOGD << "Callee: " << (*info)["Callee"];
		LOGD << "Caller: " << (*info)["Caller"];
		s_callStatus = (*info)["CallStatus"];
		s_calleE = (*info)["Callee"];
		s_calleR = (*info)["Caller"];
		PostMessage(VIDEO_REQ_READY);
		return;

	default:
		break;
	}

}

void CeLTEBrokerDlg::statusRecurso(map<string, string> *info)
{
	LOGD << "Se atiende la notificación de cambio de status.";
	
	int statusType = 0;
	int statusValue = 0;
	try
	{
		if (info->count("StatusType") > 0)
			statusType = stoi((*info)["StatusType"], nullptr, 0);
		else
		{
			LOGE << "No se cuenta con el tipo de status a procesar.";
			return;
		}

		if (info->count("StatusValue") > 0)
			statusValue = stoi((*info)["StatusValue"], nullptr, 0);
		else
		{
			LOGE << "No se cuenta con el valor del status a reportar.";
			return;
		}

	}
	catch (invalid_argument ex)
	{
		LOGE << "Error en la conversión de los status a procesar. " << ex.what();
	}
	catch (out_of_range ex)
	{
		LOGE << "Error en la conversión de los status a procesar." << ex.what();
	}

	switch (statusType)
	{
	case 3:	
		LOGD << "Indicates the group call status, which is GRPCALLSTATUS.";
		break;

	case 8:
		LOGD << "Indicates the resource ID, which is RESORCEID.";
		break;

	case 9: 
		LOGD << "Indicates the window ID of the video in the multi - pane display mode, which is DEVICEID.";
		break;

	case 10:
		LOGD << "Indicates whether the resource is selected, which is RESSELECTSTATUS.";
		break;

	case 11:
		LOGD << "Indicates whether the resource has joined this resource group, which is RESASSIGNSTATUS.";
		break;
			
	case 12: 
		LOGD << "Indicates whether the resource is available, which is RESTXSTATUS.";
		break;

	case 13: 
		LOGD << "Indicates whether the resource is being recorded, which is RESLOGGINGSTATUS.";
		break;
			
	case 14: 
		LOGD << "Indicates whether the resource is listening, which is RESDLSTATUS.";
		break;

	case 15:
		LOGD << "Indicates whether the resource has registered through proxy, which is RESREGSTATUS_PROXY.";
		if (statusValue == 4011)
		{
			LOGD << "Se logro iniciar sesión correctamente.";
			CStringW msg("Se logro iniciar sesión correctamente.");
			p_Session->setStatus(true);
			AfxMessageBox(msg);
			p_Session->triggerStatusReport();
			s_Status.SetWindowTextW(_T("Conectado"));
			listarRecursos();
		}
		else if (statusValue == 4017 && p_Session != NULL && p_Session->isActivo())
		{
			LOGE << "Se detecto el cierre de la sesión activa.";
			switch(AfxMessageBox(
				_T("Se detecto el cierre de la sesión activa.\n¿Desea reintentar la conexión?"), 
				MB_RETRYCANCEL))
			{
			case IDRETRY:
				LOGD << "Reintentando la conexión con el servidor.";
				if (p_Session->reconnectSession() == 0)
				{
					LOGD << "Se logro enviar el inicio de sesión.";
				}
				else {
					LOGE << "Error en el inicio de sesión." << p_Session->getErrorMessage();
					stringstream buffer;
					buffer << "Error en el inicio de sesión.\n" << p_Session->getErrorMessage() << endl;
					CStringW msg(buffer.str().c_str());
					AfxMessageBox(msg);
				}
				break;
			}
		}
		break;

	case 16:
		LOGD << "Indicates whether the resource has registered directly, which is RESREGSTATUS_DIRECT.";
		break;

	case 17:
		LOGD << "Indicates the ID of the group that the resouce has joined, which is ATTACHINGGROUP.";
		break;

	case 18: 
		LOGD << "Indicates the user status, which is notified by the BCC. USERSTATUS";
		break;

	case 19: 
		LOGD << "Indicates the user GPS state. USERGPSSTATUS";
		break;

	case 20: 
		LOGD << "Indicates the user listening state. USERDLSTATUS";
		break;

	case 21: 
		LOGD << "Indicates the dynamic regrouping state of the user. USERDGNASTATUS";
		break;

	case 22: 
		LOGD << "Indicates the video distribution state. VIDEODISPATCHSTATUS";
		break;

	case 23: 
		LOGD << "Indicates the muting state. MUTESTATUS";
		break;

	case 24: 
		LOGD << "Indicates the patch operation state. GRPPATCHSTATUS";
		break;

	default:
		break;
	}

}

void CeLTEBrokerDlg::statusModulo(map<string, string> *info)
{
	LOGD << "Se atiende la notificación de cambio de status.";

	int statusType = 0;
	int statusValue = 0;
	try
	{
		if (info->count("StatusType") > 0)
			statusType = stoi((*info)["StatusType"], nullptr, 0);
		else
		{
			LOGE << "No se cuenta con el tipo de status a procesar.";
			return;
		}

		if (info->count("StatusValue") > 0)
			statusValue = stoi((*info)["StatusValue"], nullptr, 0);
		else
		{
			LOGE << "No se cuenta con el valor del status a reportar.";
			return;
		}

	}
	catch (invalid_argument ex)
	{
		LOGE << "Error en la conversión de los status a procesar. " << ex.what();
	}
	catch (out_of_range ex)
	{
		LOGE << "Error en la conversión de los status a procesar." << ex.what();
	}
}

void CeLTEBrokerDlg::liberarListaRecursos(int tipo)
{
	LOGD << "Se solicita liberar los recursos asociados a las listas: " << tipo;

	if ((tipo == 0 || tipo < 0) && pl_Grupos != NULL)
	{
		LOGD << "Liberando los recursos asociados a la lista de grupos.";
		for (list<map<string, string>*>::iterator it = pl_Grupos->begin();
			it != pl_Grupos->end(); it++)
		{
			(*it)->clear();
			delete (*it);
		}
		pl_Grupos->clear();
		delete pl_Grupos;
		pl_Grupos = NULL;
	}

	if ((tipo == 1 || tipo < 0) && pl_Usuarios != NULL)
	{
		LOGD << "Liberando los recursos asociados a la lista de usuarios.";
		for (list<map<string, string>*>::iterator it = pl_Usuarios->begin();
			it != pl_Usuarios->end(); it++)
		{
			(*it)->clear();
			delete (*it);
		}
		pl_Usuarios->clear();
		delete pl_Usuarios;
		pl_Usuarios = NULL;
	}

}

void CeLTEBrokerDlg::listarRecursos()
{
	int seleccion = c_TRecruso.GetCurSel();
	LOGD << "Se solicita listar los recursos registrados en la plataforma: " << seleccion;

	liberarListaRecursos(seleccion);
	list<map<string, string>*> *lista;
	switch (seleccion)
	{
	case 0:
		LOGD << "Se solicita listar los grupos registrados en la plataforma.";
		lista = pl_Grupos = p_Session->listGroups();
		if (lista != NULL)
			pl_Usuarios = p_Session->listUsers();

		break;
	case 1:
		LOGD << "Se solicita listar los usuarios registrados en la plataforma.";
		lista = pl_Usuarios = p_Session->listUsers();
		if (lista != NULL)
			pl_Grupos = p_Session->listGroups();
		break;
	default:
		AfxMessageBox(_T("Opción no reconocida."));
		return;
	}

	
	if (lista != NULL)
	{
		c_dispositivos.DeleteAllItems();
		int index = 0;
		if (seleccion == 0)
		{
			LOGD << "Listando los grupos.";
			for (list<map<string, string>*>::iterator it = lista->begin();
				it != lista->end(); it++)
			{
				for (int cont = 0; cont < 4; cont++)
				{
					string categoria("Unknown");
					int icon = ICONO_GRUPO;
					switch (cont)
					{
					case 0:
						try
						{
							int value = stoi(((**it)["GroupCategory"]), nullptr, 0);
							categoria = p_Session->identificarCategoriaGrupo(value);
						}
						catch (invalid_argument ex)
						{
							LOGE << "Argumento invalido para la categoria. " << ((**it)["GroupCategory"]) << "\n" << ex.what();
						}
						catch (out_of_range ex)
						{
							LOGE << "Argumento fuera de rango para la categoria. " << ((**it)["GroupCategory"]) << "\n" << ex.what();
						}
						c_dispositivos.InsertItem(
							LVFIF_TEXT | LVIF_IMAGE | LVIF_PARAM,
							index, CA2W(categoria.c_str()), 0, 0, icon, (LPARAM)*it);
						break;
					case 1:
						c_dispositivos.SetItemText(index, cont, CA2W(((**it)["GroupID"]).c_str()));
						break;
					case 2:
						c_dispositivos.SetItemText(index, cont, _T("?"));
						break;
					case 3:
						c_dispositivos.SetItemText(index, cont, CA2W(((**it)["GroupName"]).c_str()));
						break;
					default:
						break;
					}

				}
				index++;
			}
		}

		else if (seleccion == 1)
		{
			LOGD << "Listando los usuarios.";
			for (list<map<string, string>*>::iterator it = lista->begin();
				it != lista->end(); it++)
			{
				for (int cont = 0; cont < 4; cont++)
				{
					string categoria("Unknown");
					int icon = 0;
					switch (cont)
					{
					case 0:
						try
						{
							int value = stoi(((**it)["UserCategory"]), nullptr, 0);
							switch (value)
							{
							case 0: //DISPATCHER indicates a DC user.
							case 4: // PLMNUSER indicates a PLMN user.
							case 50: // ALLTYPEUSER indicates a user of any user type.
							case 255: // OTHERUSER indicates a user whose type is not defined.
								icon = ICONO_USUARIO;
								break;
							case 1: // FIXEDCAMERA indicates a fixed camera.
								icon = ICONO_CAMARA;
								break;
							case 2: // PSTNUSER indicates a PSTN user.
								icon = ICONO_TELEFONO;
								break;
							case 3: // TETRAUSER indicates a TETRA user.
							case 5: // EXTERNALPTT indicates an external PTT user.
							case 9: // PTTUSER indicates a PTT user.
								icon = ICONO_RADIO;
								break;
							case 6: // SDKUSER indicates an SDK gateway internal user.
							case 7: // APPUSER indicates an tAPP user.
							case 8: // UELOGINUSER indicates a logged - in terminal user.
								icon = ICONO_BROWSER;
								break;
							default:
								break;
							}
							categoria = p_Session->identificarCategoriaUsuario(value);
						}
						catch (invalid_argument ex)
						{
							LOGE << "Argumento invalido para la categoria. " << ((**it)["UserCategory"]) << "\n" << ex.what();
						}
						catch (out_of_range ex)
						{
							LOGE << "Argumento fuera de rango para la categoria. " << ((**it)["UserCategory"]) << "\n" << ex.what();
						}
						c_dispositivos.InsertItem(
							LVFIF_TEXT | LVIF_IMAGE | LVIF_PARAM,
							index, CA2W(categoria.c_str()), 0, 0, icon, (LPARAM)*it);
						break;
					case 1:
						c_dispositivos.SetItemText(index, cont, CA2W(((**it)["UserID"]).c_str()));
						break;
					case 2:
						c_dispositivos.SetItemText(index, cont, _T("?"));
						break;
					case 3:
						c_dispositivos.SetItemText(index, cont, CA2W(((**it)["UserName"]).c_str()));
						break;
					default:
						break;
					}

				}
				index++;
			}
		}
	}
	else
	{
		stringstream buffer;
		buffer << "Error al intentar generar el listado de los recursos.\n" << p_Session->getErrorMessage();
		AfxMessageBox(CA2W(buffer.str().c_str()));
	}
}

void CeLTEBrokerDlg::OnRclickListDispositivos(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	LOGD << "Se detecto un click derecho en el listado de dispositivos.";
	map<string, string> *itemData = (map<string, string> *)
		c_dispositivos.GetItemData(pNMItemActivate->iItem);

	int seleccion = c_TRecruso.GetCurSel();
	string valor("");
	if (itemData != NULL)
		switch (seleccion)
		{
		case 0:
			valor = (*itemData)["GroupID"];
			break;
		case 1:
			valor = (*itemData)["UserID"];
			break;
		default:
			break;
		}
	LOGD << "El ID del recurso seleccionado es: " << valor;

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	
	CPoint pt(pNMListView->ptAction);
	CMenu menu;
	menu.LoadMenu(IDM_LISTCTRL);
	CMenu* pContextMenu = menu.GetSubMenu(0);

	POINT p;
	p.x = pt.x;
	p.y = pt.y;
	::ClientToScreen(pNMHDR->hwndFrom, &p);
	int nID = pContextMenu->TrackPopupMenu(
		TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RETURNCMD,
		p.x, p.y, this);
	LOGD << "Selección menu contextual: " << nID;

	switch (nID)
	{
	case ID_LISTCTRL_LLAMADAP2P:
		solicitaDatosLlamada(1, valor);
		break;
	case ID_LISTCTRL_LLAMADAGRUPO:
		solicitaDatosLlamada(0, valor);
		break;
	case ID_LISTCTRL_MENSAJETEXTO:
		solicitaDatosMensaje(0, valor);
		break;
	case ID_LISTCTRL_MENSAJEMULTI:
		solicitaDatosMensaje(1, valor);
		break;
	case ID_LISTCTRL_VIDEO:
		this->p_Session->iniciarVideo(valor,
			ELTE_VIDEO_CIF,
			ELTE_CAMERA_BACK,
			ELTE_CAM_CONF_NREQ,
			ELTE_CAM_SND_NREQ);
		break;
	case ID_LISTCTRL_GPS:
		break;
	default:
		break;
	}

	*pResult = 0;
}

void CeLTEBrokerDlg::solicitaDatosLlamada(int tipo, string valor)
{
	LOGD << "Se inicia con la solicitud de los datos de la llamada. " << tipo 
		<< "/" << valor;

	CDialogLlamada modal;
	modal.seleccionarTipoInicio(tipo, valor);
	modal.cargarRecursos(pl_Grupos, pl_Usuarios);
	int res = modal.DoModal();
	if (res == IDOK)
	{
		LOGD << "Tipo de llamada: " << (modal.tipo_Llamada == 0 ? "GRUPO" : "P2P")
			<< " Recurso destino: " << modal.recurso_destino;

		int res = -100;
		switch (modal.tipo_Llamada)
		{
		case 0:
			res = p_Session->generarLlamadaGrupo(modal.recurso_destino);
			break;
		case 1:
			res = p_Session->generarLlamadaP2P(modal.recurso_destino);
			break;
		}

		if (res != 0)
		{
			stringstream buffer;
			buffer << "Error en la solicitud de la llamada. " <<
				(res == -100 ? "Tipo de interface desconocida." : p_Session->getErrorMessage());
			AfxMessageBox(CA2W(buffer.str().c_str()));
		}
		else
			AfxMessageBox(_T("Se logro generar la llamada."));
	}
	else
		LOGD << "Se cancelo la operación.";
}

void CeLTEBrokerDlg::solicitaDatosMensaje(int tipo, string destino)
{
	LOGD << "Se inicia con la solicitud de los datos de los mensajes. " << tipo;

	CDialogMensaje modal;
	modal.seleccionarTipoInicio(tipo);
	int res = modal.DoModal();
	if (res == IDOK)
	{
		LOGD << "Tipo de mensaje: " << (modal.tipo_Mensaje == 0 ? "SMS" : "MMS")
			<< " Mensaje: " << modal.s_mensaje;

		int res = -100;
		switch (modal.tipo_Mensaje)
		{
		case 0:
			res = p_Session->enviarMensaje(ELTE_MENSAJE_SMS, destino, modal.s_mensaje, "");
			break;
		case 1:
			res = p_Session->enviarMensaje(ELTE_MENSAJE_MMS, destino, modal.s_mensaje, "");
			break;
		}

		if (res != 0)
		{
			stringstream buffer;
			buffer << "Error en la solicitud de la generación del mensaje. " <<
				(res == -100 ? "Tipo de interface desconocida." : p_Session->getErrorMessage());
			AfxMessageBox(CA2W(buffer.str().c_str()));
		}
		else
			AfxMessageBox(_T("Se logro generar el mensaje."));
	}
	else
		LOGD << "Se cancelo la operación.";
}

void CeLTEBrokerDlg::desplegarVideo(string recurso)
{
	LOGD << "Se solicita desplegar el video del recurso: " << recurso;

	/*d_Video = new CDialogVideo(this);
	d_Video->desplegarVideo(p_Session, recurso);
	d_Video->Create(IDD_DIALOG_VIDEO);
	CRect rect;
	d_Video->GetClientRect(rect);
	d_Video->crearRecursoVideo(rect);

	d_Video->ShowWindow(SW_SHOWNA);

	::SetWindowPos(d_Video->GetSafeHwnd(),
		HWND_TOPMOST,
		0, 0, 0, 0,
		SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOMOVE)^*/
}

void CeLTEBrokerDlg::OnSelchangeComboRecursos()
{
	LOGD << "Se detecto un cambio en la selección del listado de recursos.";
	listarRecursos();
}


void CeLTEBrokerDlg::OnBnClickedButtonListado()
{
	LOGD << "Se solicita actualizar el listado de recursos.";
}


void CeLTEBrokerDlg::OnBnClickedButtonSesion()
{
	LOGD << "Se solicita cambiar el status de la sesión.";
}

void CeLTEBrokerDlg::enviarMensaje(int tipo, string recurso, string mensaje)
{
	LOGD << "Se solicita enviar un mensaje de tipo " << tipo <<
		" al recurso " << recurso << " mensaje: " << mensaje;
}

void CeLTEBrokerDlg::generarLlamada(int tipo, string recurso)
{
	LOGD << "Se solicita generar una llamada de tipo " << tipo << " al recurso " << recurso;
}

void CeLTEBrokerDlg::mostrarVideo(string recurso)
{
	LOGD << "Se solicita mostrar el recurso de video asociado al dispositivo: " << recurso;
}

afx_msg LRESULT CeLTEBrokerDlg::OnVideoReqReady(WPARAM wParam, LPARAM lParam)
{
	LOGD << "Se solicita atender el evento de video " << s_callStatus
		<< " / " << s_calleE << " -> " << s_calleR;

	if (s_callStatus.compare("3003") != 0) {
		LOGD << "No se logro iniciar la llamada de video.";
		return 0;
	}

	LOGD << "Iniciando la generación del dialogo para mostrar el video.";
	CDialogVideo* dlg = new CDialogVideo();
	if (dlg == NULL) {
		LOGE << "No se logro generar el dialogo del video.";
		return 0;
	}

	dlg->SetResourceID(s_calleE);
	dlg->Create(IDD_DIALOG_VIDEO, NULL);
	
	CRect rect;
	dlg->GetClientRect(rect);
	dlg->CreateVideoStatic(rect);
	dlg->ShowWindow(SW_SHOWNA);
	p_Session->asignarRecursoVideo(s_calleE, dlg->GetVideoStaticHwnd());

	return 0;
}
