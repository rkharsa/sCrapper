#include "header.h"
#include "parser.h"

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


  /*  char *filePath = "../configFile.sconf";// à remplacer par getFilePath() mais là on gagne du temps pour les tests

    FILE *file = fopen(filePath, "r");
    if(file == NULL) {
        return -1;
    }

    int actionsLength = 0;
    int tasksLength = 0;
    char repositorie[200];
    Action *actions = getActions(file, &actionsLength);
    Task *tasks = getTasks(file, &tasksLength, actions, actionsLength);
    for (int i = 0; i < actionsLength; i++) {
        sprintf(repositorie,"%s%d",actions[i].name,i);
        printf("%s",repositorie);
        deleteRepositorie(repositorie);
        createRepositorie(repositorie);
        char *extractAlltag[8]={"a","source","strong","img","script","link","p","header"};
        execute(extractAlltag, actions[i].url,8,repositorie);
    }

   // printActions(actions, actionsLength);
    //printTasks(tasks, tasksLength);

    fclose(file);*/
 /*deleteRepositorie("download");
   createRepositorie("download");//je vais devoir adapter le noms des filename en fonction de sa
    //faire une fonction qui fait la liste des options
   char *extractAlltag[8]={"a","source","strong","img","script","link","p","header"};
    execute(extractAlltag,"https://curl.haxx.se/libcurl/",1,"download");*/
   /*char repositorie[200];
   sprintf(repositorie,"%s%d","name",0);
   printf("%s",repositorie);
    deleteRepositorie(repositorie);
    createRepositorie(repositorie);
    char *extractAlltag[8]={"a","source","strong","img","script","link","p","header"};
    execute(extractAlltag, "https://www.marmiton.org/recettes/index/categorie/pizza",8,repositorie);*/
    fistWawe("https://curl.haxx.se/libcurl/");
    int max_deph=2;
    for (int i = 0; i < max_deph ; i++) {
        printf("\nPROFONDEUR :%d \n",i);
        nextWave(i);
    }
//printf("%s",getBeginUrl("https://www.marmiton.org/recettes/index/categorie/pizza",1)) ;

return 0;
}
