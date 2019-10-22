#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "curl.h"
#include <time.h>

#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

/*
typedef struct StringRes {
    char *ptr;
    size_t len;
} StringRes;

typedef struct Option {
    char *name;
    char *value;
} Option;

typedef struct Action {
    char *name; // nom action
    char *url; // url du site
    Option *options; // liste des options et de leur valeurs
} Action;


void initString(StringRes *s);
size_t writefunc(void *ptr, size_t size, size_t nmemb, StringRes *s);
char *getHtmlCode(char* url);
*/
void task(int hours, int minute,int second);

#endif // HEADER_H_INCLUDED