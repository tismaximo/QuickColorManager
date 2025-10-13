#pragma once
#include "../QuickColorManager.h"
#include "../exceptions/Exceptions.h"

struct MonitorInformationPair {
public:
	std::vector<PHYSICAL_MONITOR> monitors;
	std::vector<DISPLAY_DEVICE> info;
	void set(PHYSICAL_MONITOR m, DISPLAY_DEVICE d);
	std::pair<PHYSICAL_MONITOR, DISPLAY_DEVICE> get(unsigned int i);
};
