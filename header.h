#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dir.h>
#include "curl.h"

#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED


typedef struct StringRes {
    char *ptr;
    size_t len;
} StringRes;


typedef  struct  CounterFile{
int nbImg;
int nbVideo;
int nbLinkTag;
int nbLink;
int nbJs;
int nbContent;


}CounterFile;

int * routerCounter(CounterFile*  counterFile,char * beginTag);
void counterIncrem(CounterFile * counterFile,char*beginTag);
CounterFile initCounterFile();

int deleteRepositorie(char* repositorieName);
int createRepositorie(char* repositorieName);

char* filenameDynamicContainer(char * type,int i,char* ext );
char* filenameDynamicTxt(char * type,int i );
char* hrefOrSrcRouter(char * tag);
char* getHostUrl(char* url);
void getCodeInFile(char* url,int i ,char* beginTag);
void execute(char**tabaction,char * url,int taille );

void extractAll(char *url,char* tag,CounterFile* counterFile) ;
void extractContentBetweenTag(char *  codeHtml,int number,char* beginTag,char * endTag);
void extractLink(char * codeHtml,FILE* file,char* searchBeginTag,char * typeHrefOrSrc,CounterFile* counterFile);
void treatment(char * urlFind ,char * beginTag,FILE* file,CounterFile*counterFile );
void process(int beginTag,int endTag,char* codeHtml,char* searchBeginTag,FILE*file,const char**p,char const*toSearch,int posHref,CounterFile * counterFile);
int checkBegin(int beginTag,int endTag,char*  codeHtml,int i,int posHref);
int positionOfSymbole(int begin ,char *codeHtml,char charToFind);
int positionOfAttribut(int begin,int end,char* codeHtml, char *  attrToFind);

size_t writefunc(void *ptr, size_t size, size_t nmemb, StringRes *s);
char *getHtmlCode(char* url);
char * getExtension(char * url );
void saveMedia(char* url,int i,char * beginTag );
void task(char* url,int i,char * beginTag );



#endif // HEADER_H_INCLUDED