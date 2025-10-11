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

#pragma comment(lib, "Dxva2.lib")

typedef unsigned short U8;

static std::string hexString(const int& num) {
	std::stringstream ss;
	ss << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << num;
	std::string hexCode = ss.str();
	return hexCode;
}

static std::string unwide(const std::wstring& wstr) {
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	return converter.to_bytes(wstr);
}

static int valueFromArg(const std::string& arg) {
	try {
		int val = std::stoi(arg);
		return val;
	}
	catch (const std::invalid_argument& _) {
		return -1;
	}
}

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

enum Errors {
	ARG_ERROR,
	VAL_ERROR,
	FILE_ERROR,
	DEVICE_ERROR
};


const std::vector<int> EXPECTED_CMDS_CAPABILITIES = {
	GET,
	SET,
	SAVE
};
const std::map<int, std::string> CMDS_STRINGS = {
	{GET, "Get feature"},
	{SET, "Set feature"},
	{SAVE, "Save settings"},
};

const std::vector<int> EXPECTED_VCP_CAPABILITIES = {
	CONTRAST,
	BRIGHTNESS,
	GAMMA,
	RED_BALANCE,
	GREEN_BALANCE,
	BLUE_BALANCE,
	AUTO_ADJUST,
	AUTO_COLOR,
	RESTORE
};
const std::map<int, std::string> VCP_STRINGS = {
	{RESTORE, "Restore"},
	{BRIGHTNESS, "Brightness"},
	{CONTRAST, "Contrast"},
	{GAMMA, "Gamma"},
	{RED_BALANCE, "Red balance"},
	{GREEN_BALANCE, "Green balance"},
	{BLUE_BALANCE, "Blue balance"},
	{AUTO_ADJUST, "Automatic adjust settings"},
	{AUTO_COLOR, "Automatic adjust colors"}
};
const std::map<std::string, VcpFeature> VCP_ARGS = {
	{"-brightness", BRIGHTNESS},
	{"-contrast", CONTRAST},
	{"-gamma", GAMMA},
	{"-red", RED_BALANCE},
	{"-green", GREEN_BALANCE},
	{"-blue", BLUE_BALANCE}
};



struct Settings {
public:
	std::string alias;
	U8 brightness;
	U8 contrast;
	U8 gamma;
	U8 redBalance;
	U8 greenBalance;
	U8 blueBalance;
	Settings(
		std::string alias,
		U8 brightness   = 70,
		U8 contrast     = 70,
		U8 gamma        = 70,
		U8 redBalance   = 70,
		U8 greenBalance = 70,
		U8 blueBalance  = 70
	) :
		alias(alias),
		brightness(brightness),
		contrast(contrast),
		gamma(gamma),
		redBalance(redBalance),
		greenBalance(greenBalance),
		blueBalance(blueBalance)
	{}
	std::string str() const {
		std::ostringstream ss;
		ss << "Settings From " << this->alias << ":\nBrightness : " << +this->brightness
		<< "\nContrast: " << +this->contrast
		<< "\nGamma: " << +this->gamma
		<< "\nRed balance: " << +this->redBalance
		<< "\nGreen balance: " << +this->greenBalance
		<< "\nBlue balance: " << +this->blueBalance;
		return ss.str();
	}
};

struct MonitorInformationPair {
public:
	std::vector<PHYSICAL_MONITOR> monitors;
	std::vector<DISPLAY_DEVICE> info;
};

class Logger {
public:
	static void log(const std::string& message);
	static void log(std::vector<std::string> messages);
};

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

class MonitorGetter {
protected:
	MonitorInformationPair mip;
public:
	MonitorGetter();
	std::vector<Monitor> getAll();
	~MonitorGetter();
};

class Tester {
public:
	static bool testAll(const std::vector<Monitor>&);
	static bool testFeatures(Monitor);
};

class SettingsManager {
protected:
	std::string settingsPath;
public:
	SettingsManager(std::string);
	bool save(Settings);
	bool load(std::string alias, Settings&) const;
	bool apply(Monitor, Settings);
	bool getFromMonitor(Monitor, Settings&);
	bool fileExists();
	void createDefaults(std::vector<Monitor> monitors);
	std::vector<std::string> list();
};

class App {
protected:
	std::vector<Monitor> monitors;
	SettingsManager manager;
public:
	App(std::vector<Monitor> monitors, SettingsManager manager);
	int doSet(int id, std::vector<std::string> features, std::vector<U8> vals);
	int doGet(int id, std::vector<std::string> features, std::vector<U8>& vals, bool maxvalues);
	int doLoad(int id, std::string settingsAlias);
	int doSave(int id, std::string settingsAlias);
	std::vector<std::string> doListDevices();
	std::vector<std::string> doListSettings();
};

class ConsoleApp : public App {
public:
	ConsoleApp(std::vector<Monitor>, SettingsManager);
	std::pair<std::string, U8> parseArgValue(std::string searchArg, char arg[], char value[]);
	int parseArgs(int argc, char* argv[]);
	bool pushArgTo(std::string searchArg, char arg[], char value[], std::vector<std::string>& features, std::vector<U8>& vals);
	void printList(std::vector<std::string>);
	void loop();
};

#endif
