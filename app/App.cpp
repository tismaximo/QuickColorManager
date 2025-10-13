#include "App.h"

App::App(std::vector<Monitor> monitors, SettingsManager manager): monitors(monitors), manager(manager) {}

int App::doSet(int id, std::vector<std::string> features, std::vector<U16> vals) {
    if (id < 1 || id > this->monitors.size()) {
		throw NotFoundException(id);
    }
    Monitor m = this->monitors[id - 1];

    for (int i = 0; i < features.size(); i++) {
        std::string arg = features[i];
        auto it = VCP_ARGS.find(arg);
        if (it == VCP_ARGS.end()) {
			throw ArgumentException(arg);
        }

        m.set(it->second, vals[i]);
    }

    return 0;
}

int App::doGet(int id, std::vector<std::string> features, std::vector<U16>& vals, bool maxvalues) {
    if (id < 1 || id > this->monitors.size()) {
        throw NotFoundException(id);
    }
    Monitor m = this->monitors[id - 1];

    for (int i = 0; i < features.size(); i++) {
        auto arg = VCP_ARGS.find(features[i]);
        if (arg == VCP_ARGS.end()) {
			throw ArgumentException(features[i]);
        }

        m.get(arg->second, vals[i], maxvalues); 
    }

    return 0;
}

int App::doLoad(int id, std::string alias) {
    if (id < 1 || id > this->monitors.size()) {
        throw NotFoundException(id);
    }
    Monitor m = this->monitors[id - 1];

    Settings settings(alias);
    if (!this->manager.load(alias, settings)) {
		return -1; // no se encontro la configuracion con el alias dado
    }

    if (!this->manager.apply(m, settings)) {
        Logger::log("INFO: or more of the settings from the device couldn't be loaded from the settings file. Run 'qmc test' to see which (if any) features are unsupported by your device. Execution will continue.");
    }

    Logger::log("Settings loaded successfully.");
    return 0;
}

int App::doSave(int id, std::string alias) {
    if (id < 1 || id > this->monitors.size()) {
        throw NotFoundException(id);
    }
    Monitor m = this->monitors[id - 1];

    Settings settings(alias);
    if (!this->manager.getFromMonitor(m, settings)) {
        Logger::log("INFO: One or more of the settings from the device couldn't be saved to the settings file. Run 'qmc test' to see which (if any) features are unsupported by your device. Execution will continue.");
    }

    if (!this->manager.save(settings)) {
        throw FileException(this->manager.getSettingsPath());
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