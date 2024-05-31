#ifndef LOADING_FRAME_H
#define LOADING_FRAME_H

#include "AbstractFrame.h"

class ErrorFrame : public AbstractFrame
{
public:
    ErrorFrame(wxWindow *p_parent,
               wxWindowID id,
               const std::string &errorText,
               const wxPoint &pos = wxDefaultPosition,
               const wxSize &size = wxDefaultSize);

    ~ErrorFrame();

private:
    void showErrorText(const std::string &p_errorText);

    wxStaticText *m_errorText;
};

#endif // LOADING_FRAME_H