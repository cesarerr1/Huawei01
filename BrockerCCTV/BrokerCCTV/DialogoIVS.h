#pragma once
#include "MyButton.h"
#include "ivs_ocxplayerctrl3.h"
#include "Logger.h"
#include "include\IVS_SDK.h"
#include "afxcmn.h"
#include "Configuracion.h"

// Cuadro de diálogo de CDialogoIVS
using namespace CPlusPlusLogging;
class CDialogoIVS : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogoIVS)

public:
	CDialogoIVS(CConfiguracion *conf, CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDialogoIVS();

// Datos del cuadro de diálogo
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IVS_DIALOG };
#endif

protected:
	CConfiguracion *configuracion;
	Logger *pLogger;
	bool login;
	IVS_INT32 sessionID;
	IVS_CHAR camara[1024];
	IVS_UINT32 lock;
	IVS_ULONG playerHandler;
	char velocidadPan[128];
	char velocidadZoom[128];
	char velocidadTilt[128];
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX/DDV
	DECLARE_MESSAGE_MAP()

public:
	CBrush m_brush;
	CMyButton m_botonCentro;
	CMyButton m_botonZoomOut;
	CMyButton m_botonZoomIn;
	CMyButton m_botonTiltOut;
	CMyButton m_botonTiltIn;
	CSliderCtrl m_sliderPan;
	CSliderCtrl m_sliderZoom;
	CSliderCtrl m_sliderTilt;
	CIvs_ocxplayerctrl3 m_IVSControl;
	void DesplegarCamara(char *camara);
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnNMReleasedcaptureSliderPan(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureSliderZoom(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureSliderTilt(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
