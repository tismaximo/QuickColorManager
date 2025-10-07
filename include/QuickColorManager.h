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

static std::string hexString(const int& num) {
	std::stringstream ss;
	ss << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << num;
	std::string hexCode = ss.str();
	return hexCode;
}

enum CmdCapability {
	GET  = 0x01,
	SET  = 0x02,
	SAVE = 0x03
};

enum VcpCapability {
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

struct Settings {
public:
	uint8_t brightness;
	uint8_t contrast;
	uint8_t gamma;
	uint8_t redBalance;
	uint8_t greenBalance;
	uint8_t blueBalance;
	Settings(
		uint8_t brightness   = 70,
		uint8_t contrast     = 70,
		uint8_t gamma        = 70,
		uint8_t redBalance   = 70,
		uint8_t greenBalance = 70,
		uint8_t blueBalance  = 70
	) :
		brightness(brightness),
		contrast(contrast),
		gamma(gamma),
		redBalance(redBalance),
		greenBalance(greenBalance),
		blueBalance(blueBalance)
	{}
	std::string str() {
		std::ostringstream ss;
		ss << "Settings:\nBrightness: " << +this->brightness
			<< "\nContrast: " << +this->contrast
			<< "\nGamma: " << +this->gamma
			<< "\nRed balance: " << +this->redBalance
			<< "\nGreen balance: " << +this->greenBalance
			<< "\nBlue balance: " << +this->blueBalance;
		return ss.str();
	}
};

class Logger {
public:
	static void log(const std::string& message);
	static void log(const Settings& settings);
};

class Monitor {
protected:
	HANDLE handle;
public:
	Monitor(HANDLE);
	bool set(VcpCapability, uint8_t);
	bool get(VcpCapability, uint8_t&);
	std::string getCapabilitiesString();
	std::string getMonitorString(std::string);
	~Monitor();
};

class MonitorGetter {
protected:
	std::vector<PHYSICAL_MONITOR> monitors;
public:
	MonitorGetter();
	std::vector<Monitor> getAll();
	~MonitorGetter();
};

class Tester {
public:
	static bool testCapabilities(Monitor h);
};

class SettingsManager {
protected:
	std::string settingsPath;
public:
	SettingsManager(std::string);
	bool save(Settings);
	bool load(Settings&);
	bool apply(Monitor, Settings);
	bool getFromMonitor(Monitor, Settings&);
};

#endif
