#ifndef MAIN_FRAME_H
#define MAIN_FRAME_H

#include <wx/notebook.h>

#include "AbstractFrame.h"
#include "ProgramConfigurationHandler.h"

#include "NotebookAdapter.h"

#include "panels/MainPanel.h"
#include "panels/SendInvoicesPanel.h"
#include "panels/SendRemindersPanel.h"
#include "panels/StatusPanel.h"

class MainFrame : public AbstractFrame
{
public:
    MainFrame(ProgramConfiguration *p_programConfig,
              wxWindow *parent,
              wxWindowID id,
              const wxPoint &pos = wxDefaultPosition,
              const wxSize &size = wxDefaultSize);

    ~MainFrame();

    void showInvoicesPanel();

    void showRemindersPanel();

private:
    // Program configuration:
    ProgramConfiguration *m_programConfig;

    // Notebook to hold the panels:
    NotebookAdapter *m_notebook;

    // All Panels:
    MainPanel *m_mainPanel;
    SendInvoicesPanel *m_sendInvoicesPanel;
    SendRemindersPanel *m_sendRemindersPanel;
    StatusPanel *m_statusPanel;

};

#endif // MAIN_FRAME_H