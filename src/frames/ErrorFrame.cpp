#include "frames/ErrorFrame.h"

#include "Constants.h"
#include <wx/gtk/colour.h>

ErrorFrame::ErrorFrame(wxWindow *p_parent,
                       wxWindowID p_id,
                       const std::string &p_errorText,
                       const wxPoint &p_pos,
                       const wxSize &p_size)
    : AbstractFrame(p_parent, p_id, "Error", p_pos, p_size)
{
    // Set the window's size:
    setDynamicWindowSize(Constants::Panels::Size::DEFAULT_WIDTH_PERCENTAGE,
                         Constants::Panels::Size::DEFAULT_HEIGHT_PERCENTAGE);

    // Display login text:
    showErrorText(p_errorText);
}

void ErrorFrame::showErrorText(const std::string &p_errorText)
{
    std::string errorText = "Error occurred: \n\n" + p_errorText;

    // Create a static text control with your desired login text
    m_errorText = new wxStaticText(this, wxID_ANY, errorText, wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);

    m_errorText->SetForegroundColour(wxColour(255, 0, 0)); // Red color
}

ErrorFrame::~ErrorFrame()
{

}
