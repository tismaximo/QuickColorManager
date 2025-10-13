#include "SettingsManager.h"

// escribir al archivo manualmente propiedad por propiedad para manejar std::string correctamente

static void write(std::ofstream& file, const Settings& settings) {
    size_t strlen = settings.alias.size();
    file.write(reinterpret_cast<const char*>(&strlen), sizeof(strlen));
    file.write(settings.alias.data(), strlen); // se escribe el tamaño de la std string Y la std string, ifstream no puede saber que tamaño leer si no
    file.write(reinterpret_cast<const char*>(&settings.brightness), sizeof(settings.brightness));
    file.write(reinterpret_cast<const char*>(&settings.contrast), sizeof(settings.contrast));
    file.write(reinterpret_cast<const char*>(&settings.gamma), sizeof(settings.gamma));
    file.write(reinterpret_cast<const char*>(&settings.redBalance), sizeof(settings.redBalance));
    file.write(reinterpret_cast<const char*>(&settings.greenBalance), sizeof(settings.greenBalance));
    file.write(reinterpret_cast<const char*>(&settings.blueBalance), sizeof(settings.blueBalance));
}

static bool read(std::ifstream& file, Settings& settings) {
    size_t strlen;
    if (!file.read(reinterpret_cast<char*>(&strlen), sizeof(strlen))) return false;
    settings.alias.resize(strlen);
    if (!file.read(&settings.alias[0], strlen)) return false; // apunta al primer caracter del array interno de std::string y escribe sobre el
    if (!file.read(reinterpret_cast<char*>(&settings.brightness), sizeof(settings.brightness))) return false;
    if (!file.read(reinterpret_cast<char*>(&settings.contrast), sizeof(settings.contrast))) return false;
    if (!file.read(reinterpret_cast<char*>(&settings.gamma), sizeof(settings.gamma))) return false;
    if (!file.read(reinterpret_cast<char*>(&settings.redBalance), sizeof(settings.redBalance))) return false;
    if (!file.read(reinterpret_cast<char*>(&settings.greenBalance), sizeof(settings.greenBalance))) return false;
    if (!file.read(reinterpret_cast<char*>(&settings.blueBalance), sizeof(settings.blueBalance))) return false;
    return true;
}

SettingsManager::SettingsManager(std::string path): settingsPath(path) {
}

std::string SettingsManager::getSettingsPath() const {
    return this->settingsPath;
}

bool SettingsManager::save(Settings settings) {
    static std::mutex mtx;
    std::lock_guard<std::mutex> lock(mtx);

    std::ifstream in(this->settingsPath, std::ios::binary);

    if (!in.is_open()) {
        in.open(this->settingsPath, std::ios::out | std::ios::binary);
        in.close();

        in.open(this->settingsPath, std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);
    }

    if (!in || !in.is_open()) {
		throw FileException(this->settingsPath);
    }

    Settings temp(settings.alias);
    int pos = 0;

    std::vector<Settings> all;

    while (read(in, temp)) {
        all.push_back(temp);
    }

    bool replace = false;
    for (Settings& s : all) {
        if (s.alias == settings.alias) {
            s = settings;
            replace = true;
        }
    }
    if (!replace) {
        all.push_back(settings);
    }
    in.close();

    std::ofstream out(this->settingsPath, std::ios::binary | std::ios::trunc);
    for (Settings s : all) {
        write(out, s);
    }

    out.close();
    return true;
}

bool SettingsManager::load(std::string alias, Settings& settings) const {
    static std::mutex mtx;
    std::lock_guard<std::mutex> lock(mtx);

    std::ifstream in(this->settingsPath, std::ios::binary);

    if (!in || !in.is_open()) {
		throw FileException(this->settingsPath);
    }
    
    while (read(in, settings)) {
        if (settings.alias == alias) {
            in.close();
            return true;
        }
    }

    in.close();
    Logger::log("Settings alias not found: " + alias);
    return false;
}

std::vector<std::string> SettingsManager::list() {
    std::ifstream in(this->settingsPath, std::ios::binary);
    std::vector<std::string> strs;

    if (!in || !in.is_open()) {
        throw FileException(this->settingsPath);
    }

    std::string str;
    Settings settings("");

    while (read(in, settings)) {
        strs.push_back(settings.alias);
    }

    in.close();
    return strs;
}

bool SettingsManager::fileExists() {
    static std::mutex mtx;
    std::lock_guard<std::mutex> lock(mtx);

    std::ifstream file(this->settingsPath);

    if (!file.is_open()) {
        return false;
    }
    file.close();
    return true;
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

void SettingsManager::createDefaults(std::vector<Monitor> monitors) {
    bool exists = fileExists();
    if (!exists) {
        Logger::log("Creating default settings...");
        std::map<std::string, int> duplicates;
        bool success = true;

        for (Monitor m : monitors) {
            std::string monStr = m.getMonitorString();
            std::replace(monStr.begin(), monStr.end(), ' ', '-');
            std::string alias = "default-" + monStr;
            Settings temp("");

            if (exists && load(alias, temp)) {
                int num = ++duplicates.find(alias)->second;
                alias += num;
            }

            else {
                duplicates.insert({ alias, 0 });
            }

            Settings s(alias);
            getFromMonitor(m, s);
            success = save(s) && success;
        }

        if (success) {
            Logger::log("Default settings created successfully!");
        }
        else {
            Logger::log("Default settings couldnt be created.");
        }
    }
}