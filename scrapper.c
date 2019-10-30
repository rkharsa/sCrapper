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
}
void get_code_in_file(char* url,int i ){
    char filename[200];
    int result;

    sprintf(filename,"download/css/style%i.css",1);
    FILE* fp = fopen(filename,"w");
    //open session curl=
    CURL *curl =curl_easy_init();
    printf("%s",url);
    if(curl){
        curl_easy_setopt(curl,CURLOPT_URL,url);//work on this url
        curl_easy_setopt(curl,CURLOPT_WRITEDATA,fp);
        curl_easy_setopt(curl,CURLOPT_FAILONERROR,1L);
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
 * @brief extract all we need
 */
void extract_all(char *url,char *filename,char* begin_tag,char * src_or_href) {
  char *code_html = getHtmlCode(url);
 //printf("%s",code_html);
    //char *code_html = "<meta content=\"text/html; charset=UTF-8\" http-equiv=\"Content-Type\">";
    FILE * file = fopen(filename,"w+");
    if(file!=NULL) {
        //extract_href_from_html(code_html,file);
        //extract_first_title(code_html,file,"1");
       extract_href(code_html,file,begin_tag,src_or_href);
        fclose(file);
    }
}
/* extract all txt in tag extact p h1 h2 h3 h4 h5 h6 strong txthref*/
 void extract_first_title(char *  code_html,FILE* file,char * title_level){
     int i,end,begin,find_begin_save;
     char *search_begin_tag ="<h1",*tag_open = code_html;
    char *search_end_tag ="</h1>",*tag_end = code_html;
     while ((tag_open=strstr(tag_open,search_begin_tag))!= NULL && (tag_end=strstr(tag_end,search_end_tag))!=NULL){
         begin=tag_open-code_html;
         end=tag_end-code_html;
         find_begin_save=0;
         for(i=begin;i<end;i++){
                 if(find_begin_save==1) {
                     if (code_html[i] == '<'){
                         find_begin_save=0;
                         continue;
                     }
                     fputc(code_html[i], file);
                 }else{
                     if (code_html[i] == '>') {
                         find_begin_save = 1;
                     }
                 }
         }
         fputc('\n', file);
         tag_open+= strlen(search_begin_tag);
         tag_end+=strlen(search_end_tag);
     }
 }

/*char *filename_dynamic(char * type,int i ){
    char *str[20];

   if(!strcmp("link",type)){
       sprintf(str, "/download/link/link%d.txt", i);
        return *str ;
    }else if (!strcmp("img",type)){
       sprintf(str, "/download/link/img%d.txt", i);
        return str;
    }else if(!strcmp("css",type)){
       sprintf(str, "/download/link/css%d.txt", i);
        return str;
    }else if(!strcmp("js",type)){
       sprintf(str, "/download/link/js%d.txt", i);
        return str;
    }
}*/
char * get_extension(char * url ){
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
void saveImg(char* url,int i ){//verif type mime
    CURL *curl ;
    char *urlCpy=malloc(sizeof(char)*200);
    strcpy(urlCpy,url);
    char* ext=get_extension(url);
    char filename[200];
    int result;
    if(!strcmp(ext," ")) {
        sprintf(filename,"download/picture/image%i",i);
    }else{
        sprintf(filename,"download/picture/image%i.%s",i,ext);
    }

    printf("%s    %s\n",filename,ext);
    FILE* fp=fopen(filename,"wb");
    curl=curl_easy_init();
    curl_easy_setopt(curl,CURLOPT_URL,urlCpy);
    curl_easy_setopt(curl,CURLOPT_WRITEDATA,fp);
    curl_easy_setopt(curl,CURLOPT_FAILONERROR,1L);

    result=curl_easy_perform(curl);
    if(result==CURLE_OK){
        printf("Download successful\n");
    }else{
        printf("ERROR: %s\n",curl_easy_strerror(result));
    }
    fclose(fp);
    curl_easy_cleanup(curl);
}
void treatment(char * url_find ,char * begin_tag,FILE* file,    int nb_url ) {
        if (!strcmp(begin_tag, "<img")) {
            fprintf(file, "%s \n", url_find);
            saveImg(url_find, nb_url);
        } else if (!strcmp(begin_tag, "<a ") ) {
            fprintf(file, "%s \n", url_find);
        }else if (!strcmp(begin_tag, "<link") || !strcmp(begin_tag,"<script")) {
            fprintf(file, "%s \n", url_find);
            get_code_in_file(url_find,nb_url);
        }
    }

    void extract_href(char *code_html, FILE *file, char *search_begin_tag, char *typeHrefOrSrc) {
        int begin_tag, end_tag, find_begin_save, i, http, counter = 0, nb_url = 0,pos_href,pos_rel;
        const char *to_search = search_begin_tag, *p = code_html;
        char *url_find;
        while ((p = strstr(p, to_search)) != NULL) {
            begin_tag = p - code_html;
            //printf("\n %c \n",code_html[begin_tag]);
            find_begin_save = 0;
            counter = 0;
            url_find = malloc(sizeof(char) * 200);
            end_tag = position_of_symbole(begin_tag, code_html, '>');
            if (end_tag == -1) {
                p += strlen(to_search);
                continue;
            }
            pos_href = position_of_attribut(begin_tag, end_tag, code_html, typeHrefOrSrc);
            for (i = begin_tag; i < end_tag; ++i) {
                if (find_begin_save == 1) {
                    if (code_html[i] == '\"' || code_html[i] == '\'' || code_html[i]=='>') {
                        url_find[counter] = '\0';
                       // printf("%s\n",url_find);
                        treatment(url_find, search_begin_tag, file, nb_url);
                        p += strlen(to_search);
                        break;
                    } else {
                        url_find[counter] = code_html[i];
                        counter++;
                    }
                } else {
                    http = check_begin(begin_tag, end_tag, code_html, typeHrefOrSrc, i,pos_href);
                    if (http != -1) {
                        i = http - 1;
                        nb_url++;
                        find_begin_save = 1;
                    }
                }
            }
            p += strlen(to_search);
        }
    }
    int check_begin(int begin_tag, int end_tag, char *code_html, char *typeHrefOrSrc, int i,int pos_href) {
        int http;
        if (pos_href != -1) {
            if (code_html[i + (begin_tag - pos_href)] == '\'' || code_html[i + (begin_tag - pos_href)] == '"') {
                http = position_of_attribut(i + (begin_tag - pos_href), end_tag, code_html, "http");
                if (http != -1) {
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
    int position_of_attribut(int begin, int end, char *code_html, char *attr_to_find) {
        char *str = malloc(sizeof(char) * (end - begin));
        int position, counter = 0;
        for (int i = begin; i < end; i++) {
            str[counter] = code_html[i];
            counter++;
        }
        const char *p = str;
    //    printf("\n%s\n",str);
        p = strstr(p, attr_to_find);
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
    int position_of_symbole(int begin, char *code_html, char char_to_find) {
        for (int i = 0; i <500 ; i++) {
            if (char_to_find != '>' && i == 10) {
                return -1;
            }
            if (code_html[ begin +i] == '>') {
                return begin + i;
            }
        }
        return -1;
    }

