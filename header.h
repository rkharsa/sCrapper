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

typedef struct Action {
    char *name; // nom action
    char *url; // url du site
    Option *options; // liste des options et de leur valeurs
} Action;
void extract_all(char *url);
void extract_href_from_html(char * code_html,FILE* file);
int equal_position(char* code_html,int i);
void initString(StringRes *s);
size_t writefunc(void *ptr, size_t size, size_t nmemb, StringRes *s);
char *getHtmlCode(char* url);
void extract_first_title(char *  code_html,FILE* file,char * title_level);
int position_of_symbole(int begin ,char *code_html,char char_to_find);
int position_of_attribut(int begin,int end,char* code_html, char *  attr_to_find);
void extract_href(char * code_html,FILE* file,char* search_begin_tag,char * typeHrefOrSrc);
#endif // HEADER_H_INCLUDED