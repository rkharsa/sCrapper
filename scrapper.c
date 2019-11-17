#include "header.h"
/**
 * file who group all algorithm of  scrapping
 */
/**
 *@author Rani Kharsa
 * @param tabaction
 * @param url
 * @param taille
 * @param folder
 * @param toSearchMime
 */
void execute(char** tabaction, char* url, int taille, char* folder,char* toSearchMime) {

    printf("EXECUTE\n");
    CounterFile counterFile = initCounterFile();
    for (int i = 0; i < taille; i++) {
        printf("%s\n", "--------------------------------------------------------------");
        printf("                                %s  \n", tabaction[i]);
        printf("%s\n", "--------------------------------------------------------------");
        //essayer de mettre en place une barre de progression du style [#########]
        extractAll(url, tabaction[i], &counterFile, folder,toSearchMime);
    }
}
/**
 * @author Rani Kharsa
 * @param tag
 * @return begin tag
 * @example
 * tag = a
 * return <a
 */
char* getBeginTag(char* tag) {
    char* beginTag = malloc(sizeof(char) * strlen(tag) + 10);
    sprintf(beginTag, "<%s", tag);
    return beginTag;
}
/**
 * @author Rani Kharsa
 * @param tag
 * @return end tag
 * @example
 * tag = a
 * return </a>
 */
char* getEndTag(char* tag) {
    char* beginTag = malloc(sizeof(char) * strlen(tag) + 10);
    sprintf(beginTag, "</%s>", tag);
    return beginTag;
}

/**
 * @author Rani Kharsa
 * @param url
 * @brief extract all what  we need
 */

void extractAll(char* url, char* tag, CounterFile* counterFile, char* folder,char*toSearchMime) {
    printf("EXTRACT ALL\n");
    char* codeHtml = getHtmlCode(url);
    counterIncrem(counterFile, " ");
    if (!strcmp(tag, "img") || !strcmp(tag, "source") || !strcmp(tag, "a") || !strcmp(tag, "script") ||
        !strcmp(tag, "link")) {
        FILE* file = fopen(filenameDynamicTxt(folder, tag, *routerCounter(counterFile, " ")), "w+");
        if (file != NULL) {
            extractLink(codeHtml, file, tag, counterFile, folder,url,toSearchMime);
            fclose(file);
        } else {
            printf("Can't open the file");
        }
    } else {
        extractContentBetweenTag(codeHtml, counterFile->nbContent, tag, folder);
        counterIncrem(counterFile, "content");
    }

}
/**
 * @author Rani Kharsa
 * @param counterSpace
 * @param value
 * @brief  count the number of space between 2 char
 */
void counterSpaceFunc(int* counterSpace, char value) {
    if (value == ' ' || value == 9) {
        *counterSpace += 1;
    } else {
        if (value != '\n') {
            *counterSpace = 0;
        }

    }
}
/**
 * @author Rani Kharsa
 * @param counterReturnLine
 * @param value
 * @brief count the number of line break
 */
void counterReturnLineFunc(int* counterReturnLine, char value) {
    if (value == '\n') {
        *counterReturnLine += 1;
    } else {
        if (value != ' ' && value != 9 && value != 13) {
            *counterReturnLine = 0;
        }
    }
}
/**
 * @author Rani Kharsa
 * @param posBeginTag
 * @param posEndTag
 * @param codeHtml
 * @param file
 * @brief save  the content text between 2 tag
 */
