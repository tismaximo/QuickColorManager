#pragma once
#include "../QuickColorManager.h"
#include "../logger/Logger.h"
#include "../monitor/Monitor.h"
#include "../exceptions/Exceptions.h"

class SettingsManager {
protected:
	std::string settingsPath;
public:
	SettingsManager(std::string);
	std::string getSettingsPath() const;
	bool save(Settings);
	bool load(std::string alias, Settings&) const;
	bool apply(Monitor, Settings);
	bool getFromMonitor(Monitor, Settings&);
	bool fileExists();
	void createDefaults(std::vector<Monitor> monitors);
	std::vector<std::string> list();
};