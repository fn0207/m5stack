#ifndef ARUDUINO_TIMER_H_INCLUDE
#define ARUDUINO_TIMER_H_INCLUDE

#define TIMER_STATUS_STOP   0
#define TIMER_STATUS_START  1
#define TIMER_STATUS_FINISH 2

#define MINUTE_MAX 60
#define SECOND_MAX 60


class Aruduino_Timer {
  public:
    Aruduino_Timer(int min = 0, int sec = 0);
    ~Aruduino_Timer();

    void plus_min();
    void plus_sec();
    void status_change();
    int  get_min();
    int  get_sec();
    int  get_status();
    void  timer_run();

  private:
    int status;
    int minute, second;
    int target_time;
};
#endif