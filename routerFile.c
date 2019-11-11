#include "header.h"
/**
 * @author Rani Kharsa
 * @param type
 * @param i
 * @return path
 * @brief permit to redirect toward the path
 */

char* filenameDynamicTxt(char * type,int i ){
    char *str=malloc(sizeof(char)*50);

    if(!strcmp("a",type)){
        sprintf(str, "download/linkOfAllTag/link%d.txt", i);
    }else if (!strcmp("img",type)){
        sprintf(str, "download/linkOfAllTag/img%d.txt", i);
    }else if(!strcmp("link",type)){
        sprintf(str, "download/linkOfAllTag/css%d.txt", i);
    }else if(!strcmp("script",type)){
        sprintf(str, "download/linkOfAllTag/js%d.txt", i);
    }else if(!strcmp("source",type)){
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
char* filenameDynamicContainer(char * type,int i,char* ext ){
    char *str=malloc(sizeof(char)*50);

    if (!strcmp("<img",type)){
        if(!strcmp(ext," ")) {
            sprintf(str,"download/imgTag/image%i",i);
        }else{
            sprintf(str,"download/imgTag/image%i.%s",i,ext);
        }
    }else if(!strcmp("<source",type)){
        sprintf(str, "download/sourceTag/video%d.%s", i,ext);
    }
    else if(!strcmp("<link",type)){
        if(!strcmp(ext," ")) {
            sprintf(str, "download/linkTag/link%d.txt", i);
        }else{
            sprintf(str, "download/linkTag/link%d.%s", i,ext);
        }
    }else if(!strcmp("<script",type)){
        sprintf(str, "download/scriptTag/js%d.js", i);
    }else{
        sprintf(str, "download/content/%s%i.txt",type,i);
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

char* getHostUrl(char* url){
    CURLU *h;
    CURLUcode uc;
    char *host;
    h = curl_url(); /* get a handle to work with */
    if(!h)
        return "1";
    /* parse a full URL */
    uc = curl_url_set(h, CURLUPART_URL, "http://example.com/path/index.html", 0);
    /* extract host name from the parsed URL */
    uc = curl_url_get(h, CURLUPART_HOST, &host, 0);
    if(!uc) {
        printf("Host name: %s\n", host);
        curl_free(host);
    }

    curl_url_cleanup(h); /* free url handle */
return host;
}
int deleteRepositorie(char* repositorieName){
    system("rmdir /Q  /S download");
}
int createRepositorie( char* repositorieName){
    system("mkdir download");
    system("cd download && mkdir content");
    system("cd download && mkdir imgTag");
    system("cd download && mkdir scriptTag");
    system("cd download && mkdir linkOfAllTag");
    system("cd download && mkdir linkTag");
    system("cd download && mkdir sourceTag");
return 0;
}