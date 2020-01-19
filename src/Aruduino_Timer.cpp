#include "Aruduino_Timer.h"
#include <M5Stack.h>

Aruduino_Timer::Aruduino_Timer(int min, int sec) {
        minute = min;
        second = sec;
        status = TIMER_STATUS_STOP;
}
Aruduino_Timer::~Aruduino_Timer() {}

void Aruduino_Timer::plus_min() {
    minute++;
    minute = minute % MINUTE_MAX;
}
void Aruduino_Timer::plus_sec() {
    second++;
    second = second % SECOND_MAX;
}

void Aruduino_Timer::status_change() {
    if(status == TIMER_STATUS_STOP) {
        status = TIMER_STATUS_START;
        target_time = millis() + 1000;

    }
    else { 
        status = TIMER_STATUS_STOP;
    }
}

int  Aruduino_Timer::get_min() {
    return minute;
}

int  Aruduino_Timer::get_sec() {
    return second;
}

int  Aruduino_Timer::get_status() {
    return status; 
}

void Aruduino_Timer::timer_run() {
    if(status != TIMER_STATUS_START) return;

    if (target_time < millis()) {
        // Set next update for 1 second later
            target_time = target_time + 1000;

        // Adjust the time values by adding 1 second
        second--;
        if(second < 0) {
            second = 59;
            minute--;
        }
        if(second == 0 && minute == 0) {
            status = TIMER_STATUS_FINISH;
        }

    }
}