
// eLTEBrokerDlg.h : header file
//

#pragma once

#include "eLTESession.h"
#include "Configuracion.h"
#include "DialogVideo.h"
#include "afxcmn.h"

// CeLTEBrokerDlg dialog
class CeLTEBrokerDlg : public CDialogEx
{
// Construction
public:
	void setConfiguracion(Configuracion* configuracion);
	void seteLTESesion(eLTESession* pSesion);
	CeLTEBrokerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ELTEBROKER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	void mostrarVideo(string recurso);
	void generarLlamada(int tipo, string recurso);
	void enviarMensaje(int tipo, string recurso, string mensaje);

	void desplegarVideo(string recurso);
	void solicitaDatosMensaje(int tipo, string destino);
	void solicitaDatosLlamada(int tipo, string valor);

	void liberarListaRecursos(int tipo);
	void listarRecursos();
	void statusModulo(map<string, string> *info);
	void statusRecurso(map<string, string> *info);
	void mensajeSesioneLTE(WPARAM msg, map<string, string> *info);
	void postInitView();
	void initListViewColumn();

	list<map<string, string>*> *pl_Grupos;
	list<map<string, string>*> *pl_Usuarios;
	CDialogVideo *d_Video;
	eLTESession *p_Session;
	Configuracion *p_Configuracion;
	CImageList l_iconos;
	HICON m_hIcon;
	string s_callStatus;
	string s_calleE;
	string s_calleR;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL DestroyWindow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CListCtrl c_dispositivos;
	afx_msg void OnRclickListDispositivos(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSelchangeComboRecursos();
	afx_msg void OnBnClickedButtonListado();
	afx_msg void OnBnClickedButtonSesion();
	CButton b_Listado;
	CButton b_Sesion;
	CStatic s_Status;
	CComboBox c_TRecruso;
protected:
//	afx_msg LRESULT OnVideoReqReady(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnVideoReqReady(WPARAM wParam, LPARAM lParam);
};
