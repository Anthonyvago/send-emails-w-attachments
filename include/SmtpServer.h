#ifndef SMTP_SERVER_H
#define SMTP_SERVER_H

#include <iostream>
#include <string>

#include "JsonParser.h"

// SMTP client library
#include <cpp/opportunisticsecuresmtpclient.hpp>
#include <cpp/plaintextmessage.hpp>

using namespace jed_utils::cpp;


/**
 * @class SmtpServer
 * @brief Represents an SMTP server for sending emails.
 */
class SmtpServer
{
public:
    /**
     * @brief Constructs a SmtpServer object.
     * @param p_emailCreds Email server configuration.
     */
    SmtpServer(EmailCredentials *p_emailCreds);

    /**
     * @brief Default destructor.
     */
    ~SmtpServer() = default;

    /**
     * @brief Sends an email.
     *
     * @param msg Message object
     * @return true if the email was sent successfully, otherwise false.
     * @return false if the email was not sent successfully.
     */
    bool sendPlaintextEmail(const PlaintextMessage &msg);

    /**
     * @brief Gets the error message.
     * @return The error message.
     */
    std::string getErrorMessage() const;

private:
    EmailCredentials *m_emailCreds = nullptr; /**< Email server configuration. */

    std::string m_errorMessage; /**< The error message. */

    OpportunisticSecureSMTPClient m_smtpClient;
};

#endif // SMTP_SERVER_H