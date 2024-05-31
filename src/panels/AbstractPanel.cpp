#include "panels/AbstractPanel.h"

#include "Constants.h"

#include <wx/display.h>

// AbstractPanel class definition
AbstractPanel::AbstractPanel(ProgramConfiguration *p_programConfig,
                             const wxSize &p_frameSize,
                             wxWindow *parent,
                             wxWindowID id)
    : wxPanel(parent, id),
      m_programConfig(*p_programConfig),
      m_frameWidth(p_frameSize.GetWidth()),
      m_frameHeight(p_frameSize.GetHeight())
{
  // Get the monitor's width and height:
  wxDisplay display;
  m_monitorWidth = display.GetGeometry().GetWidth();
  m_monitorHeight = display.GetGeometry().GetHeight();

  // Set background color to light grey:
  SetBackgroundColour(Constants::Style::WHITE_GREY);

  // Set the font for the panel:
  wxFont font(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
  SetFont(font);

  // Set the foreground color to black:
  SetForegroundColour(Constants::Style::BLACK);
}

void AbstractPanel::clearAndSetSizer(wxBoxSizer *p_boxSizer)
{
  // Clear the panel:
  GetSizer()->Clear();

  // Set the new sizer:
  SetSizer(p_boxSizer);
  Layout();
}