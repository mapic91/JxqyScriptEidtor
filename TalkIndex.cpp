#include "TalkIndex.h"
#include "wx/file.h"
#include "wx/log.h"
#include "wx/msgdlg.h"

const wxString TalkPath = wxT("script\\common\\Talk.dat");
const wxString TalkIndexPath = wxT("script\\common\\Talkidx.dat");

int CharToInt(char* char4)
{
	int temp = 0;
	temp |= ( ((int)((unsigned char)char4[0]) & (int)0xFF) );
	temp |= ( ((int)((unsigned char)char4[1]) & (int)0xFF) << 8 );
	temp |= ( ((int)((unsigned char)char4[2]) & (int)0xFF) << 16 );
	temp |= ( ((int)((unsigned char)char4[3]) & (int)0xFF) << 24 );
	return temp;
}

void IntToChar(int intNum, char* charStr)
{
	charStr[0] = (char)(intNum & 0xFF);
	charStr[1] = (char)((intNum >> 8) & 0xFF);
	charStr[2] = (char)((intNum >> 16) & 0xFF);
	charStr[3] = (char)((intNum >> 24) & 0xFF);
}

void IntToChar(int i1, int i2, int i3, char* charStr)
{
	IntToChar(i1, charStr);
	IntToChar(i2, charStr + 4);
	IntToChar(i3, charStr + 8);
}

TalkIndex::TalkIndex()
{
	wxLogNull logNo;
	wxFile talkFile, indexFile;
	char *talkText;
	char *indexBuffer;
	int talkFileSize, indexFileSize;
	if(talkFile.Open(TalkPath) &&
		indexFile.Open(TalkIndexPath))
	{
		talkFileSize = talkFile.Length();
		talkText = new char[talkFileSize];
		talkFile.Read(talkText, talkFileSize);

		indexFileSize = indexFile.Length();
		indexBuffer = new char[indexFileSize];
		indexFile.Read(indexBuffer, indexFileSize);
		talkFile.Close();
		indexFile.Close();
	}
	else
	{
		return;
	}

	int count = indexFileSize / 12;
	int *textOffset = new int[count + 1];

	int index = 8;
	for(int ic = 0; ic < count; ic++, index += 12)
	{
		textOffset[ic] = CharToInt(indexBuffer + index);
	}
	textOffset[count] = talkFileSize;

	index = 0;
	for(int i = 0; i < indexFileSize; i += 12, index++)
	{
		TalkDetail detail;
		detail.Index = CharToInt(indexBuffer + i);
		detail.PortraitIndex = CharToInt(indexBuffer + i + 4);
		detail.Text = wxString(talkText + textOffset[index],
								textOffset[index+1] - textOffset[index]);
		m_talkList.push_back(detail);
	}

	delete[] textOffset;
	delete[] indexBuffer;
	delete[] talkText;
}

TalkIndex::~TalkIndex()
{
	//dtor
}

TalkIndex::iterator TalkIndex::Begin()
{
	return m_talkList.begin();
}

TalkIndex::iterator TalkIndex::End()
{
	return m_talkList.end();
}

int TalkIndex::Count()
{
	return m_talkList.size();
}

int TalkIndex::GetNewIndex()
{
	if(Count() == 0)
	{
		return 0;
	}
	else
	{
		return (m_talkList.rbegin()->Index + 1);
	}
}

int TalkIndex::GetListIndex(int itemIndex)
{
	iterator end = End();
	int c = 0;
	for(iterator it = Begin(); it != end; it++, c++)
	{
		if(it->Index == itemIndex)
		{
			return c;
		}
	}
	return -1;
}

TalkIndex::iterator TalkIndex::GetIterator(int index)
{
	iterator it = Begin();
	iterator end = End();
	int c = 0;
	for(; it != end; it++, c++)
	{
		if(c == index)
		{
			break;
		}
	}
	return it;
}

TalkDetail* TalkIndex::GetItem(int index)
{
	iterator it = GetIterator(index);
	if(it != End())
	{
		return &(*it);
	}
	return NULL;
}

TalkDetail* TalkIndex::AppendItem()
{
	int newIndex = GetNewIndex();
	TalkDetail detail;
	detail.Index = newIndex;
	m_talkList.push_back(detail);
	return &(*m_talkList.rbegin());
}

TalkDetail* TalkIndex::AddAfter(int index)
{
	iterator it = GetIterator(index);
	if(it == End())
	{
		return AppendItem();
	}
	else
	{
		TalkDetail detail;
		detail.Index = it->Index + 1;

		it++;//Add one because insert in list is insert before
		return &(*m_talkList.insert(it, detail));
	}
}

void TalkIndex::Delete(int index)
{
	iterator it = GetIterator(index);
	if(it != End())
	{
		m_talkList.erase(it);
	}
}

void TalkIndex::Save()
{
	wxLogNull logNo;
	wxFile talkFile, indexFile;
	char intBuf[12];
	int offset = 0;
	if(talkFile.Open(TalkPath, wxFile::write) &&
		indexFile.Open(TalkIndexPath, wxFile::write))
	{
        for(iterator it = m_talkList.begin(); it != m_talkList.end(); it++)
		{
            if(it->Text.IsEmpty())
			{
				continue;
			}
			else
			{
				wxWritableCharBuffer str = it->Text.char_str();
				int length = strlen(str);
				talkFile.Write(str, length);
				IntToChar(it->Index, it->PortraitIndex, offset, intBuf);
				indexFile.Write(intBuf, 12);
				offset += length;
			}
		}
	}
}

