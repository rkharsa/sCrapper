#include "header.h"
/**
 * @author Rani Kharsa
 * @param url
 * @date 16/10/2019
 * @brief permit to get HTML code from a url
 */
void getHtmlCode(char* url){
    //open session curl
    CURL *curl =curl_easy_init();
    if(curl){
        curl_easy_setopt(curl,CURLOPT_URL,url);//work on this url
        CURLcode  res= curl_easy_perform(curl);//execute all  the setopt
        if(res!=CURLE_OK){
            fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
        }
        //clean and close session curl
        curl_easy_cleanup(curl);
    }else{
        printf("curl_easy_init() failed");
    }
}
void