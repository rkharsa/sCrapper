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

typedef struct  Link{
char *url;
char* type;
int passage;
}Link;
typedef struct LinkLibrary{
    Link* links;
    int nombreLink;
    int *nombrePic;
    int *nombreVid;
}LinkLibrary;
char* filename_dynamic(char * type,int i );
char* filename_dynamic_container(char * type,int i,char* ext );
void get_code_in_file(char* url,int i,char* begin_tag );
void treatment(char * url_find ,char * begin_tag,FILE* file,    int nb_url );
char * get_extension(char * url );
int is_exist_in_file(FILE * file ,char * url);
//char *filename_dynamic(char * type,int i );
void saveImg(char* url,int i,char * begin_tag );
void extract_all(char *url,char* filename,char* begin_tag,char * src_or_href) ;
int check_begin(int begin_tag,int end_tag,char*  code_html,int i,int pos_href);
void initString(StringRes *s);
size_t writefunc(void *ptr, size_t size, size_t nmemb, StringRes *s);
char *getHtmlCode(char* url);
void extract_first_title(char *  code_html,FILE* file,char * title_level);
int position_of_symbole(int begin ,char *code_html,char char_to_find);
int position_of_attribut(int begin,int end,char* code_html, char *  attr_to_find);
void extract_href(char * code_html,FILE* file,char* search_begin_tag,char * typeHrefOrSrc);
#endif // HEADER_H_INCLUDED