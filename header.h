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

void fistWawe(char* url);

void nextWave(int waveDeph);

char* getBeginTag(char* tag);

char* getEndTag(char* tag);

int* routerCounter(CounterFile* counterFile, char* tag);

void counterIncrem(CounterFile* counterFile, char* tag);

CounterFile initCounterFile();

void deleteFolder(char* folderName);

void createFolder(char* folderName);

char* filenameDynamicContainer(char* folder, char* type, int i, char* ext);

char* filenameDynamicTxt(char* folder, char* tag, int i);

char* hrefOrSrcRouter(char* tag);

void getCodeInFile(char* url, int i, char* tag, char* folder);

void execute(char** tabaction, char* url, int taille, char* folder);

void extractAll(char* url, char* tag, CounterFile* counterFile, char* folder);

void extractContentBetweenTag(char* codeHtml, int number, char* tag, char* folder);

void extractLink(char* codeHtml, FILE* file, char* tag, CounterFile* counterFile, char* folder);

void treatment(char* urlFind, char* tag, FILE* file, CounterFile* counterFile, char* folder);

void process(int beginTag, int endTag, char* codeHtml, char* tag, FILE* file, const char** p, char const* toSearch,
             int posHref, CounterFile* counterFile, char* folder);

int checkBegin(int beginTag, int endTag, char* codeHtml, int i, int posHref);

int positionOfSymbole(int begin, char* codeHtml, char charToFind);

int positionOfAttribut(int begin, int end, char* codeHtml, char* attrToFind);

size_t writefunc(void* ptr, size_t size, size_t nmemb, StringRes* s);

char* getHtmlCode(char* url);

char* getExtension(char* url);

void saveMedia(char* url, int i, char* tag, char* folder);

void task(char* url, int i, char* beginTag);


#endif // HEADER_H_INCLUDED