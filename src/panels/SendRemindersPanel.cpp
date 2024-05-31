#include "panels/SendRemindersPanel.h"
#include "NotebookAdapter.h"

// SendRemindersPanel class definition
SendRemindersPanel::SendRemindersPanel(ProgramConfiguration *p_programConfig,
                                       const wxSize &p_frameSize,
                                       NotebookAdapter *p_notebookAdapter,
                                       wxWindow *p_parent,
                                       wxWindowID p_id)
    : AbstractPanel(p_programConfig, p_frameSize, p_parent, p_id),
      m_notebookAdapter(p_notebookAdapter)
{
    // Create a button to send reminders:
    m_buttonSendReminders = new wxButton(this, wxID_ANY, "Send Reminders");
    m_buttonSendReminders->Bind(wxEVT_BUTTON, &SendRemindersPanel::onSendReminders, this);
}

// Event handler for the button to send reminders
void SendRemindersPanel::onSendReminders(wxCommandEvent &event)
{
    wxMessageBox(wxT("Sending reminders..."), wxT("Send Reminders"), wxOK | wxICON_INFORMATION);

    event.Skip();
}