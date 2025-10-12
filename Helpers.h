#pragma once
#include "Includes.h"

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