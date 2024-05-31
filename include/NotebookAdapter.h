#ifndef NOTEBOOK_ADAPTER_H
#define NOTEBOOK_ADAPTER_H

#include <wx/wx.h>
#include <wx/simplebook.h>
#include <vector>

#include "ProgramConfigurationHandler.h"

/**
 * @class NotebookAdapter
 * @brief A custom adapter class for a wxNotebook control.
 *
 * This class extends the wxNotebook class and provides additional functionality for managing pages.
 */
class NotebookAdapter : public wxSimplebook
{
public:
    /**
     * @brief Constructs a NotebookAdapter object.
     * @param p_parent The parent window.
     * @param p_id The window identifier.
     */
    NotebookAdapter(wxWindow *p_parent,
                    wxWindowID p_id = wxID_ANY);

    /**
     * @brief Shows the invoices panel.
     */
    void showInvoicesPanel(const std::vector<std::string> &p_pdfList);

    /**
     * @brief Shows the reminders panel.
     */
    void showRemindersPanel(const std::vector<std::string> &p_pdfList);

    /**
     * @brief Shows the status panel.
     *
     * @param p_invoiceLines
     */
    void showStatusPanel(const std::vector<std::pair<wxStaticText *, wxTextCtrl *>> &p_invoiceLines);

    /**
     * @brief Returns the list of PDF files.
     * @return The list of PDF files.
     */
    std::vector<std::string> getPdfList() const;

    /**
     * @brief Get the Invoice Lines object
     *
     * @return std::vector<std::pair<std::string, std::string>>
     */
    std::vector<std::pair<wxStaticText *, wxTextCtrl *>> getInvoiceLines() const;

    /**
     * @brief Adjusts the frame (parent) width
     *
     */
    void adjustFrameWidth(size_t p_width);

    /**
     * @brief Adjusts the frame (parent) height
     *
     */
    void adjustFrameHeight(size_t p_height);

protected:
private:
    std::vector<std::string> m_pdfList;
    std::vector<std::pair<wxStaticText *, wxTextCtrl *>> m_invoiceLines;
};

#endif // NOTEBOOK_ADAPTER_H
