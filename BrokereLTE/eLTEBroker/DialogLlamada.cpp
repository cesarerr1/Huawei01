// DialogLlamada.cpp : implementation file
//

#include "stdafx.h"
#include "eLTEBroker.h"
#include "DialogLlamada.h"
#include "afxdialogex.h"
#include "plog\Log.h"

// CDialogLlamada dialog

IMPLEMENT_DYNAMIC(CDialogLlamada, CDialogEx)

CDialogLlamada::CDialogLlamada(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_LLAMADA, pParent)
{
	tipo_Llamada = -1;
	pl_Grupos = NULL;
	pl_Usuarios = NULL;
	b_Inicializado = false;
}

CDialogLlamada::~CDialogLlamada()
{
}

void CDialogLlamada::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_LLAMADA_TIPO, t_llamada);
	DDX_Control(pDX, IDC_COMBO_LLAMADA_DESTINO, t_destino);
}


BEGIN_MESSAGE_MAP(CDialogLlamada, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_LLAMADA_TIPO, &CDialogLlamada::OnSelchangeComboLlamadaTipo)
END_MESSAGE_MAP()


// CDialogLlamada message handlers
void CDialogLlamada::cargarRecursos(list<map<string, string>*> *grupos, 
	list<map<string, string>*> *usuarios)
{
	LOGD << "Cargando el listado de recursos disponibles.";
	pl_Grupos = grupos;
	pl_Usuarios = usuarios;

	if (b_Inicializado && tipo_Llamada >= 0)
		actualizarListaDestinos();
}

void CDialogLlamada::seleccionarTipoInicio(int tipo, string valor)
{
	LOGD << "Se solicita cargar la inicialización del dialogo. " << tipo << "/" << valor;
	tipo_Llamada = tipo;
	recurso_destino = valor;

	if (b_Inicializado && pl_Usuarios != NULL && pl_Grupos != NULL)
		actualizarListaDestinos();
}

BOOL CDialogLlamada::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	LOGD << "Inicialización del dialogo. " << tipo_Llamada;
	b_Inicializado = true;

	if (tipo_Llamada >= 0)
	{
		t_llamada.SetCurSel(tipo_Llamada);
		if (pl_Grupos != NULL && pl_Usuarios != NULL)
			actualizarListaDestinos();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogLlamada::actualizarListaDestinos()
{
	LOGD << "Se solicita actualizar el listado de destinos disponibles. " << tipo_Llamada;

	t_destino.ResetContent();
	if (tipo_Llamada == 0 && pl_Grupos != NULL)
	{
		for (list<map<string, string>*>::iterator it = pl_Grupos->begin();
			it != pl_Grupos->end(); it++)
		{
			int index = t_destino.AddString(CA2W((**it)["GroupName"].c_str()));
			if (index >= 0)
				t_destino.SetItemDataPtr(index, *it);
			if ((**it)["GroupID"].compare(recurso_destino) == 0)
				t_destino.SetCurSel(index);
		}
	}

	else if (tipo_Llamada == 1 && pl_Usuarios != NULL)
	{
		for (list<map<string, string>*>::iterator it = pl_Usuarios->begin();
			it != pl_Usuarios->end(); it++)
		{
			int index = t_destino.AddString(CA2W((**it)["UserName"].c_str()));
			if (index >= 0)
				t_destino.SetItemDataPtr(index, *it);
			if ((**it)["UserID"].compare(recurso_destino) == 0)
				t_destino.SetCurSel(index);
		}
	}
}


void CDialogLlamada::OnSelchangeComboLlamadaTipo()
{
	tipo_Llamada = t_llamada.GetCurSel();
	LOGD << "Se detecto un cambio en la selección del tipo de llamada. " << tipo_Llamada;
	actualizarListaDestinos();
}


void CDialogLlamada::OnOK()
{
	LOGD << "Se acepto las opciones capturadas por el usuario. " << tipo_Llamada;
	int seleccion = t_destino.GetCurSel();
	if (seleccion < 0)
	{
		AfxMessageBox(_T("No se ha seleccionado un destino para la llamada."));
		return;
	}

	map<string, string> *item = (map<string, string>*)t_destino.GetItemDataPtr(seleccion);
	switch (tipo_Llamada)
	{
	case 0:
		recurso_destino = (*item)["GroupID"];
		LOGD << "Recurso destino grupo: " << recurso_destino;
		break;
	case 1:
		recurso_destino = (*item)["UserID"];
		LOGD << "Recurso destino usuario: " << recurso_destino;
		break;
	default:
		AfxMessageBox(_T("Tipo de recurso no reconocido."));
		return;
	}

	CDialogEx::OnOK();
}


void CDialogLlamada::OnCancel()
{
	LOGD << "Se cancelo la operación.";

	CDialogEx::OnCancel();
}
