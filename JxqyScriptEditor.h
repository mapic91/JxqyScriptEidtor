#ifndef JXQYSCRIPTEDITOR_H
#define JXQYSCRIPTEDITOR_H

#include "JxqyStc.h"
#include "ConfigManager.h"

//(*Headers(JxqyScriptEditor)
#include <wx/sizer.h>
#include <wx/menu.h>
#include <wx/aui/aui.h>
#include <wx/frame.h>
//*)

class JxqyScriptEditor: public wxFrame
{
	public:

		JxqyScriptEditor(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~JxqyScriptEditor();

	private:

		//(*Declarations(JxqyScriptEditor)
		wxMenuItem* MenuItem8;
		wxMenuItem* MenuItem7;
		wxAuiNotebook* m_AuiBook;
		wxMenuItem* MenuItem5;
		wxMenuItem* MenuItem2;
		wxMenuItem* MenuItem1;
		wxMenuItem* MenuItem4;
		wxMenuItem* MenuItem14;
		wxMenuItem* MenuItem11;
		wxMenuItem* MenuItem15;
		wxMenuItem* MenuItem13;
		wxMenu* Menu1;
		wxMenuItem* MenuItem10;
		wxMenuItem* MenuItem12;
		wxMenuItem* MenuItem3;
		wxMenuItem* MenuItem6;
		wxMenuBar* m_menuBar;
		wxMenu* Menu2;
		wxMenuItem* MenuItem9;
		//*)

		//File
		void OnNewFile(wxCommandEvent &event);
		void OnOpenFile(wxCommandEvent &event);
		void OnSave(wxCommandEvent &event);
		void OnSaveAs(wxCommandEvent &event);
		void OnSaveAll(wxCommandEvent &event);
		void OnClose(wxCommandEvent &event);
		void OnCloseAll(wxCommandEvent &event);
		void OnExit(wxCommandEvent &event);
		//Setting
		void OnFontSetting(wxCommandEvent &event);
		void OnColourSetting(wxCommandEvent &event);
		void OnWordWrap(wxCommandEvent &event);
		void OnFunctionHelpShow(wxCommandEvent &event);
		void OnFunctionFileChoose(wxCommandEvent &event);

		void OnPageClose(wxAuiNotebookEvent &event);

		int GetOpenedFile(const wxString &path);
		void SetPageChanged(bool changed = true, int idx = -1);
		//true - saved to file, false - not saved to file
		bool SavePageToFile(int idx = -1, const wxString& path = wxEmptyString, const wxString &defaultFileName = wxEmptyString, bool *veto = NULL);
		wxString GetPageTiltleClean(int idx = -1);


		void AddNewFile();
		JxqyStc* GetInitlizedJxqyStc();
		void SetJxqyStcStyleFromSetting(JxqyStc *stc);
		void ResetOpenedPageStyle();

		void Init();
		void Uninit();

	protected:

		//(*Identifiers(JxqyScriptEditor)
		static const long ID_AUINOTEBOOK1;
		static const long MYID_SAVEALL;
		static const long MYID_CLOSE;
		static const long MYID_CLOSEALL;
		static const long MYID_FONTSETTING;
		static const long MYID_COLOURSETTING;
		static const long MYID_WORDWRAP;
		static const long MYID_FUNHELP;
		static const long MYID_JXQY2;
		static const long MYID_YYCS;
		static const long MYID_XJXQY;
		//*)

	public:

		//(*Handlers(JxqyScriptEditor)
		//*)


	private:
		ConfigManager m_cfg;

		DECLARE_EVENT_TABLE()
};

#endif
