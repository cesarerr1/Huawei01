
// RestServer.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

#include "Configuracion.h"

// CRestServerApp:
// See RestServer.cpp for the implementation of this class
//

class CRestServerApp : public CWinApp
{
public:
	CRestServerApp();

private:
	void InicializacionAuxiliares();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()

private:
	Configuracion m_Configuracion;
};

extern CRestServerApp theApp;
