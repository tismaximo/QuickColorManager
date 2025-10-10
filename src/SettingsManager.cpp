#include "../include/QuickColorManager.h"

SettingsManager::SettingsManager(std::string path): settingsPath(path) {
}

bool SettingsManager::save(Settings settings) {
    std::fstream file(this->settingsPath, std::ios::out | std::ios::in | std::ios::binary);

    if (!file || !file.is_open()) {
        Logger::log("Error when opening the settings file. Make sure the file is in the same folder as this .exe and that it has read/write permissions");
        return false;
    }

    Settings temp(settings.alias);
    int pos = 0;

    while (file >> temp.alias >> temp.brightness >> temp.contrast >> temp.gamma >> temp.redBalance >> settings.greenBalance >> settings.blueBalance) {
        if (settings.alias == temp.alias) {
            file.seekp(pos * sizeof(Settings), std::ios::beg);
            file.write(reinterpret_cast<const char*>(&settings), sizeof(settings));
            file.close();
            Logger::log("INFO: Replaced pre-existing settings with alias: " + temp.alias);
            return file.good();
        }
        pos++;
    }

    file.close();

    std::ofstream out(this->settingsPath, std::ios::binary | std::ios::app);
    out.write(reinterpret_cast<const char*>(&settings), sizeof(settings));
    out.close();

    return out.good();
}

bool SettingsManager::load(std::string alias, Settings& settings) const {
    std::ifstream in(this->settingsPath, std::ios::binary);

    if (!in || in.is_open()) {
        Logger::log("Error when opening the settings file. Make sure the file is in the same folder as this .exe and that it has read/write permissions");
        return false;
    }
    
    while (in >> settings.alias >> settings.brightness >> settings.contrast >> settings.gamma >> settings.redBalance >> settings.greenBalance >> settings.blueBalance) {
        if (settings.alias == alias) {
            in.close();
            return in.good();
        }
    }

    in.close();
    Logger::log("ERROR: Settings alias not found: " + alias);
    return false;
}

std::vector<std::string> SettingsManager::list() {
    std::ifstream in(this->settingsPath, std::ios::binary);
    std::vector<std::string> strs;

    if (!in || in.is_open()) {
        Logger::log("Error when opening the settings file. Make sure the file is in the same folder as this .exe and that it has read/write permissions");
        return strs;
    }

    std::string str;
    Settings settings("");

    while (in >> settings.alias >> settings.brightness >> settings.contrast >> settings.gamma >> settings.redBalance >> settings.greenBalance >> settings.blueBalance) {
        strs.push_back(settings.alias);
    }

    in.close();
    return strs;
}

bool SettingsManager::apply(Monitor monitor, Settings settings) {
    bool success = true;
    success = monitor.set(BRIGHTNESS, settings.brightness) && success;
    success = monitor.set(CONTRAST, settings.contrast) && success;
    success = monitor.set(GAMMA, settings.gamma) && success;
    success = monitor.set(RED_BALANCE, settings.redBalance) && success;
    success = monitor.set(GREEN_BALANCE, settings.greenBalance) && success;
    success = monitor.set(BLUE_BALANCE, settings.blueBalance) && success;
    return success;
}

bool SettingsManager::getFromMonitor(Monitor monitor, Settings& settings) {
    bool success = true;
    success = monitor.get(BRIGHTNESS, settings.brightness) && success;
    success = monitor.get(CONTRAST, settings.contrast) && success;
    success = monitor.get(GAMMA, settings.gamma) && success;
    success = monitor.get(RED_BALANCE, settings.redBalance) && success;
    success = monitor.get(GREEN_BALANCE, settings.greenBalance) && success;
    success = monitor.get(BLUE_BALANCE, settings.blueBalance) && success;
    return success;
}