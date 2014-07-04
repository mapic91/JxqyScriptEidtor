#ifndef COLOURSETTINGDIALOG_H
#define COLOURSETTINGDIALOG_H

//(*Headers(ColourSettingDialog)
#include <wx/stattext.h>
#include <wx/listbox.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/clrpicker.h>
//*)
#include "ConfigManager.h"

class ColourSettingDialog: public wxDialog
{
	public:

		ColourSettingDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~ColourSettingDialog();

	private:

		//(*Declarations(ColourSettingDialog)
		wxButton* m_button_Forground;
		wxStaticText* StaticText2;
		wxStaticText* StaticText1;
		wxButton* m_button_Cancle;
		wxButton* m_button_OK;
		wxButton* m_button_Background;
		wxListBox* m_listBox_Style;
		wxColourPickerCtrl* m_colourPickerCtrl_Forground;
		wxColourPickerCtrl* m_colourPickerCtrl_BackGround;
		//*)
		int GetCorrectedListSelection();

		ConfigManager m_cfg;

	protected:

		//(*Identifiers(ColourSettingDialog)
		static const long ID_LISTBOX1;
		static const long ID_STATICTEXT1;
		static const long ID_STATICTEXT2;
		static const long ID_COLOURPICKERCTRL1;
		static const long ID_COLOURPICKERCTRL2;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_BUTTON3;
		static const long ID_BUTTON4;
		//*)

	public:

		//(*Handlers(ColourSettingDialog)
		void Onm_colourPickerCtrl_BackGroundColourChanged(wxColourPickerEvent& event);
		void Onm_button_ForgroundClick(wxCommandEvent& event);
		void Onm_button_BackgroundClick(wxCommandEvent& event);
		void Onm_button_OKClick(wxCommandEvent& event);
		void Onm_button_CancleClick(wxCommandEvent& event);
		void Onm_listBox_StyleSelect(wxCommandEvent& event);
		void Onm_colourPickerCtrl_ForgroundColourChanged(wxColourPickerEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
