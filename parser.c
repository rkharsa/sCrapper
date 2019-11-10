//
// Created by Jérémy TERNISIEN on 14/10/2019.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"

int checkFileExtension(char *filePath, char *extension) {
    if(strrchr(filePath, '.') != NULL && strcmp(extension, strrchr(filePath, '.') + 1) != 0) {
        printf("L\'extension du fichier n\'est pas %s, veuillez entrer un nouveau chemin\n", extension);
        return 0;
    }

    return 1;
}

int checkFileExists(char *filePath) {
    FILE *file = NULL;

    file = fopen(filePath, "r");

    if(file == NULL) {
        printf("Nous ne trouvons pas de fichier de configuration à cet endroit là, veuillez entrer un nouveau chemin\n");
        return 0;
    }

    fclose(file);
    return 1;
}

char *getFilePath() {

    char *filePath = malloc(sizeof(char) * LINE_FILE_MAX + 1);

    printf("Veuillez entrer le chemin de votre fichier de configuration\n");

    do {
        fgets(filePath, LINE_FILE_MAX, stdin);

        if(filePath[strlen(filePath) - 1] == '\n') {
            filePath[strlen(filePath) - 1] = '\0';
        }

        if(checkFileExtension(filePath, "sconf") == 0) {
            continue;
        }

    } while(checkFileExists(filePath) == 0);

    printf("Fichier de configuration trouvé\n\nLecture du fichier en cours...\n");

    return filePath;
}

long getMaxLineSize(FILE *file) {
    char currentChar;
    long count = 0;
    long max = 0;
    if(file == NULL) {
        printf("Error with get max size of line");
        return 0;
    }

    currentChar = fgetc(file);
    while(currentChar != EOF) {
        if(currentChar == '\n') {
            currentChar = fgetc(file);
            count = 0;
            continue;
        }

        count++;
        if(count > max) {
            max = count;
        }
        currentChar = fgetc(file);
    }

    rewind(file);
    return max + 1;
}

void printActions(Action *actions, int length) {

    for (int i = 0; i < length; i++) {
        printf("name : *%s*\nurl : *%s*\n", actions[i].name, actions[i].url);

        for (int j = 0; j < actions[i].length; j++) {

            printf("Action %d\nOption %d\nKey : *%s*\nValue : *%s*\n",
                   i, j, actions[i].keys[j], actions[i].values[j]);
        }
    }

}

void printTasks(Task *tasks, int length) {

    for (int i = 0; i < length; i++) {
        printf("name : *%s*\nhour : *%d*\nminutes : *%d*\nsecondes : *%d*\n", tasks[i].name, tasks[i].hours,
               tasks[i].minutes, tasks[i].seconds);
        for (int j = 0; j < tasks[i].actionLength; ++j) {
            printf("action : *%s*\n", tasks[i].actions[j].name);
        }

    }

}

char *removeSpaces(char *str)
{
    int i = 0;
    int j = 0;
    char *newStr = malloc(sizeof(char) * strlen(str) + 1);

    while(str[i] == ' ') {
        i++;
    }

    while(str[strlen(str) - 1 - j] == ' ') {
        j++;
    }

    strncpy(newStr, str + i, strlen(str + i) - j);
    newStr[strlen(str + i) - j] = '\0';

    return newStr;
}

int checkTaskFormat(char *optionStr, char *first, char *last) {
    if(strstr(optionStr, first) == NULL
       || strstr(optionStr, last) == NULL) {
        return 0;
    }

    if(strstr(optionStr, first) > strstr(optionStr, last)) {
        return 0;
    }

    return 1;
}

int checkOptionFormat(char *optionStr, char *first, char *middle, char *last) {
    if(strstr(optionStr, first) == NULL
       || strstr(optionStr, last) == NULL
       || strstr(optionStr, middle) == NULL) {
        return 0;
    }

    if(strstr(optionStr, first) > strstr(optionStr, last)
       || strstr(optionStr, first) > strstr(optionStr, middle)
       || strstr(optionStr, middle) > strstr(optionStr, last)) {
        return 0;
    }

    return 1;
}

int isOptionFinished(char *line) {
    int i;
    for(i = 0; i < strlen(line); i++) {
        switch(line[i]) {
            case '=' : return 1;
            case '{' : return 0;
            case '(' : return 0;
            case EOF : return 1;
            default:   continue;
        }
    }
    return 0;
}


