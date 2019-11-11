#include "header.h"

CounterFile initCounterFile(){
    CounterFile counterFile;
    counterFile.nbLink=0;
    counterFile.nbJs=0;
    counterFile.nbVideo=0;
    counterFile.nbContent=0;
    counterFile.nbLinkTag=0;
    counterFile.nbImg=0;
    return counterFile;

}
int * routerCounter(CounterFile*  counterFile,char * beginTag){
    if(!strcmp(beginTag,"<img")){
        return &counterFile->nbImg;
    }else if(!strcmp(beginTag,"<source")){
        return &counterFile->nbVideo;
    }else if(!strcmp(beginTag,"<link")){
        return &counterFile->nbLinkTag;
    }else if(!strcmp(beginTag,"<script")){
        return &counterFile->nbJs;
    }else if(!strcmp(beginTag,"<content")){
        return &counterFile->nbContent;
    }else {
        return  &counterFile->nbLink;
    }
}
void counterIncrem(CounterFile * counterFile,char*beginTag){
    *routerCounter(counterFile,beginTag)+=1;
}