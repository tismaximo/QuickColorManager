#include "Monitor.h"

Monitor::Monitor(HANDLE handle, DISPLAY_DEVICE info): handle(handle), info(info) {
}

DISPLAY_DEVICE Monitor::getInfo() const {
	return this->info;
}

bool Monitor::set(VcpFeature feature, U16 val) const {
	U16 temp;
	bool maxvalues = true;
	if (!this->get(feature, temp, maxvalues)) {
		return false;
	}
	if (val > temp) {
		throw ValueException(VCP_STRINGS.at(feature), val, temp);
	}
	// chequear que el valor este dentro del rango permitido
	bool success = SetVCPFeature(this->handle, feature, val);

	if (!success) {
		return false;
	}

	return true;
}


bool Monitor::get(VcpFeature feature, U16& val, bool maxvalues) const {
	DWORD wordval = val;
	bool success = true;

	if (maxvalues) {
		DWORD maxval = val;
		success = GetVCPFeatureAndVCPFeatureReply(this->handle, feature, nullptr, &wordval, &maxval);
		val = maxval;
	}
	else {
		success = GetVCPFeatureAndVCPFeatureReply(this->handle, feature, nullptr, &wordval, nullptr);
		val = wordval;
	}

	if (!success) {
		return false;
	}

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

