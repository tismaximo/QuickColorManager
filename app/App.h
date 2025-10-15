#pragma once
#include "../QuickColorManager.h"
#include "../monitor/Monitor.h"
#include "../settings/SettingsManager.h"
#include "../config/Vcp.h"
#include "../exceptions/Exceptions.h"
#include "../test/Tester.h"
#include "../helpers/Helpers.h"

class App {
protected:
	std::vector<Monitor> monitors;
	SettingsManager manager;
public:
	App(std::vector<Monitor> monitors, SettingsManager manager);
	int doSet(int id, std::vector<std::string> features, std::vector<U16> vals);
	int doGet(int id, std::vector<std::string> features, std::vector<U16>& vals, bool maxvalues);
	int doLoad(int id, std::string settingsAlias);
	int doSave(int id, std::string settingsAlias);
	std::vector<std::string> doListDevices();
	std::vector<std::string> doListSettings();
	bool doTest(std::vector<Monitor> monitors);
	bool init();
};