#ifndef MAIN_PANEL_H
#define MAIN_PANEL_H

#include <wx/wx.h>
#include <wx/dir.h>
#include <vector>

#include "panels/AbstractPanel.h"
#include "NotebookAdapter.h"

// MainPanel class definition
class MainPanel : public AbstractPanel
{
public:
    MainPanel(ProgramConfiguration *p_programConfig,
              const wxSize &p_frameSize,
              NotebookAdapter *p_notebook,
              wxWindow *p_parent,
              wxWindowID p_id = wxID_ANY);

private:
    // Event handlers for the buttons to send invoices and reminders
    void onSendInvoices(wxCommandEvent &event);
    void onSendReminders(wxCommandEvent &event);

    bool findPdfFiles(const std::string &p_dirName, std::vector<std::string> &p_pdfFiles) const;

    // Notebook to hold the panels:
    NotebookAdapter *m_notebook;

    // Parent window and ID:
    wxWindow *m_parentWindow;
    wxWindowID m_id;

    // Buttons to send invoices and reminders:
    wxButton *m_buttonSendInvoices;
    wxButton *m_buttonSendReminders;

    // List of invoice files
    std::vector<wxString> m_invoiceFiles;
};

#endif // MAIN_PANEL_H