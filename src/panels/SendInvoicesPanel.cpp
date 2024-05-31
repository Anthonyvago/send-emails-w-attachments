#include "panels/SendInvoicesPanel.h"

#include "Constants.h"
#include <wx/defs.h>

SendInvoicesPanel::SendInvoicesPanel(ProgramConfiguration *p_programConfig,
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
    Bind(wxEVT_SHOW, &SendInvoicesPanel::onShow, this);
}

// Define the event table
BEGIN_EVENT_TABLE(SendInvoicesPanel, wxPanel)
// No additional events needed for this example
END_EVENT_TABLE()

void SendInvoicesPanel::onShow(wxShowEvent &event)
{
    if (event.IsShown())
    {
        // Get the list of invoice files:
        std::vector<std::string> pdfList = m_notebookAdapter->getPdfList();

        wxBoxSizer *verticalMainSizer = new wxBoxSizer(wxVERTICAL);

        // Add some space between the top of the panel and the title:
        verticalMainSizer->AddSpacer(30);

        // Add a static text control with the title:
        wxStaticText *staticText = new wxStaticText(this, wxID_ANY, Constants::Panels::SendInvoicesPanel::TITLE);
        staticText->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
        verticalMainSizer->Add(staticText, 0, wxALIGN_CENTER_HORIZONTAL, 10); // Adjust alignment as needed

        // Add some space between the title and the text fields:
        verticalMainSizer->AddSpacer(30);

        // For each invoice, create a static text control and a text field right next to it:
        for (size_t pdfIndex = 0; pdfIndex < pdfList.size(); pdfIndex++)
        {
            // Static text for the PDF name:
            wxBoxSizer *horizontalSizer = new wxBoxSizer(wxHORIZONTAL);
            wxStaticText *staticText = new wxStaticText(this, wxID_ANY, wxString::FromUTF8(pdfList[pdfIndex].c_str()));
            staticText->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
            horizontalSizer->Add(staticText, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10); // Adjust alignment as needed

            // Text field for the email address:
            wxTextCtrl *textField = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition);
            textField->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
            horizontalSizer->Add(textField, 1, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
            
            m_invoiceLine.push_back(std::make_pair(staticText, textField));

            // Bind TAB key to move to the next text field:
            textField->Bind(wxEVT_CHAR, &SendInvoicesPanel::onTextFieldChar, this);

            verticalMainSizer->Add(horizontalSizer, 0, wxEXPAND | wxALL, 7); // Adjust spacing as needed
        }

        // Add some space between the text fields and the button:
        verticalMainSizer->AddSpacer(10);

        // Create the button to send invoices:
        m_buttonSendInvoices = new wxButton(this, wxID_ANY, Constants::Panels::SendInvoicesPanel::BTN_TEXT_SEND_INVOICES);
        m_buttonSendInvoices->Bind(wxEVT_BUTTON, &SendInvoicesPanel::onSendInvoices, this);
        m_buttonSendInvoices->SetSize(wxSize(m_frameWidth / 2, 50));
        m_buttonSendInvoices->SetFont(wxFont(17, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

        // Add the button to the sizer:
        verticalMainSizer->Add(m_buttonSendInvoices, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10); // Adjust alignment as needed

        // Add the sizer to the panel:
        clearAndSetSizer(verticalMainSizer);

        // Adjust the size of the parent frame according to the number of invoices:
        size_t newHeight = 150 + 50 * pdfList.size();
        m_notebookAdapter->adjustFrameHeight(newHeight);
    }
}

void SendInvoicesPanel::onTextFieldChar(wxKeyEvent &event)
{
    // Move to the next text field when the TAB key is pressed:
    if (event.GetKeyCode() == WXK_TAB && event.ShiftDown() == false)
    {
        for (size_t i = 0; i < m_invoiceLine.size(); i++)
        {
            if (m_invoiceLine[i].second->HasFocus())
            {
                if (i == m_invoiceLine.size() - 1)
                {
                    m_invoiceLine[0].second->SetFocus();
                }
                else
                {
                    m_invoiceLine[i + 1].second->SetFocus();
                }
                break;
            }
        }
    }
    else if (event.GetKeyCode() == WXK_TAB && event.ShiftDown() == true)
    {
        for (size_t i = 0; i < m_invoiceLine.size(); i++)
        {
            if (m_invoiceLine[i].second->HasFocus())
            {
                if (i == 0)
                {
                    m_invoiceLine[m_invoiceLine.size() - 1].second->SetFocus();
                }
                else
                {
                    m_invoiceLine[i - 1].second->SetFocus();
                }
                break;
            }
        }
    }
    // Skip the event if the TAB key is not pressed:
    else
    {
        event.Skip();
    }
}

void SendInvoicesPanel::onSendInvoices(wxCommandEvent &event)
{
    m_notebookAdapter->showStatusPanel(m_invoiceLine);
    event.Skip();
}