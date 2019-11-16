//
// Created by Jérémy TERNISIEN on 16/11/2019.
//

#ifndef SCRAPPER_FILE_H
#define SCRAPPER_FILE_H

int removeDirectoryFiles(const char *filePath, const struct stat *sb, int flag, struct FTW *ftwbuf);
int createDirectory(char* path, int mode);
int removeDirectory(char* path);
int copyPasteFile(FILE* srcFile, FILE* destFile);
int countLinesFromFile(FILE* file, char* line, int lineSize);
int isLineCorrect(char** filters, int filtersLength, char* line);
int removeDuplicateLines(FILE* file, char* filePath);
int filterLinesFile(FILE* file, char* filePath, char** filters, int filtersLength);

#endif //SCRAPPER_FILE_H
