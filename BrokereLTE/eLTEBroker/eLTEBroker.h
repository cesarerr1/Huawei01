
// eLTEBroker.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

#include "Configuracion.h"
#include "Server.h"

// CeLTEBrokerApp:
// See eLTEBroker.cpp for the implementation of this class
//

class CeLTEBrokerApp : public CWinApp
{
public:
	void CierreAuxiliares();
	void InicializacionAuxiliares();
	CeLTEBrokerApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()

protected:
	std::unique_ptr<Server> p_Server;
	eLTESession *p_Session;
	Configuracion m_Configuracion;
};

extern CeLTEBrokerApp theApp;
