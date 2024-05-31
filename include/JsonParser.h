#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <string>

/**
 * @brief The ProgramConfiguration struct
 *
 */
typedef struct
{
    std::string companyName;
    std::string companyEmail;
    std::string companyPhone;
    std::string invoicesDirectoryName;
    std::string invoicesFileExtension;
    bool sendToSelf;
    std::string newInvoiceSubject;
    std::string reminderSubject;
} ProgramConfiguration;

/**
 * @brief The EmailCredentials struct
 *
 */
typedef struct
{
    std::string smtpServer;
    uint16_t port;
    std::string username;
    std::string password;
} EmailCredentials;

/**
 * @class LoginCredentialHandler
 * @brief Handles the login credentials for the application.
 *
 * The LoginCredentialHandler class is responsible for managing the login credentials
 * used by the application. It provides methods to read the login credentials from a
 * configuration file.
 */
class JsonParser
{

public:
    /**
    @brief Default constructor.
     */
    JsonParser();

    /**
    @brief Default destructor.
     */
    ~JsonParser() = default;

    /**
     * @brief Reads the project configuration from a configuration file.
     *
     * @return ProgramConfiguration*
     */
    ProgramConfiguration *readProjectConfigFile();

    /**
     * @brief Reads the email configuration from a configuration file.
     *
     * @return EmailConfiguration*
     */
    EmailCredentials *readEmailCredentialsConfig();

    /**
     * @brief Get the Error Message object
     * 
     * @return std::string 
     */
    std::string getErrorMessage() const;

private:
    ProgramConfiguration m_programConfig; /**< The login credentials object. */
    EmailCredentials m_emailConfig;       /**< The email configuration object. */

    std::string m_errorMessage = ""; /**< The error message. */
};

#endif // JSON_PARSER_H