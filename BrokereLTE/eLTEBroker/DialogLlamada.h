#pragma once
#include "afxwin.h"


// CDialogLlamada dialog

class CDialogLlamada : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogLlamada)

public:
	void seleccionarTipoInicio(int tipo, string valor);
	void cargarRecursos(list<map<string, string>*> *grupos, 
		list<map<string, string>*> *usuarios);
	CDialogLlamada(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogLlamada();

protected:
	void actualizarListaDestinos();
	void cargarListadoRecursos(int tipo);
	bool b_Inicializado;
	list<map<string, string>*> *pl_Grupos;
	list<map<string, string>*> *pl_Usuarios;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LLAMADA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	string recurso_destino;
	int tipo_Llamada;
	CComboBox t_llamada;
	CComboBox t_destino;
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboLlamadaTipo();
	virtual void OnOK();
	virtual void OnCancel();
};
