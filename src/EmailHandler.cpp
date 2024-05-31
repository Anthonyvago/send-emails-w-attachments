#include "EmailHandler.h"

#include "Constants.h"

#include <regex>
#include <fstream>
#include <sstream>

EmailHandler::EmailHandler(ProgramConfiguration *p_programConfig, EmailCredentials *p_emailCreds)
    : m_programConfig(p_programConfig),
      m_emailCredentials(p_emailCreds),
      m_smtpServer(p_emailCreds)
{
}

bool EmailHandler::sendEmail(const PlaintextMessage &p_emailMessage)
{
  return m_smtpServer.sendPlaintextEmail(p_emailMessage);
}

bool EmailHandler::readEmailContent(enum EmailType p_emailType,
                                    std::string &p_inputStr) const
{
  std::string filePath = p_emailType == NEW_INVOICE ? Constants::EmailContentFiles::NEW_INVOICE : Constants::EmailContentFiles::REMINDER;

  // Open the file:
  std::ifstream emailFile(filePath);

  // Check if the file is opened successfully:
  if (!emailFile.is_open())
  {
    std::cerr << "Failed to open the email content file: " << filePath << std::endl;
    return false;
  }

  // Create a stringstream to hold the file content
  std::stringstream buffer;

  // Read the file content into the buffer:
  buffer << emailFile.rdbuf();

  // Close the file:
  emailFile.close();

  // Assign the buffer content to the input string:
  p_inputStr = buffer.str();

  return true;
}

void EmailHandler::replacePlaceholders(std::string &p_textInput,
                                       const std::unordered_map<std::string, std::string> &p_replacements) const
{
  for (const auto &replacement : p_replacements)
  {
    std::string replacementKey = "{" + replacement.first + "}";
    size_t index = 0;
    while ((index = p_textInput.find(replacementKey, index)) != std::string::npos)
    {
      p_textInput.replace(index, replacementKey.size(), replacement.second);
      index += replacement.second.size();
    }
  }
}

PlaintextMessage EmailHandler::constructEmailMessage(const std::string &p_recipient, const std::string &p_attachmentFileName) const
{
  // 1. Sender email address:
  MessageAddress senderEmailAddress(m_emailCredentials->username);

  // 2. Vector of recipients:
  std::vector<MessageAddress> recipients = {MessageAddress(p_recipient)};

  // SIDE QUEST: Invoice number is extracted from the attachment file name:
  std::string invoiceNumber = extractInvoiceNumber(p_attachmentFileName);

  // 3. Subject:
  std::string subject = m_programConfig->newInvoiceSubject;

  // Replace placeholders in the subject:
  const std::unordered_map<std::string, std::string> replacements = {
      {Constants::TextFilePlaceholders::INVOICE_NR, invoiceNumber},
      {Constants::TextFilePlaceholders::COMPANY_NAME, m_programConfig->companyName},
      {Constants::TextFilePlaceholders::COMPANY_EMAIL, m_programConfig->companyEmail},
      {Constants::TextFilePlaceholders::COMPANY_PHONE, m_programConfig->companyPhone}};
  replacePlaceholders(subject, replacements);

  // 4. Body:
  std::string body = "";
  readEmailContent(NEW_INVOICE, body);

  // Replace placeholders in the body:
  replacePlaceholders(body, replacements);

  // 5. CC (only added if the sendToSelf flag is set to true):
  std::vector<MessageAddress> ccRecipients;
  if (m_programConfig->sendToSelf)
  {
    ccRecipients.push_back(MessageAddress(m_emailCredentials->username));
  }

  // 6. Attachments (only added if the attachment file name is NOT empty):
  std::vector<Attachment> attachments;
  if (p_attachmentFileName != "")
  {
    std::string directory = m_programConfig->invoicesDirectoryName + "/";
    attachments.push_back(Attachment(directory + p_attachmentFileName, p_attachmentFileName, p_attachmentFileName));
  }

  // FINAL: Create the email message and return it:
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