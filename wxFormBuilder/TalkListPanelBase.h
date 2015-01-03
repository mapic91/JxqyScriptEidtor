///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __TALKLISTPANELBASE_H__
#define __TALKLISTPANELBASE_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/dataview.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class TalkListPanelBase
///////////////////////////////////////////////////////////////////////////////
class TalkListPanelBase : public wxFrame 
{
	private:
	
	protected:
		wxPanel* m_panel1;
		wxDataViewListCtrl* m_listView;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		
	
	public:
		
		TalkListPanelBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 700,350 ), long style = wxCAPTION|wxCLOSE_BOX|wxFRAME_FLOAT_ON_PARENT|wxFRAME_NO_TASKBAR|wxFRAME_TOOL_WINDOW|wxRESIZE_BORDER|wxSYSTEM_MENU|wxTAB_TRAVERSAL );
		
		~TalkListPanelBase();
	
};

#endif //__TALKLISTPANELBASE_H__
