// DialogoTrunking.cpp: archivo de implementaci�n
//

#include "stdafx.h"
#include "BrokerCCTV.h"
#include "DialogoTrunking.h"
#include "afxdialogex.h"


// Cuadro de di�logo de CDialogoTrunking

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

	// TODO:  Agregue aqu� la inicializaci�n adicional
		
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPCI�N: las p�ginas de propiedades OCX deben devolver FALSE
}
