#pragma once
#include "../QuickColorManager.h"
#include "../config/Vcp.h"
#include "../helpers/Helpers.h"


struct VcpValuePair {
	VcpFeature key;
	U16 value;
	friend bool operator == (const VcpValuePair& a, const VcpValuePair& b) {
		return a.key == b.key && a.value == b.value;
	}
	friend bool operator != (const VcpValuePair& a, const VcpValuePair& b) {
		return !(a == b);
	}
	VcpValuePair operator = (const VcpValuePair& other) {
		this->key = other.key;
		this->value = other.value;
		return *this;
	}
};
// mapa de tamaño fijo para serializar/deserializar del archivo de settings binario y poder alamacenar una cantidad arbitraria de settings vcp

struct SettingsFileVcpMap {
private:
	VcpFeature key[SETTINGS_MAP_SIZE];
	U16 value[SETTINGS_MAP_SIZE]{ 0 };
public:
	struct Iterator {
	private:
		const SettingsFileVcpMap* ptr;
		VcpValuePair current;
		size_t index;
	public:
		Iterator(const SettingsFileVcpMap* ptr, VcpValuePair current, size_t index) : ptr(ptr), current(current), index(index) {}
		const VcpValuePair& operator*() const {
			return current;
		}
		const VcpValuePair* operator->() const {
			return &current;
		}
		Iterator& operator++() {
			index++;
			current = { ptr->key[index], ptr->value[index] };
			return *this;
		}
		Iterator operator++(int) {
			Iterator tmp = *this;
			++(*this);
			current = { ptr->key[index], ptr->value[index] };
			return tmp;
		}
		friend bool operator== (const Iterator& a, const Iterator& b) {
			return a.index == b.index;
		}
		friend bool operator!= (const Iterator& a, const Iterator& b) {
			return a.index != b.index;
		}
	};
	SettingsFileVcpMap() {
		std::fill_n(this->key, SETTINGS_MAP_SIZE, NONE);
	}
	void set(VcpFeature k, U16 v) {
		for (int i = 0; i < SETTINGS_MAP_SIZE; i++) {
			if (this->key[i] == k) {
				this->value[i] = v;
				return;
			}
			if (this->key[i] == NONE) {
				this->key[i] = k;
				this->value[i] = v;
				return;
			}
		}
	}
	U16 get(VcpFeature k) const {
		for (int i = 0; i < SETTINGS_MAP_SIZE; i++) {
			if (this->key[i] == k) {
				return this->value[i];
			}
			if (this->key[i] == NONE) {
				return 0;
			}
		}
		return 0;
	}
	Iterator begin() const {
		return Iterator(this, VcpValuePair{ key[0], value[0] }, 0);
	}
	Iterator end() const {
		int lastIndex = 0;
		for (int i = 0; i < SETTINGS_MAP_SIZE; i++) {
			if (this->key[i] == NONE) {
				lastIndex = i;
				break;
			}
		}
		return Iterator(this, VcpValuePair{ NONE, 0 }, lastIndex);
	}
	~SettingsFileVcpMap() = default;
};

struct Settings {
public:
	std::string alias;
	SettingsFileVcpMap values;
	Settings(std::string alias);
	std::string str() const;
};

