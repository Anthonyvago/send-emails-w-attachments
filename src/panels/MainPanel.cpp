#include "panels/MainPanel.h"

#include "Constants.h"
#include <algorithm>
#include <filesystem>
#include <wx/defs.h>
#include <wx/gdicmn.h>
#include <wx/gtk/stattext.h>
#include <wx/sizer.h>
#include <wx/display.h>
#include <regex>

// MainPanel class definition
MainPanel::MainPanel(ProgramConfiguration *p_programConfig,
                     const wxSize &p_frameSize,
                     NotebookAdapter *p_notebook,
                     wxWindow *p_parent,
                     wxWindowID p_id)
    : AbstractPanel(p_programConfig, p_frameSize, p_parent, p_id),
      m_notebook(p_notebook),
      m_parentWindow(p_parent),
      m_id(p_id)
{
    // Create a vertical sizer:
    wxBoxSizer *verticalSizer = new wxBoxSizer(wxVERTICAL);

    // Add spacing:
    verticalSizer->AddSpacer(static_cast<int>(static_cast<float>(m_frameHeight) * 0.2));

    // Add the title of this panel to the vertical sizer:
    wxStaticText *titleLabel = new wxStaticText(this, wxID_ANY, Constants::Panels::MainPanel::TITLE, wxDefaultPosition, wxSize(m_frameWidth, 40), wxALIGN_CENTER);
    titleLabel->SetFont(wxFont(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    verticalSizer->Add(titleLabel, 0, wxALIGN_CENTER | wxALL, 10);

    // Create horizontal sizer for the buttons:
    wxBoxSizer *btnSizer = new wxBoxSizer(wxHORIZONTAL);

    // Create the buttons:
    wxButton *sendInvoicesButton = new wxButton(this, wxID_ANY, Constants::Panels::MainPanel::BTN_TEXT_SEND_INVOICES, wxDefaultPosition, wxSize(m_frameWidth / 3, 50), wxBORDER_SIMPLE);
    wxButton *sendRemindersButton = new wxButton(this, wxID_ANY, Constants::Panels::MainPanel::BTN_TEXT_SEND_REMINDERS, wxDefaultPosition, wxSize(m_frameWidth / 3, 50), wxBORDER_SIMPLE);

    sendInvoicesButton->SetFont(wxFont(13, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    sendRemindersButton->SetFont(wxFont(13, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

    // Add the buttons to the button sizer:
    btnSizer->Add(sendInvoicesButton, 0, wxALL, 10);
    btnSizer->Add(sendRemindersButton, 0, wxALL, 10);

    verticalSizer->Add(btnSizer, 0, wxALIGN_CENTER);

    sendInvoicesButton->Bind(wxEVT_BUTTON, &MainPanel::onSendInvoices, this);
    sendRemindersButton->Bind(wxEVT_BUTTON, &MainPanel::onSendReminders, this);

    // Set the sizer for the panel:
    SetSizer(verticalSizer);
}

// Event handler for the button to send invoices
void MainPanel::onSendInvoices(wxCommandEvent &event)
{
    std::string invoicesDir = m_programConfig.invoicesDirectoryName;
    if (invoicesDir.empty())
    {
        wxMessageBox(wxT("Invoices directory is not set; Check configuration file!"), wxT("Error"), wxOK | wxICON_ERROR);
        return;
    }

    std::vector<std::string> pdfList;
    bool result = findPdfFiles(invoicesDir, pdfList);

    // If pdf files could not be found or an error occurred:
    if (!result)
    {
        return;
    }

    // Show the SendInvoicesPanel
    m_notebook->showInvoicesPanel(pdfList);
    event.Skip();
}

// Event handler for the button to send reminders
void MainPanel::onSendReminders(wxCommandEvent &event)
{
    std::string invoicesDir = m_programConfig.invoicesDirectoryName;
    if (invoicesDir.empty())
    {
        wxMessageBox(wxT("Invoices directory is not set; Check configuration file!"), wxT("Error"), wxOK | wxICON_ERROR);
        return;
    }

    std::vector<std::string> pdfList;
    bool result = findPdfFiles(invoicesDir, pdfList);
    if (!result)
    {
        return;
    }

    m_notebook->showRemindersPanel(pdfList);
    event.Skip();
}

bool naturalOrderComparator(const std::string &a, const std::string &b)
{
    std::regex re("(\\D+)(\\d*)"); // Regular expression to split non-digit and digit parts
    std::smatch matchA, matchB;
    std::string strA = a, strB = b;

    while (std::regex_search(strA, matchA, re) && std::regex_search(strB, matchB, re))
    {
        if (matchA[1] != matchB[1])
        {
            return matchA[1] < matchB[1]; // Compare non-digit parts
        }
        if (matchA[2] != matchB[2])
        {
            return std::stoi(matchA[2]) < std::stoi(matchB[2]); // Compare digit parts
        }
        strA = matchA.suffix().str();
        strB = matchB.suffix().str();
    }
    return a < b; // Fallback to default comparison
}

bool MainPanel::findPdfFiles(const std::string &p_dirName, std::vector<std::string> &p_pdfFiles) const
{
    try
    {
        for (const auto &entry : std::filesystem::directory_iterator(p_dirName))
        {
            if (entry.is_regular_file() && entry.path().extension() == ".pdf")
            {
                p_pdfFiles.push_back(entry.path().filename().string());
            }
        }
    }
    catch (const std::filesystem::filesystem_error &e)
    {
        wxString errMsg(e.what(), wxConvUTF8);
        wxMessageBox("Error occurred while reading the invoices directory!\n\nTraceback:\n" + errMsg, wxT("Error"), wxOK | wxICON_ERROR);
        return false;
    }

    // Check if pdf files were found:
    if (p_pdfFiles.empty())
    {
        wxMessageBox(wxT("No PDF files found in the invoices directory!"), wxT("Error"), wxOK | wxICON_ERROR);
        return false;
    }

    std::sort(p_pdfFiles.begin(), p_pdfFiles.end(), naturalOrderComparator);

    return true;
}