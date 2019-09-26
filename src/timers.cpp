#include "timers.h"

bool timer::check_pass(int time) {
    if (this->last_time + gap_time > time) {
        return false;
    }
    return true;
}

timer::timer(int l_time, int g_time) {
    this->last_time = l_time;
    this->gap_time = g_time;
}

void timer::set_time(int ntime) {
    this->last_time = ntime;
}

timer::timer() {
    this->last_time = 0;
    this->gap_time = 0;
}