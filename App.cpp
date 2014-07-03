/***************************************************************
 * Name:      App.cpp
 * Purpose:   Code for Application Class
 * Author:
 * Created:
 * Copyright:
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "App.h"

#include <wx/image.h>

//(*AppHeaders
#include "JxqyScriptEditor.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(wxWidgets_templateApp);

bool wxWidgets_templateApp::OnInit()
{
	//(*AppInitialize
	bool wxsOK = true;
	wxInitAllImageHandlers();
	if ( wxsOK )
	{
	JxqyScriptEditor* Frame = new JxqyScriptEditor(0);
	Frame->Show();
	SetTopWindow(Frame);
	}
	//*)
	return wxsOK;
}
