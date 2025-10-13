#pragma once
#include "../QuickColorManager.h"
#include "../monitor/Monitor.h"

class ICodedException : public std::exception {
public:
	virtual int errorCode() const noexcept = 0;
	virtual ~ICodedException() noexcept = default;
};

class ArgumentException : public ICodedException {
private:
	std::string message;
public:
	ArgumentException(const std::string& arg) {
		this->message = "Invalid argument: " + arg;
	}
	const char* what() const noexcept override {
		return this->message.c_str();
	}
	int errorCode() const noexcept {
		return ARG_ERROR;
	}
};

class ValueException : public ICodedException {
private:
	std::string message;
public:
	ValueException(const std::string& argument, int value) {
		this->message = "Invalid value for argument " + argument + ": " + std::to_string(value);
	}
	const char* what() const noexcept override {
		return this->message.c_str();
	}
	int errorCode() const noexcept {
		return VAL_ERROR;
	}
};

class FileException : public ICodedException {
private:
	std::string message;
public:
	FileException(const std::string& file) {
		this->message = "Couldn't read/write to file: "+ file +". Check whether this program has read/write permissisons or that the file exists";
	}
	const char* what() const noexcept override {
		return this->message.c_str();
	}
	int errorCode() const noexcept {
		return FILE_ERROR;
	}
};

class DeviceException : public ICodedException {
private:
	std::string message;
public:
	DeviceException(const std::string& monitorstring) {
		this->message = "The device "+ monitorstring + " doesn't have any physical settings available (very common in laptops) or DDC/CI is disabled. The device manual might have instructions on how to enable it.";
	}
	const char* what() const noexcept override {
		return this->message.c_str();
	}
	int errorCode() const noexcept {
		return DEVICE_ERROR;
	}
};

class NotFoundException : public ICodedException {
private:
	std::string message;
public:
	NotFoundException(int i) {
		this->message = "Device with the following id wasnt found: " + std::to_string(i);
	}
	const char* what() const noexcept override {
		return this->message.c_str();
	}
	int errorCode() const noexcept {
		return OUT_OF_BOUNDS;
	}
};