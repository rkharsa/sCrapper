//
// Created by Frantz on 19/10/2019.
// FILE CONTAINING FUNCTION TASK ADMINSITRATOR
#include "parser.h"
#include "header.h"
#include "manager.h"
#include "file.h"

/**
 *
 * @return
 * return the current timestamp
 */
long getCurrentTime() {
    time_t current_time;
    current_time = time(NULL);
    long t = current_time;
    return t;
}

/**
 *
 * @param currentTime
 * @param hours
 * @param minutes
 * @param seconds
 * @return
 *
 * return a timestamp incremented
 */
long incrementTime(long currentTime, int hours, int minutes, int seconds) {
    long destime = currentTime;
    long h = hours * 3600;
    long m = minutes * 60;
    destime += h + m + seconds;;
    return destime;

}

/**
 *
 * @param taskname
 * @param actionName
 *
 * for versionning write in a file when an action is executed
 */
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
    FILE* f = fopen(fn, "a+");
    if (f != NULL) {
        fputs(message, f);
        fputs(time, f);
        fclose(f);
    }
    free(fn);
}

/**
 *
 * @param key
 * @param action
 * @return
 *
 * find the value of a key for an action
 */
char* findValueByKey(char* key, Action action) {
    for (int j = 0; j < action.optionsLength; j++) {
        if (strcmp(action.keys[j], key) == 0) {
            return action.values[j];
        }
    }
    return NULL;
}

/**
 *
 * @param action
 * @param key
 * @return
 * find the value  integer of a key for an action
 */
int findIntValueByKey(Action action, char* key) {

    for (int i = 0; i < action.optionsLength; ++i) {
        if (strcmp(action.keys[i], key) == 0) {
            return atoi(action.values[i]);
        }
    }

    return 0;
}

/**
 *
 * @param arg
 * @return
 * thread for executeAction
 */
void* taskthread(void* arg) {
    Task* t = (struct Task*) arg;
    for (int i = 0; i < 1; ++i) {
        for (int j = 0; j < t[i].actionsLength; ++j) {
            executeAction(t[i], t[i].actions[j]);
        }
    }
    return NULL;
}

/**
 * execute action with tags option
 * @param action
 * @param tags
 * @param maxDepth
 */
void executeTags(Action action, char* tags, int maxDepth) {
    int tagsLength = 0;
    char** tagsList = strToArrayStr(tags + 1, &tagsLength, ",)");

    removeDirectory(action.name);
    createDirectoryTreeStruct(action.name);

    if (maxDepth <= 0) {
        execute(tagsList, action.url, tagsLength, action.name, "0");
        return;
    }

    firstWave(action.url);
    if (maxDepth > 1) {
        for (int i = 0; i < maxDepth; ++i) {
            nextWave(i);//faire un sort puis uniq puis merge puis resort et uniq <3
        }
    }
    execute(tagsList, action.url, tagsLength, action.name, "0");
}

/**
 * execute all actions
 * @param task
 * @param action
 */
void executeAction(Task task, Action action) {
    char* value = findValueByKey("versionning", action);
    if (strcmp(value, "on") == 0) {
        writeInFile(task.name, action.name);
    }

    for (int i = 0; i < action.optionsLength; ++i) {
        //d'abord check si ya un max-depth ? OUI ok je parle tout seul
        //getMaxDepth
        if (strcmp(action.keys[i], "type") == 0) {
            // à implémenter
        } else if (strcmp(action.keys[i], "tags") == 0) {

            executeTags(action, action.values[i], findIntValueByKey(action,
                                                                    "max-depth"));
        }
    }
}

/**
 *
 * @param task
 * @param taskLenght
 * check when a task need to be executed create a thread
 */
void taskExec(Task* task, int taskLenght) {
    long fromtime = getCurrentTime();
    while (1) {
        for (int i = 0; i < taskLenght; i++) {
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
                    char* value = findValueByKey("versionning", task[i].actions[j]);
                    if (strcmp(value, "on") == 0) {
                        writeInFile(task[i].name, task[i].actions[j].name);
                    }
                    pthread_t thread1;
                    pthread_create(&thread1, NULL, taskthread, &task[i]);
                }
                task[i].nextOccurence = incrementTime(newTime, hours, minutes, seconds);
            }
        }
    }
}

