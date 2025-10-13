#include "QuickColorManager.h"
#include "settings/SettingsManager.h"
#include "monitor/MonitorGetter.h"
#include "app/ConsoleApp.h"
#include "logger/Logger.h"
#include "exceptions/Exceptions.h"

int main(int argc, char* argv[]) {
	MonitorGetter getter;
	SettingsManager manager("settings.dat");
	auto monitors = getter.getAll();
	ConsoleApp app(monitors, manager);
	manager.createDefaults(monitors);
#ifdef NDEBUG
	return app.runRelease(argc, argv);
#else
	app.runDebug();
	return 0;
#endif
};