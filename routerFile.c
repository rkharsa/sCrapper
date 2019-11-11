#include "header.h"
/**
 * @author Rani Kharsa
 * @param type
 * @param i
 * @return path
 * @brief permit to redirect toward the path
 */

char* filenameDynamicTxt(char * tag,int i ){
    char *str=malloc(sizeof(char)*50);

    if(!strcmp("a",tag)){
        sprintf(str, "download/linkOfAllTag/link%d.txt", i);
    }else if (!strcmp("img",tag)){
        sprintf(str, "download/linkOfAllTag/img%d.txt", i);
    }else if(!strcmp("link",tag)){
        sprintf(str, "download/linkOfAllTag/css%d.txt", i);
    }else if(!strcmp("script",tag)){
        sprintf(str, "download/linkOfAllTag/js%d.txt", i);
    }else if(!strcmp("source",tag)){
        sprintf(str, "download/linkOfAllTag/video%d.txt", i);
    }
    return str;
}
/**
 * @author Rani Kharsa
 * @param type
 * @param i
 * @param ext
 * @return path
 * @brief permit to redirect toward the path
 */
char* filenameDynamicContainer(char * tag,int i,char* ext ){
    char *str=malloc(sizeof(char)*50);

    if (!strcmp("img",tag)){
        if(!strcmp(ext," ")) {
            sprintf(str,"download/imgTag/image%i",i);
        }else{
            sprintf(str,"download/imgTag/image%i.%s",i,ext);
        }
    }else if(!strcmp("source",tag)){
        sprintf(str, "download/sourceTag/video%d.%s", i,ext);
    }
    else if(!strcmp("link",tag)){
        if(!strcmp(ext," ")) {
            sprintf(str, "download/linkTag/link%d.txt", i);
        }else{
            sprintf(str, "download/linkTag/link%d.%s", i,ext);
        }
    }else if(!strcmp("script",tag)){
        sprintf(str, "download/scriptTag/js%d.js", i);
    }else{
        sprintf(str, "download/content/%s%i.txt",tag,i);
    }

    return str;
}
/**
 * @author Rani kharsa
 * @param tag
 * @return src or href
 */
char* hrefOrSrcRouter(char * tag){
    char *str=malloc(sizeof(char)*50);
    if (!strcmp("a",tag) || !strcmp("link",tag) ){
       sprintf(str,"href");
    }
   else if(!strcmp("script",tag) || !strcmp("source",tag) || !strcmp("img",tag) ){
        sprintf(str,"src");
    }

    return str;
}


int deleteRepositorie(char* repositorieName){
    char* command=malloc(sizeof(char)*200);
    sprintf(command, "rmdir /Q  /S %s",repositorieName);
    system(command);
}
int createRepositorie( char* repositorieName){

     char* command=malloc(sizeof(char)*200);
    sprintf(command, "mkdir %s && "
                     "cd %s && mkdir content && mkdir imgTag "
                     "&& mkdir scriptTag "
                     "&& mkdir linkofAllTag "
                     "&& mkdir linkTag "
                     "&& mkdir sourceTag ",repositorieName,repositorieName);
    system(command);


    return 0;
}