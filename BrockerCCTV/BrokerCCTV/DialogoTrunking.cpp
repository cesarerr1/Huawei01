// DialogoTrunking.cpp: archivo de implementación
//

#include "stdafx.h"
#include "BrokerCCTV.h"
#include "DialogoTrunking.h"
#include "afxdialogex.h"


// Cuadro de diálogo de CDialogoTrunking

IMPLEMENT_DYNAMIC(CDialogoTrunking, CDialogEx)

CDialogoTrunking::CDialogoTrunking(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TRUNKING_DIALOG, pParent)
{

}

CDialogoTrunking::~CDialogoTrunking()
{
}

void CDialogoTrunking::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogoTrunking, CDialogEx)
END_MESSAGE_MAP()


// Controladores de mensajes de CDialogoTrunking


BOOL CDialogoTrunking::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Agregue aquí la inicialización adicional
		
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPCIÓN: las páginas de propiedades OCX deben devolver FALSE
}
