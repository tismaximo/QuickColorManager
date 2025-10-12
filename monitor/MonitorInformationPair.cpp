#include "../QuickColorManager.h"
#include "MonitorTypes.h"

void MonitorInformationPair::set(PHYSICAL_MONITOR m, DISPLAY_DEVICE d) {
	monitors.push_back(m);
	info.push_back(d);
}

std::pair<PHYSICAL_MONITOR, DISPLAY_DEVICE> MonitorInformationPair::get(unsigned int i) {
	std::pair<PHYSICAL_MONITOR, DISPLAY_DEVICE> ret;
	if (i > monitors.size() || i > info.size()) {
		return ret;
	}
	ret.first = monitors[i];
	ret.second = info[i];
	return ret;
}