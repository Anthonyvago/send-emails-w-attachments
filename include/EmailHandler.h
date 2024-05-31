#ifndef EMAIL_HANDLER_HPP
#define EMAIL_HANDLER_HPP

#include <iostream>
#include <unordered_map>

#include "SmtpServer.h"

// SMTP client library
#include <cpp/opportunisticsecuresmtpclient.hpp>
#include <cpp/plaintextmessage.hpp>

using namespace jed_utils::cpp;

enum EmailType
{
    NEW_INVOICE,
    REMINDER
};

/**
 * @class EmailHandler
 * @brief Represents an SMTP server for sending emails.
 */
class EmailHandler
{

public:
    /**
     * @brief Constructs a EmailHandler object.
     *
     */
    EmailHandler(ProgramConfiguration *p_emailServerConfig, EmailCredentials *p_emailContentConfig);

    /**
     * @brief Default destructor.
     */
    ~EmailHandler() = default;

    /**
     * @brief Sends an email.
     *
     * @param p_emailMessage Email message
     * @return true if the email was sent successfully, otherwise false.
     * @return false if the email was not sent successfully.
     */
    bool sendEmail(const PlaintextMessage &p_emailMessage);

    /**
     * @brief Reads the email content from a .txt file and returns it as a string.
     *
     * @param p_emailType Type of email: NEW_INVOICE or REMINDER
     * @return true if the email content was read successfully, otherwise false.
     */
    bool readEmailContent(enum EmailType p_emailType, std::string &p_inputStr) const;

    /**
     * @brief Replaces placeholders in the text.
     *
     * @param p_textInput Input string
     * @param p_replacements Replacements to be made of the form {placeholder, replacement}
     * @return std::string The string with the placeholders replaced.
     */
    void replacePlaceholders(std::string &p_textInput,
                             const std::unordered_map<std::string, std::string> &p_replacements) const;

    /**
     * @brief Constructs an email message.
     *
     * @param p_recipient Where the email will be sent
     * @param p_attachmentFileName The attachment file name
     * @return PlaintextMessage The email message
     */
    PlaintextMessage constructEmailMessage(const std::string &p_recipient,
                                           const std::string &p_attachmentFileName) const;

    /**
     * @brief Checks whether the email address has a valid format.
     *
     * @param emailAddress Email address to check
     * @return true if email address has a valid format
     * @return false
     */
    bool validEmailAddressFormat(const std::string &emailAddress) const;

    /**
     * @brief Extracts the invoice number from the attachment file name.
     *
     * @param p_attachmentFileName The attachment file name
     * @return std::string The invoice number
     */
    std::string extractInvoiceNumber(const std::string &p_attachmentFileName) const;

private:
    // Will hold the email server configuration
    ProgramConfiguration *m_programConfig = nullptr;

    // Will hold the email content configuration
    EmailCredentials *m_emailCredentials = nullptr;

    SmtpServer m_smtpServer;
};

#endif // EMAIL_HANDLER_HPP