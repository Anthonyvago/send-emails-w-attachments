#ifndef PROGRAM_CONFIGURATION_HANDLER_H
#define PROGRAM_CONFIGURATION_HANDLER_H

#include <string>

/**
 * @brief The ProgramConfiguration struct
 * 
 */
typedef struct
{
    std::string invoicesDirectoryName;
    std::string smtpServer;
    uint16_t port;
    std::string email;
    std::string password;
} ProgramConfiguration;

/**
 * @brief The EmailConfiguration struct
 * 
 */
typedef struct
{
    std::string subject;
    std::string greeting;
    std::string body;
    std::string signature;
    bool sendToSelf;
} EmailConfiguration;

/**
 * @class LoginCredentialHandler
 * @brief Handles the login credentials for the application.
 *
 * The LoginCredentialHandler class is responsible for managing the login credentials
 * used by the application. It provides methods to read the login credentials from a
 * configuration file.
 */
class ProgramConfigurationHandler
{

public:
    /**
    @brief Default constructor.
     */
    ProgramConfigurationHandler();

    /**
    @brief Default destructor.
     */
    ~ProgramConfigurationHandler() = default;

    /**
     * @brief Reads the project configuration from a configuration file.
     * 
     * @return ProgramConfiguration*
     */
    ProgramConfiguration* readProjectConfigFile();

    /**
     * @brief Reads the email configuration from a configuration file.
     * 
     * @return EmailConfiguration* 
     */
    EmailConfiguration* readEmailConfigFile();

    std::string getErrorMessage() const;

private:
    ProgramConfiguration m_programConfig; /**< The login credentials object. */
    EmailConfiguration m_emailConfig; /**< The email configuration object. */

    std::string m_errorMessage = ""; /**< The error message. */
};

#endif // LOGIN_CREDENTIALS_HANDLER_H