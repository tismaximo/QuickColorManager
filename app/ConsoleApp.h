#pragma once
#include "../QuickColorManager.h"
#include "../test/Tester.h"
#include "App.h"

class ConsoleApp : public App {
public:
	ConsoleApp(std::vector<Monitor>, SettingsManager);
	std::pair<std::string, U8> parseArgValue(std::string searchArg, char arg[], char value[]);
	int parseArgs(int argc, char* argv[]);
	bool pushArgTo(std::string searchArg, char arg[], char value[], std::vector<std::string>& features, std::vector<U8>& vals);
	void printList(std::vector<std::string>);
	void loop();
};