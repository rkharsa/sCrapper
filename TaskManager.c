//
// Created by Frantz on 19/10/2019.
//
#include "header.h"

long getCurrentTime() {
    time_t current_time;
    char *c_time_string;
    current_time = time(NULL);
    long t = current_time;
    return t;
}

long incrementTime(long currentTime, int hours, int minutes, int seconds) {
    long destime = currentTime;
    long h = hours * 3600;
    long m = minutes * 60;
    destime += h + m + seconds;;
    return destime;

}

void task(Task *task) {
    int j = 1;
    long fromtime = getCurrentTime();
    while (j == 1) {
        _sleep(900);
        for (int i = 0; i < 2; ++i) {
            long newTime = getCurrentTime();
            long destime = 0;
            int hours = task[i].hours;
            int minutes = task[i].minutes;
            int seconds = task[i].seconds;
            if (task[i].nextOccurence == 0) {
                task[i].nextOccurence = incrementTime(fromtime, hours, minutes, seconds);
            }
            destime = task[i].nextOccurence;
            if (destime == newTime) {
                printf("Je compte lancer la tache %d\n", i);
                task[i].nextOccurence = incrementTime(newTime, hours, minutes, seconds);
                printf("prochaine exe a %d\n", task[i].nextOccurence);
            }
        }
    }
}

