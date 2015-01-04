#ifndef TALKLISTPANEL_H
#define TALKLISTPANEL_H

#include "wxFormBuilder/TalkListPanelBase.h"
#include "TalkIndex.h"

class TalkListPanel : public TalkListPanelBase
{
	public:
		TalkListPanel(wxWindow *parent);
		virtual ~TalkListPanel();
	protected:
		void InitFromTalkList();
		virtual void OnClose( wxCloseEvent& event );
		virtual void OnItemEdited( wxDataViewEvent& event );
		virtual void OnAdd( wxCommandEvent& event );
		virtual void OnInsert( wxCommandEvent& event );
		virtual void OnDelete( wxCommandEvent& event );
		virtual void OnGoto( wxCommandEvent& event );
		virtual void OnSave( wxCommandEvent& event );

	private:
		wxVector<wxVariant> CreateItemData(int itemIndex, int portraitIndex, const wxString &text);
		int AppendItem(TalkDetail* detail);
		int AppendItem(int itemIndex, int portraitIndex = 0, const wxString &text = wxEmptyString);
		int InsertItem(int row, int itemIndex, int portraitIndex = 0, const wxString &text = wxEmptyString);
		void SelectAndShowRow(int row);
		int GetItemIndex(int row);

	private:
		enum
		{
			INDEX_COLUMN,
			PORTRAIT_COLUMN,
			TEXT_COLUMN
		};

		//TalkIndex
		TalkIndex m_talkList;

		wxDataViewColumn* m_columnIndex;
		wxDataViewColumn* m_columnPortrait;
		wxDataViewColumn* m_columnText;
};

#endif // TALKLISTPANEL_H
