#ifndef ABSTRACT_PANEL_H
#define ABSTRACT_PANEL_H

#include <wx/wx.h>

#include "ProgramConfigurationHandler.h"

// AbstractPanel class definition
class AbstractPanel : public wxPanel
{
public:
    AbstractPanel(ProgramConfiguration *p_programConfig,
                  const wxSize &p_frameSize,
                  wxWindow *parent,
                  wxWindowID id = wxID_ANY);

protected:
    /**
     * @brief Clear the panel and set a new panel.
     * 
     * @param p_boxSizer The new panel to set.
     */
    void clearAndSetSizer(wxBoxSizer *p_boxSizer);

    ProgramConfiguration m_programConfig;

    // Frame's width and height (set in initializer list):
    int m_frameWidth;
    int m_frameHeight;

    // Monitor's width and height (set in the constructor):
    int m_monitorWidth;
    int m_monitorHeight;
};

#endif // ABSTRACT_PANEL_H