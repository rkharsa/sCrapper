#include "header.h"


/**
 * @author Rani Kharsa
 * @param url
 * @date 16/10/2019
 * @brief permit to get HTML code from a url
 */


/*

void initString(StringRes *s) {
    s->len = 0;
    s->ptr = malloc(s->len+1);
    if (s->ptr == NULL) {
        fprintf(stderr, "malloc() failed\n");
        exit(EXIT_FAILURE);
    }
    s->ptr[0] = '\0';
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, StringRes *s) {
    size_t new_len = s->len + size * nmemb;
    s->ptr = realloc(s->ptr, new_len + 1);
    if (s->ptr == NULL) {
        fprintf(stderr, "realloc() failed\n");
        exit(EXIT_FAILURE);
    }
    memcpy(s->ptr + s->len, ptr, size * nmemb);
    s->ptr[new_len] = '\0';
    s->len = new_len;

    return size * nmemb;
}


char *getHtmlCode(char* url){
    //open session curl
    CURL *curl =curl_easy_init();
    if(curl){
        StringRes s;
        initString(&s);

        curl_easy_setopt(curl,CURLOPT_URL,url);//work on this url
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
        CURLcode res = curl_easy_perform(curl);//execute all  the setopt
        if(res!=CURLE_OK){
            fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
        }
        //clean and close session curl
        curl_easy_cleanup(curl);
        return s.ptr;
    }else{
        printf("curl_easy_init() failed");
        return NULL;
    }
}*/
