#include "header.h"



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


void extract_all(char *url) {
    char *code_html = getHtmlCode(url);
   //char *code_html = "<a href=http:rien# lklj>";

    FILE * file = fopen("sourceUrl.txt","w");
    if(file!=NULL) {
        //extract_href_from_html(code_html,file);
        //extract_first_title(code_html,file,"1");
        extract_href(code_html,file,"<img","src");
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
* step 1 find tag <a>
* step 2 find position of the href attribut
* step 3 find position of the equal symbol
* step 4 read and write in txt file all between quotes
 * img
 * href
 * video
 * commencant par http
*/
void extract_href(char * code_html,FILE* file,char* search_begin_tag,char * typeHrefOrSrc) {
    int  begin_tag,end_tag,find_begin_save, i,pos_href, pos_quotes,pos_apostrophe,http,pos_quotes__apostrophe;
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
                if(pos_href!=-1){
                    pos_quotes=position_of_symbole(pos_href,code_html,'"');
                    pos_apostrophe=position_of_symbole(pos_href,code_html,'\'');
                    if(pos_quotes!=-1 || pos_apostrophe!=-1){
                            if(pos_quotes!=-1){
                                pos_quotes__apostrophe=pos_quotes;
                            }else{
                                pos_quotes__apostrophe=pos_apostrophe;
                            }
                            http=position_of_attribut(pos_quotes__apostrophe,end_tag,code_html,"http");
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

int position_of_symbole(int begin ,char *code_html,char char_to_find){
    for (int i = 0; i <1000 ; ++i) {
        if(code_html[begin+i]==char_to_find){
            return begin+i ;
        }
    }
    return -1;
    }


void extract_href_from_html(char * code_html,FILE* file){
    int stop,i,counter_quotes,find_begin,not_found,ok;
    const char *to_search = "<a",*p = code_html;
    while ((p = strstr(p, to_search)) != NULL) {
        stop = 1;
        ok=0;
        i = p - code_html ;
        counter_quotes = 0;
        find_begin=0;
        not_found=0;
        while (stop) {
            if(find_begin==1){
                if (code_html[i] != '\"'&& code_html[i]!='\'' && counter_quotes<2 ) {
                    if(code_html[i]=='#' && code_html[i+1]=='#'&& code_html[i+2]=='#' && ok==0){
                        break;
                    }
                    ok++;
                    fputc(code_html[i], file);
                    i++;
                }else {
                    if(counter_quotes>=2){
                        fputs("\n", file);
                        counter_quotes = 0;
                        stop = 0;
                    }else{
                        counter_quotes++;
                    }
                    i++;
                }}else{
                if(code_html[i] == 'h' && code_html[i+1] == 'r' && code_html[i+2] == 'e' && code_html[i+3] == 'f'  ) {
                    i +=4 ;
                    if(equal_position(code_html,i)==-1){
                        break;
                    }else{
                        find_begin=1;
                        i+=equal_position(code_html,i);
                    }
                }else{
                    not_found++;
                    if(not_found==10){
                        break;
                    }
                    find_begin=0;
                    i+=1;
                }
            }
        }
        p += strlen(to_search);
    }
}
/**
 * @author Rani Kharsa
 * @param code_html
 * @param i
 * @return number of space + 1
 * @brief permit to find position of the equal symbol
 */
int equal_position(char* code_html,int i){
    int space=0,x;
        for(x=i;x<i+10;x++){
            if(code_html[x]=='='){
                return  space+1;
            }
            space++;
        }
        return  -1;
}
