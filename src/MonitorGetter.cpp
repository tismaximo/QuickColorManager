#include "../include/QuickColorManager.h"
/*
    explicacion:
    callback que se pasa a enumDisplayMonitors para buscar todos los monitores de todas las señales
    por cada ejecucion busca uno o mas monitores fisicos recibiendo imagen de la misma señal y los agrega a pData por referencia
*/
BOOL CALLBACK MonitorEnumHandlers(HMONITOR hMon, HDC hdcMon, LPRECT lprcMon, LPARAM pData) {
    auto mip = reinterpret_cast<MonitorInformationPair*>(pData);
    std::vector<PHYSICAL_MONITOR>* monitors = &mip->monitors;
    std::vector<DISPLAY_DEVICE>* info = &mip->info;

    DWORD monitorCount = 0;
    if (!GetNumberOfPhysicalMonitorsFromHMONITOR(hMon, &monitorCount)) {
        return FALSE;
    }

    std::vector<PHYSICAL_MONITOR> temp(monitorCount);
    if (!GetPhysicalMonitorsFromHMONITOR(hMon, monitorCount, temp.data())) {
        return FALSE;
    }

    MONITORINFOEX mi;
    mi.cbSize = sizeof(mi);
    if (!GetMonitorInfo(hMon, &mi)) {
        return FALSE;
    }

    DISPLAY_DEVICE dd;
    dd.cb = sizeof(dd);
    if (!EnumDisplayDevices(mi.szDevice, 0, &dd, 0)) {
        return FALSE;
    }

    for (const PHYSICAL_MONITOR& pm : temp) {
        monitors->push_back(pm);
        info->push_back(dd);
    }

    return TRUE;
}

std::vector<Monitor> MonitorGetter::getAll() {
    LPARAM data = reinterpret_cast<LPARAM>(&this->mip);
    EnumDisplayMonitors(nullptr, nullptr, MonitorEnumHandlers, data);
    std::vector<HANDLE> vec;

    for (const PHYSICAL_MONITOR& m : this->mip.monitors) {
        vec.push_back(m.hPhysicalMonitor);
    }

    std::vector<Monitor> handlers;
    int i = 0;
    for (const HANDLE& h : vec) {
        handlers.emplace_back(h, this->mip.info[i]);
        i++;
    }
    
    return handlers;
}

MonitorGetter::MonitorGetter() {
}

MonitorGetter::~MonitorGetter() {
    DestroyPhysicalMonitors(static_cast<DWORD>(this->mip.monitors.size()), this->mip.monitors.data());
}
