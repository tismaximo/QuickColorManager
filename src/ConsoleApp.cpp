#include "../include/QuickColorManager.h"

static void printSetUsageText() {
	std::cout << "\tset <device-id> (-brightness, -contrast, -gamma, -red, -green, -blue): Apply one or more settings. Example usage: qcm set -brightness 70 -contrast 75 -red 100\n";
}

static void printGetUsageText() {
	std::cout << "\tget <device-id> (-brightness, -contrast, -gamma, -red, -green, -blue) (--all, --maxvalues): Get one or more currently loaded settings. Example usage: qcm get -brightness -contrast --maxvalues\n";
}

static void printSaveUsageText() {
	std::cout << "\tsave <device-id> <alias>: Saves the currently loaded settings from the device to the specified alias. \n";
}

static void printLoadUsageText() {
	std::cout << "\tload <device-id> <alias>: Loads settings from an alias.\n";
}

static void printListUsageText() {
	std::cout << "\tlist <settings|devices>: Lists all available settings or devices.\n";
}

static void printUsageText() {
	/*
	Quick Color Manager is a tool that allows its users to easily change between color settings across multiple monitors.

	Available commands:

	set <device-id> (-brightness, -contrast, -gamma, -red, -green, -blue): Apply one or more settings. Example usage: qcm set -brightness 70 -contrast 75 -red 100
	get <device-id> (-brightness, -contrast, -gamma, -red, -green, -blue) {--all, --maxvalues}: Get one or more currently loaded settings. Example usage: qcm get -brightness -contrast --maxvalues
	save <device-id> <alias>: Saves the currently loaded settings from the device to the specified alias.
	load <device-id> <alias>: Loads settings from an alias.
	list <settings|devices>: Lists all available settings or devices.
	*/
	std::cout << "Quick Color Manager is a tool that allows its users to easily change between color settings across multiple monitors.\n\n";
	std::cout << "Available commands:\n\n";
	printSetUsageText();
	printGetUsageText();
	printSaveUsageText();
	printLoadUsageText();
	printListUsageText();
}

static void printInvalidArgument() {
	std::cout << "Invalid argument. Run 'qmc' to see all available commands and valid options.";
}

static void printIdNotFound(int id) {
	std::cout << "Device with the following id was not found: " << id << "\nRun 'qmc list devices' to see all the available devices and their ids.";
}

static void printSettingNotFound(std::string alias) {
	std::cout << "Settings with the following alias were not found: " << alias << "\nRun 'qmc list settings' to see all the available settings and their aliases.";
}

ConsoleApp::ConsoleApp(std::vector<Monitor> monitors, SettingsManager manager): App(monitors, manager) {}

int ConsoleApp::parseArgs(int argc, char* argv[]) {
	if (argc < 2) {
		printUsageText();
		return 0;
	}

	if (strcmp(argv[1], "save") == 0) {
		if (argc != 4) {
			printListUsageText();
			return 0;
		}

		int i = atoi(argv[2]) - 1;
		if (i < 0 || i > this->monitors.size()) {
			printIdNotFound(i);
			return 2;
		}
		Monitor m = monitors[i];

		Settings settings(argv[3]);
		if (!manager.getFromMonitor(m, settings)) {
			Logger::log("One or more of the settings from the device couldn't be saved to the settings file. Run 'qmc test' to see which (if any) features are unsupported by your device.");
			return 3;
		}

		if (!manager.save(settings)) {
			Logger::log("Couldn't write to the settings file. Check that the file exists and that the program has write permissions.");
			return 4;
		}

	}

	if (strcmp(argv[1], "list") == 0) {
		if (argc == 2) {
			printListUsageText();
			return 0;
		}
		else if (strcmp(argv[2], "devices") == 0) {
			this->doListDevices();
			return 0;
		}
		else if (strcmp(argv[2], "devices") == 0) {
			this->doListSettings();
			return 0;
		}
		else {
			printInvalidArgument();
			return 1;
		}
	}

	return 0;
}