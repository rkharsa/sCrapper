#include "header.h"

int main(int argc, char *argv[])
{
    printf("%s\n","--------------------------------------------------------------");
printf("%s","  _________                                 .__                \n"
            " /   _____/ ________________  ______ ______ |__| ____    ____  \n"
            " \\_____  \\_/ ___\\_  __ \\__  \\ \\____ \\\\____ \\|  |/    \\  / ___\\ \n"
            " /        \\  \\___|  | \\// __ \\|  |_> >  |_> >  |   |  \\/ /_/  >\n"
            "/_______  /\\___  >__|  (____  /   __/|   __/|__|___|  /\\___  / \n"
            "        \\/     \\/           \\/|__|   |__|           \\//_____/  ");
    printf("\n%s\n","--------------------------------------------------------------");
  char *extractAlltag[10]={"a","img","source","link","script"};
  execute(extractAlltag,"https://stackoverflow.com/questions/43777913/the-difference-in-file-access-mode-w-and-wb");

 return 0;
}
