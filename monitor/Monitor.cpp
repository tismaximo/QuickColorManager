#include "Monitor.h"

Monitor::Monitor(HANDLE handle, DISPLAY_DEVICE info): handle(handle), info(info) {
}

DISPLAY_DEVICE Monitor::getInfo() {
	return this->info;
}

bool Monitor::set(VcpFeature feature, U16 val) {
	bool success = SetVCPFeature(this->handle, feature, val);

	std::string text = hexString(feature);
	auto it = VCP_STRINGS.find(feature);
	if (it != VCP_STRINGS.end()) {
		text = it->second;
	}

	if (!success) {
		return false;
	}

	return true;
}


bool Monitor::get(VcpFeature feature, U16& val, bool maxvalues) {
	DWORD wordval = val;
	DWORD maxval = val;
	bool success = true;
	if (maxvalues) {
		success = GetVCPFeatureAndVCPFeatureReply(this->handle, feature, nullptr, &wordval, &maxval);
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
		return false;
	}

	if (maxvalues) val = maxval;
	else val = wordval;
	return true;
}

std::string Monitor::getCapabilitiesString() {
	DWORD size = 0;

	if (!GetCapabilitiesStringLength(this->handle, &size)) {
		throw DeviceException(this->getMonitorString());
	}

	std::vector<char> str(size);
	if (!CapabilitiesRequestAndCapabilitiesReply(this->handle, str.data(), size)) {
		throw DeviceException(this->getMonitorString());
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

