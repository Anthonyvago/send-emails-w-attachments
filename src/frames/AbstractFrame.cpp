#include "frames/AbstractFrame.h"

#include "Constants.h"

AbstractFrame::AbstractFrame(wxWindow *p_parent,
                             wxWindowID p_id,
                             const wxString &p_title,
                             const wxPoint &p_pos,
                             const wxSize &p_size)
    : wxFrame(p_parent, p_id, p_title, p_pos, p_size)
{
}

void AbstractFrame::setDynamicWindowSize(int p_windowWidthPercentage,
                                         int p_windowHeightPercentage)
{
  int screenWidth = wxDisplay().GetGeometry().GetWidth();
  int screenheight = wxDisplay().GetGeometry().GetHeight();

  float screenWidthMultiplier = static_cast<float>(p_windowWidthPercentage) / 100.0f;
  float screenHeightMultiplier = static_cast<float>(p_windowHeightPercentage) / 100.0f;

  int newScreenWidth = static_cast<int>(static_cast<float>(screenWidth) * screenWidthMultiplier);
  int newScreenHeight = static_cast<int>(static_cast<float>(screenheight) * screenHeightMultiplier);

  SetSize(newScreenWidth, newScreenHeight);
}

// SETTERS:
void AbstractFrame::setWindowId(wxWindowID p_newWindowId)
{
  SetId(p_newWindowId);
}

void AbstractFrame::setWindowTitle(const wxString &p_newTitle)
{
  SetTitle(p_newTitle);
}

void AbstractFrame::setPosition(const wxPoint &p_pos)
{
  SetPosition(p_pos);
}

void AbstractFrame::setSize(const wxSize &size)
{
  SetSize(size);
}

// GETTERS:
wxWindow *AbstractFrame::getParentWindow() const
{
  return GetParent();
}

wxWindowID AbstractFrame::getWindowId() const
{
  return GetId();
}

wxString AbstractFrame::getWindowTitle() const
{
  return GetTitle();
}

wxPoint AbstractFrame::getPosition() const
{
  return GetPosition();
}

wxSize AbstractFrame::getSize() const
{
  return GetSize();
}