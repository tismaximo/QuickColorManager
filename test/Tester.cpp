#include "Tester.h"

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
			Logger::log("Feature NOT supported: " + text);
			flag = false;
			continue;
		}
		Logger::log("Feature supported: " + text);
	}
	return flag;
}


bool Tester::testAll(const std::vector<Monitor>& monitors) {
	bool result = true;
	for (Monitor m : monitors) {
		result = Tester::testFeatures(m);
	}

	return result;
}

bool Tester::testFeatures(Monitor monitor) {
	bool result = true;
	std::string model = monitor.getMonitorString();
	std::string str = monitor.getCapabilitiesString();
	if (str == "") {
		Logger::log("Your monitor (" + model + ") is incompatible with this application. This might happen if youre on a laptop or if your screen doesnt support DDC/CI or if DDC/CI is disabled.");
		return false;
	}
	
	std::string match = "vcp(";
	size_t startVcp = str.find(match);

	if (startVcp == std::string::npos) {
		Logger::log("Your monitor (" + model + ") doesnt support any of the supported VCP features (brightness, contrast, etc). Changing these settings in this program is likely not going to work.");
		return result = false;
	}

	startVcp += match.length();
	std::string substr = str.substr(startVcp);
	std::string vcp = findSubstrExcludeParenthesis(substr);
	result = findCapabilitiesInSubstring(EXPECTED_VCP_CAPABILITIES, VCP_STRINGS, vcp);

	if (!result) {
		Logger::log("The monitor (" + model + ") doesnt support all VCP features, some features might not work on it. NOTE: The gamma feature is expected not to work in most monitors.");
	}
	else {
		Logger::log("The monitor (" + model + ") passed the test!");
	}

	return result;
}