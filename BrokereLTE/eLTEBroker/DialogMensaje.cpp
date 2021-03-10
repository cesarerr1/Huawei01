// DialogMensaje.cpp : implementation file
//

#include "stdafx.h"
#include "eLTEBroker.h"
#include "DialogMensaje.h"
#include "afxdialogex.h"
#include "plog\Log.h"


// CDialogMensaje dialog

IMPLEMENT_DYNAMIC(CDialogMensaje, CDialogEx)

CDialogMensaje::CDialogMensaje(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_MENSAJE, pParent)
{
	b_inicializado = false;
	tipo_Mensaje = -1;
	path_Medio = "";
	s_mensaje = "";
}

CDialogMensaje::~CDialogMensaje()
{
}

void CDialogMensaje::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_LLAMADA_TIPO, t_mensaje);
	DDX_Control(pDX, IDC_EDIT2, m_mensaje);
	DDX_Control(pDX, IDC_MFCBUTTON_SEARCH, b_busqueda);
	DDX_Control(pDX, IDC_EDIT1, m_path);
}


BEGIN_MESSAGE_MAP(CDialogMensaje, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_LLAMADA_TIPO, &CDialogMensaje::OnCbnSelchangeComboLlamadaTipo)
END_MESSAGE_MAP()


// CDialogMensaje message handlers


void CDialogMensaje::OnCbnSelchangeComboLlamadaTipo()
{
	int seleccion = t_mensaje.GetCurSel();
	LOGD << "Se modifico el tipo de mensaje a ser enviado: " << seleccion;

	switch (seleccion)
	{
	case 0:
		m_path.SetWindowTextW(_T(""));
		GetDlgItem(IDC_MFCBUTTON_SEARCH)->EnableWindow(false);
		break;
	case 1:
		m_path.SetWindowTextW(_T(""));
		GetDlgItem(IDC_MFCBUTTON_SEARCH)->EnableWindow(true);
		break;
	default:
		break;
	}
}


BOOL CDialogMensaje::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	LOGD << "Inicializando el dialogo de captura del mensaje.";

	if (tipo_Mensaje >= 0)
		t_mensaje.SetCurSel(tipo_Mensaje);

	b_inicializado = true;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CDialogMensaje::OnOK()
{
	LOGD << "Se acepto la operación.";

	CString text;
	m_mensaje.GetWindowTextW(text);
	s_mensaje = CW2A(text);
	LOGD << "El texto capturado es: " << s_mensaje;

	CDialogEx::OnOK();
}


void CDialogMensaje::OnCancel()
{
	LOGD << "Se cancelo la operación.";

	CDialogEx::OnCancel();
}

void CDialogMensaje::seleccionarTipoInicio(int tipo)
{
	LOGD << "Se solicita carga el tipo de mensaje configurado. " << tipo;

	tipo_Mensaje = tipo;
	if (b_inicializado)
		t_mensaje.SetCurSel(tipo_Mensaje);

}