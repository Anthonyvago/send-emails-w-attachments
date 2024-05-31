#ifndef EMAIL_THREAD_H
#define EMAIL_THREAD_H

#include <wx/thread.h>

class StatusPanel;

class EmailThread : public wxThread
{
public:
    EmailThread(StatusPanel *p_panel);
    virtual ~EmailThread();

protected:
    virtual ExitCode Entry(); // Entry point for the thread execution

private:
    StatusPanel *m_panel;
};

#endif // EMAIL_THREAD_H