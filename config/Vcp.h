#pragma once
#include "../QuickColorManager.h"

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
	{"brightness", BRIGHTNESS},
	{"contrast", CONTRAST},
	{"gamma", GAMMA},
	{"red", RED_BALANCE},
	{"green", GREEN_BALANCE},
	{"blue", BLUE_BALANCE},
};
