#include "header.h"

/**
 * @author Jerem
 * @param s
 */

void initString(StringRes *s) {
    s->len = 0;
    s->ptr = malloc(s->len+1);
    if (s->ptr == NULL) {
        fprintf(stderr, "malloc() failed\n");
        exit(EXIT_FAILURE);
    }
    s->ptr[0] = '\0';
}
/**
 * @author Jerem
 * @param ptr
 * @param size
 * @param nmemb
 * @param s
 * @return
 */
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

/**
 * @author Rani Kharsa
 * @param url
 * @date 16/10/2019
 * @brief permit to get HTML code from a url
 */
char *getHtmlCode(char* url){
    //open session curl

    CURL *curl =curl_easy_init();

    if(curl){
        StringRes s;
        initString(&s);

        curl_easy_setopt(curl,CURLOPT_URL,url);//work on this url
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER,FALSE);
        CURLcode res = curl_easy_perform(curl);//execute all  the setop
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
}
/**
 * @author Rani Kharsa
 * @param url
 * @param i
 * @param begin_tag
 * @brief permit to save the result of the request in file
 */
void getCodeInFile(char* url,int i ,char* beginTag){
    char filename[200];
    int result;

    strcpy(filename,filenameDynamicContainer(beginTag,i,"rien"));
    FILE* fp = fopen(filename,"w");
    //open session curl=
    CURL *curl =curl_easy_init();
    if(curl){
        curl_easy_setopt(curl,CURLOPT_URL,url);//work on this url
        curl_easy_setopt(curl,CURLOPT_WRITEDATA,fp);
        curl_easy_setopt(curl,CURLOPT_FAILONERROR,1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER,FALSE);
        CURLcode  res= curl_easy_perform(curl);//execute all  the setopt
        if(res!=CURLE_OK){
            fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
        }
        //clean and close session curl
        curl_easy_cleanup(curl);
    }else{
        printf("curl_easy_init() failed");
    }
    fclose(fp);
}
/**
 * @author Rani Kharsa
 * @param url
 * @return extension
 * @brief get extension of img or video
 */
char * getExtension(char * url ){
    char * ext;
    char delim[] = ".";
    char *ptr = strtok(url, delim);
    while(ptr != NULL)
    {
        ext=ptr;
        ptr = strtok(NULL, delim);
    }
    if(strlen(ext)>5)
        return " ";
    //printf("%s\n",ext);
    return ext;
}
/**
 * @author Rani Kharsa
 * @param url
 * @param i
 * @param begin_tag
 * @brief save media in local
 */
void saveMedia(char* url,int i,char* beginTag ){//verif type mime
    CURL *curl ;
    char *urlCpy=malloc(sizeof(char)*200);
    strcpy(urlCpy,url);
    char* ext=getExtension(url);
    char filename[200];
    int result;
    strcpy(filename,filenameDynamicContainer(beginTag,i,ext ));
  //  printf("url cpy   %s\n filename : %s\n extt: %s",urlCpy,filename,ext);
    FILE* fp=fopen(filename,"wb");
    curl=curl_easy_init();
    curl_easy_setopt(curl,CURLOPT_URL,urlCpy);
    curl_easy_setopt(curl,CURLOPT_WRITEDATA,fp);
    curl_easy_setopt(curl,CURLOPT_FAILONERROR,1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER,FALSE);
    result=curl_easy_perform(curl);
    if(result==CURLE_OK){
        printf("Download successful\n");
    }else{
        printf("ERROR: %s\n",curl_easy_strerror(result));
    }
    fclose(fp);
    curl_easy_cleanup(curl);
}