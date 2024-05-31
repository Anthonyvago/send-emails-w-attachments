#include "frames/MainFrame.h"

#include "Constants.h"
#include "frames/ErrorFrame.h"

MainFrame::MainFrame(ProgramConfiguration *p_programConfig,
                     wxWindow *parent,
                     wxWindowID id,
                     const wxPoint &pos,
                     const wxSize &size)
    : AbstractFrame(parent, id, Constants::Panels::TITLE, pos, size),
      m_programConfig(p_programConfig)
{
    // Create the notebook:
    m_notebook = new NotebookAdapter(this, wxID_ANY);

    // Create the main panel:
    m_mainPanel = new MainPanel(m_programConfig, size, m_notebook, m_notebook);
    m_sendInvoicesPanel = new SendInvoicesPanel(m_programConfig, size, m_notebook, m_notebook);
    m_sendRemindersPanel = new SendRemindersPanel(m_programConfig, size, m_notebook, m_notebook);
    m_statusPanel = new StatusPanel(m_programConfig, size, m_notebook, m_notebook);

    m_notebook->AddPage(m_mainPanel, "Main panel");
    m_notebook->AddPage(m_sendInvoicesPanel, "Send invoices panel");
    m_notebook->AddPage(m_sendRemindersPanel, "Send reminders panel");
    m_notebook->AddPage(m_statusPanel, "Status Panel");

    // Create vertical boxsizer:
    wxBoxSizer *notebookBoxSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(notebookBoxSizer);
    GetSizer()->Add(m_notebook, 1, wxEXPAND);
}

MainFrame::~MainFrame()
{
}