void saveContent(int posBeginTag, int posEndTag, char* codeHtml, FILE* file) {
    int counterSpace = 0, counterReturnLine = 0;
    int findBeginSave = 0;
    for (int i = posBeginTag; i < posEndTag; i++) {
        if (findBeginSave == 1) {
            if (codeHtml[i] == '<') {
                findBeginSave = 0;
                continue;
            }
            counterSpaceFunc(&counterSpace, codeHtml[i]);
            counterReturnLineFunc(&counterReturnLine, codeHtml[i]);
            if (counterReturnLine < 2 && counterSpace < 2) {
                fputc(codeHtml[i], file);
            }
        } else {
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
void extractContentBetweenTag(char* codeHtml, int number, char* tag, char* folder) {
    int end, begin;
    char* searchBeginTag = getBeginTag(tag), * tagOpen = codeHtml;
    char* searchEndTag = getEndTag(tag), * tagEnd = codeHtml;

    FILE* file = fopen(filenameDynamicContainer(folder, tag, number, "txt"), "w+");
    if (file != NULL) {
        while ((tagOpen = strstr(tagOpen, searchBeginTag)) != NULL && (tagEnd = strstr(tagEnd, searchEndTag)) != NULL) {
            begin = tagOpen - codeHtml;
            end = tagEnd - codeHtml;
            saveContent(begin, end, codeHtml, file);
            tagOpen += strlen(searchBeginTag);
            tagEnd += strlen(searchEndTag);
        }
        fclose(file);
        printf("%s\n", "Download successful");
    }
 }
 /**
  * @author Rani Kharsa
  * @param i
  * @param posEndTag
  * @param urlFind
  * @param url
  * @param codeHtml
  * @param counter
  * @param findBeginSave
  * @brief check if link have a good begin pattern
  */
void checkBeginLink(int* i,int posEndTag ,char**urlFind,char* url,char* codeHtml,int* counter,int *findBeginSave){
    int http;
    if ((codeHtml[*i] == '"' || codeHtml[*i]=='\'') && codeHtml[*i+1]!='#') {
        http=positionOfAttribut(*i,posEndTag,codeHtml,"http");
        if(http!=-1){
            if(codeHtml[http+5]!='&' && ((codeHtml[http+5]==':' && codeHtml[http+6]=='/') || (codeHtml[http+6]==':' && codeHtml[http+7]=='/'))) {
                *findBeginSave = 1;
            }
            return;
        } else if(codeHtml[*i+1]=='/' ){
            strcpy(*urlFind,getBeginUrl(url));
            *counter=(int)strlen(*urlFind);
            *findBeginSave=1;
        }
    }
}
/**
 * @author Rani Kharsa
 * @param posBeginTag
 * @param posEndTag
 * @param codeHtml
 * @param file
 * @param url
 * @param tag
 * @param folder
 * @param counterFile
 * @param toSearchMime
 * @brief permit to find url and then make a treatment
 */
void saveLink(int posBeginTag,int posEndTag,char* codeHtml,FILE* file,char* url,char* tag,char*folder,
        CounterFile* counterFile,char* toSearchMime ){
    int findBeginSave=0,counter=0;
    char* urlFind=malloc(sizeof(char)*400);
    for(int i=posBeginTag;i<posEndTag;i++){
        if(findBeginSave==1) {
            if (codeHtml[i] == '"' || codeHtml[i]=='\'' ) {
                urlFind[counter]='\0';
                if(strlen(urlFind)!=0){
                    treatment(urlFind,tag,file,counterFile,folder,toSearchMime);
                }
                break;
            }
            urlFind[counter]=codeHtml[i];
            counter++;
        }else{
            checkBeginLink(&i,posEndTag,&urlFind,url,codeHtml,&counter,&findBeginSave);
        }
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

 void extractLink(char *  codeHtml,FILE*file ,char *tag,CounterFile* counterFile,char * folder,char*url,char* toSearchMime) {
     printf("EXTRACTLINK\n");
     int end, begin, posHref;
     char *searchBeginTag = getBeginTag(tag), *tagOpen = codeHtml;
     if (file != NULL) {
         while ((tagOpen = strstr(tagOpen, searchBeginTag)) != NULL) {
             begin = tagOpen - codeHtml;
             end = positionOfSymbole(begin, codeHtml, '>');
             if (end != -1) {
                 posHref = positionOfAttribut(begin, end, codeHtml, hrefOrSrcRouter(tag));
                 if (posHref != -1) {
                     saveLink(posHref, end, codeHtml, file,url,tag,folder,counterFile,toSearchMime);
                 }
             }
             tagOpen += strlen(searchBeginTag);
         }
     }
 }

/**
* @author Rani kharsa
* @param url_find
* @param begin_tag
* @param file
* @param nb_url
 * @brief redirection  to the good function for save
*/
void treatment(char* urlFind, char* tag, FILE* file, CounterFile* counterFile, char* folder,char* toSearchMime) {
    printf("%s \n", urlFind);
    int* counter = routerCounter(counterFile, tag);
    if (!strcmp(tag, "img") || !strcmp(tag, "source")) {

        if(strcmp(toSearchMime, "0") == 0 || verifTypeMime(urlFind, toSearchMime) == 1) {
            fprintf(file, "%s \n", urlFind);
            saveMedia(urlFind, *counter, tag, folder,toSearchMime);
            counterIncrem(counterFile, tag);
        }

    } else if (!strcmp(tag, "a")) {

            fprintf(file, "%s \n", urlFind);
            printf("%s\n", "Download successful");

    } else if (!strcmp(tag, "link") || !strcmp(tag, "script")) {

        char* urlCpy = malloc(sizeof(char) * strlen(urlFind) + 10);
        strcpy(urlCpy, urlFind);
        if (!strcmp(getExtension(urlFind), "png") || !strcmp(getExtension(urlFind), "ico") ||
            !strcmp(getExtension(urlFind), "svg")) {

            fprintf(file, "%s \n", urlCpy);
            saveMedia(urlCpy, *counter, tag, folder,toSearchMime);

        } else {

            fprintf(file, "%s \n", urlCpy);
            getCodeInFile(urlCpy, *counter, tag, folder,toSearchMime);
        }
        counterIncrem(counterFile,tag);

    }

}



/**
 * @author Rani Kharsa
 * @param begin
 * @param end
 * @param code_html
 * @param attr_to_find
 * @return position
 * @brief give the position of world in string  between 2 positions
 */
int positionOfAttribut(int begin, int end, char* codeHtml, char* attrToFind) {
    char* str = malloc(sizeof(char) * (end - begin));
    int position,pos, counter = 0;
    for (int i = begin; i < end; i++) {
        str[counter] = codeHtml[i];
        counter++;
    }
    const char* p = str;
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
            if (codeHtml[ begin +i] == charToFind) {
                return begin + i;
            }
        }
        return -1;
 }