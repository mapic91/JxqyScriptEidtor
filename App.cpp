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
#include "IPC.cpp"
#include <wx/image.h>
#include "wx/log.h"

//(*AppHeaders
#include <wx/image.h>
//*)

IMPLEMENT_APP(wxWidgets_templateApp);

bool wxWidgets_templateApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    //*)

    JxqyScriptEditor* Frame = new JxqyScriptEditor(0);

    if(argc > 1)
    {
		wxLogNull lognul;
        DDEClient *client = new DDEClient();
        DDEConnection* connection = NULL;

        connection = (DDEConnection*)client->MakeConnection(wxT("localhost"), DDE_SERVICE + wxGetUserId(), DDE_TOPIC);

        if(connection)
        {
            for(int i = 1; i < argc; i++)
			{
				wxFileName fn(argv[i]);
				fn.Normalize();
				connection->Execute(fn.GetFullPath());
			}
            connection->Disconnect();
			delete connection;
			delete client;
			return false;
        }
        else
		{
			for(int i = 1; i < argc; i++)
			{
				wxFileName fn(argv[i]);
				fn.Normalize();
				Frame->OpenFile(fn.GetFullPath());
			}
		}
        delete client;
    }

    g_DDEServer = new DDEServer(Frame);
    g_DDEServer->Create(DDE_SERVICE + wxGetUserId());

    Frame->Show();
    SetTopWindow(Frame);

    return wxsOK;
}
int wxWidgets_templateApp::OnExit()
{
	if(g_DDEServer) delete g_DDEServer;
	return 0;
}
