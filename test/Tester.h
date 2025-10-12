#pragma once
#include "../QuickColorManager.h"
#include "../logger/Logger.h"
#include "../monitor/Monitor.h"
#include "../config/Vcp.h"

class Tester {
public:
	static bool testAll(const std::vector<Monitor>&);
	static bool testFeatures(Monitor);
};