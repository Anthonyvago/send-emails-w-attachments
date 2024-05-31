#include "NotebookAdapter.h"

#include "Constants.h"
#include "frames/MainFrame.h"

NotebookAdapter::NotebookAdapter(wxWindow *p_parent,
                                 wxWindowID p_id)
    : wxSimplebook(p_parent, p_id)
{
}

void NotebookAdapter::showInvoicesPanel(const std::vector<std::string> &p_pdfList)
{
    m_pdfList = p_pdfList;
    SetSelection(Constants::PanelIndexes::INVOICES);
}

void NotebookAdapter::showRemindersPanel(const std::vector<std::string> &p_pdfList)
{
    m_pdfList = p_pdfList;
    SetSelection(Constants::PanelIndexes::REMINDERS);
}

void NotebookAdapter::showStatusPanel(const std::vector<std::pair<wxStaticText *, wxTextCtrl *>> &p_invoiceLines)
{
    m_invoiceLines = p_invoiceLines;
    SetSelection(Constants::PanelIndexes::STATUS);
}

std::vector<std::string> NotebookAdapter::getPdfList() const
{
    return m_pdfList;
}

std::vector<std::pair<wxStaticText *, wxTextCtrl *>> NotebookAdapter::getInvoiceLines() const
{
    return m_invoiceLines;
}

void NotebookAdapter::adjustFrameWidth(size_t p_width)
{
    // Get frame parent:
    MainFrame *mainFrame = dynamic_cast<MainFrame *>(GetParent());
    if (mainFrame == nullptr)
    {
        return;
    }

    // Adjust the frame width:
    mainFrame->SetSize(int(p_width), mainFrame->GetSize().GetHeight());
}

void NotebookAdapter::adjustFrameHeight(size_t p_height)
{
    // Get frame parent:
    MainFrame *mainFrame = dynamic_cast<MainFrame *>(GetParent());
    if (mainFrame == nullptr)
    {
        return;
    }

    // Adjust the frame width:
    mainFrame->SetSize(mainFrame->GetSize().GetWidth(), int(p_height));
}
