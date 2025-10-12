#include "../QuickColorManager.h"

struct MonitorInformationPair {
public:
	std::vector<PHYSICAL_MONITOR> monitors;
	std::vector<DISPLAY_DEVICE> info;
	void set(PHYSICAL_MONITOR m, DISPLAY_DEVICE d) {
		monitors.push_back(m);
		info.push_back(d);
	}
	std::pair<PHYSICAL_MONITOR, DISPLAY_DEVICE> get(unsigned int i) {
		std::pair<PHYSICAL_MONITOR, DISPLAY_DEVICE> ret;
		if (i > monitors.size() || i > info.size()) {
			return ret;
		}
		ret.first = monitors[i];
		ret.second = info[i];
		return ret;
	}
};
