#include "SmtpServer.h"

#include "cpp/opportunisticsecuresmtpclient.hpp"
#include "cpp/plaintextmessage.hpp"

using namespace jed_utils::cpp;

SmtpServer::SmtpServer(EmailCredentials *p_emailCreds)
    : m_emailCreds(p_emailCreds),
      m_errorMessage(""),
      m_smtpClient(p_emailCreds->smtpServer, p_emailCreds->port)
{
    m_smtpClient.setCredentials(Credential(p_emailCreds->username, p_emailCreds->password));
}

bool SmtpServer::sendPlaintextEmail(const PlaintextMessage &msg)
{
    try
    {
        int errorNumber = m_smtpClient.sendMail(msg);

        // Check if an error occurred:
        if (errorNumber != 0)
        {
            std::cout << m_smtpClient.getCommunicationLog() << '\n';

            std::string errorMessage = m_smtpClient.getErrorMessage(errorNumber);
            m_errorMessage = std::to_string(errorNumber) + ": " + errorMessage;

            std::cout << m_errorMessage << '\n';

            return false;
        }
    }
    catch (std::invalid_argument &err)
    {
        m_errorMessage = err.what();
        return false;
    }

    return true;
}

std::string SmtpServer::getErrorMessage() const
{
    return m_errorMessage;
}