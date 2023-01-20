// File: timer.h
// Description: Measures user space time and signals a timeout

#ifndef TPL_UTIL_TIMER_H_
#define TPL_UTIL_TIMER_H_

#include <ctime>

namespace tpl {

class Timer {
    // Ensure clock_t is a 64 bit value
    // A 32 bit clock_t width will overflow after ~72 minutes which is longer than the expected runtime.
    // A 64 bit clock_t width will overflow after ~ 300,00 years
    static_assert(sizeof(std::clock_t) == 8);

public:
    Timer() = delete;
    Timer(double seconds_limit) : seconds_limit(seconds_limit) {}

    void start() {
        cpu_start_time = std::clock();
    }

    bool is_timeout() {
        std::clock_t cpu_current_time = std::clock();
        double current_duration = ((cpu_current_time - cpu_start_time) / (double)CLOCKS_PER_SEC);
        return seconds_limit > 0 && current_duration >= seconds_limit;
    }

    double get_duration() {
        std::clock_t cpu_current_time = std::clock();
        double current_duration = ((cpu_current_time - cpu_start_time) / (double)CLOCKS_PER_SEC);
        return current_duration;
    }

    double get_time_remaining() {
        std::clock_t cpu_current_time = std::clock();
        double current_duration = ((cpu_current_time - cpu_start_time) / (double)CLOCKS_PER_SEC);
        return seconds_limit - current_duration;
    }

private:
    double seconds_limit;
    std::clock_t cpu_start_time = 0;
};

}    // namespace tpl

#endif    // TPL_UTIL_TIMER_H_
