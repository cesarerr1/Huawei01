#pragma once
#include "afxwin.h"
#include "afxbutton.h"


// CDialogMensaje dialog

class CDialogMensaje : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogMensaje)

public:
	void seleccionarTipoInicio(int tipo);
	CDialogMensaje(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogMensaje();

protected:
	bool b_inicializado;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MENSAJE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	string s_mensaje;
	string path_Medio;
	int tipo_Mensaje;
	CComboBox t_mensaje;
	CEdit m_mensaje;
	afx_msg void OnCbnSelchangeComboLlamadaTipo();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	CMFCButton b_busqueda;
	CEdit m_path;
};
