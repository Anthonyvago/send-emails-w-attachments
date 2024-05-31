#ifndef EMAIL_HANDLER_HPP
#define EMAIL_HANDLER_HPP

#include <iostream>

#include "ProgramConfigurationHandler.h"
#include "SmtpServer.h"

// SMTP client library
#include <cpp/opportunisticsecuresmtpclient.hpp>
#include <cpp/plaintextmessage.hpp>

using namespace jed_utils::cpp;

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
    EmailHandler(ProgramConfiguration *p_emailServerConfig, EmailConfiguration *p_emailContentConfig);

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
     * @brief This function checks whether certain placeholders are present in
     * the subject string and replaces this placeholder with the third given argument.
     *
     * @param p_input Input text in which the placeholder may be present.
     * @param placeholder Placeholder to be replaced.
     * @param textInsteadOfPlaceholder Text to replace the placeholder.
     */
    void checkAndReplacePlaceholder(std::string &p_input,
                                    const std::string &placeholder,
                                    const std::string &textInsteadOfPlaceholder) const;

    /**
     * @brief Extracts the invoice number from the attachment file name.
     *
     * @param p_attachmentFileName The attachment file name
     * @return std::string The invoice number
     */
    std::string extractInvoiceNumber(const std::string &p_attachmentFileName) const;

private:
    // Will hold the email server configuration
    ProgramConfiguration *m_emailServerConfig = nullptr;

    // Will hold the email content configuration
    EmailConfiguration *m_emailContentConfig = nullptr;

    SmtpServer m_smtpServer;
};

#endif // EMAIL_HANDLER_HPP