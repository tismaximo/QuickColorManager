#pragma once
#include "../QuickColorManager.h"

class ICodedException : public std::exception {
protected:
	std::string message;
public:
	virtual int errorCode() const noexcept = 0;
	const char* what() const noexcept override {
		return this->message.c_str();
	}
	virtual ~ICodedException() noexcept = default;
};

class ArgumentException : public ICodedException {
public:
	ArgumentException(const std::string& arg) {
		this->message = "Invalid argument: " + arg;
	}
	int errorCode() const noexcept {
		return ARG_ERROR;
	}
};

class ValueException : public ICodedException {
public:
	ValueException(const std::string& argument, int value, int maxvalue = -1) {
		this->message = "Invalid value for argument " + argument + ": " + std::to_string(value);
		if (maxvalue != -1) {
			this->message += ". Maximum admitted value is " + std::to_string(maxvalue);
		}
	}
	int errorCode() const noexcept {
		return VAL_ERROR;
	}
};

class NoValueException : public ICodedException {
public:
	NoValueException(const std::string& argument) {
		this->message = "No value given for argument " + argument;

	}
	int errorCode() const noexcept {
		return VAL_ERROR;
	}
};

class FileException : public ICodedException {
public:
	FileException(const std::string& file) {
		this->message = "Couldn't read/write to file: "+ file +". Check whether this program has read/write permissisons or that the file exists";
	}
	int errorCode() const noexcept {
		return FILE_ERROR;
	}
};

class DeviceException : public ICodedException {
public:
	DeviceException(const std::string& monitorstring) {
		this->message = "The device "+ monitorstring + " doesn't have any physical settings available (very common in laptops) or DDC/CI is disabled. The device manual might have instructions on how to enable it.";
	}
	int errorCode() const noexcept {
		return DEVICE_ERROR;
	}
};

class NotFoundException : public ICodedException {
public:
	NotFoundException(int i) {
		this->message = "Device with the following id wasnt found: " + std::to_string(i);
	}
	int errorCode() const noexcept {
		return OUT_OF_BOUNDS;
	}
};