#pragma once
#include "../QuickColorManager.h"
#include "../logger/Logger.h"
#include "../config/Vcp.h"
#include "../exceptions/Exceptions.h"
#include "../helpers/Helpers.h"

class Monitor {
protected:
	HANDLE handle;
	DISPLAY_DEVICE info;
public:
	Monitor(HANDLE, DISPLAY_DEVICE);
	bool set(VcpFeature, U16 val) const;
	bool get(VcpFeature, U16& val, bool maxvalues = false) const;
	std::string getCapabilitiesString();
	std::string getMonitorString();
	DISPLAY_DEVICE getInfo() const;
	bool operator==(const Monitor& that) const;
	~Monitor();
};
