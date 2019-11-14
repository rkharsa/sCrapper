#include "header.h"
#include "parser.h"
#include "manager.h"

int main(int argc, char* argv[]) {

    printf("%s\n", "--------------------------------------------------------------");
    printf("%s", "  _________                                 .__                \n"
                 " /   _____/ ________________  ______ ______ |__| ____    ____  \n"
                 " \\_____  \\_/ ___\\_  __ \\__  \\ \\____ \\\\____ \\|  |/    \\  / ___\\ \n"
                 " /        \\  \\___|  | \\// __ \\|  |_> >  |_> >  |   |  \\/ /_/  >\n"
                 "/_______  /\\___  >__|  (____  /   __/|   __/|__|___|  /\\___  / \n"
                 "        \\/     \\/           \\/|__|   |__|           \\//_____/  ");
    printf("\n%s\n", "--------------------------------------------------------------");

    char* filePath = "../configFile.sconf";//getFilePath();// à remplacer par getFilePath() mais là on gagne du temps pour les tests

    FILE* file = fopen(filePath, "r");
    if (file == NULL) {
        return EXIT_FAILURE;
    }

    int actionsLength = 0;
    int tasksLength = 0;
    Action* actions = getActions(file, &actionsLength);
    Task* tasks = getTasks(file, &tasksLength, actions, actionsLength);

    for (int i = 0; i < tasksLength; ++i) {
        for (int j = 0; j < tasks[i].actionsLength; ++j) {
            //printf("%s\n%d\n", tasks[i].actions[j].name, j);
            executeAction(tasks[i].actions[j]);
        }
    }

    fclose(file);
    return EXIT_SUCCESS;

    //commandInFile("sort -u", "../testg.txt");
    // commandInFile("egrep -v \".png|.jpeg|.svg\"", "../testg.txt");
    //return 0;


    /*for (int i = 0; i < actionsLength; i++) {
        sprintf(folder,"%s%d",actions[i].name,i);
        printf("%s",folder);
        deleteFolder(folder);
        createFolder(folder);
        char *extractAlltag[8]={"a","source","strong","img","script","link","p","header"};
        execute(extractAlltag, actions[i].url,8,folder);
    }//
    deleteFolder("download");
      createFolder("download");//je vais devoir adapter le noms des filename en fonction de sa
      //faire une fonction qui fait la liste des options
      char *extractAlltag[8]={"a","source","strong","img","script","link","p","header"};
      execute(extractAlltag,"https://www.marmiton.org/recettes/index/categorie/pizza",8);
    char folder[200];
    sprintf(folder,"%s%d","name",0);
    printf("%s",folder);
     deleteFolder(folder);
     createFolder(folder);
     char *extractAlltag[8]={"a","source","strong","img","script","link","p","header"};
     execute(extractAlltag, "https://www.marmiton.org/recettes/index/categorie/pizza",8,folder);
    fistWawe("https://curl.haxx.se/libcurl/");
     int max_deph=3;
     for (int i = 0; i < max_deph ; i++) {
         printf("\nPROFONDEUR :%d \n",i);
         nextWave(i);
     }*/

    //return 0;
}
