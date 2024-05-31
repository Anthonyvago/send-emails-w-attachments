#include "EmailThread.h"

#include "panels/StatusPanel.h"

EmailThread::EmailThread(StatusPanel *p_panel)
    : wxThread(wxTHREAD_DETACHED),
      m_panel(p_panel)
{
}

EmailThread::~EmailThread()
{
}

wxThread::ExitCode EmailThread::Entry()
{
    if (m_panel)
    {
        m_panel->handleSendEmails();
    }
    return (wxThread::ExitCode)0;
}