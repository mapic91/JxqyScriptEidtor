#ifndef JXQYSCRIPTEDITOR_H
#define JXQYSCRIPTEDITOR_H

#include "JxqyStc.h"
#include "ConfigManager.h"
#include "FindDialog.h"

#include "wx/filedlg.h"
#include "wx/dnd.h"
//(*Headers(JxqyScriptEditor)
#include <wx/sizer.h>
#include <wx/menu.h>
#include <wx/aui/aui.h>
#include <wx/toolbar.h>
#include <wx/frame.h>
//*)

class JxqyScriptEditor: public wxFrame
{
	public:

		JxqyScriptEditor(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~JxqyScriptEditor();
		bool OpenFile(const wxString& path);
		JxqyStc* GetCurrentStc();

	private:

		//(*Declarations(JxqyScriptEditor)
		wxToolBarToolBase* ToolBarItem4;
		wxMenuItem* MenuItem8;
		wxToolBarToolBase* ToolBarItem9;
		wxMenuItem* MenuItem26;
		wxMenuItem* MenuItem7;
		wxAuiNotebook* m_AuiBook;
		wxMenuItem* MenuItem25;
		wxToolBarToolBase* ToolBarItem3;
		wxToolBarToolBase* ToolBarItem12;
		wxMenuItem* MenuItem5;
		wxToolBarToolBase* ToolBarItem11;
		wxMenuItem* MenuItem2;
		wxMenu* Menu3;
		wxToolBarToolBase* ToolBarItem10;
		wxMenuItem* MenuItem1;
		wxMenuItem* MenuItem4;
		wxMenuItem* MenuItem14;
		wxMenuItem* MenuItem11;
		wxMenuItem* MenuItem29;
		wxMenu m_menuPageTabPopup;
		wxMenuItem* MenuItem15;
		wxMenuItem* MenuItem22;
		wxMenuItem* MenuItem17;
		wxMenuItem* MenuItem13;
		wxMenu* Menu1;
		wxMenuItem* MenuItem10;
		wxToolBarToolBase* ToolBarItem6;
		wxMenuItem* MenuItem12;
		wxMenuItem* MenuItem24;
		wxMenuItem* MenuItem27;
		wxToolBarToolBase* ToolBarItem1;
		wxMenuItem* MenuItem3;
		wxMenuItem* MenuItem20;
		wxMenuItem* MenuItem28;
		wxMenuItem* MenuItem6;
		wxToolBar* m_toolBar;
		wxMenuItem* MenuItem23;
		wxMenuBar* m_menuBar;
		wxToolBarToolBase* ToolBarItem5;
		wxToolBarToolBase* ToolBarItem8;
		wxMenuItem* MenuItem21;
		wxMenuItem* MenuItem16;
		wxMenu* Menu2;
		wxMenuItem* MenuItem9;
		wxMenuItem* MenuItem18;
		wxMenuItem* MenuItem30;
		wxToolBarToolBase* ToolBarItem2;
		wxMenu* Menu5;
		wxMenu* Menu4;
		wxMenuItem* MenuItem19;
		wxToolBarToolBase* ToolBarItem7;
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
		//Edit
		void OnEdit(wxCommandEvent &event);
		//Search
		void OnSearch(wxCommandEvent &event);
		//Setting
		void OnFontSetting(wxCommandEvent &event);
		void OnColourSetting(wxCommandEvent &event);
		void OnWordWrap(wxCommandEvent &event);
		void OnFunctionHelpShow(wxCommandEvent &event);
		void OnLineNumberShow(wxCommandEvent &event);
		void OnFunctionFileChoose(wxCommandEvent &event);
		//Help
		void OnHelp(wxCommandEvent &event);
		void OnAbout(wxCommandEvent &event);
		//Pagetab popup
		void OnPageTabPopup(wxCommandEvent &event);

		void OnPageClose(wxAuiNotebookEvent &event);

		void OnActivate(wxActivateEvent &event);

		bool ClosePage(int idx = -1, bool deletePage = true);
		bool CloseAllPage(size_t keep = -1);

		int GetOpenedFile(const wxString &path);
		void SetPageChanged(bool changed = true, int idx = -1);
		//true - saved to file, false - not saved to file
		bool SavePageToFile(int idx = -1, const wxString& path = wxEmptyString, const wxString &defaultFileName = wxEmptyString, bool *pageCloseVeto = NULL);
		wxString GetPageTiltleClean(int idx = -1);

		void AddNewFile();
		JxqyStc* GetInitlizedJxqyStc();
		void SetJxqyStcStyleFromSetting(JxqyStc *stc);
		void ResetOpenedPageStyle();
		void ResetPageTitleTooltip(int idx = -1);
		void SetMenuAndPageState(JxqyStc *stc = NULL);

		wxFileDialog* GetFileSaveDialog(const wxString& defaultFileName = wxEmptyString);
		wxFileDialog* GetFileOpenDialog();

		void Init();
		void Uninit();

	protected:

		//(*Identifiers(JxqyScriptEditor)
		static const long ID_AUINOTEBOOK1;
		static const long MYID_SAVEALL;
		static const long MYID_CLOSE;
		static const long MYID_CLOSEALL;
		static const long MYID_UNDO;
		static const long MYID_REDO;
		static const long MYID_CUT;
		static const long MYID_COPY;
		static const long MYID_PASTE;
		static const long MYID_DELETE;
		static const long MYID_SELECTALL;
		static const long MYID_FONTSETTING;
		static const long MYID_COLOURSETTING;
		static const long MYID_WORDWRAP;
		static const long MYID_FUNHELP;
		static const long MYID_SHOWLINENUMBER;
		static const long MYID_JXQY2;
		static const long MYID_YYCS;
		static const long MYID_XJXQY;
		static const long TOOLBAR_MYID_SAVEALL;
		static const long TOOLBAR_MYID_UNDO;
		static const long TOOLBAR_MYID_REDO;
		static const long TOOLBAR_MYID_CUT;
		static const long TOOLBAR_MYID_COPY;
		static const long TOOLBAR_MYID_PASTE;
		static const long ID_TOOLBAR1;
		static const long MYID_PAGETABCLOSENOTTHIS;
		static const long MYID_PAGETABCLOSEALL;
		static const long MYID_OPENFILEDIR;
		//*)

	public:

		//(*Handlers(JxqyScriptEditor)
		void OnFrameClose(wxCloseEvent& event);
		void OnPageClosed(wxAuiNotebookEvent& event);
		void OnPageChanged(wxAuiNotebookEvent& event);
		void OBookTabRightDown(wxAuiNotebookEvent& event);
		void Onm_AuiBookPageChanging(wxAuiNotebookEvent& event);
		//*)
		void OnStcChange(wxStyledTextEvent &event);

	private:
		ConfigManager m_cfg;
		FindDialog *m_find;

		DECLARE_EVENT_TABLE()
};

class MyFileDrop:public wxFileDropTarget
{
public:
    MyFileDrop(){mainfram = NULL;}
    MyFileDrop(JxqyScriptEditor *frame){mainfram = frame;}
    void SetMainFrame(JxqyScriptEditor *frame){mainfram = frame;}
    virtual bool OnDropFiles(wxCoord x, wxCoord y, const wxArrayString& filenames);
private:
    JxqyScriptEditor *mainfram;

};

#endif
