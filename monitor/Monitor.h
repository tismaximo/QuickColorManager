#pragma once
#include "../QuickColorManager.h"
#include "../logger/Logger.h"
#include "../config/Vcp.h"

class Monitor {
protected:
	HANDLE handle;
	DISPLAY_DEVICE info;
public:
	Monitor(HANDLE, DISPLAY_DEVICE);
	bool set(VcpFeature, U8 val);
	bool get(VcpFeature, U8& val, bool maxvalues = false);
	std::string getCapabilitiesString();
	std::string getMonitorString();
	DISPLAY_DEVICE getInfo();
	bool operator==(const Monitor& that) const;
	~Monitor();
};
