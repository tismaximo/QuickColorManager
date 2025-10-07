#include "../include/QuickColorManager.h"

void Logger::log(const std::string& message) {
	static std::mutex mtx;
    std::lock_guard<std::mutex> lock(mtx);

    std::time_t now = std::time(nullptr);
    std::tm tm_now{};
    localtime_s(&tm_now, &now);

    std::ostringstream oss;
    oss << "["
        << std::put_time(&tm_now, "%Y-%m-%d %H:%M:%S")
        << "] " << message << "\n";

    std::ofstream file("log.txt", std::ios::app);
    if (file.is_open()) {
        file << oss.str();
    }
    std::cout << message << "\n";
}