void setOptions(Action *action, FILE *file, int position) {
    long lineSize = getMaxLineSize(file);
    char *lineFile = malloc(sizeof(char) * lineSize + 1); // +1 pour le 0
    char *newKey = malloc(sizeof(char) * lineSize + 1);
    char *newValue = malloc(sizeof(char) * lineSize + 1);
    int keyLength;
    int valueLength;
    char **tempKeys;
    char **tempValues;

    fseek(file, position, SEEK_SET);

    action->keys = malloc(sizeof(char*));
    action->values = malloc(sizeof(char*));
    action->length = 0;

    while(fgets(lineFile, (int)lineSize, file) != NULL) {

        if(lineFile[strlen(lineFile) - 1] == '\n') {
            lineFile[strlen(lineFile) - 1] = '\0';
        }

        if(isOptionFinished(lineFile) == 1) {
            break;
        }

        if(checkOptionFormat(lineFile, "{", "->", "}") == 1) { // si il ya bien { -> }

            keyLength = strstr(lineFile, "->") - lineFile - 2;
            valueLength = strchr(lineFile, '}') - strstr(lineFile, "->") - 3;

            strncpy(newKey, strchr(lineFile, '{') + 1, keyLength);
            newKey[keyLength] = '\0';

            strncpy(newValue, strstr(lineFile, "->") + 3, valueLength);
            newValue[valueLength] = '\0';

            if(strcmp(removeSpaces(newKey), "name") == 0) {

                action->name = malloc(sizeof(char) * strlen(removeSpaces(newValue)) + 1);
                strcpy(action->name, removeSpaces(newValue));

            } else if (strcmp(removeSpaces(newKey), "url") == 0) {

                action->url = malloc(sizeof(char) * strlen(removeSpaces(newValue)) + 1);
                strcpy(action->url, removeSpaces(newValue));

            } else {

                if(action->length > 0) {

                    tempKeys = realloc(action->keys
                            , sizeof(char*) * (action->length + 1));

                    tempValues = realloc(action->values
                            , sizeof(char*) * (action->length + 1));

                    action->keys = tempKeys;
                    action->values = tempValues;
                }



                action->keys[action->length] = malloc(sizeof(char) * strlen(removeSpaces(newKey)) + 1);
                action->values[action->length] = malloc(sizeof(char) * strlen(removeSpaces(newValue)) + 1);

                strcpy(action->keys[action->length], removeSpaces(newKey));
                strcpy(action->values[action->length], removeSpaces(newValue));

                action->length += 1;
            }
        }
    }
}



void setTaskActions(Task *task, Action *actions, int actionLength, char *urls) {

    char *temp = malloc(sizeof(char) * strlen(urls));
    int index = 0;
    int arrayLength = 0;
    char **stringArray = malloc(sizeof(char*));
    char **newStringArray;
    Action *newAction;

    task->actionLength = 0;

    for (int i = 0; i < strlen(urls); ++i) {

        if(urls[i] == ',' || urls[i] == ')') {

            newStringArray = realloc(stringArray, sizeof(char*) * (arrayLength + 1));
            stringArray = newStringArray;

            stringArray[arrayLength] = malloc(sizeof(char) * strlen(temp) + 1);
            strcpy(stringArray[arrayLength], removeSpaces(temp));
            memset(temp, 0, strlen(temp));

            arrayLength++;
            index = 0;
        } else if(urls[i] != '('){
            temp[index] = urls[i];
            index++;
        }
    }

    for (int j = 0; j < arrayLength; ++j) {
        for(int k = 0; k < actionLength; k++) {
            if(strcmp(actions[k].url, stringArray[j]) == 0) {
                //malloc actions etc etc mon poto
                if(task->actionLength > 0) {
                    newAction = realloc(task->actions, sizeof(Action) * (task->actionLength + 1));
                    task->actions = newAction;
                } else {
                    task->actions = malloc(sizeof(Action));
                }

                task->actions[task->actionLength] = actions[k];
                task->actionLength++;
            }
        }
    }

}


