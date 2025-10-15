#pragma once

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

#include "config/Messages.h"

typedef unsigned short U16;

enum CmdCapability {
	GET  = 0x01,
	SET  = 0x02,
	SAVE = 0x03
};

enum VcpFeature {
	BRIGHTNESS = 0x10,
	CONTRAST = 0x12,
	GAMMA = 0x72,
	RED_BALANCE = 0x16,
	GREEN_BALANCE = 0x18,
	BLUE_BALANCE = 0x1A,
	AUTO_ADJUST = 0xAE,
	AUTO_COLOR = 0xAC,
	RESTORE = 0x04,
	SHARPNESS = 0x87,
	SATURATION = 0x8A,
	RED_SATURATION = 0x59,
	YELLOW_SATURATION = 0x5A,
	GREEN_SATURATION = 0x5B,
	CYAN_SATURATION = 0x5C,
	BLUE_SATURATION = 0x5D,
	MAGENTA_SATURATION = 0x5E,
	HUE = 0x8B,
	NONE = 0x00
};

enum Error {
	ARG_ERROR,
	VAL_ERROR,
	FILE_ERROR,
	DEVICE_ERROR,
	OUT_OF_BOUNDS
};

struct MonitorInformationPair;
struct Settings;
struct SettingsFileVcpMap;
struct VcpValuePtrPair;

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
class NoValueException;
class ArgumentException;
class FileException;
class DeviceException;
class NotFoundException;