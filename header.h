#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "configuration.c"
#include "curl.h"
#include "scrapper.c"
typedef struct Option {
    char *name;
    char *value;
} Option;

typedef struct Action {
    char *name; // nom action
    char *url; // url du site
    Option *options; // liste des options et de leur valeurs
} Action;

void getHtmlCode(char* url);
#endif // HEADER_H_INCLUDED