#include "header.h"

void execute(char** tabaction){
    for(int i=0;i<4;++i){
        printf("###############%s#####################\n",tabaction[i]);
        //essayer de mettre en place une barre de progression du style [#########]
        extractAll("https://www.marmiton.org/recettes/recette_pizza-aux-3-fromages_31450.aspx", tabaction[i]);
    }
}
/**
 * @author Rani Kharsa
 * @param url
 * @brief extract all what  we need
 */
void extractAll(char *url,char* tag) {
    char *codeHtml = getHtmlCode(url);
    char *srcOrHref=malloc(sizeof(char)*50);
    strcpy(srcOrHref,hrefOrSrcRouter(tag));
    char *beginTag = malloc(sizeof(char)*strlen(tag)+10);
    sprintf(beginTag,"<%s\0",tag);
    char* filename=malloc(sizeof(char)*40);
    strcpy(filename,filenameDynamicTxt(tag,1));

    FILE * file = fopen(filename,"w+");
    if(file!=NULL) {
      // extractContentBetweenTag(codeHtml,0,"<header","</header>");
      extractLink(codeHtml,file,beginTag,srcOrHref);
        fclose(file);
    }
}
char* trim_space(char *str,int taille ) {
    int beginSave=0,counter=0;
    char* newStr= malloc(sizeof(char)*taille);
    for (int i = 0; i <strlen(str) ; i++) {
        if(str[i]!=' ' || beginSave==1){
            beginSave=1;
            newStr[counter]=str[i];
            counter++;
        }
    }

    for ( int j= strlen(newStr) ; 0<j ; j--) {
        if(newStr[j]!=32 && newStr[j]!=0){
            break;
        }

    }
 printf("%s strlen %d",newStr,strlen(newStr));
    return newStr;

}
/**
 * @author Rani Kharsa
 * @param code_html
 * @param file
 * @param title_level
 * @brief extract all between a tag
 */
 void extractContentBetweenTag(char *  codeHtml,int number,char* beginTag,char * endTag){
     int i,end,begin,findBeginSave;
     char *searchBeginTag =beginTag,*tagOpen = codeHtml;
    char *searchEndTag =endTag,*tagEnd = codeHtml;
    FILE* file = fopen("download/content.txt","w");
    if(file!=NULL){
        while ((tagOpen=strstr(tagOpen,searchBeginTag))!= NULL && (tagEnd=strstr(tagEnd,searchEndTag))!=NULL){
            begin=tagOpen-codeHtml;
            end=tagEnd-codeHtml;
            findBeginSave=0;
            for(i=begin;i<end;i++){
                if(findBeginSave==1) {
                    if (codeHtml[i] == '<'){
                        findBeginSave=0;
                        continue;
                    }
                    fputc(codeHtml[i], file);
                }else{
                    if (codeHtml[i] == '>') {
                        findBeginSave = 1;
                    }
                }
            }
            fputc('\n', file);
            tagOpen+= strlen(searchBeginTag);
            tagEnd+=strlen(searchEndTag);
        }
        fclose(file);
    }

 }
 /**
  * @author Rani Kharsa
  * @param code_html
  * @param file
  * @param search_begin_tag
  * @param typeHrefOrSrc
  * @brief extract all link
  */
    void extractLink(char *codeHtml, FILE *file, char *searchBeginTag, char *typeHrefOrSrc) {
        int beginTag, endTag,nbUrl=0,posHref,posRel;
        const char *toSearch = searchBeginTag, *p = codeHtml;
        while ((p = strstr(p, toSearch)) != NULL) {
            beginTag = p - codeHtml;
            endTag = positionOfSymbole(beginTag, codeHtml, '>');
            if (endTag == -1) {
                p += strlen(toSearch);
                continue;
            }
            posHref= positionOfAttribut(beginTag,endTag,codeHtml, typeHrefOrSrc);
            if(posHref!=-1){
                process(beginTag,endTag,codeHtml,searchBeginTag,file,&nbUrl,&p,toSearch,posHref);
            }

            p += strlen(toSearch);
        }
        }

