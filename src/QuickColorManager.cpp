#include "../include/QuickColorManager.h"

int main(int argc, char* argv[]) {
    MonitorGetter getter;
    auto monitors = getter.getAll();
    App app(monitors);
    ConsoleApp capp(app);
    capp.parseArgs(argc, argv);
    std::cout << app.doListDevices();

#ifndef NDEBUG
    std::cout << "Press ENTER to exit.";
    std::cin.get();
#endif
    return 0;
};