void setTasksOptions(Task *task, FILE *file, int position, Action *actions, int actionLength) {
    long lineSize = getMaxLineSize(file);
    char *lineFile = malloc(sizeof(char) * lineSize + 1); // +1 pour le 0
    char *newKey = malloc(sizeof(char) * lineSize + 1);
    char *newValue = malloc(sizeof(char) * lineSize + 1);
    int keyLength;
    int valueLength;

    fseek(file, position, SEEK_SET);

    while(fgets(lineFile, (int)lineSize, file) != NULL) {

        if(lineFile[strlen(lineFile) - 1] == '\n') {
            lineFile[strlen(lineFile) - 1] = '\0';
        }

        if(isOptionFinished(lineFile) == 1) {
            break;
        }

        if(checkOptionFormat(lineFile, "{", "->", "}") == 1) { // si il ya bien { -> }

            // a refacto
            keyLength = strstr(lineFile, "->") - lineFile - 2;
            valueLength = strchr(lineFile, '}') - strstr(lineFile, "->") - 3;

            strncpy(newKey, strchr(lineFile, '{') + 1, keyLength);
            newKey[keyLength] = '\0';

            strncpy(newValue, strstr(lineFile, "->") + 3, valueLength);
            newValue[valueLength] = '\0';

            // a refacto ptete mdr
            if(strcmp(removeSpaces(newKey), "name") == 0) {

                task->name = malloc(sizeof(char) * strlen(removeSpaces(newValue)) + 1);
                strcpy(task->name, removeSpaces(newValue));

            } else if (strcmp(removeSpaces(newKey), "minute") == 0) {

                task->minutes = atoi(newValue);

            } else if (strcmp(removeSpaces(newKey), "second") == 0) {

                task->seconds = atoi(newValue);

            } else if (strcmp(removeSpaces(newKey), "hour") == 0) {

                task->hours = atoi(newValue);

            }

        } else if(checkTaskFormat(lineFile, "(",")") == 1) {

            setTaskActions(task, actions, actionLength, lineFile);

        }
    }
}

long getLinePosAfterChar(char charToFind, FILE *file, int iteration) {
    rewind(file);//revenir au debut du fichier
    char c;
    int count = 0;

    while((c = fgetc(file)) != EOF) {

        if(c == charToFind && (c = fgetc(file)) != '=') {
            count += 1;
            fseek(file, -1, SEEK_CUR);
            if(count == iteration) {// aller juska \n ?
                while((c = fgetc(file)) != '\n') {
                    if(c == EOF) {
                        return -1;
                    }
                }
                return ftell(file);
            }
        }
    }

    return -1;
}

long getLinePosAfterStr(char *strToFind, FILE *file, int iteration) {
    rewind(file);//revenir au debut du fichier
    int strCount = 0;
    long lineSize = getMaxLineSize(file);
    char *lineFile = malloc(sizeof(char) * lineSize + 1); // +1 pour le 0

    while(fgets(lineFile, (int)lineSize, file) != NULL) {
        if(lineFile[strlen(lineFile) - 1] == '\n') {
            lineFile[strlen(lineFile) - 1] = '\0';
        }

        if(strstr(lineFile, strToFind) != NULL) {// chaîne trouvée
            strCount += 1;
            if(strCount == iteration) { // si on veut aller à la deuxième action par ex
                return ftell(file);
            }
        }

    }

    return -1;
}

//juste faudra check que le name et url existent bien a laide dune fct de verif




//fct principale enffft
Action *parseActions(FILE *fileToParse, int *actionLength) {
    rewind(fileToParse);
    int position;
    Action *action = malloc(sizeof(Action));
    Action *newAction;

    while((position = (int)getLinePosAfterChar('=', fileToParse, *actionLength + 1)) != -1) {

        if(*actionLength > 0) {
            newAction = realloc(action, sizeof(Action) * (*actionLength + 1));

            if(newAction == NULL) {
                fprintf(stderr, "ouch");
            } else {
                action = newAction;
            }
        }

        setOptions(&action[*actionLength], fileToParse, position);

        *actionLength += 1;
    }
    return action;
}


Task *parseTasks(FILE *fileToParse, int *length, Action *actions, int actionLength) {
    rewind(fileToParse);
    int position;
    Task *task = malloc(sizeof(Task));
    Task *newTask;

    while((position = (int)getLinePosAfterStr("==", fileToParse, *length + 1)) != -1) {

        if(*length > 0) {
            newTask = realloc(task, sizeof(Task) * (*length + 1));
            task = newTask;
        }

        setTasksOptions(&task[*length], fileToParse, position, actions, actionLength);
        *length += 1;
    }
    return task;
}

