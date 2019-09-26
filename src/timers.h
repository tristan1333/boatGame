#ifndef TIMERS_H
#define TIMERS_H


class timer {
public:
    int last_time;
    int gap_time;

    bool check_pass(int);

    void set_time(int);

    timer(int, int);

    timer();
};


#endif
