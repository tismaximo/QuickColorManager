#include "../include/QuickColorManager.h"

static std::string findSubstrExcludeParenthesis(std::string str) {
	size_t startPrths = 0;

	while ((startPrths = str.find("(")) != std::string::npos) {
		size_t endPrths = str.find(")", startPrths);
		size_t len = endPrths - startPrths;
		str.erase(startPrths, len);
	}

	return str;
}

static bool findCapabilitiesInSubstring(const std::vector<int>& capabilities, const std::map<int, std::string>& lookup, const std::string& substr) {
	bool flag = true;
	for (int cap : capabilities) {
		std::string hexCode = hexString(cap);

		size_t pos = substr.find(hexCode);
		auto it = lookup.find(cap);
		std::string text = hexCode;

		if (it != lookup.end()) {
			text = it->second;
		}
		if (pos == std::string::npos) {
			Logger::log("Capability NOT supported: " + text);
			flag = false;
			continue;
		}
		Logger::log("Capability supported: " + text);
	}
	return flag;
}


bool Tester::testCapabilities(Monitor h) {
	bool result = true;

	std::string str = h.getCapabilitiesString();
	std::string model = h.getMonitorString(str);
	std::string match = "vcp(";
	size_t startVcp = str.find(match);
	if (startVcp == std::string::npos) {
		Logger::log("Your monitor (" + model + ") doesnt support any of the supported VCP options (brightness, contrast, etc). Changing these settings in this program is likely not going to work.");
		return result = false;
	}

	startVcp += match.length();
	std::string substr = str.substr(startVcp);
	std::string vcp = findSubstrExcludeParenthesis(substr);
	result = findCapabilitiesInSubstring(EXPECTED_VCP_CAPABILITIES, VCP_STRINGS, vcp);

	if (!result) {
		Logger::log("The monitor (" + model + ") didn't pass the test, some functionalities might not work on it. NOTE: Gamma is expected not to work in most monitors.");
	}
	else {
		Logger::log("The monitor (" + model + ") passed the test!");
	}

	return result;
}