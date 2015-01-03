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

	private:
		//TalkIndex
		TalkIndex m_talkList;

		wxDataViewColumn* m_columnIndex;
		wxDataViewColumn* m_columnPortrait;
		wxDataViewColumn* m_columnText;
};

#endif // TALKLISTPANEL_H
