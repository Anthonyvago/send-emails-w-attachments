#include "EmailHandler.h"

#include <regex>

EmailHandler::EmailHandler(ProgramConfiguration *p_emailServerConfig, EmailConfiguration *p_emailContentConfig)
    : m_emailServerConfig(p_emailServerConfig),
      m_emailContentConfig(p_emailContentConfig),
      m_smtpServer(p_emailServerConfig)
{
}

bool EmailHandler::sendEmail(const PlaintextMessage &p_emailMessage)
{
  return m_smtpServer.sendPlaintextEmail(p_emailMessage);
}

PlaintextMessage EmailHandler::constructEmailMessage(const std::string &p_recipient, const std::string &p_attachmentFileName) const
{
  // Sender email address:
  MessageAddress senderEmailAddress(m_emailServerConfig->email);

  // Vector of recipients:
  std::vector<MessageAddress> recipients = {MessageAddress(p_recipient)};

  // Invoice number is extracted from the attachment file name:
  std::string invoiceNumber = extractInvoiceNumber(p_attachmentFileName);

  // Subject:
  std::string subject = m_emailContentConfig->subject;
  checkAndReplacePlaceholder(subject, "{invoice_number}", invoiceNumber);

  // Body:
  std::string body = m_emailContentConfig->greeting + ",\n\n" +
                     m_emailContentConfig->body + "\n\n" +
                     m_emailContentConfig->signature;
  checkAndReplacePlaceholder(body, "{invoice_number}", invoiceNumber);

  // CC (only added if the sendToSelf flag is set to true):
  std::vector<MessageAddress> ccRecipients;
  if (m_emailContentConfig->sendToSelf)
  {
    ccRecipients.push_back(MessageAddress(m_emailServerConfig->email));
  }

  // Attachments (only added if the attachment file name is NOT empty):
  std::vector<Attachment> attachments;
  if (p_attachmentFileName != "")
  {
    std::string directory = m_emailServerConfig->invoicesDirectoryName + "/";
    attachments.push_back(Attachment(directory + p_attachmentFileName, p_attachmentFileName, p_attachmentFileName));
  }

  // Create the email message:
  return PlaintextMessage(senderEmailAddress,
                          recipients,
                          subject,
                          body,
                          ccRecipients,
                          {},
                          attachments);
}

bool EmailHandler::validEmailAddressFormat(const std::string &emailAddress) const
{
  // Regular expression pattern for validating email addresses
  static const std::regex pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");

  return std::regex_match(emailAddress, pattern);
}

void EmailHandler::checkAndReplacePlaceholder(std::string &p_input,
                                              const std::string &placeholder,
                                              const std::string &textInsteadOfPlaceholder) const
{
  // Check if the placeholder is present in the input string:
  size_t placeHolderIndex = p_input.find(placeholder);
  if (placeHolderIndex != std::string::npos)
  {
    // Replace the placeholder with the given text:
    p_input.replace(placeHolderIndex, placeholder.size(), textInsteadOfPlaceholder);
  }
}

std::string EmailHandler::extractInvoiceNumber(const std::string &p_attachmentFileName) const
{
  // The invoice number is extracted by looking for the first digit inside the attachment file name.
  // If it found a digit, it then checks if the next character is also a digit and so on.
  // Eventually this list of digits is returned as a string.

  // Search for the first digit in the attachment file name:
  size_t firstDigitIndex;
  for (firstDigitIndex = 0; firstDigitIndex < p_attachmentFileName.size(); firstDigitIndex++)
  {
    if (std::isdigit(p_attachmentFileName[firstDigitIndex]))
    {
      break;
    }
  }

  // Check if a digit was found:
  if (firstDigitIndex == p_attachmentFileName.size())
  {
    return "";
  }

  // Extract the invoice number:
  std::string invoiceNumber = "";
  for (size_t i = firstDigitIndex; i < p_attachmentFileName.size(); i++)
  {
    if (std::isdigit(p_attachmentFileName[i]))
    {
      invoiceNumber += p_attachmentFileName[i];
    }
    else
    {
      break;
    }
  }

  return invoiceNumber;
}