#include <wx/wx.h>

#include "Constants.h"
#include "frames/MainFrame.h"
#include "frames/ErrorFrame.h"
#include "JsonParser.h"

int getWidth()
{
    wxDisplay display;
    return static_cast<int>(static_cast<float>(display.GetGeometry().GetWidth()) * static_cast<float>(Constants::Panels::Size::DEFAULT_WIDTH_PERCENTAGE / 100.0f));
}

int getHeight()
{
    wxDisplay display;
    return static_cast<int>(static_cast<float>(display.GetGeometry().GetHeight()) * static_cast<float>(Constants::Panels::Size::DEFAULT_HEIGHT_PERCENTAGE / 100.0f));
}

class MyApp : public wxApp
{
public:
    // Initialize your application here
    // Create and show your main frame or other UI elements
    virtual bool OnInit() override
    {
        // Retrieve the login credentials from the configuration file:
        JsonParser jsonParser;

        // Read login credentials from the config file
        ProgramConfiguration *programConfig = jsonParser.readProjectConfigFile();
        // Check if credentials were successfully read
        if (programConfig == nullptr)
        {
            // Display error frame:
            m_errorFrame = new ErrorFrame(nullptr, wxID_ANY, jsonParser.getErrorMessage());
            m_errorFrame->Show();
            return true;
        }

        // Go to first frame (MainFrame):
        m_mainFrame = new MainFrame(programConfig, nullptr, wxID_ANY, wxDefaultPosition, wxSize(getWidth(), getHeight()));
        m_mainFrame->Show();

        return true;
    }

    virtual int OnExit() override
    {

        return 0; // Return an exit code (usually 0 for success)
    }

protected:
private:
    MainFrame* m_mainFrame;
    ErrorFrame* m_errorFrame;
};

wxIMPLEMENT_APP(MyApp);