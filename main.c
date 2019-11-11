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


    char *filePath = "../configFile.sconf";// à remplacer par getFilePath() mais là on gagne du temps pour les tests

    FILE *file = fopen(filePath, "r");
    if(file == NULL) {
        return -1;
    }

    int actionsLength = 0;
    int tasksLength = 0;

    Action *actions = getActions(file, &actionsLength);
    Task *tasks = getTasks(file, &tasksLength, actions, actionsLength);
    for (int i = 0; i < actionsLength; i++) {
        deleteRepositorie(actions[i].name);
        createRepositorie(actions[i].name);//je vais devoir adapter le noms des filename en fonction de sa
        //faire une fonction qui fait la liste des options
        char *extractAlltag[8]={"a","source","strong","img","script","link","p","header"};
        execute(extractAlltag,actions[i].url,8);
    }

   // printActions(actions, actionsLength);
    //printTasks(tasks, tasksLength);

    fclose(file);
   /* deleteRepositorie("download");
    createRepositorie("download");//je vais devoir adapter le noms des filename en fonction de sa
    //faire une fonction qui fait la liste des options
    char *extractAlltag[8]={"a","source","strong","img","script","link","p","header"};
    execute(extractAlltag,"https://www.marmiton.org/recettes/index/categorie/pizza",8);*/
    return 0;
}
