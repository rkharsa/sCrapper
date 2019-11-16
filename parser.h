//
// Created by Jérémy TERNISIEN on 14/10/2019.
//

#ifndef SCRAPER_PARSER_H
#define SCRAPER_PARSER_H
#define LINE_FILE_MAX 1000

#include <stdio.h>

typedef struct Action {
    char* name;
    char* url;
    int optionsLength;
    char** keys;// option1 option2 versionning
    char** values;// value1 value2 valueversionning
} Action;

typedef struct Task {
    char* name;
    int seconds;
    int minutes;
    int hours;
    int actionsLength;
    Action* actions;
    long nextOccurence;
} Task;

int delimitersStillExist(char* string, char* delimiters);

char** strToArrayStr(char* line, int* length, char* delimiters);

char* getStrUntilChrs(char* str, int* position, char* chrs);

char* getKey(char* line, char* first, char* delimiter);

void setActionOption(Action* action, char* line, char* first, char* delimiter, char* last);

char* getValue(char* line, char* delimiter, char* last);

void linkTaskActions(Task* task, char** urls, int urlsLength, Action* actions, int actionsLength);

void setActionAttribute(Action* action, char* key, char* value);

void setTaskAttribute(Task* task, char* key, char* value);

void setKeyValue(Action* action, char* key, char* value);

int checkLineEnds(char* line, char* first, char* last);

char* fgetsWithCheck(FILE* file, int size);

int checkFileExtension(char* filePath, char* extension);

int checkFileExists(char* filePath);

char* getFilePath();

int getMaxLineSize(FILE* file);

void printActions(Action* actions, int length);

void printTasks(Task* tasks, int length);

char* removeStrSpaces(char* str);

char* removeConsecutiveChars(char* str, char banned);

int checkLineFormat(char* optionStr, char* first, char* middle, char* last);

int isActionFinished(char* line);

int isTaskFinished(char* line);

void setAllActionOptions(Action* action, FILE* file, int position);

void setAllTaskOptions(Task* task, FILE* file, int position, Action* actions, int actionLength);

long getLinePosAfterChar(char charToFind, FILE* file, int iteration);

long getLinePosAfterStr(char* strToFind, FILE* file, int iteration);

Action* getActions(FILE* fileToParse, int* actionLength);

Task* getTasks(FILE* fileToParse, int* length, Action* actions, int actionLength);

void taskExec(Task* task, int taskLenght);

#endif //SCRAPER_PARSER_H
