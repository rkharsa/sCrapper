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
        sprintf(str, "download/link/link%d.txt", i);
    }else if (!strcmp("img",type)){
        sprintf(str, "download/link/img%d.txt", i);
    }else if(!strcmp("link",type)){
        sprintf(str, "download/link/css%d.txt", i);
    }else if(!strcmp("script",type)){
        sprintf(str, "download/link/js%d.txt", i);
    }else if(!strcmp("source",type)){
        sprintf(str, "download/link/video%d.txt", i);
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
            sprintf(str,"download/picture/image%i",i);
        }else{
            sprintf(str,"download/picture/image%i.%s",i,ext);
        }
    }else if(!strcmp("<source",type)){
        sprintf(str, "download/video/video%d.%s", i,ext);
    }
    else if(!strcmp("<link",type)){
        sprintf(str, "download/css/css%d.css", i);
    }else if(!strcmp("<script",type)){
        sprintf(str, "download/js/js%d.js", i);
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

void createRepositorie(){
   // system(md parseur)
}