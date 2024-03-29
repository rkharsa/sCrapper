//
// Created by Jérémy TERNISIEN on 14/10/2019.
// FILE CONTAINING FUNCTIONS FOR THE CONFIGURATION FILE PARSING

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"

/**
 *
 * @param str
 * @param banned
 * @return str without consecutive chars
 */
char* removeConsecutiveChars(char* str, char banned) {
    char* newStr = malloc(sizeof(char) * strlen(str) + 1);
    int newIndex = 0;

    if (str[0] != banned) {
        newStr[0] = str[0];
    }

    for (int i = 1; i < strlen(str); i++) {
        if (str[i] != banned) {
            newStr[newIndex] = str[i];
            newIndex++;
        } else if (str[i] == banned && str[i - 1] != banned) {
            newStr[newIndex] = str[i];
            newIndex++;
        }
    }

    newStr[newIndex] = '\0';
    return newStr;
}

/**
 *
 * @param filePath
 * @param extension
 * @return verify extension of a file
 */
int checkFileExtension(char* filePath, char* extension) {

    if (strrchr(filePath, '.') != NULL && strcmp(extension, strrchr(filePath, '.') + 1) != 0) {
        printf("L\'extension du fichier n\'est pas %s, veuillez entrer un nouveau chemin\n", extension);
        return 0;
    }

    return 1;
}

/**
 *
 * @param filePath
 * @return check if a file exists
 */
int checkFileExists(char* filePath) {

    FILE* file = NULL;

    file = fopen(filePath, "r");

    if (file == NULL) {
        printf("Nous ne trouvons pas de fichier de configuration à cet endroit là, veuillez entrer un nouveau chemin\n");
        return 0;
    }

    fclose(file);
    return 1;
}

/**
 *
 * @return path of .sconf file
 */
char* getFilePath() {

    char* filePath = malloc(sizeof(char) * LINE_FILE_MAX + 1);

    printf("Veuillez entrer le chemin de votre fichier de configuration\n");

    do {
        fgets(filePath, LINE_FILE_MAX, stdin);

        if (filePath[strlen(filePath) - 1] == '\n') {
            filePath[strlen(filePath) - 1] = '\0';
        }

    } while (checkFileExists(filePath) == 0 || checkFileExtension(filePath, "sconf") == 0);

    printf("Fichier de configuration trouvé\n\nLecture du fichier en cours...\n");

    return filePath;
}

/**
 *
 * @param file
 * @return size of the longest line of the file
 */
int getMaxLineSize(FILE* file) {
    rewind(file);
    long count = 0;
    long max = 0;
    char currentChar = fgetc(file);

    while (currentChar != EOF) {
        if (currentChar == '\n') {
            currentChar = fgetc(file);
            count = 0;
            continue;
        }

        count++;
        if (count > max) {
            max = count;
        }
        currentChar = fgetc(file);
    }

    rewind(file);
    return max + 1;
}

/**
 * print the actions
 * @param actions
 * @param length
 */
void printActions(Action* actions, int length) {

    for (int i = 0; i < length; i++) {
        printf("name : *%s*\nurl : *%s*\n", actions[i].name, actions[i].url);

        for (int j = 0; j < actions[i].optionsLength; j++) {

            printf("Action %d\nOption %d\nKey : *%s*\nValue : *%s*\n",
                   i, j, actions[i].keys[j], actions[i].values[j]);
        }
    }

}

/**
 * print the tasks
 * @param tasks
 * @param length
 */
void printTasks(Task* tasks, int length) {

    for (int i = 0; i < length; i++) {
        printf("name : *%s*\nhour : *%d*\nminutes : *%d*\nsecondes : *%d*\n", tasks[i].name, tasks[i].hours,
               tasks[i].minutes, tasks[i].seconds);

        for (int j = 0; j < tasks[i].actionsLength; ++j) {
            printf("action name : *%s*\naction url : *%s*\n", tasks[i].actions[j].name, tasks[i].actions[j].url);
        }
    }
}

/**
 *
 * @param str
 * @return str without blank spaces
 */
