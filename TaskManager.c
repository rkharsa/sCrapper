//
// Created by Frantz on 19/10/2019.
//
#include "parser.h"
#include "header.h"

long getCurrentTime() {
    time_t current_time;
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

int writeInFile(char *taskname, char *actionName) {
    time_t now;
    time(&now);
    char *time = ctime(&now);
    char message[100];
    strcpy(message, "Nom de l'action: ");
    strcat(message, actionName);
    strcat(message, " Nom de la tâche: ");
    strcat(message, taskname);
    strcat(message, " Date: ");
    FILE *f = fopen("history.txt", "a+");
    if (f != NULL) {
        fputs(message, f);
        fputs(time, f);
        fclose(f);
    }
    // free(time);
}

void versionning(char *taskname, Action *actions, int actionlen) {
    printf(actions[0].url);
    for (int k = 0; k < actionlen; k++) {
        for (int j = 0; j < actions[k].optionsLength; j++) {
            if (strcmp(actions[k].keys[j], "versionning") == 0) {
                if (strcmp(actions[k].values[j], "on") == 0) {
                    writeInFile(taskname, actions[k].name);
                }
            }
        }
    }
}

void taskExec(Task *task, int taskLenght) {
    int j = 1;
    long fromtime = getCurrentTime();
    while (j == 1) {
        for (int i = 0; i < taskLenght; ++i) {
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
                versionning(task[i].name, task[i].actions, task[i].actionsLength);
                task[i].nextOccurence = incrementTime(newTime, hours, minutes, seconds);
            }
        }
    }
}

