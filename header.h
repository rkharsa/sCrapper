#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    Option options[10]; // liste des options et de leur valeurs
} Action;

typedef struct Task {
    Action *Action; // nom action
    int hours;
    int minutes;
    int seconds;
    char *nextOccurence; // nom action

} Task;
#include "curl.h"
#include <time.h>

#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED



/*
void initString(StringRes *s);
size_t writefunc(void *ptr, size_t size, size_t nmemb, StringRes *s);
char *getHtmlCode(char* url);
*/
void task(Task *task);

#endif // HEADER_H_INCLUDED