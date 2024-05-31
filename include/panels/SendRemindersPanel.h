#ifndef SEND_REMINDERS_PANEL_H
#define SEND_REMINDERS_PANEL_H

#include <wx/wx.h>

#include "panels/AbstractPanel.h"
#include "NotebookAdapter.h"

// SendRemindersPanel class definition
class SendRemindersPanel : public AbstractPanel
{
public:
    SendRemindersPanel(ProgramConfiguration *p_programConfig,
                       const wxSize &p_frameSize,
                       NotebookAdapter *p_notebookAdapter,
                       wxWindow *p_parent,
                       wxWindowID p_id = wxID_ANY);

private:
    NotebookAdapter *m_notebookAdapter;

    // Event handler for the button to send reminders
    void onSendReminders(wxCommandEvent &event);

    // Button to send reminders:
    wxButton *m_buttonSendReminders;
};

#endif // SEND_REMINDERS_PANEL_H