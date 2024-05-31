#ifndef ABSTRACT_FRAME_H
#define ABSTRACT_FRAME_H

#include <wx/wx.h>
#include <wx/display.h>

/**
 * @class AbstractFrame
 * @brief A class that represents an abstract frame in a graphical user interface.
 * 
 * This class is derived from the wxFrame class and provides additional functionality for setting and getting window properties.
 */
class AbstractFrame : public wxFrame
{
public:
    /**
     * @brief Constructs an AbstractFrame object.
     * 
     * @param parent The parent window.
     * @param id The window identifier.
     * @param title The window title.
     * @param pos The window position.
     * @param size The window size.
     */
    AbstractFrame(wxWindow *parent,
                  wxWindowID id,
                  const wxString &title,
                  const wxPoint &pos = wxDefaultPosition,
                  const wxSize &size = wxDefaultSize);

    ~AbstractFrame() = default;

    /**
     * @brief Sets the size of the window to a percentage of the width and height of the entire screen.
     *
     * @param p_windowHeightPercentage Percentage of the entire width of the screen.
     * @param p_windowWidthPercentage Percentage of the entire height of the screen.
     */
    void setDynamicWindowSize(int p_windowHeightPercentage,
                              int p_windowWidthPercentage);

    // SETTERS:
    /**
     * @brief Sets the window identifier.
     * 
     * @param p_newWindowId The new window identifier.
     */
    void setWindowId(wxWindowID p_newWindowId);

    /**
     * @brief Sets the window title.
     * 
     * @param p_newTitle The new window title.
     */
    void setWindowTitle(const wxString &p_newTitle);

    /**
     * @brief Sets the window position.
     * 
     * @param p_pos The new window position.
     */
    void setPosition(const wxPoint &p_pos);

    /**
     * @brief Sets the window size.
     * 
     * @param size The new window size.
     */
    void setSize(const wxSize &size);

    // GETTERS:
    /**
     * @brief Returns the parent window.
     * 
     * @return The parent window.
     */
    wxWindow *getParentWindow() const;

    /**
     * @brief Returns the window identifier.
     * 
     * @return The window identifier.
     */
    wxWindowID getWindowId() const;

    /**
     * @brief Returns the window title.
     * 
     * @return The window title.
     */
    wxString getWindowTitle() const;

    /**
     * @brief Returns the window position.
     * 
     * @return The window position.
     */
    wxPoint getPosition() const;

    /**
     * @brief Returns the window size.
     * 
     * @return The window size.
     */
    wxSize getSize() const;
};

#endif