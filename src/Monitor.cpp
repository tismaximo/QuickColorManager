#include "../include/QuickColorManager.h"

Monitor::Monitor(HANDLE handle): handle(handle) {
}

bool Monitor::set(VcpCapability feature, uint8_t val) {
	bool success = SetVCPFeature(this->handle, feature, val);

	std::string text = hexString(feature);
	auto it = VCP_STRINGS.find(feature);
	if (it != VCP_STRINGS.end()) {
		text = it->second;
	}

	if (!success) {
		Logger::log("Failed to set: " + text);
		return false;
	}

	Logger::log("Successfully set: " + text);
	return true;
}


bool Monitor::get(VcpCapability feature, uint8_t& val) {
	DWORD wordval = val;
	bool success = GetVCPFeatureAndVCPFeatureReply(this->handle, feature, nullptr, &wordval, nullptr);

	std::string text = hexString(feature);
	auto it = VCP_STRINGS.find(feature);
	if (it != VCP_STRINGS.end()) {
		text = it->second;
	}

	if (!success) {
		Logger::log("Failed to get: " + text);
		return false;
	}

	val = wordval;
	Logger::log("Successfully got: " + text);
	return true;
}

std::string Monitor::getCapabilitiesString() {
	DWORD size = 0;

	if (!GetCapabilitiesStringLength(this->handle, &size)) {
		return std::string("");
	}

	std::vector<char> str(size);
	if (!CapabilitiesRequestAndCapabilitiesReply(this->handle, str.data(), size)) {
		return std::string("");
	}

	return std::string(str.begin(), str.end());
}

std::string Monitor::getMonitorString(std::string str = "") {
	if (str == "") str = this->getCapabilitiesString();
	size_t start = str.find("type(");
	size_t endFirst = str.find(")", start);
	size_t endSecond = str.find(")", endFirst + 1);
	size_t len = endSecond - start + 1;
	return str.substr(start, len);
}

Monitor::~Monitor() {
}

