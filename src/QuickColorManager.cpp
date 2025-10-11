#include "../include/QuickColorManager.h"

int main(int argc, char* argv[]) {
    MonitorGetter getter;
    SettingsManager manager("settings.dat");
    auto monitors = getter.getAll();
    ConsoleApp app(monitors, manager);
    manager.createDefaults(monitors);
#ifndef NDEBUG
    app.loop();
#endif
    app.parseArgs(argc, argv);
    return 0;
};