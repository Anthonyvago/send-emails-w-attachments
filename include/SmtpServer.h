#ifndef SMTP_SERVER_H
#define SMTP_SERVER_H

#include <iostream>
#include <string>

// SMTP client library
#include <cpp/opportunisticsecuresmtpclient.hpp>
#include <cpp/plaintextmessage.hpp>

#include "ProgramConfigurationHandler.h"

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
     * @param p_emailServerConfig Email server configuration
     */
    SmtpServer(ProgramConfiguration *p_emailServerConfig);

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
    ProgramConfiguration *m_emailServerConfig = nullptr; /**< Email server configuration. */

    std::string m_errorMessage; /**< The error message. */

    OpportunisticSecureSMTPClient m_smtpClient;
};

#endif // SMTP_SERVER_H