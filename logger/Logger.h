#pragma once
#include "../QuickColorManager.h"

class Logger {
public:
	static void log(const std::string& message);
	static void log(std::vector<std::string> messages);
};
