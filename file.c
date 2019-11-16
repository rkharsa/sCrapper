//
// Created by Jérémy TERNISIEN on 16/11/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <ftw.h>
#include <string.h>
#include "parser.h"
#include "file.h"

void createDirectoryTreeStruct(char *path) {
    char* tempDirectory = malloc(sizeof(char) * strlen(path) + 20);
    createDirectory(path, 0777);

    sprintf(tempDirectory, "%s/content", path);
    createDirectory(tempDirectory, 0777);
    sprintf(tempDirectory, "%s/imgTag", path);
    createDirectory(tempDirectory, 0777);
    sprintf(tempDirectory, "%s/scriptTag", path);
    createDirectory(tempDirectory, 0777);
    sprintf(tempDirectory, "%s/linkofAllTag", path);
    createDirectory(tempDirectory, 0777);
    sprintf(tempDirectory, "%s/linkTag", path);
    createDirectory(tempDirectory, 0777);
    sprintf(tempDirectory, "%s/sourceTag", path);
    createDirectory(tempDirectory, 0777);
}

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
