#ifndef STATUS_PANEL_H
#define STATUS_PANEL_H

#include <wx/wx.h>
#include <wx/wx.h>
#include <vector>

#include "EmailHandler.h"
#include "panels/AbstractPanel.h"
#include "NotebookAdapter.h"
#include "EmailThread.h"

enum class InvoiceStatus
{
    IGNORING,
    PENDING,
    SENDING,
    SENT,
    ERROR,
    ERROR_INPUT
};

// SendPanel class definition
class StatusPanel : public AbstractPanel
{
public:
    StatusPanel(ProgramConfiguration *p_programConfig,
                const wxSize &p_frameSize,
                NotebookAdapter *p_notebookAdapter,
                wxWindow *p_parent,
                wxWindowID p_id = wxID_ANY);

    /**
     * @brief This method sends the emails.
     *
     */
    void handleSendEmails();

private:
    // Event handler for the show event
    void OnShow(wxShowEvent &event);

    /**
     * @brief Refreshes the status of the invoices.
     *
     */
    void refreshInvoiceStatusColors();

    /**
     * @brief This method changes the status of the invoice given an index in the m_statusTexts vector.
     *
     * @param invoiceIndex 
     * @param newStatus String of the new status
     */

    /**
     * @brief This method changes the status of the invoice given an index in the m_statusTexts vector.
     * 
     * @param p_invoiceIndex Index of the invoice in the m_statusTexts vector
     * @param p_newStatus New enum status of type InvoiceStatus
     * @param p_someText Some text which can be added to the status
     */
    void updateInvoiceStatus(size_t p_invoiceIndex,
                             const enum InvoiceStatus &p_newStatus,
                             const std::string &p_someText = "");

        std::vector<std::pair<wxStaticText *, InvoiceStatus>> m_statusTexts;

    // NotebookAdapter instance (parent):
    NotebookAdapter *m_notebookAdapter;

    JsonParser m_jsonParser;

    EmailThread *m_emailThread;

    wxDECLARE_EVENT_TABLE();
};

#endif // STATUS_PANEL_H