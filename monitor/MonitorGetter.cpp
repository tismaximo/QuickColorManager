#include "MonitorGetter.h"
/*
    explicacion:
    callback que se pasa a enumDisplayMonitors para buscar todos los monitores de todas las se�ales
    por cada ejecucion busca uno o mas monitores fisicos recibiendo imagen de la misma se�al y los agrega a pData por referencia
*/
BOOL CALLBACK MonitorEnumHandlers(HMONITOR hMon, HDC hdcMon, LPRECT lprcMon, LPARAM pData) {
    auto mip = reinterpret_cast<MonitorInformationPair*>(pData);

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
		mip->set(pm, dd); // para todos los monitores encontrados se agrega el monitor fisico y el device info (el device info es el mismo para todos los monitores fisicos)
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
