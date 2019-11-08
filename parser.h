//
// Created by Jérémy TERNISIEN on 14/10/2019.
//

#ifndef SCRAPER_PARSER_H
#define SCRAPER_PARSER_H
#define LINE_FILE_MAX 1000

typedef struct Action {
    char *name;
    char *url;
    int length;
    char **keys;
    char **values;
} Action;

typedef struct Task {
    char *name;
    int seconds;
    int minutes;
    int hours;
    int actionLength;
    Action *actions;
} Task;


char *getFilePath();
long getMaxLineSize(FILE *file);
void printActions(Action *actions, int length);
void printTasks(Task *tasks, int length);
char *removeSpaces(char *str);
int checkTaskFormat(char *optionStr, char *first, char *last);
int checkOptionFormat(char *optionStr, char *first, char *middle, char *last);
int isOptionFinished(char *line);
void setOptions(Action *action, FILE *file, int position);
void setTaskActions(Task *task, Action *actions, int actionLength, char *urls);
void setTasksOptions(Task *task, FILE *file, int position, Action *actions, int actionLength);
long getLinePosAfterChar(char charToFind, FILE *file, int iteration);
long getLinePosAfterStr(char *strToFind, FILE *file, int iteration);
Action *parseActions(FILE *fileToParse, int *actionLength);
Task *parseTasks(FILE *fileToParse, int *length, Action *actions, int actionLength);

#endif //SCRAPER_PARSER_H
