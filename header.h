#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "curl.h"

#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED


typedef struct StringRes {
    char *ptr;
    size_t len;
} StringRes;

typedef struct Option {
    char *name;
    char *value;
} Option;

typedef  struct  CounterFile{
int nbImg;
int nbVideo;
int nbLinkTag;
int nbLink;
int nbJs;
int nbContent;

}CounterFile;
int deleteRepositorie(char* repositorieName);
int createRepositorie(char* repositorieName);
char* filenameDynamicContainer(char * type,int i,char* ext );
char* filenameDynamicTxt(char * type,int i );
char* hrefOrSrcRouter(char * tag);
char* getHostUrl(char* url);
void getCodeInFile(char* url,int i ,char* beginTag);
void execute(char**tabaction,char * url,int taille );

void extractAll(char *url,char* tag) ;
void extractContentBetweenTag(char *  codeHtml,int number,char* beginTag,char * endTag);
void extractLink(char * codeHtml,FILE* file,char* searchBeginTag,char * typeHrefOrSrc);
void treatment(char * urlFind ,char * beginTag,FILE* file,    int nbUrl );
void process(int beginTag,int endTag,char* codeHtml,char* searchBeginTag,FILE*file,int* nbUrl,const char**p,char const*toSearch,int posHref);
int checkBegin(int beginTag,int endTag,char*  codeHtml,int i,int posHref);
int positionOfSymbole(int begin ,char *codeHtml,char charToFind);
int positionOfAttribut(int begin,int end,char* codeHtml, char *  attrToFind);

size_t writefunc(void *ptr, size_t size, size_t nmemb, StringRes *s);
char *getHtmlCode(char* url);
void getCodeInFile(char* url,int i,char* beginTag );
char * getExtension(char * url );
void saveMedia(char* url,int i,char * beginTag );










#endif // HEADER_H_INCLUDED