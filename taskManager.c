//
// Created by Frantz on 19/10/2019.
//
#include "parser.h"
#include "header.h"
#include "manager.h"
#include "file.h"

long getCurrentTime() {
    time_t current_time;
    current_time = time(NULL);
    long t = current_time;
    return t;
}

int executeIsAvailable(int val) {
    return val;
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

char* findValueByKey(char* key, Action action) {
    for (int j = 0; j < action.optionsLength; j++) {
        if (strcmp(action.keys[j], key) == 0) {
            return action.values[j];
        }
    }
    return NULL;
}

int findIntValueByKey(Action action, char* key) {

    for (int i = 0; i < action.optionsLength; ++i) {
        if(strcmp(action.keys[i], key) == 0) {
            return atoi(action.values[i]);
        }
    }

    return 0;
}

void *taskthread(void *arg) {
    Action *a = (struct Action *) arg;
    executeAction(*a);
    //free(a);
    return NULL;
}

void executeTags(Action action, char *tags, int maxDepth) {
    int tagsLength = 0;
    char** tagsList = strToArrayStr(tags + 1, &tagsLength, ",)");

    removeDirectory(action.name);
    createDirectoryTreeStruct(action.name);

    if(maxDepth <= 0) {
        execute(tagsList, action.url, tagsLength, action.name,"0");
        return;
    }

    firstWave(action.url);
    if(maxDepth > 1) {
        for (int i = 0; i < maxDepth; ++i) {
            nextWave(i);//faire un sort puis uniq puis merge puis resort et uniq <3
        }
    }
    printf("EXECUTE TAG\n");

    execute(tagsList, action.url, tagsLength, action.name,"0");
}

void executeAction(Action action) { // parcourir chaque option
    printf("EXECUTE ACTION\n");

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

void taskExec(Task* task, int taskLenght) {
    long fromtime = getCurrentTime();
    while (1) {
        printf("WHGILE\n");
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
                    printf("FOR\n");
                    char* value = findValueByKey("versionning", task[i].actions[j]);
                    if (strcmp(value, "on") == 0) {
                        writeInFile(task[i].name, task[i].actions[j].name);
                    }
                    printf("NEW ACTION\n");
                    executeAction(task[i].actions[j]);
                }
                task[i].nextOccurence = incrementTime(newTime, hours, minutes, seconds);
            }
        }
    }
}

