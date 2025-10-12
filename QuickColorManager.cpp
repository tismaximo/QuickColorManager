#include "QuickColorManager.h"
#include "settings/SettingsManager.h"
#include "monitor/MonitorGetter.h"
#include "app/ConsoleApp.h"

int main(int argc, char* argv[]) {
    try {
        MonitorGetter getter;
        SettingsManager manager("settings.dat");
        auto monitors = getter.getAll();
        ConsoleApp app(monitors, manager);
        manager.createDefaults(monitors);
#ifndef NDEBUG
        app.loop();
#endif
        app.parseArgs(argc, argv);
    }
    catch (const std::exception& e) {
        std::string what(e.what());
        Logger::log("Program threw an exception: " + what);
    }
    catch (...) {
        Logger::log("Program threw an unknown exception, finishing execution");
    }
    
    return 0;
};