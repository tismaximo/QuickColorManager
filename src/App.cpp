#include "../include/QuickColorManager.h"

App::App(std::vector<Monitor> monitors, SettingsManager manager): monitors(monitors), manager(manager) {}

int App::doSet(int id, std::vector<std::string> features, std::vector<uint8_t> vals) {
    if (id < 0 || id > this->monitors.size()) {
        Logger::log("ERROR: Device with the following id not found: " + id);
        return VAL_ERROR;
    }
    Monitor m = this->monitors[id];

    for (int i = 0; i < features.size(); i++) {
        std::string arg = features[i];
        auto it = VCP_ARGS.find(arg);
        if (it == VCP_ARGS.end()) {
            Logger::log("ERROR: Feature not found: " + arg);
            return ARG_ERROR;
        }
        m.set(it->second, vals[i]);
    }
}

int App::doGet(int id, std::vector<std::string> features, std::vector<uint8_t>& vals, bool maxvalues) {
    if (id < 0 || id > this->monitors.size()) {
        Logger::log("ERROR: Device with the following id not found: " + id);
        return VAL_ERROR;
    }
    Monitor m = this->monitors[id];


    for (int i = 0; i < features.size(); i++) {
        auto arg = VCP_ARGS.find(features[i]);
        if (arg == VCP_ARGS.end()) {
            Logger::log("ERROR: Feature not found: " + features[i]);
            return ARG_ERROR;
        }

        bool success = m.get(arg->second, vals[i]);
        if (!success) {
            return VAL_ERROR;
        }
    }

    return 0;
}

int App::doLoad(int id, std::string alias) {
    if (id < 0 || id > this->monitors.size()) {
        Logger::log("ERROR: Device with the following id not found: " + id);
        return VAL_ERROR;
    }
    Monitor m = this->monitors[id];

    Settings settings(alias);
    if (!this->manager.load(alias, settings)) {
        Logger::log("ERROR: Couldn't read from the settings file. Check that the file exists and that the program has read permissions.");
        return FILE_ERROR;
    }

    if (!this->manager.apply(m, settings)) {
        Logger::log("INFO: or more of the settings from the device couldn't be loaded from the settings file. Run 'qmc test' to see which (if any) features are unsupported by your device. Execution will continue.");
    }
    Logger::log("Settings loaded successfully.");
    return 0;
}

int App::doSave(int id, std::string alias) {
    if (id < 0 || id > this->monitors.size()) {
        Logger::log("ERROR: Device with the following id not found: " + id);
        return VAL_ERROR;
    }
    Monitor m = this->monitors[id];

    Settings settings(alias);
    if (!this->manager.getFromMonitor(m, settings)) {
        Logger::log("INFO: One or more of the settings from the device couldn't be saved to the settings file. Run 'qmc test' to see which (if any) features are unsupported by your device. Execution will continue.");
    }

    if (!this->manager.save(settings)) {
        Logger::log("ERROR: Couldn't write to the settings file. Check that the file exists and that the program has write permissions.");
        return FILE_ERROR;
    }
    Logger::log("Settings saved successfully.");
    return 0;
}

std::vector<std::string> App::doListDevices() {
    std::vector<std::string> strs; 
    std::wostringstream wss; // se usa wostringstream en lugar de stringstream por que las propiedades de DEVICE_INFO usan wide strings

    for (Monitor m : this->monitors) {
        DISPLAY_DEVICE info = m.getInfo();
        auto it = std::find(monitors.begin(), monitors.end(), m);
        int id = it - monitors.begin() + 1;
        wss << id << " | " << info.DeviceName << ": " << info.DeviceString;
        strs.push_back(unwide(wss.str()));
        wss.str(std::wstring());
    }

    return strs;
}

std::vector<std::string> App::doListSettings() {
    return this->manager.list();
}