char* removeStrSpaces(char* str) {
    int i = 0;
    int j = 0;
    char* newStr = malloc(sizeof(char) * strlen(str) + 1);

    while (str[i] == ' ') {
        i++;
    }

    while (str[strlen(str) - 1 - j] == ' ') {
        j++;
    }

    strncpy(newStr, str + i, strlen(str + i) - j);
    newStr[strlen(str + i) - j] = '\0';

    return newStr;
}

/**
 *
 * @param line
 * @param first
 * @param last
 * @return check the first and last characters of a line
 */
int checkLineEnds(char* line, char* first, char* last) {
    if (strstr(line, first) == NULL
        || strstr(line, last) == NULL) {
        return 0;
    }

    if (strstr(line, first) > strstr(line, last)) {
        return 0;
    }

    return 1;
}

/**
 *
 * @param line
 * @param first
 * @param middle
 * @param last
 * @return if the format of aline is good like {opt1 -> val1}
 */
int checkLineFormat(char* line, char* first, char* middle, char* last) {

    if (strstr(line, first) == NULL
        || strstr(line, last) == NULL
        || strstr(line, middle) == NULL) {
        return 0;
    }

    if (strstr(line, first) > strstr(line, last)
        || strstr(line, first) > strstr(line, middle)
        || strstr(line, middle) > strstr(line, last)) {
        return 0;
    }

    return 1;
}

/**
 *
 * @param line
 * @return if action still have more options
 */
int isActionFinished(char* line) {
    int i;
    for (i = 0; i < strlen(line); i++) {
        switch (line[i]) {
            case '=' :
                return 1;
            case '{' :
                return 0;
            case '(' :
                return 1;
            case EOF :
                return 1;
            default:
                continue;
        }
    }
    return 0;
}

/**
 *
 * @param line
 * @return if task still have more options
 */
int isTaskFinished(char* line) {
    int i;
    for (i = 0; i < strlen(line); i++) {
        switch (line[i]) {
            case '=' :
                return 1;
            case '{' :
                return 0;
            case '(' :
                return 0;
            case EOF :
                return 1;
            default:
                continue;
        }
    }
    return 0;
}

/**
 *
 * @param file
 * @param size
 * @return fgets with \0 and not \n
 */
char* fgetsWithCheck(FILE* file, int size) {

    char* line = malloc(sizeof(char) * (size + 1));

    if (fgets(line, size, file) == NULL) {
        return NULL;
    }

    if (line[strlen(line) - 1] == '\n') {
        line[strlen(line) - 1] = '\0';
    }

    return line;
}

/**
 * set option in action
 * @param action
 * @param key
 * @param value
 */
void setKeyValue(Action* action, char* key, char* value) {

    if (action->optionsLength > 0) {
        char** tempKeys = realloc(action->keys, sizeof(char*) * (action->optionsLength + 1));
        char** tempValues = realloc(action->values, sizeof(char*) * (action->optionsLength + 1));

        action->keys = tempKeys;
        action->values = tempValues;
    }

    action->keys[action->optionsLength] = malloc(sizeof(char) * strlen(key) + 1);
    action->values[action->optionsLength] = malloc(sizeof(char) * strlen(value) + 1);

    strcpy(action->keys[action->optionsLength], key);
    strcpy(action->values[action->optionsLength], value);

    action->optionsLength++;
}

/**
 * set option of an action
 * @param action
 * @param key
 * @param value
 */
void setActionAttribute(Action* action, char* key, char* value) {

    if (strcmp(key, "name") == 0) {

        action->name = malloc(sizeof(char) * strlen(value) + 1);
        action->name = value;

    } else if (strcmp(key, "url") == 0) {

        action->url = malloc(sizeof(char) * strlen(value) + 1);
        action->url = value;

    } else {
        setKeyValue(action, key, value);
    }

}

/**
 * set option of a task
 * @param task
 * @param key
 * @param value
 */

void setTaskAttribute(Task* task, char* key, char* value) {

    if (strcmp(key, "name") == 0) {

        task->name = malloc(sizeof(char) * strlen(value) + 1);
        task->name = value;

    } else if (strcmp(key, "second") == 0) {
        task->seconds = atoi(value);

    } else if (strcmp(key, "minute") == 0) {
        task->minutes = atoi(value);

    } else if (strcmp(key, "hour") == 0) {
        task->hours = atoi(value);
    }
}

