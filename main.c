#include "header.h"
int main(int argc, char *argv[])
{

    char* extractAll[4][3]={{"<a \0","href\0","download/link/hrefUrl.txt\0"},{"<img\0","src\0","download/link/imgUrl.txt\0"},{"<script\0","src\0","download/link/jsUrl.txt\0"},{"<video\0","src\0","download/link/videoUrl.txt\0"}};
   /*  for(int i=0;i<4;++i){
            printf("%s",extractAll[i][2]);
            extract_all("https://stackoverflow.com/questions/39956310/junit-assertthat-check-that-object-equals-string", extractAll[i][2],extractAll[i][0],extractAll[i][1]);
        }*/
   extract_all("https://github.com/rkharsa", extractAll[1][2],extractAll[1][0],extractAll[1][1]);




    return 0;
}