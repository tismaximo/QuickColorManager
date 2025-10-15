#include "App.h"

App::App(std::vector<Monitor> monitors, SettingsManager manager): monitors(monitors), manager(manager) {}

int App::doSet(int id, std::vector<std::string> features, std::vector<U16> vals) {
    if (id < 1 || id > this->monitors.size()) {
		throw NotFoundException(id);
    }
    Monitor m = this->monitors[id - 1];

    for (int i = 0; i < features.size(); i++) {
		VcpFeature feature = findFeatureByArg(features[i]);
        m.set(feature, vals[i]);
    }

    return 0;
}

int App::doGet(int id, std::vector<std::string> features, std::vector<U16>& vals, bool maxvalues) {
    if (id < 1 || id > this->monitors.size()) {
        throw NotFoundException(id);
    }
    Monitor m = this->monitors[id - 1];

    for (int i = 0; i < features.size(); i++) {
        VcpFeature feature = findFeatureByArg(features[i]);
		U16 val = 0;
        if (m.get(feature, val, maxvalues)) {
			vals[i] = val;
        }
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

bool App::doTest(std::vector<Monitor> monitors) {
    Logger::log("NOTE: Sometimes devices claim not to support some features even though they actually do. You may still try changing settings at your own risk.");
    bool result;
    try {
        result = Tester::testAll(monitors);
        return result;
    }
    catch (const DeviceException& e) {
        std::string what(e.what());
        Logger::log("[ERROR] " + what);
        return false;
	}
}

bool App::init() {
    if (!this->manager.fileExists()) {
        this->manager.createDefaults(this->monitors);
        doTest(this->monitors);
		return true; // significa que el archivo no existia y se creo uno nuevo, si es asi se debera mostrar la advertencia 
    }
    return false; // significa que el archivo ya existia
}