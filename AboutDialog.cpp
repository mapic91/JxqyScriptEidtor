#include "AboutDialog.h"

//(*InternalHeaders(AboutDialog)
#include <wx/string.h>
//*)

//(*IdInit(AboutDialog)
const long AboutDialog::ID_STATICTEXT1 = wxNewId();
const long AboutDialog::ID_STATICTEXT2 = wxNewId();
const long AboutDialog::ID_STATICTEXT3 = wxNewId();
const long AboutDialog::ID_STATICTEXT4 = wxNewId();
const long AboutDialog::ID_STATICTEXT5 = wxNewId();
const long AboutDialog::ID_BUTTON1 = wxNewId();
const long AboutDialog::ID_HYPERLINKCTRL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(AboutDialog,wxDialog)
	//(*EventTable(AboutDialog)
	//*)
END_EVENT_TABLE()

AboutDialog::AboutDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(AboutDialog)
	Create(parent, wxID_ANY, _T("关于"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(304,163));
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _T("剑\n侠\n情\n缘\n脚\n本\n编\n辑\n器"), wxPoint(32,8), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	StaticText1->SetForegroundColour(wxColour(255,128,64));
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _T("版本："), wxPoint(80,16), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	StaticText2->SetForegroundColour(wxColour(37,169,180));
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _T("V1.2"), wxPoint(128,16), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	StaticText3->SetForegroundColour(wxColour(37,169,180));
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _T("    BY："), wxPoint(80,48), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	StaticText4->SetForegroundColour(wxColour(37,169,180));
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _T("2015.1.4"), wxPoint(192,96), wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	StaticText5->SetForegroundColour(wxColour(128,0,0));
	Button1 = new wxButton(this, ID_BUTTON1, _T("确定"), wxPoint(200,136), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	Button1->SetDefault();
	HyperlinkCtrl1 = new wxHyperlinkCtrl(this, ID_HYPERLINKCTRL1, _T("小试刀剑"), _T("http://hi.baidu.com/qndryqnqbmbbceq"), wxPoint(128,48), wxDefaultSize, wxHL_CONTEXTMENU|wxHL_ALIGN_CENTRE|wxNO_BORDER, _T("ID_HYPERLINKCTRL1"));
	Center();

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&AboutDialog::OnButton1Click);
	//*)
}

AboutDialog::~AboutDialog()
{
	//(*Destroy(AboutDialog)
	//*)
}


void AboutDialog::OnButton1Click(wxCommandEvent& event)
{
	EndModal(wxID_OK);
}
