#include "../include/QuickColorManager.h"

// escribir al archivo manualmente propiedad por propiedad para manejar std::string correctamente

static void writeofstream(std::ofstream& file, const Settings& settings) {
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

static void writefstream(std::fstream& file, const Settings& settings) {
    size_t strlen = settings.alias.size();
    file.write(reinterpret_cast<const char*>(&strlen), sizeof(strlen));
    file.write(settings.alias.data(), strlen);
    file.write(reinterpret_cast<const char*>(&settings.brightness), sizeof(settings.brightness));
    file.write(reinterpret_cast<const char*>(&settings.contrast), sizeof(settings.contrast));
    file.write(reinterpret_cast<const char*>(&settings.gamma), sizeof(settings.gamma));
    file.write(reinterpret_cast<const char*>(&settings.redBalance), sizeof(settings.redBalance));
    file.write(reinterpret_cast<const char*>(&settings.greenBalance), sizeof(settings.greenBalance));
    file.write(reinterpret_cast<const char*>(&settings.blueBalance), sizeof(settings.blueBalance));
}

static bool readifstream(std::ifstream& file, Settings& settings) {
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

static bool readfstream(std::fstream& file, Settings& settings) {
    size_t strlen;
    if (!file.read(reinterpret_cast<char*>(&strlen), sizeof(strlen))) return false;
    settings.alias.resize(strlen);
    if (!file.read(&settings.alias[0], strlen)) return false;
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

bool SettingsManager::save(Settings settings) {
    static std::mutex mtx;
    std::lock_guard<std::mutex> lock(mtx);

    std::fstream file(this->settingsPath, std::ios::out | std::ios::in | std::ios::binary | std::ios::trunc);

    if (!file.is_open()) {
        file.open(this->settingsPath, std::ios::out | std::ios::binary);
        file.close();

        file.open(this->settingsPath, std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);
    }

    if (!file || !file.is_open()) {
        Logger::log("Error when opening the settings file. Make sure the file is in the same folder as this .exe and that it has read/write permissions");
        return false;
    }

    Settings temp(settings.alias);
    int pos = 0;

    std::vector<Settings> all;

    while (readfstream(file, temp)) {
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
    file.close();
    std::ofstream out(this->settingsPath, std::ios::binary | std::ios::trunc);
    for (Settings s : all) {
        writeofstream(out, s);
    }

    out.close();
    return true;
}

bool SettingsManager::load(std::string alias, Settings& settings) const {
    static std::mutex mtx;
    std::lock_guard<std::mutex> lock(mtx);

    std::ifstream in(this->settingsPath, std::ios::binary);

    if (!in || !in.is_open()) {
        Logger::log("Error when opening the settings file. Make sure the file is in the same folder as this .exe and that it has read/write permissions");
        return false;
    }
    
    while (readifstream(in, settings)) {
        if (settings.alias == alias) {
            in.close();
            return true;
        }
    }

    in.close();
    Logger::log("ERROR: Settings alias not found: " + alias);
    return false;
}

std::vector<std::string> SettingsManager::list() {
    std::ifstream in(this->settingsPath, std::ios::binary);
    std::vector<std::string> strs;

    if (!in || !in.is_open()) {
        Logger::log("Error when opening the settings file. Make sure the file is in the same folder as this .exe and that it has read/write permissions");
        return strs;
    }

    std::string str;
    Settings settings("");

    while (readifstream(in, settings)) {
        strs.push_back(settings.alias);
    }

    in.close();
    return strs;
}

bool SettingsManager::fileExists() {
    static std::mutex mtx;
    std::lock_guard<std::mutex> lock(mtx);

    std::fstream file(this->settingsPath, std::ios::out | std::ios::in | std::ios::binary);

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
    if (!fileExists()) {
        Logger::log("Creating default settings...");
        std::map<std::string, int> duplicates;
        bool success = true;

        for (Monitor m : monitors) {
            std::string monStr = m.getMonitorString();
            std::replace(monStr.begin(), monStr.end(), ' ', '-');
            std::string alias = "default-" + monStr;
            Settings temp("");

            if (fileExists() && load(alias, temp)) {
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