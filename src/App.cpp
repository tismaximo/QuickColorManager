#include "../include/QuickColorManager.h"

App::App(std::vector<Monitor> monitors, SettingsManager manager): monitors(monitors), manager(manager) {}

int App::doSet(std::vector<std::string> features, uint8_t val) {
    return 0;

}

int App::doGet(std::vector<std::string> features, uint8_t& val, bool maxvalues) {
    return 0;
}

int App::doLoad(std::string settingsAlias) {
    return 0;

}

int App::doSave(std::string settingsAlias) {
    return 0;
}

std::string App::doListDevices() {
    std::wostringstream wss; // se usa wostringstream en lugar de stringstream por que las propiedades de DEVICE_INFO usan wide strings

    wss << "These are the available devices (id | basic device name | full device name):\n";
    for (Monitor m : this->monitors) {
        DISPLAY_DEVICE info = m.getInfo();
        auto it = std::find(monitors.begin(), monitors.end(), m);
        int id = it - monitors.begin() + 1;
        wss << id << " | " << info.DeviceName << ": " << info.DeviceString << "\n";
    }

    return unwide(wss.str());
}

std::string App::doListSettings() {
    std::string str;
    return str;
}