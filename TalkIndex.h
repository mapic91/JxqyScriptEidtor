#ifndef TALKINDEX_H
#define TALKINDEX_H

#include <map>

#include "wx/string.h"

struct TalkDetail
{
	TalkDetail()
	{
		PortraitIndex = 0;
	}
	int PortraitIndex;
	wxString Text;
};

class TalkIndex
{
	public:
		TalkIndex();
		virtual ~TalkIndex();

	public:
		typedef std::map<int, TalkDetail>::iterator iterator;

		/**\brief Get iterator at begin.
		 *
		 *\return Begin iterator.
		 *
		 */
		iterator Begin();

		/**\brief Get iterator at end.
		 *
		 *\return End iterator.
		 *
		 */
		iterator End();

		/**\brief Get item count.
		 *
		 *\return Item count.
		 *
		 */
		int Count();

		/**\brief Get TalkDetail at index.
		 *
		 *\param index Item index
		 *\return The found item.NULL if not found.
		 *
		 */
		TalkDetail *GetItem(int index);

		/**\brief Set item's portrait index and text at index.
		 *
		 *\param index Item index.
		 *\param portraitIndex Portrait index to set.
		 *\param text Text to set.
		 *\return True if item exist.False otherwise.
		 *
		 */
		bool SetItem(int index, int portraitIndex, const wxString& text);

		/**\brief Add new item at index.
		 *
		 *\param index Item index to add.
		 *\return True on sucess.If item already exist return false.
		 *
		 */
		bool AddItem(int index);

		/**\brief Add new item after index.
		 *
		 *\param index Item index to add after.
		 *\return True on sucess.If item already exist return false.
		 *
		 */
		bool AddAfter(int index);

		/**\brief Add new item before index.
		 *
		 *\param index Item index to add before.
		 *\return True on sucess.If item already exist return false.
		 *
		 */
		bool AddBefore(int index);

		/**\brief Save to file.
		 *
		 *\return void
		 *
		 */
		void Save();

	private:
		std::map<int, TalkDetail> m_talkList;
};

#endif // TALKINDEX_H
