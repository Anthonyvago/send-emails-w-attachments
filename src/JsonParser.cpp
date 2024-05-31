#include "JsonParser.h"

#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include "Constants.h"

JsonParser::JsonParser() : m_errorMessage("")
{
}

ProgramConfiguration *JsonParser::readProjectConfigFile()
{
    // Open the JSON file:
    std::ifstream jsonStream(Constants::Configuration::PROJECT_CONFIG_FILE_PATH);
    if (!jsonStream.is_open())
    {
        std::string errorHeading = "Failed to open the program config file:";
        std::cout << Constants::OutputStd::RED << errorHeading << Constants::OutputStd::RESET << std::endl;
        m_errorMessage = errorHeading;
        return nullptr;
    }

    // Parse the JSON file:
    nlohmann::json json;

    try
    {
        jsonStream >> json;
    }
    catch (const nlohmann::json::parse_error &e)
    {
        std::string errorHeading = "Failed to parse the program config file:";
        std::cout << Constants::OutputStd::RED << errorHeading << Constants::OutputStd::RESET << std::endl
                  << e.what() << std::endl;
        m_errorMessage = errorHeading + "\n" + e.what();
        return nullptr;
    }

    // Try extracting data from the JSON file:
    try
    {

        m_programConfig.companyName = json.at(Constants::JsonKeys::COMPANY_NAME).get<std::string>();
        m_programConfig.companyEmail = json.at(Constants::JsonKeys::COMPANY_EMAIL).get<std::string>();
        m_programConfig.companyPhone = json.at(Constants::JsonKeys::COMPANY_PHONE).get<std::string>();
        m_programConfig.invoicesDirectoryName = json.at(Constants::JsonKeys::INVOICES_DIR_PATH).get<std::string>();
        m_programConfig.invoicesFileExtension = json.at(Constants::JsonKeys::INVOICE_FILE_EXT).get<std::string>();
        m_programConfig.sendToSelf = json.at(Constants::JsonKeys::SEND_TO_SELF).get<bool>();
        m_programConfig.newInvoiceSubject = json.at(Constants::JsonKeys::NEW_INVOICE_SUBJECT).get<std::string>();
        m_programConfig.reminderSubject = json.at(Constants::JsonKeys::REMINDER_SUBJECT).get<std::string>();
        return &m_programConfig;
    }
    catch (nlohmann::json::exception &e)
    {
        std::string errorHeading = "Failed to extract data from the program config file:";
        std::cout << Constants::OutputStd::RED << errorHeading << Constants::OutputStd::RESET << std::endl
                  << e.what() << std::endl;
        m_errorMessage = errorHeading + "\n" + e.what();

        return nullptr;
    }

    return nullptr;
}

EmailCredentials* JsonParser::readEmailCredentialsConfig()
{
    // Open the JSON file:
    std::ifstream jsonStream(Constants::Configuration::SMTP_CONFIG_FILE_PATH);
    if (!jsonStream.is_open())
    {
        std::string errorHeading = "Failed to open the email credentials config file:";
        std::cout << Constants::OutputStd::RED << errorHeading << Constants::OutputStd::RESET << std::endl;
        m_errorMessage = errorHeading;
        return nullptr;
    }

    // Parse the JSON file:
    nlohmann::json json;

    try
    {
        jsonStream >> json;
    }
    catch (const nlohmann::json::parse_error &e)
    {
        std::string errorHeading = "Failed to parse the email credentials config file:";
        std::cout << Constants::OutputStd::RED << errorHeading << Constants::OutputStd::RESET << std::endl
                  << e.what() << std::endl;
        m_errorMessage = errorHeading + "\n" + e.what();
        return nullptr;
    }

    // Try extracting data from the JSON file:
    try
    {

        m_emailConfig.smtpServer = json.at(Constants::JsonKeys::SMTP_SERVER).get<std::string>();
        m_emailConfig.port = json.at(Constants::JsonKeys::PORT).get<uint16_t>();
        m_emailConfig.username = json.at(Constants::JsonKeys::USERNAME).get<std::string>();
        m_emailConfig.password = json.at(Constants::JsonKeys::PASSWORD).get<std::string>();
        return &m_emailConfig;
    }
    catch (nlohmann::json::exception &e)
    {
        std::string errorHeading = "Failed to extract data from the email configuration file: ";
        std::cout << Constants::OutputStd::RED << errorHeading << Constants::OutputStd::RESET << std::endl
                  << e.what() << std::endl;
        m_errorMessage = errorHeading + "\n" + e.what();

        return nullptr;
    }

    return nullptr;
}

std::string JsonParser::getErrorMessage() const
{
    return m_errorMessage;
}