/**
 *
 * @param line
 * @param first
 * @param delimiter
 * @return get key in file config
 */

char* getKey(char* line, char* first, char* delimiter) {

    char* key = malloc(sizeof(char) * strlen(line) + 1);
    int length = strstr(line, delimiter) - line - strlen(delimiter);

    strncpy(key, strstr(line, first) + strlen(first), length);
    key[length] = '\0';

    return removeStrSpaces(key);
}

/**
 *
 * @param line
 * @param delimiter
 * @param last
 * @return get value in file config
 */
char* getValue(char* line, char* delimiter, char* last) {

    char* value = malloc(sizeof(char) * strlen(line) + 1);
    int length = strstr(line, last) - strstr(line, delimiter) - strlen(delimiter);

    strncpy(value, strstr(line, delimiter) + strlen(delimiter), length);
    value[length] = '\0';

    return removeStrSpaces(value);
}

/**
 * set option of an action
 * @param action
 * @param line
 * @param first
 * @param delimiter
 * @param last
 */

void setActionOption(Action* action, char* line, char* first, char* delimiter, char* last) {

    if (checkLineFormat(line, first, delimiter, last) == 0) {
        return;
    }

    char* key = getKey(line, first, delimiter);
    char* value = getValue(line, delimiter, last);

    setActionAttribute(action, key, value);
}

/**
 * return str until one char of chrs
 * @param str
 * @param position
 * @param chrs
 * @return
 */
char* getStrUntilChrs(char* str, int* position, char* chrs) {

    char* newStr = malloc(sizeof(char) * strlen(str) + 1);
    int i;

    for (i = 0; i < strlen(str); i++) {
        for (int j = 0; j < strlen(chrs); ++j) {
            if (str[i] == chrs[j]) {
                *position += i;
                newStr[i] = '\0';
                return newStr;
            }
        }
        newStr[i] = str[i];
    }

    return newStr;
}

/**
 * check if delimiters still existing in the rest of the string
 * @param string
 * @param delimiters
 * @return
 */
int delimitersStillExist(char* string, char* delimiters) {
    for (int i = 0; i < strlen(delimiters); ++i) {
        if (strchr(string, delimiters[i]) != NULL) {
            return 1;
        }
    }

    return 0;
}

/**
 *
 * @param line
 * @param length
 * @param delimiters
 * @return an array of strings delimited by delimiters
 */
char** strToArrayStr(char* line, int* length, char* delimiters) {// ex : (bjr, bye) -> [0] -> "bjr" [1] -> "bye"

    char** list = malloc(sizeof(char*));
    char** reallocList;
    int position = 0;

    while (position < strlen(line) && delimitersStillExist(line + position, delimiters) == 1) {

        reallocList = realloc(list, sizeof(char*) * (*length + 1));
        list = reallocList;

        char* newStr = getStrUntilChrs(line + position, &position, delimiters);
        list[*length] = malloc(sizeof(char) * (strlen(newStr) + 1));
        strcpy(list[*length], removeStrSpaces(newStr));
        *length += 1;
        position++;
    }

    return list;
}

/**
 * make the link between actions and tasks
 * @param task
 * @param urls
 * @param urlsLength
 * @param actions
 * @param actionsLength
 */
void linkTaskActions(Task* task, char** urls, int urlsLength, Action* actions, int actionsLength) {

    Action* tempActions;
    task->actionsLength = 0;
    task->actions = malloc(sizeof(Action));

    for (int i = 0; i < urlsLength; ++i) {
        for (int j = 0; j < actionsLength; j++) {

            if (strcmp(actions[j].url, urls[i]) == 0) {

                tempActions = realloc(task->actions, sizeof(Action) * (task->actionsLength + 1));
                task->actions = tempActions;

                task->actions[task->actionsLength] = actions[j];
                task->actionsLength++;
            }
        }
    }
}

/**
 * set all task actions
 * @param action
 * @param file
 * @param position
 */

void setAllActionOptions(Action* action, FILE* file, int position) {

    long maxLineSize = getMaxLineSize(file);
    char* fileLine;

    fseek(file, position, SEEK_SET);

    action->keys = malloc(sizeof(char*));
    action->values = malloc(sizeof(char*));
    action->optionsLength = 0;

    while ((fileLine = fgetsWithCheck(file, (int) maxLineSize)) != NULL && isActionFinished(fileLine) == 0) {
        setActionOption(action, fileLine, "{", "->", "}");
    }

}

