#include "header.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
    deleteRepositorie("download");
   createRepositorie("download");
    printf("%s\n","--------------------------------------------------------------");
printf("%s","  _________                                 .__                \n"
            " /   _____/ ________________  ______ ______ |__| ____    ____  \n"
            " \\_____  \\_/ ___\\_  __ \\__  \\ \\____ \\\\____ \\|  |/    \\  / ___\\ \n"
            " /        \\  \\___|  | \\// __ \\|  |_> >  |_> >  |   |  \\/ /_/  >\n"
            "/_______  /\\___  >__|  (____  /   __/|   __/|__|___|  /\\___  / \n"
            "        \\/     \\/           \\/|__|   |__|           \\//_____/  ");
    printf("\n%s\n","--------------------------------------------------------------");


  char *extractAlltag[8]={"a","img","source","link","script","p","header","strong"};
  execute(extractAlltag,"https://openclassrooms.com/fr/courses/19980-apprenez-a-programmer-en-c/16421-lire-et-ecrire-dans-des-fichiers",8);


 return 0;
}
