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

/**
 * @author Rani Kharsa
 * @param url
 * @brief extract all we need
 */
void extract_all(char *url) {
    char *code_html = getHtmlCode(url);
   //char *code_html = "<a alt=\"rien\" class=\'ro\' ref=\"http:rien#\">";

    FILE * file = fopen("sourceUrl.txt","w");
    if(file!=NULL) {
        //extract_href_from_html(code_html,file);
        //extract_first_title(code_html,file,"1");
        extract_href(code_html,file,"<a","href");
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
/**
* @author Rani Kharsa
* @param code_html
* @param file
 * @param  search_begin_tag : <a <img
 * @param typeHrefOrSrc :href  src
* step 1 find tag <a>
* step 2 find position of the href attribut
* step 3 find position of the first quote
 * step 4 find http
* step 5 read and write in txt file all between quotes
 * step 6 if  he find quotes then stop and next
 * @brief extract img  href
*/
void extract_href(char * code_html,FILE* file,char* search_begin_tag,char * typeHrefOrSrc) {
    int  begin_tag,end_tag,find_begin_save, i,pos_href,http;
    const char *to_search = search_begin_tag, *p = code_html;
    while ((p = strstr(p, to_search)) != NULL) {
        begin_tag = p - code_html;
        find_begin_save=0;
        end_tag = position_of_symbole(begin_tag, code_html, '>');
        if(end_tag==-1){
            p += strlen(to_search);
            continue;
        }
        for (i = begin_tag; i < end_tag; ++i) {
            if (find_begin_save == 1) {
               if(code_html[i] == '\"' || code_html[i] == '\''){
                   fputc('\n',file);
                   p += strlen(to_search);
                   break;
               }else{
                   fputc(code_html[i],file);
               }
            } else {
                pos_href=position_of_attribut(begin_tag,end_tag,code_html,typeHrefOrSrc);
                if(pos_href!=-1 ){
                    if(code_html[i+(begin_tag-pos_href)]=='\'' || code_html[i+(begin_tag-pos_href)]=='"'){
                        http=position_of_attribut(i+(begin_tag-pos_href),end_tag,code_html,"http");
                        if(http!=-1) {
                            i=http-1;
                            find_begin_save = 1;
                            p += strlen(to_search);
                            continue;

                        }
                    }

                }
            }
        }
        p += strlen(to_search);
        }
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
int position_of_attribut(int begin,int end,char* code_html, char *  attr_to_find){
    char *str=malloc(sizeof(char)*(end-begin));
    int position,counter=0;
    for(int i=begin;i<end;i++){
            str[counter]=code_html[i];
            counter++;
    }
    const char *p=str;
    //printf("%s\n",str);
    p=strstr(p,attr_to_find);
    position=p - str+begin;//essayer - counter
    if(p!=NULL)
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
int position_of_symbole(int begin ,char *code_html,char char_to_find){
    for (int i = 0; i <1000 ; ++i) {
        if(code_html[begin+i]==char_to_find){
            return begin+i ;
        }
    }
    return -1;
    }
