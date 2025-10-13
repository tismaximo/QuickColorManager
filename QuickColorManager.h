#pragma once
#ifndef APP_HEADER_H
#define APP_HEADER_H

#include <iostream>
#include <windows.h>
#include <highlevelmonitorconfigurationapi.h>
#include <lowlevelmonitorconfigurationapi.h>
#include <physicalmonitorenumerationapi.h>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <map>
#include <sstream>
#include <iomanip> 
#include <mutex>
#include <thread>
#include <algorithm>
#include <codecvt>
#include <cstdlib>
#include <utility>
#include <exception>

#pragma comment(lib, "Dxva2.lib")

#include "helpers/Helpers.h"

typedef unsigned short U16;

enum CmdCapability {
	GET  = 0x01,
	SET  = 0x02,
	SAVE = 0x03
};

enum VcpFeature {
	 BRIGHTNESS	   = 0x10,
	 CONTRAST      = 0x12,
	 GAMMA         = 0x72,
	 RED_BALANCE   = 0x16,
	 GREEN_BALANCE = 0x18,
	 BLUE_BALANCE  = 0x1A,
	 AUTO_ADJUST   = 0xAE,
	 AUTO_COLOR    = 0xAC,
	 RESTORE	   = 0x04
};

enum Error {
	ARG_ERROR,
	VAL_ERROR,
	FILE_ERROR,
	DEVICE_ERROR,
	OUT_OF_BOUNDS
};

struct Settings {
public:
	std::string alias;
	U16 brightness;
	U16 contrast;
	U16 gamma;
	U16 redBalance;
	U16 greenBalance;
	U16 blueBalance;
	Settings(std::string alias,
		U16 brightness = 70,
		U16 contrast = 70,
		U16 gamma = 70,
		U16 redBalance = 70,
		U16 greenBalance = 70,
		U16 blueBalance = 70);
	std::string str() const;
};

struct MonitorInformationPair;

class Logger {
public:
	static void log(const std::string& message);
	static void log(std::vector<std::string> messages);
};

class Monitor;
class MonitorGetter;
class Tester;
class SettingsManager;
class App;
class ConsoleApp;

class ICodedException;
class ValueException;
class ArgumentException;
class FileException;
class DeviceException;
class NotFoundException;

#endif
