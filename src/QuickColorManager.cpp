#include "../include/QuickColorManager.h"

#pragma comment(lib, "Dxva2.lib")

int main() {
    MonitorGetter getter;
    auto monitors = getter.getAll();
    for (Monitor m : monitors) {
        Tester::testCapabilities(m);
    }
};