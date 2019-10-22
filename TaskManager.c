//
// Created by Frantz on 19/10/2019.
//
#include "header.h"

char *getCurrentTime() {
    time_t current_time;
    char *c_time_string;
    char *t = malloc(sizeof(char) * 8);
    char *v;

    current_time = time(NULL);
    c_time_string = ctime(&current_time);
    c_time_string = strtok(c_time_string, " ");
    c_time_string = strtok(NULL, " ");
    c_time_string = strtok(NULL, " ");
    c_time_string = strtok(NULL, " ");
    char *hour = (char *) strtok(c_time_string, ":");
    char *minute = (char *) strtok(NULL, ":");
    char *second = (char *) strtok(NULL, ":");
    strcpy(t, hour);
    strcat(t, ":");
    strcat(t, minute);
    strcat(t, ":");
    strcat(t, second);
    return t;
}

void task(int hours, int minutes, int seconds) {
    char *val = getCurrentTime();
    char *destime = malloc(sizeof(char) * 8);
    char *hour = (char *) strtok(val, ":");
    char *minute = (char *) strtok(NULL, ":");
    char *second = (char *) strtok(NULL, ":");
    char *heure = malloc(sizeof(char) * 2);
    char *min = malloc(sizeof(char) * 2);
    char *seconde = malloc(sizeof(char) * 2);
    int h = atoi(hour);
    int hdest = 0;
    int mdest = 0;
    int sdest = 0;
    int m = atoi(minute);
    int s = atoi(second);
    if (hours > 0 || h + hours >= 23) {
       if (h == 23) {
            hdest = 0 + hours-1;
        }
       if (h + hours > 23 && h < 23) {

            int tmph = 0;
            tmph = 23 - h;
            hdest = 0 + (hours - tmph);
        }
    } else {
        hdest = hours + h;
    }
    if (minutes > 0 && m + minutes >= 59) {
        if (m == 59) {
            mdest = 0 + minutes -1;
            hdest = hdest + 1;

        }
        if (m + minutes > 59 && m < 59) {
            int tmpm = 0;
            tmpm = 59 - m;
            mdest = 0 + (minutes - tmpm);
            hdest = hdest + 1;

        }
    } else {
        mdest = minutes + m;

    }
    if (seconds > 0 && s + seconds < 59) {
        if (s == 59) {
            sdest = 0 + seconds-1;
            mdest = mdest + 1;
        }
        if (s + seconds > 59 && s < 59) {
            int tmps = 0;
            tmps = 59 - s;
            sdest = 0 + (seconds - tmps);
            mdest = mdest + 1;
        }
    } else {
        sdest = seconds + s;
    }
    if (hdest >= 0 && hdest < 10) {
        strcpy(heure, "0");
        char buffer[2];
        itoa(hdest, buffer, 10);
        strcat(heure, buffer);
    } else {
        strcpy(heure, itoa(hdest, heure, 10));

    }
    if (mdest >= 0 && mdest < 10) {
        strcpy(min, "0");
        char buffer[2];
        itoa(mdest, buffer, 10);
        strcat(min, buffer);
    } else {
        strcpy(minute, itoa(mdest, min, 10));

    }
    if (sdest >= 0 && sdest < 10) {
        strcpy(seconde, "0");
        char buffer[2];
        itoa(sdest, buffer, 10);
        strcat(seconde, buffer);
    } else {
        strcpy(seconde, itoa(sdest, seconde, 10));
    }
    printf("Currendqqdt time is %s %s %s", heure, min, seconde);

}



