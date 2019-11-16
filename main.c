#include "header.h"
#include "parser.h"
#include "manager.h"
#include <ftw.h>
#include <unistd.h>

// VALIDES ET FONCITONNELLES

int removeDirectoryFiles(const char *filePath, const struct stat *sb, int flag, struct FTW *ftwbuf) {
    int code = remove(filePath);

    if(code != 0) {
        printf("Error deleting %s\n", filePath);
    }

    return code;
}

int createDirectory(char* path, int mode) {

    if(mkdir(path, mode) == 0) {
        return 0;
    } else {
        printf("Directory %s could not be create\n", path);
        return -1;
    }
}

int removeDirectory(char* path) {
    return nftw(path, removeDirectoryFiles, 64, FTW_DEPTH | FTW_PHYS);
}

int copyPasteFile(FILE* srcFile, FILE* destFile) {
    char c;
    rewind(srcFile);
    rewind(destFile);

    while((c = fgetc(srcFile)) != EOF) {
        fputc(c, destFile);
    }

    return 0;
}

int countLinesFromFile(FILE* file, char* line, int lineSize) {

    char* currentLine = malloc(sizeof(char) * lineSize + 1);
    int countLine = 0;

    rewind(file);
    while(fgets(currentLine, lineSize, file) != NULL) {

        if(currentLine[strlen(currentLine) - 1] == '\n') {
            currentLine[strlen(currentLine) - 1] = '\0';
        }

        if(strcmp(currentLine, line) == 0) {
            countLine += 1;
        }
    }

    return countLine;
}

int isLineCorrect(char** filters, int filtersLength, char* line) {
    int exist = 0;
    for (int i = 0; i < filtersLength; ++i) {
        if(strstr(line, filters[i]) != NULL) {
            exist++;
        }
    }

    return exist == 0 && line != NULL && line[0] != '\0';
}

int removeDuplicateLines(FILE* file, char* filePath) {

    int lineSize = getMaxLineSize(file);
    char* line = malloc(sizeof(char) * (lineSize + 1));
    FILE* tempFile = fopen("temp.txt", "w+");

    if(tempFile == NULL) {
        printf("Can not open %s\n", "temp.txt");
        fclose(file);
        return -1;
    }

    while(fgets(line, lineSize, file) != NULL) {

        if(line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }

        if(countLinesFromFile(tempFile, line, lineSize) < 1) {
            fputs(line, tempFile);
            fputc('\n', tempFile);
        }

    }

    fclose(file);
    fclose(tempFile);

    remove(filePath);
    rename("temp.txt", filePath);

    return 0;
}



int filterLinesFile(FILE* file, char* filePath, char** filters, int filtersLength) {

    int lineSize = getMaxLineSize(file);
    char* line = malloc(sizeof(char) * (lineSize + 1));

    FILE* tempFile = fopen("temp.txt", "w+");

    if(tempFile == NULL) {
        printf("Can not open %s\n", "temp.txt");
        fclose(file);
        return -1;
    }

    while(fgets(line, lineSize, file) != NULL) {

        if(line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }

        if(isLineCorrect(filters, filtersLength, line) == 1) {
            fputs(line, tempFile);
            fputc('\n', tempFile);
        }

    }

    fclose(file);
    fclose(tempFile);

    remove(filePath);
    rename("temp.txt", filePath);

    return 0;
}

int main(int argc, char* argv[]) {

    char** str = malloc(sizeof(char*) * 3);

    str[0] = malloc(sizeof(char) * 6);
    strcpy(str[0], ".png");

    str[1] = malloc(sizeof(char) * 6);
    strcpy(str[1], ".jpeg");

    str[2] = malloc(sizeof(char) * 6);
    strcpy(str[2], ".svg");

    //printf("%d", filterLinesFile("../testg.txt",  str, 3));

    FILE* f1 = fopen("../testg.txt", "r");

    printf("%d", removeDuplicateLines(f1, "../testg.txt"));
    //fclose(f1);


   /* printf("%s\n", "--------------------------------------------------------------");
    printf("%s", "  _________                                 .__                \n"
                 " /   _____/ ________________  ______ ______ |__| ____    ____  \n"
                 " \\_____  \\_/ ___\\_  __ \\__  \\ \\____ \\\\____ \\|  |/    \\  / ___\\ \n"
                 " /        \\  \\___|  | \\// __ \\|  |_> >  |_> >  |   |  \\/ /_/  >\n"
                 "/_______  /\\___  >__|  (____  /   __/|   __/|__|___|  /\\___  / \n"
                 "        \\/     \\/           \\/|__|   |__|           \\//_____/  ");
    printf("\n%s\n", "--------------------------------------------------------------");

    char* filePath = "../configFile.sconf";//getFilePath();// à remplacer par getFilePath() mais là on gagne du temps pour les tests

    FILE* file = fopen(filePath, "r");
    if (file == NULL) {
        return EXIT_FAILURE;
    }

    int actionsLength = 0;
    int tasksLength = 0;
    Action* actions = getActions(file, &actionsLength);
    Task* tasks = getTasks(file, &tasksLength, actions, actionsLength);

    for (int i = 0; i < tasksLength; ++i) {
        for (int j = 0; j < tasks[i].actionsLength; ++j) {
            //printf("%s\n%d\n", tasks[i].actions[j].name, j);
            executeAction(tasks[i].actions[j]);
        }
    }

    fclose(file);*/
   return EXIT_SUCCESS;
}
