#include "header.h"

/**
 * @author Jerem
 * @param s
 */

void initString(StringRes* s) {
    s->len = 0;
    s->ptr = malloc(s->len + 1);
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
size_t writefunc(void* ptr, size_t size, size_t nmemb, StringRes* s) {
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
char* getHtmlCode(char* url) {
    //open session curl

    CURL* curl = curl_easy_init();

    if (curl) {
        StringRes s;
        initString(&s);

        curl_easy_setopt(curl, CURLOPT_URL, url);//work on this url
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER,0);
        //curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION,1L);

        CURLcode res = curl_easy_perform(curl);//execute all  the setop
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        //clean and close session curl

        return s.ptr;
    } else {
        printf("curl_easy_init() failed");
        return NULL;
    }
    curl_easy_cleanup(curl);
}

/**
 * @author Rani Kharsa
 * @param url
 * @param i
 * @param begin_tag
 * @brief permit to save the result of the request in file
 */
void getCodeInFile(char* url, int i, char* tag, char* folder,char* toSearchMime) {
    if(!strcmp(toSearchMime ,"0") || verifTypeMime(url, toSearchMime, getTypeMime(url)) == 1 ) {
        char filename[200];
        int result;
        char *urlCpy = malloc(sizeof(char) * strlen(url) + 10);
        strcpy(urlCpy, url);

        strcpy(filename, filenameDynamicContainer(folder, tag, i, getExtension(url)));
        FILE *fp = fopen(filename, "w");
        //open session curl
        if (fp != NULL) {
            CURL *curl = curl_easy_init();
            if (curl) {
                curl_easy_setopt(curl, CURLOPT_URL, urlCpy);//work on this url
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
                curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);
                curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
                //    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION,1L);
                CURLcode res = curl_easy_perform(curl);//execute all  the setopt
                if (res != CURLE_OK) {
                    fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
                } else {
                    printf("Download successful\n");
                }
                //clean and close session curl

            } else {
                printf("curl_easy_init() failed");
            }
            curl_easy_cleanup(curl);
            fclose(fp);
        } else {
            printf("Can't open the file file :%s \n", filename);
        }
    }
}

/**
 * @author Rani Kharsa
 * @param url
 * @return extension
 * @brief get extension of img or video
 */
char* getExtension(char* url) {
    char* ext=malloc(sizeof(char)*10);
    char delim[] = ".";
    char* ptr = strtok(url, delim);
    while (ptr != NULL) {
        ext = ptr;
        ptr = strtok(NULL, delim);
    }
    if (strlen(ext) >= 4 || strstr(ext, "com") != NULL)
        return " ";
    //printf("%s\n",ext);
    return ext;
}
char* getTypeMime(char *url){
    char *ct = NULL;
    int res;
   CURL *curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);//work on this url
        curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
        res = curl_easy_perform(curl);

        if(res==CURLE_OK) {

            res = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &ct);
            if(!res && ct) {
                printf("Content-Type: %s\n", ct);
            }
        }else{
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        curl_easy_cleanup(curl);
    }else{
        printf("\nerreur curlllll\n");
    }

    return ct;
}
int verifTypeMime(char *url,char*typeMimeToSearch, char* typeMime){
    int itThisType=0;
    printf(" lurl buh %s",url);
    if(strcmp(typeMimeToSearch, "0") != 0) {

        if (strstr(typeMime, typeMimeToSearch) != NULL) {
            itThisType = 1;
        }
    }
    //printf("\ntype mimmei verif %s\n", getTypeMime(url));

    return itThisType;
}

/**
 * @author Rani Kharsa
 * @param url
 * @param i
 * @param begin_tag
 * @brief save media in local
 */
void saveMedia(char* url, int i, char* tag, char* folder,char* toSearchMime) {//verif type mime
  if(!strcmp(toSearchMime ,"0") || verifTypeMime(url, toSearchMime, getTypeMime(url)) == 1 ){
      CURL* curl;
      curl = curl_easy_init();
      char* urlCpy = malloc(sizeof(char) * strlen(url) + 10);
      strcpy(urlCpy, url);
      char* ext = getExtension(url);
      char filename[200];
      int result;
      strcpy(filename, filenameDynamicContainer(folder, tag, i, ext));
      //  printf("url cpy   %s\n filename : %s\n extt: %s",urlCpy,filename,ext);
      FILE* fp = fopen(filename, "wb");
      if (fp != NULL) {
          curl_easy_setopt(curl, CURLOPT_URL, urlCpy);
          curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
          curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);
          curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
          // curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
          result = curl_easy_perform(curl);
          if (result == CURLE_OK) {
              printf("Download successful\n");
          } else {
              printf("ERROR: %s\n", curl_easy_strerror(result));
          }
          fclose(fp);
      } else {
          printf("Can't open  the file\n");
      }
      curl_easy_cleanup(curl);
  }

}



char* getHostName(char* url ){
    CURLU *h;
    CURLUcode uc;
    char *host;
    char *path;

    h = curl_url(); /* get a handle to work with */
    if(!h)
        return "1";

    /* parse a full URL */
    uc = curl_url_set(h, CURLUPART_URL, url, 0);

    /* extract host name from the parsed URL */
    uc = curl_url_get(h, CURLUPART_HOST, &host, 0);

    curl_url_cleanup(h);
    return host;

}

char* getBeginUrl(char *url,int slash){
    char *beginUrl=malloc (sizeof(char)*strlen(url));
    char *httpsOrHttp=malloc (sizeof(char)*7);
    if(strstr(url, "https")!=NULL){
        httpsOrHttp="https";
    }else if (strstr(url, "http")!=NULL){
        httpsOrHttp="http";
    }
        sprintf(beginUrl, "%s://%s",httpsOrHttp,getHostName(url) );


    return beginUrl;
}