/**
* @author Rani kharsa
* @param begin_tag
* @param end_tag
* @param code_html
* @param search_begin_tag
* @param file
* @param nb_url
* @param p
* @param to_search
* @param pos_href
*/
void process(int beginTag,int endTag,char* codeHtml,char* searchBeginTag,FILE*file,int* nbUrl,const char**p,char const*toSearch,int posHref){
    int findBeginSave=0,counter=0,http,pos=0;
    char*url_find=malloc(sizeof(char)*500);
    for(int i=posHref-beginTag;i<endTag-beginTag;i++){
        pos=i+beginTag;
        // printf("%d\n ",pos);
        if(findBeginSave==1){
            if(codeHtml[pos]=='\"'||codeHtml[pos]=='\''){
                url_find[counter]='\0';
                treatment(url_find,searchBeginTag,file,*nbUrl);
                *p+=strlen(toSearch);
                break;
            }else{
                url_find[counter]=codeHtml[pos];
                counter++;
            }
        }else{
            http=checkBegin(beginTag,endTag,codeHtml,pos,posHref);
            if(http!=-1){
                i=http-1-beginTag;
                *nbUrl=*nbUrl+1;
                findBeginSave=1;
            }
        }
    }
    free(url_find);
}
        /**
      * @author Rani kharsa
      * @param url_find
     * @param begin_tag
     * @param file
     * @param nb_url
     */
void treatment(char * urlFind ,char * beginTag,FILE* file,    int nbUrl ) {
    //traitement des ext ici
    printf("%s\n",urlFind);
    if (!strcmp(beginTag, "<img") || !strcmp(beginTag,"<source")) {
        fprintf(file, "%s \n", urlFind);
        saveMedia(urlFind,nbUrl,beginTag);
    } else if (!strcmp(beginTag, "<a") ) {
        fprintf(file, "%s \n", urlFind);
    }else if (!strcmp(beginTag, "<link") || !strcmp(beginTag,"<script")) {
        fprintf(file, "%s \n", urlFind);
        getCodeInFile(urlFind,nbUrl,beginTag);
    }
}

/**
 * @author Rani kharsa
 * @param begin_tag
 * @param end_tag
 * @param code_html
 * @param i
 * @param pos_href
 * @return  position of http
 */
int checkBegin(int beginTag, int endTag, char *codeHtml, int i,int posHref) {
        int http;
            if (codeHtml[i + (beginTag- posHref)] == '\'' || codeHtml[i + (beginTag - posHref)] == '"') {
                http = positionOfAttribut(i + (beginTag - posHref), endTag, codeHtml, "http");
                if (http != -1) {
                    return http;
                }
        }
        return -1;
 }



/**
 * @author Rani Kharsa
 * @param begin
 * @param end
 * @param code_html
 * @param attr_to_find
 * @return position
 * @brief give the position of world in string
 */
    int positionOfAttribut(int begin, int end, char *codeHtml, char *attrToFind) {
        char *str = malloc(sizeof(char) * (end - begin));
        int position, counter = 0;
        for (int i = begin; i < end; i++) {
            str[counter] = codeHtml[i];
            counter++;
        }
        const char *p = str;
    //    printf("\n%s\n",str);
        p = strstr(p, attrToFind);
        position = p - str + begin;//essayer - counter
        if (p != NULL)
            return position;
        return -1;

    }
/**
 * @author Rani Kharsa
 * @param begin
 * @param code_html
 * @param char_to_find
 * @return postion
 * @brief give the position of the symbole in the string
 */
    int positionOfSymbole(int begin, char *codeHtml, char charToFind) {
        for (int i = 0; i <500 ; i++) {
            if (charToFind != '>' && i == 10) {
                return -1;
            }
            if (codeHtml[ begin +i] == '>') {
                return begin + i;
            }
        }
        return -1;
    }
