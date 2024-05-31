#include "panels/StatusPanel.h"

#include "Constants.h"
#include "frames/ErrorFrame.h"
#include <wx/colour.h>
#include <wx/control.h>
#include <wx/defs.h>
#include <wx/gdicmn.h>
#include <wx/gtk/stattext.h>

wxBEGIN_EVENT_TABLE(StatusPanel, wxPanel)
    EVT_SHOW(StatusPanel::OnShow)
        wxEND_EVENT_TABLE()

            StatusPanel::StatusPanel(ProgramConfiguration *p_programConfig,
                                     const wxSize &p_frameSize,
                                     NotebookAdapter *p_notebookAdapter,
                                     wxWindow *p_parent,
                                     wxWindowID p_id)
    : AbstractPanel(p_programConfig, p_frameSize, p_parent, p_id),
      m_notebookAdapter(p_notebookAdapter)
{
    // Create the sizer for the panel:
    wxBoxSizer *verticalSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(verticalSizer);

    // Bind the show event to the onShow method:
    Bind(wxEVT_SHOW, &StatusPanel::OnShow, this);
}

void StatusPanel::OnShow(wxShowEvent &event)
{
    if (event.IsShown())
    {
        // This is where the code for the status panel will go.
        // the code will be similar to the code in the SendInvoicesPanel::onShow method.
        // The code will be used to display the status of the invoices that were sent.
        // The invoices will be displayed in a list with the invoice number and the status of the invoice.

        // Get the list of invoice files:
        std::vector<std::pair<wxStaticText *, wxTextCtrl *>> invoiceLines = m_notebookAdapter->getInvoiceLines();

        wxBoxSizer *verticalMainSizer = new wxBoxSizer(wxVERTICAL);

        // Add some space between the top of the panel and the title:
        verticalMainSizer->AddSpacer(30);

        // Add a static text control with the title:
        wxStaticText *staticText = new wxStaticText(this, wxID_ANY, Constants::Panels::StatusPanel::TITLE.c_str(), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);
        staticText->SetFont(wxFont(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
        staticText->SetMaxSize(wxSize(-1, 30));

        verticalMainSizer->Add(staticText, 1, wxEXPAND, 10); // Adjust alignment as needed

        // Add some space between the title and the text fields:
        verticalMainSizer->AddSpacer(30);

        // For each invoice, create a static text control and a text field right next to it:
        for (const std::pair<wxStaticText *, wxTextCtrl *> &pair : invoiceLines)
        {
            wxBoxSizer *horizontalInvoiceLineSizer = new wxBoxSizer(wxHORIZONTAL);

            // Create a new Static text for the invoice number:
            wxStaticText *invoiceText = new wxStaticText(this, wxID_ANY, pair.first->GetLabel().ToStdString(), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT);
            invoiceText->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
            horizontalInvoiceLineSizer->Add(invoiceText, 1, wxEXPAND | wxALL);

            horizontalInvoiceLineSizer->AddSpacer(10);

            // Set all the status texts to "Pending" for now:
            std::string statusTextStr = pair.second->GetValue().ToStdString();
            if (!statusTextStr.empty())
            {
                statusTextStr = Constants::Panels::StatusPanel::Status::PENDING;
            }

            // Create a wxStaticText for the status:
            wxStaticText *statusText = new wxStaticText(this, wxID_ANY, wxString::FromUTF8(statusTextStr.c_str()), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
            statusText->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
            // Set a minimum size for the status text, so the text is not cut off:
            statusText->SetMinSize(wxSize(-1, 35));

            // Add the status text to the list of status texts so it can be updated later:
            m_statusTexts.push_back(std::make_pair(statusText, InvoiceStatus::PENDING));

            // Add the status text to invoice line pair:
            horizontalInvoiceLineSizer->Add(statusText, 1, wxEXPAND | wxALL); // Adjust alignment as needed

            // Add the horizontal sizer to the vertical sizer:
            verticalMainSizer->Add(horizontalInvoiceLineSizer, 0, wxEXPAND | wxALL, 10);

            // Add some space between the invoice number and the status text:
            // verticalMainSizer->AddSpacer(20);
        }

        // Refresh the status of each invoice:
        refreshInvoiceStatusColors();

        clearAndSetSizer(verticalMainSizer);

        // Now start the process of sending the emails by first reading the email configuration file:
        m_emailThread = new EmailThread(this);
        if (m_emailThread->Create() != wxTHREAD_NO_ERROR)
        {
            ErrorFrame *errorFrame = new ErrorFrame(this, wxID_ANY, "Could not create the thread!");
            errorFrame->Show();
            return;
        }
        if (m_emailThread->Run() != wxTHREAD_NO_ERROR)
        {
            ErrorFrame *errorFrame = new ErrorFrame(this, wxID_ANY, "Could not run the thread!");
            errorFrame->Show();
            return;
        }
    }
}

void StatusPanel::handleSendEmails()
{
    // This function handles the email sending process.
    // This process consists out of two steps:
    // 1. Read the email configuration file.
    // 2. Send the emails per invoice, update the status of the invoice (only the text) and
    //      call 'refreshInvoiceStatus()' so the color is changed as well.

    // 1. Read the email configuration file (can be nullptr if something went wrong):
    EmailConfiguration *emailContentConfig = m_programConfigHandler.readEmailConfigFile();

    // If 'emailConfig' is nullptr, then an error occurred while reading the email configuration file:
    if (emailContentConfig == nullptr)
    {
        // Display an error message:
        ErrorFrame *errorFrame = new ErrorFrame(this, wxID_ANY, m_programConfigHandler.getErrorMessage());
        errorFrame->Show();
        return;
    }

    // Create an EmailHandler instance:
    EmailHandler emailHandler(&m_programConfig, emailContentConfig);

    // 2. Get the list of invoice files:
    std::vector<std::pair<wxStaticText *, wxTextCtrl *>> invoiceLines = m_notebookAdapter->getInvoiceLines();

    // For each invoice, send the email:
    for (size_t invoiceIndex = 0; invoiceIndex < invoiceLines.size(); invoiceIndex++)
    {
        // Get the invoice number and the email address:
        std::string invoiceFileName = invoiceLines[invoiceIndex].first->GetLabel().ToStdString();
        std::string emailAddress = invoiceLines[invoiceIndex].second->GetValue().ToStdString();

        // Check if the email address is empty:
        if (emailAddress.empty())
        {
            updateInvoiceStatus(invoiceIndex, InvoiceStatus::IGNORING);
            continue; // Skip this invoice, because the email address is empty.
        }

        // Check if the email address has a valid format:
        if (!emailHandler.validEmailAddressFormat(emailAddress))
        {
            updateInvoiceStatus(invoiceIndex, InvoiceStatus::ERROR_INPUT, emailAddress);
            continue; // Skip this invoice, because the email address is invalid.
        }

        // Now the email can be sent.

        // Update the status of the invoice to "Sending":
        updateInvoiceStatus(invoiceIndex, InvoiceStatus::SENDING, emailAddress);

        // Send the email:
        auto msg = emailHandler.constructEmailMessage(emailAddress, invoiceFileName);

        bool success = emailHandler.sendEmail(msg);

        if (success)
        {
            // Update the status of the invoice to "Sending":
            updateInvoiceStatus(invoiceIndex, InvoiceStatus::SENT, emailAddress);
        }
        else
        {
            // Update the status of the invoice to "Not Sending":
            updateInvoiceStatus(invoiceIndex, InvoiceStatus::ERROR);
        }
    }
}

void StatusPanel::updateInvoiceStatus(size_t p_invoiceIndex,
                                      const enum InvoiceStatus &p_newStatus,
                                      const std::string &p_someText)
{
    // First, check if the index is out of bounds:
    if (p_invoiceIndex >= m_statusTexts.size())
    {
        return;
    }

    std::string newStatusText = "";
    switch (p_newStatus)
    {
    case InvoiceStatus::IGNORING:
        newStatusText = Constants::Panels::StatusPanel::Status::IGNORING;
        break;
    case InvoiceStatus::PENDING:
        newStatusText = Constants::Panels::StatusPanel::Status::PENDING;
        break;
    case InvoiceStatus::SENDING:
        newStatusText = Constants::Panels::StatusPanel::Status::SENDING + " " + p_someText;
        break;
    case InvoiceStatus::SENT:
        newStatusText = Constants::Panels::StatusPanel::Status::SENT + " " + p_someText;
        break;
    case InvoiceStatus::ERROR:
        newStatusText = Constants::Panels::StatusPanel::Status::ERROR;
        break;
    case InvoiceStatus::ERROR_INPUT:
        newStatusText = Constants::Panels::StatusPanel::Status::ERROR_INPUT + " " + p_someText;
        break;
    default:
        break;
    }

    // Change new status (for color change later on):
    m_statusTexts[p_invoiceIndex].second = p_newStatus;

    CallAfter([=]()
              {
                    // Update the status of the invoice:
                    m_statusTexts[p_invoiceIndex].first->SetLabel(newStatusText);

                    // Refresh the color of all status:
                    refreshInvoiceStatusColors();

                    // Update the layout of the panel so the new status fits on the UI:
                    Layout(); });
}

void StatusPanel::refreshInvoiceStatusColors()
{
    // This is where the code to refresh the status of the invoices will go.
    // The code will be used to update the status of the invoices.

    // Get the list of invoice files:
    std::vector<std::pair<wxStaticText *, wxTextCtrl *>> invoiceLines = m_notebookAdapter->getInvoiceLines();

    // For each invoice, update the status:
    for (const std::pair<wxStaticText *, InvoiceStatus>& pair : m_statusTexts)
    {
        const InvoiceStatus currentStatus = pair.second;
        wxStaticText *staticText = pair.first;

        if (currentStatus == InvoiceStatus::IGNORING) // Means the emailaddress was empty, so ignore this invoice:
        {
            staticText->SetForegroundColour(Constants::Panels::StatusPanel::Colors::IGNORING);
        }
        else if (currentStatus == InvoiceStatus::PENDING)
        {
            staticText->SetForegroundColour(Constants::Panels::StatusPanel::Colors::PENDING);
        }
        else if (currentStatus == InvoiceStatus::SENDING)
        {
            staticText->SetForegroundColour(Constants::Panels::StatusPanel::Colors::SENDING);
        }
        else if (currentStatus == InvoiceStatus::SENT)
        {
            staticText->SetForegroundColour(Constants::Panels::StatusPanel::Colors::SENT);
        }
        else if (currentStatus == InvoiceStatus::ERROR)
        {
            staticText->SetForegroundColour(Constants::Panels::StatusPanel::Colors::ERROR);
        }
        else if (currentStatus == InvoiceStatus::ERROR_INPUT)
        {
            staticText->SetForegroundColour(Constants::Panels::StatusPanel::Colors::ERROR_INPUT);
        }
    }
}