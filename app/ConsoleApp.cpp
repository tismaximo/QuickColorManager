#include "ConsoleApp.h"

static void printSetUsageText() {
	std::cout << "\tset <device-id> (-brightness, -contrast, -gamma, -red, -green, -blue): Apply one or more settings. Example usage: set -brightness 70 -contrast 75 -red 100\n";
}

static void printGetUsageText() {
	std::cout << "\tget <device-id> (--brightness, --contrast, --gamma, --red, --green, --blue, --all, --maxvalues): Get one or more currently loaded settings. Example usage: get -brightness -contrast --maxvalues. The --maxvalues flag will return the maximum admitted values for the selected settings.\n";
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

static void printTestUsageText() {
	std::cout << "\ttest: Runs a test on all devices. Will tell you which features are supported or unsupported by your devices.\n";
}

static void printUsageText() {
	/*
	Quick Color Manager is a tool that allows its users to easily change between color settings across multiple monitors.

	Available commands:

	set <device-id> (-brightness, -contrast, -gamma, -red, -green, -blue): Apply one or more settings. Example usage: qcm set -brightness 70 -contrast 75 -red 100
	get <device-id> {--brightness, --contrast, --gamma, --red, --green, --blue, --all, --maxvalues}: Get one or more currently loaded settings. Example usage: qcm get -brightness -contrast --maxvalues
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
	printTestUsageText();
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

std::pair<std::string, U16> ConsoleApp::parseArgValue(std::string searchArg, char arg[], char value[]) {
	std::pair<std::string, U16> ret("", 0);
	std::string argument(arg);

	if (argument != searchArg) {
		return ret;
	}

	int val = valueFromArg(value);
	if (val < 0) {
		Logger::log("ERROR: Invalid value or no value given for argument: " + argument);
		return ret;
	}

	ret.first = argument;
	ret.second = val;
	return ret;
}

bool ConsoleApp::pushArgTo(std::string searchArg, char arg[], char value[], std::vector<std::string>& features, std::vector<U16>& vals) {
	auto argValue = parseArgValue(searchArg, arg, value);
	if (argValue.first != "") {
		features.push_back(argValue.first);
		vals.push_back(argValue.second);
		return true;
	}
	return false;
}

void ConsoleApp::printList(std::vector<std::string> list) {
	for (std::string str : list) {
		std::cout << str << "\n";
	}
}

int ConsoleApp::parseArgs(int argc, char* argv[]) {
	if (argc < 2) {
		printUsageText();
		return 0;
	}

	if (strcmp(argv[1], "set") == 0) {
		if (argc < 4) {
			printSetUsageText();
			return 0;
		}
		
		std::vector<std::string> features;
		std::vector<U16> vals;

		for (int i = 3; i < argc; i = i+2) {
			bool found = false;
			for (auto arg : VCP_ARGS) {
				found = pushArgTo(arg.first, argv[i], argv[i + 1], features, vals) || found; // chequear que el argumento sea valido y si lo es agregar el argumento y el valor a los vectores
			}

			if (!found) {
				Logger::log("ERROR: Unrecognized argument: " + std::string(argv[i]));
				return ARG_ERROR;
			}
		}

		return this->doSet(atoi(argv[2]), features, vals);
	}

	if (strcmp(argv[1], "get") == 0) {
		if (argc < 4) {
			printGetUsageText();
			return 0;
		}

		std::vector<std::string> features;
		std::vector<U16> vals;
		bool maxvalues = false;
		bool all = false;

		for (int i = 3; i < argc; i++) {
			if (maxvalues && all) {
				i = argc + 1;
				continue; // acabar el loop, no hace falta continuar
			}

			if (strcmp(argv[i], "--maxvalues") == 0) {
				maxvalues = true;
				continue;
			}

			if (strcmp(argv[i], "--all") == 0) {
				all = true;
				features.clear();
				for (auto arg : VCP_ARGS) {
					features.push_back(arg.first);
					vals.push_back(0);
				}
				continue;
			}

			bool found = all;
			if (!all) for (auto arg : VCP_ARGS) {
				if ( argv[i] == arg.first ) {
					found = true;
					features.push_back(arg.first);
					vals.push_back(0);
				}
			}

			if (!found) {
				Logger::log("ERROR: Unrecognized argument: " + std::string(argv[i]));
				return ARG_ERROR;
			}
		}

		int retvalue = this->doGet(atoi(argv[2]), features, vals, maxvalues);
		if (retvalue != 0) {
			return retvalue;
		}

		std::cout << "Values gotten: " << "\n";
		for (int i = 0; i < features.size(); i++) {
			auto arg = VCP_ARGS.find(features[i]);
			auto str = VCP_STRINGS.find(arg->second);
			std::cout << str->second << ": " << vals[i] << "\n";
		}
		return 0;
	}

	if (strcmp(argv[1], "save") == 0) {
		if (argc > 4) {
			Logger::log("INFO: The settings alias shouldnt have any spaces");
			return 0;
		}
		if (argc < 4) {
			printSaveUsageText();
			return 0;
		}
		return this->doSave(atoi(argv[2]), argv[3]);
	}

	if (strcmp(argv[1], "load") == 0) {
		if (argc > 4) {
			Logger::log("INFO: The settings alias shouldnt have any spaces");
			return 0;
		}
		if (argc < 4) {
			printLoadUsageText();
			return 0;
		}
		return this->doLoad(atoi(argv[2]), argv[3]);
	}

	if (strcmp(argv[1], "list") == 0) {
		if (argc == 2) {
			printListUsageText();
			return 0;
		}
		else if (strcmp(argv[2], "devices") == 0) {
			std::cout << "Found the following devices (ID | DeviceName | DeviceString): \n";
			printList(this->doListDevices());
			return 0;
		}
		else if (strcmp(argv[2], "settings") == 0) {
			std::vector<std::string> list = this->doListSettings();
			if (list.size() > 0) {
				std::cout << "Found the following setting aliases in the settings file: " << "\n";
				printList(list);
			}
			else {
				std::cout << "Didnt find any settings in the settings file. Create a setting alias from the current device settings by running 'save <device-id> <alias>'" << "\n";
			}
			return 0;
		}
		else {
			printInvalidArgument();
			return ARG_ERROR;
		}
	}

	if (strcmp(argv[1], "test") == 0) {
		Tester::testAll(this->monitors);
		return 0;
	}

	return 0;
}

void ConsoleApp::loop() {
	printUsageText();
	while (true) {
		std::string in, word;
		std::cout << "Enter a command: ";
		std::getline(std::cin, in);
		in.insert(0, "qcm ");

		int argc = 0;
		std::stringstream ss(in);
		std::vector<std::string> words;
		while (ss >> word) {
			argc++;
			words.push_back(word);
		}

		char** newargs = static_cast<char**>(malloc(sizeof(char*) * argc));
		int size = 32;

		for (int i = 0; i < argc; i++) {
			newargs[i] = static_cast<char*>(malloc(sizeof(char) * size));
		}

		for (int i = 0; i < argc; i++) {
			strcpy_s(newargs[i], size, words[i].c_str());
		}

		parseArgs(argc, newargs);

		for (int i = 0; i < argc; i++) {
			free(newargs[i]);
		}
		free(newargs);
	}
}