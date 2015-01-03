#include "TalkIndex.h"
#include "wx/file.h"
#include "wx/log.h"

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
		detail.PortraitIndex = CharToInt(indexBuffer + i + 4);
		detail.Text = wxString(talkText + textOffset[index],
								textOffset[index+1] - textOffset[index]);
		m_talkList[CharToInt(indexBuffer + i)] = detail;
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

TalkDetail* TalkIndex::GetItem(int index)
{
	if(m_talkList.count(index))
	{
		return &(m_talkList[index]);
	}
	else
	{
		return NULL;
	}
}

bool TalkIndex::SetItem(int index, int portraitIndex, const wxString& text)
{
	TalkDetail *item = GetItem(index);
	if(item)
	{
		item->PortraitIndex = portraitIndex;
		item->Text = text;
	}
	return (bool)item;
}

bool TalkIndex::AddItem(int index)
{
	if(m_talkList.count(index))
	{
		return false;
	}
	else
	{
		m_talkList[index];
		return true;
	}
}

bool TalkIndex::AddAfter(int index)
{
	return AddItem(index + 1);
}

bool TalkIndex::AddBefore(int index)
{
	return AddItem(index - 1);
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
            if(it->second.Text.IsEmpty())
			{
				continue;
			}
			else
			{
				const char* str = it->second.Text.char_str();
				int length = strlen(str);
				talkFile.Write(str, length);
				IntToChar(it->first, it->second.PortraitIndex, offset, intBuf);
				indexFile.Write(intBuf, 12);
				offset += length;
			}
		}
	}
}

