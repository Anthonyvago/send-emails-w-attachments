#ifndef SEND_INVOICES_PANEL_H
#define SEND_INVOICES_PANEL_H

#include <wx/wx.h>
#include <wx/wx.h>
#include <vector>

#include "panels/AbstractPanel.h"
#include "NotebookAdapter.h"

// SendPanel class definition
class SendInvoicesPanel : public AbstractPanel
{
public:
    SendInvoicesPanel(ProgramConfiguration *p_programConfig,
                      const wxSize &p_frameSize,
                      NotebookAdapter *p_notebookAdapter,
                      wxWindow *p_parent,
                      wxWindowID p_id = wxID_ANY);

private:
    // Event handler for the button to send reminders
    void onSendInvoices(wxCommandEvent &event);

    // Event handler for the show event
    void onShow(wxShowEvent &event);

    // Event handler for the text fields:
    void onTextFieldChar(wxKeyEvent &event);

    std::vector<std::pair<wxStaticText *, wxTextCtrl *>> m_invoiceLine;

    // NotebookAdapter instance (parent):
    NotebookAdapter *m_notebookAdapter;

    // Button to send invoices:
    wxButton *m_buttonSendInvoices;

    DECLARE_EVENT_TABLE()
};

#endif // SEND_INVOICES_PANEL_H