#ifndef FINDDIALOG_H
#define FINDDIALOG_H

//(*Headers(FindDialog)
#include <wx/notebook.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/radiobut.h>
#include <wx/statbox.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)
class JxqyScriptEditor;
class JxqyStc;
class FindDialog: public wxDialog
{
	public:

		FindDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~FindDialog();
		void SetFindText(const wxString& text)
		{
			m_textCtrl_Target->SetValue(text);
			m_textCtrl_Replace_Target->SetValue(text);
		}
		void SetPage(int page) { m_noteBook->SetSelection(page); }

	private:

		//(*Declarations(FindDialog)
		wxRadioButton* m_radioButton_Up;
		wxCheckBox* m_checkBox_Wraparound;
		wxStaticText* StaticText2;
		wxButton* m_button_Replace_Replace;
		wxPanel* m_panelFind;
		wxNotebook* m_noteBook;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxStaticBox* StaticBox1;
		wxButton* m_button_Cancle;
		wxTextCtrl* m_textCtrl_Replace_Replace;
		wxButton* m_button_Next;
		wxButton* m_button_Replace_Next;
		wxTextCtrl* m_textCtrl_Target;
		wxRadioButton* m_radioButton_Down;
		wxButton* m_button_Replace_All;
		wxPanel* m_panel_Replace;
		wxCheckBox* m_checkBox_MatchCase;
		wxTextCtrl* m_textCtrl_Replace_Target;
		//*)
		void OnActivate(wxActivateEvent &event);

		bool BeginFind(const wxString& findVal, bool toPos);
		bool DoFind(const wxString& findVal, bool toPos);
		bool DoReplace(const wxString& findVal, bool toPos);

		JxqyScriptEditor *m_edit;
		JxqyStc *m_stc;
		int m_lineNumber,
			m_lineFindBegin;
		bool m_replaceBegin;

	protected:

		//(*Identifiers(FindDialog)
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_BUTTON1;
		static const long ID_PANEL1;
		static const long ID_STATICTEXT2;
		static const long ID_STATICTEXT3;
		static const long ID_TEXTCTRL2;
		static const long ID_TEXTCTRL3;
		static const long ID_BUTTON3;
		static const long ID_BUTTON4;
		static const long ID_BUTTON5;
		static const long ID_PANEL2;
		static const long ID_NOTEBOOK1;
		static const long ID_CHECKBOX1;
		static const long ID_CHECKBOX2;
		static const long ID_STATICBOX1;
		static const long ID_RADIOBUTTON1;
		static const long ID_RADIOBUTTON2;
		static const long ID_BUTTON2;
		//*)

	public:

		//(*Handlers(FindDialog)
		void Onm_button_NextClick(wxCommandEvent& event);
		void Onm_button_CancleClick(wxCommandEvent& event);
		void OnSetFocus(wxFocusEvent& event);
		void Onm_noteBookPageChanged(wxNotebookEvent& event);
		void Onm_button_Replace_ReplaceClick(wxCommandEvent& event);
		void Onm_button_Replace_NextClick(wxCommandEvent& event);
		void Onm_button_Replace_AllClick(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
