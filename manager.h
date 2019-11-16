//
// Created by Jérémy TERNISIEN on 13/11/2019.
//

#ifndef SCRAPPER_MANAGER_H
#define SCRAPPER_MANAGER_H

#include "parser.h"

void executeAction(Action action);
void taskExec(Task* task, int taskLenght);
char* findValueByKey(char* key, Action action);
void writeInFile(char* taskname, char* actionName);
long incrementTime(long currentTime, int hours, int minutes, int seconds);
long getCurrentTime();
int findIntValueByKey(Action action, char* key);

#endif //SCRAPPER_MANAGER_H