/**
 * set all tasks options
 * @param task
 * @param file
 * @param position
 * @param actions
 * @param actionsLength
 */
void setAllTaskOptions(Task* task, FILE* file, int position, Action* actions, int actionsLength) {

    long maxLineSize = getMaxLineSize(file);
    char* fileLine;

    fseek(file, position, SEEK_SET);

    while ((fileLine = fgetsWithCheck(file, (int) maxLineSize)) != NULL && isTaskFinished(fileLine) == 0) {

        if (checkLineFormat(fileLine, "{", "->", "}") == 1) {

            setTaskAttribute(task, getKey(fileLine, "{", "->"), getValue(fileLine, "->", "}"));

        } else if (checkLineEnds(fileLine, "(", ")") == 1) {

            int urlsLength = 0;
            char** urls = strToArrayStr(strchr(fileLine, '(') + 1, &urlsLength, ",)");
            linkTaskActions(task, urls, urlsLength, actions, actionsLength);
        }
    }

}

/**
 * return line after a specific char
 * @param charToFind
 * @param file
 * @param iteration
 * @return
 */
long getLinePosAfterChar(char charToFind, FILE* file, int iteration) {

    rewind(file);
    char c;
    int count = 0;

    while ((c = fgetc(file)) != EOF) {

        if (c == charToFind && (c = fgetc(file)) != '=') {
            count += 1;
            fseek(file, -1, SEEK_CUR);
            if (count == iteration) {// aller juska \n ?
                while ((c = fgetc(file)) != '\n') {
                    if (c == EOF) {
                        return -1;
                    }
                }
                return ftell(file);
            }
        }
    }

    return -1;
}

/**
 * return line after a specific string
 * @param strToFind
 * @param file
 * @param iteration
 * @return
 */
long getLinePosAfterStr(char* strToFind, FILE* file, int iteration) {

    rewind(file);//revenir au debut du fichier
    int strCount = 0;
    long lineSize = getMaxLineSize(file);
    char* fileLine = malloc(sizeof(char) * lineSize + 1); // +1 pour le 0

    while (fgets(fileLine, (int) lineSize, file) != NULL) {
        if (fileLine[strlen(fileLine) - 1] == '\n') {
            fileLine[strlen(fileLine) - 1] = '\0';
        }

        if (strstr(fileLine, strToFind) != NULL) {// chaîne trouvée
            strCount += 1;
            if (strCount == iteration) { // si on veut aller à la deuxième action par ex
                return ftell(file);
            }
        }

    }

    return -1;
}

/**
 * fill the actions depending on the config file
 * @param file
 * @param actionsLength
 * @return
 */
Action* getActions(FILE* file, int* actionsLength) {

    rewind(file);
    int position;
    Action* actions = malloc(sizeof(Action));
    Action* tempActions;

    while ((position = (int) getLinePosAfterChar('=', file, *actionsLength + 1)) != -1) {

        if (*actionsLength > 0) {
            tempActions = realloc(actions, sizeof(Action) * (*actionsLength + 1));
            actions = tempActions;
        }

        setAllActionOptions(&actions[*actionsLength], file, position);
        *actionsLength += 1;
    }

    return actions;
}

/**
 * fill the tasks depending on the config file
 * @param file
 * @param tasksLength
 * @param actions
 * @param actionsLength
 * @return
 */
Task* getTasks(FILE* file, int* tasksLength, Action* actions, int actionsLength) {

    rewind(file);
    int position;
    Task* tasks = malloc(sizeof(Task));
    Task* tempTasks;

    while ((position = (int) getLinePosAfterStr("==", file, *tasksLength + 1)) != -1) {

        if (*tasksLength > 0) {
            tempTasks = realloc(tasks, sizeof(Task) * (*tasksLength + 1));
            tasks = tempTasks;
        }

        setAllTaskOptions(&tasks[*tasksLength], file, position, actions, actionsLength);

        *tasksLength += 1;
    }

    return tasks;
}

