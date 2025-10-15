#pragma once
#include <string>

namespace Messages {
	constexpr const char* QMC_MESSAGE = "Quick Color Manager is a tool that allows its users to easily change between color settings across multiple monitors.\n\nAvailable commands:\n\n";
	constexpr const char* TEST_HELP = "\ttest: Runs a test on all devices. Will tell you which features are supported or unsupported by your devices.\n";
	constexpr const char* SET_HELP = "\tset <device-id> (brightness, contrast, gamma, red, green, blue): Apply one or more settings. Example usage: set brightness 70 contrast 75 red 100\n";
	constexpr const char* GET_HELP = "\tget <device-id> (brightness, contrast, gamma, red, green, blue, all, maxvalues): Get one or more currently loaded settings. Example usage: get brightness contrast --maxvalues. The --maxvalues flag will return the maximum admitted values for the selected settings.\n";
	constexpr const char* SAVE_HELP = "\tsave <device-id> <alias>: Saves the currently loaded settings from the device to the specified alias. \n";
	constexpr const char* LOAD_HELP = "\tload <device-id> <alias>: Loads settings from an alias.\n";
	constexpr const char* LIST_HELP = "\tlist <settings|devices>: Lists all available settings or devices.\n";

	constexpr const char* INVALID_OPTION = "Invalid option. Run 'qmc' to see all available commands and valid options.";

	constexpr const char* WARNING = "Setting unsupported features, loading one monitor's profile into another, or using this program with devices that dont follow the MCCS specification may lead to undefined monitor behavior. Use at your own risk.";
	const std::string LOG_WARNING = "[WARNING] " + std::string(WARNING);
}

