#pragma once
#include "../QuickColorManager.h"
#include "MonitorTypes.h"

class MonitorGetter {
protected:
	MonitorInformationPair mip;
public:
	MonitorGetter();
	std::vector<Monitor> getAll();
	~MonitorGetter();
};