
// ModuloCCTVDlg.h: archivo de encabezado
//

#pragma once
#include "include/IVS_SDK.h"
#include "ivs_ocxplayerctrlmain.h"
#include "Logger.h"

using namespace CPlusPlusLogging;

// Cuadro de di�logo de CModuloCCTVDlg
class CModuloCCTVDlg : public CDialogEx
{
// Construcci�n
public:
	CModuloCCTVDlg(CWnd* pParent = NULL);	// Constructor est�ndar

// Datos del cuadro de di�logo
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MODULOCCTV_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// Compatibilidad con DDX/DDV


// Implementaci�n
protected:
	HICON m_hIcon;

	// Funciones de asignaci�n de mensajes generadas
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

protected:
	Logger *pLogger = NULL;
	IVS_INT32 sessionID;
	
public:
	// Referencia al control de visualizacion
	CIvs_ocxplayerctrlmain cMainPlayer;
};
