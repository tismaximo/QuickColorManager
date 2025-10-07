#include "../include/QuickColorManager.h"
/*
    explicacion:
    callback que se pasa a enumDisplayMonitors para buscar todos los monitores de todas las señales
    por cada ejecucion busca uno o mas monitores fisicos recibiendo imagen de la misma señal y los agrega a pData por referencia
*/
BOOL CALLBACK MonitorEnumProc(HMONITOR hMon, HDC hdcMon, LPRECT lprcMon, LPARAM pData) {
    auto monitors = reinterpret_cast<std::vector<PHYSICAL_MONITOR>*>(pData);

    DWORD monitorCount = 0;
    if (!GetNumberOfPhysicalMonitorsFromHMONITOR(hMon, &monitorCount)) {
        return FALSE;
    }
    std::vector<PHYSICAL_MONITOR> temp(monitorCount);
    if (!GetPhysicalMonitorsFromHMONITOR(hMon, monitorCount, temp.data())) {
        return FALSE;
    }
    monitors->insert(monitors->end(), temp.begin(), temp.end());
    return TRUE; 
}

MonitorGetter::MonitorGetter() {
}

std::vector<Monitor> MonitorGetter::getAll() {
    LPARAM data = reinterpret_cast<LPARAM>(&this->monitors);
    EnumDisplayMonitors(nullptr, nullptr, MonitorEnumProc, data);
    std::vector<HANDLE> vec;

    for (PHYSICAL_MONITOR m : this->monitors) {
        vec.push_back(m.hPhysicalMonitor);
    }
    std::vector<Monitor> handlers;
    for (HANDLE h : vec) {
        handlers.push_back(h);
    }
    
    return handlers;
}

MonitorGetter::~MonitorGetter() {
    DestroyPhysicalMonitors(static_cast<DWORD>(this->monitors.size()), this->monitors.data());
}
