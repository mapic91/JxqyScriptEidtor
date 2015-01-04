///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "TalkListPanelBase.h"

///////////////////////////////////////////////////////////////////////////

TalkListPanelBase::TalkListPanelBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_panel1 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	m_listView = new wxDataViewListCtrl( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_listView, 1, wxALL|wxEXPAND, 0 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	m_bAdd = new wxButton( m_panel1, wxID_ANY, wxT("+"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_bAdd, 0, wxALL, 5 );
	
	m_bInsert = new wxButton( m_panel1, wxID_ANY, wxT("<+"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_bInsert, 0, wxALL, 5 );
	
	m_bDelete = new wxButton( m_panel1, wxID_ANY, wxT("x"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_bDelete, 0, wxALL, 5 );
	
	m_stGoto = new wxStaticText( m_panel1, wxID_ANY, wxT("To:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stGoto->Wrap( -1 );
	bSizer3->Add( m_stGoto, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_scGoto = new wxSpinCtrl( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS|wxTE_PROCESS_ENTER, 0, 2147483646, 0 );
	bSizer3->Add( m_scGoto, 0, wxALL, 5 );
	
	
	bSizer3->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_bSave = new wxButton( m_panel1, wxID_ANY, wxT("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_bSave, 0, wxALL, 5 );
	
	
	bSizer2->Add( bSizer3, 0, wxEXPAND, 0 );
	
	
	m_panel1->SetSizer( bSizer2 );
	m_panel1->Layout();
	bSizer2->Fit( m_panel1 );
	bSizer1->Add( m_panel1, 1, wxEXPAND | wxALL, 0 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( TalkListPanelBase::OnClose ) );
	this->Connect( wxID_ANY, wxEVT_COMMAND_DATAVIEW_ITEM_EDITING_DONE, wxDataViewEventHandler( TalkListPanelBase::OnItemEdited ) );
	m_bAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TalkListPanelBase::OnAdd ), NULL, this );
	m_bInsert->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TalkListPanelBase::OnInsert ), NULL, this );
	m_bDelete->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TalkListPanelBase::OnDelete ), NULL, this );
	m_scGoto->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TalkListPanelBase::OnGoto ), NULL, this );
	m_bSave->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TalkListPanelBase::OnSave ), NULL, this );
}

TalkListPanelBase::~TalkListPanelBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( TalkListPanelBase::OnClose ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_DATAVIEW_ITEM_EDITING_DONE, wxDataViewEventHandler( TalkListPanelBase::OnItemEdited ) );
	m_bAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TalkListPanelBase::OnAdd ), NULL, this );
	m_bInsert->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TalkListPanelBase::OnInsert ), NULL, this );
	m_bDelete->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TalkListPanelBase::OnDelete ), NULL, this );
	m_scGoto->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( TalkListPanelBase::OnGoto ), NULL, this );
	m_bSave->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TalkListPanelBase::OnSave ), NULL, this );
	
}
