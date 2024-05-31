#include "ProgramConfigurationHandler.h"

#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include "Constants.h"

ProgramConfigurationHandler::ProgramConfigurationHandler()
{
    
}

ProgramConfiguration *ProgramConfigurationHandler::readProjectConfigFile()
{
    // Open the JSON file:
    std::ifstream jsonStream(Constants::Configuration::PROJECT_CONFIG_FILE_PATH);
    if (!jsonStream.is_open())
    {
        std::string errorHeading = "Failed to open the login credentials configuration file: ";
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
        std::string errorHeading = "Failed to parse the login credentials configuration file: ";
        std::cout << Constants::OutputStd::RED << errorHeading << Constants::OutputStd::RESET << std::endl
                  << e.what() << std::endl;
        m_errorMessage = errorHeading + "\n" + e.what();
        return nullptr;
    }

    // Try extracting data from the JSON file:
    try
    {

        m_programConfig.invoicesDirectoryName = json.at("invoices_directory_name").get<std::string>();
        m_programConfig.smtpServer = json.at("smtp-server").get<std::string>();
        m_programConfig.port = json.at("port").get<uint16_t>();
        m_programConfig.email = json.at("emailaddress").get<std::string>();
        m_programConfig.password = json.at("password").get<std::string>();
        return &m_programConfig;
    }
    catch (nlohmann::json::exception &e)
    {
        std::string errorHeading = "Failed to extract data from the configuration file for the login credentials: ";
        std::cout << Constants::OutputStd::RED << errorHeading << Constants::OutputStd::RESET << std::endl
                  << e.what() << std::endl;
        m_errorMessage = errorHeading + "\n" + e.what();

        return nullptr;
    }

    return nullptr;
}

EmailConfiguration* ProgramConfigurationHandler::readEmailConfigFile()
{
    // Open the JSON file:
    std::ifstream jsonStream(Constants::Configuration::EMAIL_CONFIG_FILE_PATH);
    if (!jsonStream.is_open())
    {
        std::string errorHeading = "Failed to open the email content configuration file: ";
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
        std::string errorHeading = "Failed to parse the email content configuration file: ";
        std::cout << Constants::OutputStd::RED << errorHeading << Constants::OutputStd::RESET << std::endl
                  << e.what() << std::endl;
        m_errorMessage = errorHeading + "\n" + e.what();
        return nullptr;
    }

    // Try extracting data from the JSON file:
    try
    {

        m_emailConfig.subject = json.at("subject").get<std::string>();
        m_emailConfig.greeting = json.at("greeting").get<std::string>();
        m_emailConfig.body = json.at("body").get<std::string>();
        m_emailConfig.signature = json.at("signature").get<std::string>();
        m_emailConfig.sendToSelf = json.at("send_to_myself").get<bool>();
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

std::string ProgramConfigurationHandler::getErrorMessage() const
{
    return m_errorMessage;
}
