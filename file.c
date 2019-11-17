//
// Created by Jérémy TERNISIEN on 16/11/2019.
// FILE CONTAINING FUNCTIONS TO MANIPULATE FILES

#include <stdio.h>
#include <stdlib.h>
#include <ftw.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "parser.h"
#include "file.h"


/**
 * create a directory tree struct
 * @param path
 */
void createDirectoryTreeStruct(char *path) {
    char* tempDirectory = malloc(sizeof(char) * strlen(path) + 20);
    #ifdef _WIN32
       mkdir(path);
    #else
    createDirectory(path, 0777);
    #endif

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

/**
 * function required for ntfw for each file in a directory
 * @param filePath
 * @param sb
 * @param flag
 * @param ftwbuf
 * @return
 */
int removeDirectoryFiles(const char *filePath, const struct stat *sb, int flag, struct FTW *ftwbuf) {
    int code = remove(filePath);

    return code;
}

/**
 * create a directory
 * @param path
 * @param mode
 * @return
 */
int createDirectory(char* path, int mode) {
    #ifdef _WIN32
        if(mkdir(path) == 0) {
            return 0;
        } else {
            return -1;
        }
    #else
        if(mkdir(path, mode) == 0) {
            return 0;
        } else {
            return -1;
        }
    #endif

}

/**
 * remove a directory and all of its subfiles
 * @param path
 * @return
 */
int removeDirectory(char* path) {
    return nftw(path, removeDirectoryFiles, 64, FTW_DEPTH | FTW_PHYS);
}

/**
 * copy paste the content of a file to an other file
 * @param srcFile
 * @param destFile
 * @return
 */
int copyPasteFile(FILE* srcFile, FILE* destFile) {
    char c;
    rewind(srcFile);
    rewind(destFile);

    while((c = fgetc(srcFile)) != EOF) {
        fputc(c, destFile);
    }

    return 0;
}

/**
 *
 * @param file
 * @param line
 * @param lineSize
 * @return
 */
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

/**
 *
 * @param filters
 * @param filtersLength
 * @param line
 * @return
 */
int isLineCorrect(char** filters, int filtersLength, char* line) {
    int exist = 0;
    for (int i = 0; i < filtersLength; ++i) {
        if(strstr(line, filters[i]) != NULL) {
            exist++;
        }
    }

    return exist == 0 && line != NULL && line[0] != '\0';
}


/**
 * remove duplicate lines of a file
 * @param file
 * @param filePath
 * @return
 */
int removeDuplicateLines(FILE* file, char* filePath) {

    int lineSize = getMaxLineSize(file);
    char* line = malloc(sizeof(char) * (lineSize + 1));
    FILE* tempFile = fopen("temp.txt", "w+");

    if(tempFile == NULL) {
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


/**
 * remove lines with specific characters in from a file
 * @param file
 * @param filePath
 * @param filters
 * @param filtersLength
 * @return
 */
int filterLinesFile(FILE* file, char* filePath, char** filters, int filtersLength) {

    int lineSize = getMaxLineSize(file);
    char* line = malloc(sizeof(char) * (lineSize + 1));

    FILE* tempFile = fopen("temp.txt", "w+");

    if(tempFile == NULL) {
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
