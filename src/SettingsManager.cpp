#include "../include/QuickColorManager.h"

SettingsManager::SettingsManager(std::string path): settingsPath(path) {
}

bool SettingsManager::save(Settings settings) {
    std::ofstream out(this->settingsPath, std::ios::binary | std::ios::app);

    if (!out) {
        return false;
    }

    out.write(reinterpret_cast<const char*>(&settings), sizeof(settings));
    return out.good();
}

bool SettingsManager::load(Settings& settings) {
    std::ifstream in(this->settingsPath, std::ios::binary);

    if (!in) {
        return false;
    }

    in.read(reinterpret_cast<char*>(&settings), sizeof(settings));
    return in.good();
}

bool SettingsManager::apply(Monitor monitor, Settings settings) {
    bool success = true;
    success = success && monitor.set(BRIGHTNESS, settings.brightness);
    success = success && monitor.set(CONTRAST, settings.contrast);
    success = success && monitor.set(GAMMA, settings.gamma);
    success = success && monitor.set(RED_BALANCE, settings.redBalance);
    success = success && monitor.set(GREEN_BALANCE, settings.greenBalance);
    success = success && monitor.set(BLUE_BALANCE, settings.blueBalance);
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