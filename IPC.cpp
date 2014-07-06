#include "wx/ipc.h"

#include "JxqyScriptEditor.h"

class DDEServer;
class DDEClient;
class DDEConnection;

#define DDE_SERVICE wxT("JxqyScriptEditorServer")
#define DDE_TOPIC wxT("JxqyScriptEditorIpc")

DDEServer* g_DDEServer = NULL;

class DDEServer : public wxServer
{
    public:
        DDEServer( JxqyScriptEditor * frame) : m_Frame(frame) { ; }
        wxConnectionBase *OnAcceptConnection(const wxString& topic);
        JxqyScriptEditor* GetFrame()                 { return m_Frame;  }
        void       SetFrame(JxqyScriptEditor* frame) { m_Frame = frame; }
    private:
        JxqyScriptEditor* m_Frame;
};
class DDEConnection : public wxConnection
{
    public:
        DDEConnection(JxqyScriptEditor* frame) : m_Frame(frame) { ; }
		bool OnExec(const wxString &  topic, const wxString &  data);
        bool OnDisconnect();
    private:
        JxqyScriptEditor* m_Frame;
        wxArrayString m_openedFiles;
};
class DDEClient: public wxClient {
    public:
        DDEClient(void) {}
        wxConnectionBase *OnMakeConnection(void) { return new DDEConnection(NULL); }
};


wxConnectionBase* DDEServer::OnAcceptConnection(const wxString& topic)
{
    return topic == DDE_TOPIC ? new DDEConnection(m_Frame) : NULL;
}

bool DDEConnection::OnExec(const wxString& topic, const wxString& data)
{
	if(topic == DDE_TOPIC)
	{
		m_openedFiles.Add(data);
	}
	return true;
}

bool DDEConnection::OnDisconnect()
{
	if(!m_openedFiles.IsEmpty())
	{
		for(size_t i = 0; i < m_openedFiles.Count(); i++)
		{
			m_Frame->OpenFile(m_openedFiles[i]);
		}
		m_Frame->Raise();
	}
	return true;
}
