#pragma once
#include "../QuickColorManager.h"
#include "../config/Vcp.h"
#include "../exceptions/Exceptions.h"

static std::string hexString(const int& num) {
	std::stringstream ss;
	ss << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << num;
	std::string hexCode = ss.str();
	return hexCode;
}

// convierte una wide string a string normal
static std::string unwide(const std::wstring& wstr) {
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	return converter.to_bytes(wstr);
}

static int parseValue(const std::string& arg) {
	try {
		int val = std::stoi(arg);
		return val;
	}
	catch (const std::invalid_argument& _) {
		return -1;
	}
}

// transforma una cadena a una version "mini" para usarla como alias o identificador unico
// ejemplo: "Generic PnP Monitor" -> "generic-pnp-monitor"
static std::string ministring(std::string& str) {
	std::replace(str.begin(), str.end(), ' ', '-');
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
} 

static VcpFeature findFeatureByArg(std::string arg) {
	auto it = VCP_ARG_ALIASES.find(arg);
	if (it == VCP_ARG_ALIASES.end()) {
		throw ArgumentException(arg);
	}
	auto feature = VCP_ARGS.find(it->second);
	if (feature == VCP_ARGS.end()) {
		throw ArgumentException(arg);
	}
	return feature->second;
}