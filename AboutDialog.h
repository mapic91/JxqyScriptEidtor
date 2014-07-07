#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

//(*Headers(AboutDialog)
#include <wx/stattext.h>
#include <wx/hyperlink.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

class AboutDialog: public wxDialog
{
	public:

		AboutDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~AboutDialog();

	private:

		//(*Declarations(AboutDialog)
		wxStaticText* StaticText2;
		wxButton* Button1;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxHyperlinkCtrl* HyperlinkCtrl1;
		wxStaticText* StaticText5;
		wxStaticText* StaticText4;
		//*)

	protected:

		//(*Identifiers(AboutDialog)
		static const long ID_STATICTEXT1;
		static const long ID_STATICTEXT2;
		static const long ID_STATICTEXT3;
		static const long ID_STATICTEXT4;
		static const long ID_STATICTEXT5;
		static const long ID_BUTTON1;
		static const long ID_HYPERLINKCTRL1;
		//*)

	public:

		//(*Handlers(AboutDialog)
		void OnButton1Click(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
