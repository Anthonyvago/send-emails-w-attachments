#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <wx/wx.h>

namespace Constants
{
    namespace PanelIndexes
    {
        const static int MAIN = 0;
        const static int INVOICES = 1;
        const static int REMINDERS = 2;
        const static int STATUS = 3;
    } // namespace PanelIndexes

    namespace Style
    {
        const static wxColour BLACK = wxColour(0, 0, 0);
        const static wxColour WHITE_GREY = wxColor(240, 240, 240);
        const static wxColour DARK_BLUE_ACCENT_COLOR = wxColor(6, 57, 112); // Dark blue-ish
    } // namespace Style

    namespace Panels
    {
        const static std::string TITLE = "Automated Send Invoices";

        namespace MainPanel
        {
            const static std::string TITLE = "Selecteer een optie:";
            const static std::string BTN_TEXT_SEND_INVOICES = "Verstuur facturen";
            const static std::string BTN_TEXT_SEND_REMINDERS = "Verstuur herinneringen";
        } // namespace Main

        namespace SendInvoicesPanel
        {
            const static std::string TITLE = "Geef de e-mailadressen op (lege velden worden genegeerd):";
            const static std::string BTN_TEXT_SEND_INVOICES = "Verstuur facturen";

        } // namespace SendInvoices

        namespace StatusPanel
        {
            const static std::string TITLE = "Status:";

            namespace Status
            {
                const static std::string IGNORING = "Genegeerd";
                const static std::string PENDING = "In wachtrij";
                const static std::string SENDING = "Verzenden...";
                const static std::string SENT = "Verzonden!";
                const static std::string ERROR = "Fout opgetreden!";
                const static std::string ERROR_INPUT = "Ongeldig adres!";
            } // namespace Status

            namespace Colors
            {
                const static wxColour IGNORING = wxColour(170, 170, 170);   // light grey
                const static wxColour PENDING = wxColour(6, 57, 112);       // same as accent color
                const static wxColour SENDING = wxColour(255, 165, 0);      // orange
                const static wxColour SENT = wxColour(0, 128, 0);           // green
                const static wxColour ERROR = wxColour(220, 20, 60);        // red
                const static wxColour ERROR_INPUT = wxColour(220, 20, 60);  // red
            }
        } // namespace Status

        namespace Size
        {
            const static int DEFAULT_WIDTH_PERCENTAGE = 30;  // percentage
            const static int DEFAULT_HEIGHT_PERCENTAGE = 30; // percentage
        } // namespace Size

    } // namespace Windows

    namespace Configuration
    {
        const static std::string PROJECT_CONFIG_FILE_PATH = "../project_configuration.json";
        const static std::string EMAIL_CONFIG_FILE_PATH = "../email_content.json";
    } // namespace Login

    namespace OutputStd
    {
        const static std::string GREEN = "\033[1;32m";
        const static std::string PINK = "\033[1;35m";
        const static std::string YELLOW = "\033[1;33m";
        const static std::string ORANGE = "\033[1;31m";
        const static std::string RESET = "\033[0m";
        const static std::string RED = "\033[1;31m";
        const static std::string BLUE = "\033[1;34m";
        const static std::string CYAN = "\033[1;36m";
        const static std::string MAGENTA = "\033[1;35m";
        const static std::string WHITE = "\033[1;37m";
        const static std::string BLACK = "\033[1;30m";
        const static std::string LIGHT_RED = "\033[1;91m";
        const static std::string LIGHT_GREEN = "\033[1;92m";
        const static std::string LIGHT_YELLOW = "\033[1;93m";
        const static std::string LIGHT_BLUE = "\033[1;94m";
        const static std::string LIGHT_MAGENTA = "\033[1;95m";
        const static std::string LIGHT_CYAN = "\033[1;96m";
        const static std::string LIGHT_WHITE = "\033[1;97m";
        const static std::string DARK_GRAY = "\033[1;90m";
        const static std::string BOLD = "\033[1m";
    } // namespace OutputStd
}

#endif