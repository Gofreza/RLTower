#include "Logger.h"
#include "../Manager/UI/UiManager.h"
#include "../Manager/Localization/LocalizationManager.h"

Logger::Logger() {}

Logger::~Logger() {}

void Logger::info(const std::string message) {
    logMessages.push_back(LocalizationManager::instance().getText("logger_info") + message);
    UiManager::instance().updateConsole();
}

void Logger::danger(const std::string message) {
    logMessages.push_back(LocalizationManager::instance().getText("logger_danger") + message);
    UiManager::instance().updateConsole();
}

void Logger::combat(const std::string message) {
    logMessages.push_back(LocalizationManager::instance().getText("logger_combat") + message);
    UiManager::instance().updateConsole();
}

void Logger::warning(const std::string message) {
    logMessages.push_back(LocalizationManager::instance().getText("logger_warning") + message);
    UiManager::instance().updateConsole();
}

std::list<std::string>* Logger::getLogMessages() {
    return &logMessages;
}