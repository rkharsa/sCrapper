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

void deleteRepositorie(char* repositorieName);

void createRepositorie(char* repositorieName);

char* filenameDynamicContainer(char* repositorie, char* type, int i, char* ext);

char* filenameDynamicTxt(char* repositorie, char* tag, int i);

char* hrefOrSrcRouter(char* tag);

void getCodeInFile(char* url, int i, char* tag, char* repositorie);

void execute(char** tabaction, char* url, int taille, char* repositorie);

void extractAll(char* url, char* tag, CounterFile* counterFile, char* repositorie);

void extractContentBetweenTag(char* codeHtml, int number, char* tag, char* repositorie);

void extractLink(char* codeHtml, FILE* file, char* tag, CounterFile* counterFile, char* repositorie);

void treatment(char* urlFind, char* tag, FILE* file, CounterFile* counterFile, char* repositorie);

void process(int beginTag, int endTag, char* codeHtml, char* tag, FILE* file, const char** p, char const* toSearch,
             int posHref, CounterFile* counterFile, char* repositorie);

int checkBegin(int beginTag, int endTag, char* codeHtml, int i, int posHref);

int positionOfSymbole(int begin, char* codeHtml, char charToFind);

int positionOfAttribut(int begin, int end, char* codeHtml, char* attrToFind);

size_t writefunc(void* ptr, size_t size, size_t nmemb, StringRes* s);

char* getHtmlCode(char* url);

char* getExtension(char* url);

void saveMedia(char* url, int i, char* tag, char* repositorie);

void task(char* url, int i, char* beginTag);


#endif // HEADER_H_INCLUDED