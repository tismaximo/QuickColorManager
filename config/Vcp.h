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

const std::vector<VcpFeature> EXPECTED_VCP_CAPABILITIES = {
	CONTRAST,
	BRIGHTNESS,
	GAMMA,
	RED_BALANCE,
	GREEN_BALANCE,
	BLUE_BALANCE,
	SHARPNESS,
	SATURATION,
	RED_SATURATION,
	YELLOW_SATURATION,
	GREEN_SATURATION,
	CYAN_SATURATION,
	BLUE_SATURATION,
	MAGENTA_SATURATION,
	HUE
};

const std::vector<VcpFeature> DANGER_VCP_CAPABILITIES = {
	AUTO_ADJUST,
	AUTO_COLOR,
	RESTORE
};

const std::map<VcpFeature, std::string> VCP_STRINGS = {
	{RESTORE, "Restore"},
	{BRIGHTNESS, "Brightness"},
	{CONTRAST, "Contrast"},
	{GAMMA, "Gamma"},
	{RED_BALANCE, "Red balance"},
	{GREEN_BALANCE, "Green balance"},
	{BLUE_BALANCE, "Blue balance"},
	{AUTO_ADJUST, "Automatic adjust settings"},
	{AUTO_COLOR, "Automatic adjust colors"},
	{SHARPNESS, "Sharpness"},
	{SATURATION, "Saturation"},
	{RED_SATURATION, "Red saturation"},
	{YELLOW_SATURATION, "Yellow saturation"},
	{GREEN_SATURATION, "Green saturation"},
	{CYAN_SATURATION, "Cyan saturation"},
	{BLUE_SATURATION, "Blue saturation"},
	{MAGENTA_SATURATION, "Magenta saturation"},
	{HUE, "Hue"}
};

constexpr const char* ARG_BRIGHTNESS = "brightness";
constexpr const char* ARG_CONTRAST = "contrast";
constexpr const char* ARG_GAMMA = "gamma";
constexpr const char* ARG_RED = "red";
constexpr const char* ARG_GREEN = "green";
constexpr const char* ARG_BLUE = "blue";
constexpr const char* ARG_SHARPNESS = "sharpness";
constexpr const char* ARG_SATURATION = "saturation";
constexpr const char* ARG_REDSATURATION = "redsaturation";
constexpr const char* ARG_YELLOWSATURATION = "yellowsaturation";
constexpr const char* ARG_GREENSATURATION = "greensaturation";
constexpr const char* ARG_CYANSATURATION = "cyansaturation";
constexpr const char* ARG_BLUESATURATION = "bluesaturation";
constexpr const char* ARG_MAGENTASATURATION = "magentasaturation";
constexpr const char* ARG_HUE = "hue";

const std::map<std::string, VcpFeature> VCP_ARGS = {
	{ARG_BRIGHTNESS, BRIGHTNESS},
	{ARG_CONTRAST, CONTRAST},
	{ARG_GAMMA, GAMMA},
	{ARG_RED, RED_BALANCE},
	{ARG_GREEN, GREEN_BALANCE},
	{ARG_BLUE, BLUE_BALANCE},
	{ARG_SHARPNESS, SHARPNESS},
	{ARG_SATURATION, SATURATION},
	{ARG_REDSATURATION, RED_SATURATION},
	{ARG_YELLOWSATURATION, YELLOW_SATURATION},
	{ARG_GREENSATURATION, GREEN_SATURATION},
	{ARG_CYANSATURATION, CYAN_SATURATION},
	{ARG_BLUESATURATION, BLUE_SATURATION},
	{ARG_MAGENTASATURATION, MAGENTA_SATURATION},
	{ARG_HUE, HUE}
};

const std::map<std::string, std::string> VCP_ARG_ALIASES{
	{ARG_BRIGHTNESS, ARG_BRIGHTNESS},
	{ARG_CONTRAST, ARG_CONTRAST},
	{ARG_GAMMA, ARG_GAMMA},
	{ARG_RED, ARG_RED},
	{ARG_GREEN, ARG_GREEN},
	{ARG_BLUE, ARG_BLUE},
	{ARG_SHARPNESS, ARG_SHARPNESS},
	{ARG_SATURATION, ARG_SATURATION},
	{ARG_REDSATURATION, ARG_REDSATURATION},
	{ARG_YELLOWSATURATION, ARG_YELLOWSATURATION},
	{ARG_GREENSATURATION, ARG_GREENSATURATION},
	{ARG_CYANSATURATION, ARG_CYANSATURATION},
	{ARG_BLUESATURATION, ARG_BLUESATURATION},
	{ARG_MAGENTASATURATION, ARG_MAGENTASATURATION},
	{ARG_HUE, ARG_HUE},
	{"-br", ARG_BRIGHTNESS},
	{"-co", ARG_CONTRAST},
	{"-ga", ARG_GAMMA},
	{"-r", ARG_RED},
	{"-g", ARG_GREEN},
	{"-b", ARG_BLUE},
	{"-sh", ARG_SHARPNESS},
	{"-sa", ARG_SATURATION},
	{"-rs", ARG_REDSATURATION},
	{"-ys", ARG_YELLOWSATURATION},
	{"-gs", ARG_GREENSATURATION},
	{"-cs", ARG_CYANSATURATION},
	{"-bs", ARG_BLUESATURATION},
	{"-ms", ARG_MAGENTASATURATION},
	{"-h", ARG_HUE},
	{"--brightness", ARG_BRIGHTNESS},
	{"--contrast", ARG_CONTRAST},
	{"--gamma", ARG_GAMMA},
	{"--red", ARG_RED},
	{"--green", ARG_GREEN},
	{"--blue", ARG_BLUE},
	{"--sharpness", ARG_SHARPNESS},
	{"--saturation", ARG_SATURATION},
	{"--redsaturation", ARG_REDSATURATION},
	{"--yellowsaturation", ARG_YELLOWSATURATION},
	{"--greensaturation", ARG_GREENSATURATION},
	{"--cyansaturation", ARG_CYANSATURATION},
	{"--bluesaturation", ARG_BLUESATURATION},
	{"--magentasaturation", ARG_MAGENTASATURATION},
	{"--hue", ARG_HUE},
	{"br", ARG_BRIGHTNESS},
	{"co", ARG_CONTRAST},
	{"ga", ARG_GAMMA},
	{"r", ARG_RED},
	{"g", ARG_GREEN},
	{"b", ARG_BLUE},
	{"sh", ARG_SHARPNESS},
	{"sa", ARG_SATURATION},
	{"rs", ARG_REDSATURATION},
	{"ys", ARG_YELLOWSATURATION},
	{"gs", ARG_GREENSATURATION},
	{"cs", ARG_CYANSATURATION},
	{"bs", ARG_BLUESATURATION},
	{"ms", ARG_MAGENTASATURATION},
	{"h", ARG_HUE}
};

constexpr const int SETTINGS_MAP_SIZE = 255;