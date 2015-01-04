#ifndef TALKINDEX_H
#define TALKINDEX_H

#include <list>

#include "wx/string.h"

struct TalkDetail
{
	TalkDetail()
	{
		PortraitIndex = 0;
		Index = 0;
	}
	int Index;
	int PortraitIndex;
	wxString Text;
};

class TalkIndex
{
	public:
		TalkIndex();
		virtual ~TalkIndex();

	public:
		typedef std::list<TalkDetail>::iterator iterator;

		iterator Begin();
		iterator End();

		int Count();
		int GetNewIndex();
		int GetListIndex(int itemIndex);
		TalkDetail *GetItem(int index);
		iterator GetIterator(int index);
		TalkDetail* AppendItem();
		TalkDetail* AddAfter(int index);
		void Delete(int index);
		void Save();

	private:
		std::list<TalkDetail> m_talkList;
};

#endif // TALKINDEX_H
