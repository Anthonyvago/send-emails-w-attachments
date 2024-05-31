#include "SmtpServer.h"

#include "cpp/opportunisticsecuresmtpclient.hpp"
#include "cpp/plaintextmessage.hpp"

using namespace jed_utils::cpp;

SmtpServer::SmtpServer(ProgramConfiguration *p_emailServerConfig)
    : m_emailServerConfig(p_emailServerConfig),
      m_errorMessage(""),
      m_smtpClient(m_emailServerConfig->smtpServer, m_emailServerConfig->port)
{
    m_smtpClient.setCredentials(Credential(m_emailServerConfig->email, m_emailServerConfig->password));
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