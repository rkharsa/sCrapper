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

void writeInFile(char* taskname, char* actionName) {
    time_t now;
    time(&now);
    char* time = ctime(&now);
    char message[100];
    strcpy(message, "Nom de l'action: ");
    strcat(message, actionName);
    strcat(message, " Nom de la tâche: ");
    strcat(message, taskname);
    strcat(message, " Date: ");
    char* fn = malloc(sizeof(char) * 100);
    sprintf(fn, "%s.txt", actionName);
    printf("%s\n", fn);
    FILE* f = fopen(fn, "a+");
    if (f != NULL) {
        fputs(message, f);
        fputs(time, f);
        fclose(f);
    }
    free(fn);
}

char* findValueBykey(char* key, Action action) {
    for (int j = 0; j < action.optionsLength; j++) {
        if (strcmp(action.keys[j], key) == 0) {
            return action.values[j];
        }
    }
    return NULL;
}

void taskExec(Task* task, int taskLenght) {
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
                for (int j = 0; j < task[i].actionsLength; j++) {
                    char* value = findValueBykey("versionning", task[i].actions[j]);
                    if (strcmp(value, "on") == 0) {
                        writeInFile(task[i].name, task[i].actions[j].name);
                    }
                }
                task[i].nextOccurence = incrementTime(newTime, hours, minutes, seconds);
            }
        }
    }
}

