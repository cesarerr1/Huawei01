
// BrokerCCTVDlg.h: archivo de encabezado
//

#pragma once

#include "Logger.h"
#include "Configuracion.h"
#include "ServidorTCP.h"
#include "DialogoIVS.h"

using namespace CPlusPlusLogging;

// Cuadro de di�logo de CBrokerCCTVDlg
class CBrokerCCTVDlg : public CDialogEx
{
	// Construcci�n
public:
	void DesplegarCamara(char *idCamara);
	CBrokerCCTVDlg(CWnd* pParent = NULL);	// Constructor est�ndar

// Datos del cuadro de di�logo
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BROKERCCTV_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// Compatibilidad con DDX/DDV


// Implementaci�n
protected:
	CDialogoIVS *dlgIVS;
	HICON m_hIcon;
	Logger *pLogger;
	CConfiguracion *configuracion;
	ServidorTCP *servidorTCP;

	// Funciones de asignaci�n de mensajes generadas
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonIvs();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void PostNcDestroy();
};
