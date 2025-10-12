#include "Monitor.h"

Monitor::Monitor(HANDLE handle, DISPLAY_DEVICE info): handle(handle), info(info) {
}

DISPLAY_DEVICE Monitor::getInfo() {
	return this->info;
}

bool Monitor::set(VcpFeature feature, U8 val) {
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


bool Monitor::get(VcpFeature feature, U8& val, bool maxvalues) {
	DWORD wordval = val;
	bool success = true;
	if (maxvalues) {
		success = GetVCPFeatureAndVCPFeatureReply(this->handle, feature, nullptr, nullptr, &wordval);
	}
	else {
		success = GetVCPFeatureAndVCPFeatureReply(this->handle, feature, nullptr, &wordval, nullptr);
	}
	
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

std::string Monitor::getMonitorString() {
	return unwide(getInfo().DeviceString);
}

bool Monitor::operator==(const Monitor& that) const{
	return this->handle == that.handle;
}

Monitor::~Monitor() {
}

