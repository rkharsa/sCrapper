#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "curl.h"

#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED


typedef struct StringRes {
    char* ptr;
    size_t len;
} StringRes;


typedef struct CounterFile {
    int nbImg;
    int nbVideo;
    int nbLinkTag;
    int nbLink;
    int nbJs;
    int nbContent;


} CounterFile;

typedef struct Param {
    FILE* file;
    int posBeginTag;
    int posEndTag;
    char* tag;
    char* codeHtml;
} Param;


void firstWave(char* url);

void nextWave(int waveDeph);

char* getBeginTag(char* tag);

char* getEndTag(char* tag);

int* routerCounter(CounterFile* counterFile, char* tag);

void counterIncrem(CounterFile* counterFile, char* tag);

CounterFile initCounterFile();

char* getHostName(char* url);

char* getBeginUrl(char* url);

char* filenameDynamicContainer(char* folder, char* type, int i, char* ext);

char* filenameDynamicTxt(char* folder, char* tag, int i);

char* hrefOrSrcRouter(char* tag);

void getCodeInFile(char* url, int i, char* tag, char* folder, char* toSearchMime);

void execute(char** tabaction, char* url, int taille, char* folder, char* toSearchMime);

void extractAll(char* url, char* tag, CounterFile* counterFile, char* folder, char* toSearchMime);

void extractContentBetweenTag(char* codeHtml, int number, char* tag, char* folder);

void extractLink(char* codeHtml, FILE* file, char* tag, CounterFile* counterFile, char* folder, char* url,
                 char* toSearchMime);

void treatment(char* urlFind, char* tag, FILE* file, CounterFile* counterFile, char* folder, char* toSearchMime);

int positionOfSymbole(int begin, char* codeHtml, char charToFind);

int positionOfAttribut(int begin, int end, char* codeHtml, char* attrToFind);

size_t writefunc(void* ptr, size_t size, size_t nmemb, StringRes* s);

char* getHtmlCode(char* url);

char* getExtension(char* url);

void saveMedia(char* url, int i, char* tag, char* folder, char* toSearchMime);

void task(char* url, int i, char* beginTag);

void saveLink(int posBeginTag, int posEndTag, char* codeHtml, FILE* file, char* url, char* tag, char* folder,
              CounterFile* counterFile, char* toSearchMime);

int verifTypeMime(char* url, char* typeMimeToSearch);

char* getTypeMime(char* url);

void checkBeginLink(int* i, int posEndTag, char** urlFind, char* url, char* codeHtml, int* counter, int* findBeginSave);

#endif // HEADER_H_INCLUDED