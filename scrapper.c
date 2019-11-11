#include "header.h"

void actionTodo(){
//lister les actiones demander pour une  url

}



void execute(char** tabaction,char*url,int taille){
    CounterFile counterFile=initCounterFile();
    for(int i=0;i<taille;i++){
        printf("%s\n","--------------------------------------------------------------");
        printf("                                %s  \n",tabaction[i]);
        printf("%s\n","--------------------------------------------------------------");
        //essayer de mettre en place une barre de progression du style [#########]
        extractAll(url, tabaction[i],&counterFile);
    }
}
char *  getBeginTag(char* tag){
    char *beginTag = malloc(sizeof(char)*strlen(tag)+10);
    sprintf(beginTag,"<%s",tag);
    return beginTag;
}
char *  getEndTag(char* tag){
    char *beginTag = malloc(sizeof(char)*strlen(tag)+10);
    sprintf(beginTag,"</%s>",tag);
    return beginTag;
}
/**
 * @author Rani Kharsa
 * @param url
 * @brief extract all what  we need
 */
void extractAll(char *url,char* tag,CounterFile* counterFile) {
    char *codeHtml = getHtmlCode(url);
counterIncrem(counterFile," ");
    if(!strcmp(tag,"img") || !strcmp(tag,"source")|| !strcmp(tag,"a")|| !strcmp(tag,"script")|| !strcmp(tag,"link")) {
        FILE * file = fopen(filenameDynamicTxt(tag,*routerCounter(counterFile," ")),"w+");
        if (file != NULL) {
           extractLink(codeHtml, file, tag,counterFile);
            fclose(file);
        }else{
            printf("Can't open the file");
        }
    }else{
        extractContentBetweenTag(codeHtml,counterFile->nbContent,tag);
        counterIncrem(counterFile,"<content");
       }

    }

void counterSpaceFunc(int * counterSpace,char value){
    if(value==' ' || value==9 ){
        *counterSpace+=1;
    }else{
        if(value!='\n' ){
            *counterSpace=0;
        }

    }
}

void counterReturnLineFunc(int * counterReturnLine,char value){
    if(value=='\n' ){
        *counterReturnLine+=1;
    }else {
        if (value != ' ' && value!=9  && value!=13) {
            *counterReturnLine = 0;
        }
    }
}
void saveContent(int posBeginTag,int posEndTag,char* codeHtml,FILE* file){
    int counterSpace=0,counterReturnLine=0;
    int findBeginSave=0;
    for(int i=posBeginTag;i<posEndTag;i++){
        if(findBeginSave==1) {
            if (codeHtml[i] == '<' ){
                findBeginSave=0;
                continue;
            }
            counterSpaceFunc(&counterSpace,codeHtml[i]);
            counterReturnLineFunc(&counterReturnLine,codeHtml[i]);
            if(counterReturnLine<2 && counterSpace <2){
                fputc(codeHtml[i], file);
            }
        }else{
            if (codeHtml[i] == '>') {
                findBeginSave = 1;
            }
        }
    }
    fputc('\n', file);
}
/**
 * @author Rani Kharsa
 * @param code_html
 * @param file
 * @param title_level
 * @brief extract all between a tag
 */
 /* si il a plus de 6 espace il arrete d'enregistrer et reprends quand il rencontre des lettres*/
 void extractContentBetweenTag(char *  codeHtml,int number,char *tag){
     int end,begin;
     char *searchBeginTag =getBeginTag(tag),*tagOpen = codeHtml;
    char *searchEndTag =getEndTag(tag),*tagEnd = codeHtml;

    FILE* file = fopen(filenameDynamicContainer(tag,number,"txt"),"w+");
        if(file!=NULL){
        while ((tagOpen=strstr(tagOpen,searchBeginTag))!= NULL && (tagEnd=strstr(tagEnd,searchEndTag))!=NULL){
            begin=tagOpen-codeHtml;
            end=tagEnd-codeHtml;
            saveContent(begin,end,codeHtml,file);
            tagOpen+= strlen(searchBeginTag);
            tagEnd+=strlen(searchEndTag);
        }
        fclose(file);
        printf("%s\n","Download successful");
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
    void extractLink(char *codeHtml, FILE *file, char *tag,CounterFile* counterFile) {
        int beginTag, endTag,posHref;
        const char *toSearch = getBeginTag(tag), *p = codeHtml;
        while ((p = strstr(p, toSearch)) != NULL) {
            beginTag = p - codeHtml;
            endTag = positionOfSymbole(beginTag, codeHtml, '>');
            if (endTag == -1) {
                p += strlen(toSearch);
                continue;
            }
            posHref= positionOfAttribut(beginTag,endTag,codeHtml, hrefOrSrcRouter(tag));
            if(posHref!=-1){
                process(beginTag,endTag,codeHtml,tag,file,&p,toSearch,posHref,counterFile);
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
void process(int beginTag,int endTag,char* codeHtml,char* tag,FILE*file,const char**p,char const*toSearch,int posHref,CounterFile* counterFile){
    int findBeginSave=0,counter=0,http,pos=0;
    char*url_find=malloc(sizeof(char)*400);
    for(int i=posHref-beginTag;i<endTag-beginTag;i++){
        pos=i+beginTag;
        // printf("%d\n ",pos);
        if(findBeginSave==1){
            if(codeHtml[pos]=='\"'||codeHtml[pos]=='\''){
                url_find[counter]='\0';
                treatment(url_find,tag,file,counterFile);
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
void treatment(char * urlFind ,char * tag,FILE* file,CounterFile* counterFile ) {
    printf("%s \n",urlFind);
    int * counter=routerCounter(counterFile,tag);
    if (!strcmp(tag, "img") || !strcmp(tag,"source")) {
        fprintf(file, "%s \n", urlFind);
        saveMedia(urlFind,*counter,tag);
        counterIncrem(counterFile,tag);
    } else if (!strcmp(tag, "a") ) {
        fprintf(file, "%s \n", urlFind);
        printf("%s\n","Download successful");
    }else if (!strcmp(tag, "link") || !strcmp(tag,"script")) {
        char *urlCpy=malloc(sizeof(char)*strlen(urlFind)+10);
        strcpy(urlCpy,urlFind);
        if(!strcmp(getExtension(urlFind),"png")||  !strcmp(getExtension(urlFind),"ico") || !strcmp(getExtension(urlFind),"svg")){
            fprintf(file, "%s \n", urlCpy);
            saveMedia(urlCpy,*counter,tag);
        }else{
            fprintf(file, "%s \n", urlCpy);
            getCodeInFile(urlCpy,*counter,tag);
        }
        counterIncrem(counterFile,getBeginTag(tag));
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
                    if(codeHtml[http+5]!='&'){
                        return http;
                    }
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
        p = strstr(p, attrToFind);
        position = p - str + begin;
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
