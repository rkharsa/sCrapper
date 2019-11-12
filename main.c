#include "header.h"
#include "parser.h"

int main(int argc, char *argv[])
{
    /*printf("%s\n","--------------------------------------------------------------");
printf("%s","  _________                                 .__                \n"
            " /   _____/ ________________  ______ ______ |__| ____    ____  \n"
            " \\_____  \\_/ ___\\_  __ \\__  \\ \\____ \\\\____ \\|  |/    \\  / ___\\ \n"
            " /        \\  \\___|  | \\// __ \\|  |_> >  |_> >  |   |  \\/ /_/  >\n"
            "/_______  /\\___  >__|  (____  /   __/|   __/|__|___|  /\\___  / \n"
            "        \\/     \\/           \\/|__|   |__|           \\//_____/  ");
    printf("\n%s\n","--------------------------------------------------------------");
  char *extractAlltag[10]={"a","img","script","source","link"};
  execute(extractAlltag,"https://openclassrooms.com/forum/sujet/barre-de-progression-en-c");*/

    char *filePath = "../configFile.sconf";// à remplacer par getFilePath() mais là on gagne du temps pour les tests

    FILE *file = fopen(filePath, "r");
    if(file == NULL) {
        return -1;
    }

    int actionsLength = 0;
    int tasksLength = 0;

    Action *actions = getActions(file, &actionsLength);
    Task *tasks = getTasks(file, &tasksLength, actions, actionsLength);

    printActions(actions, actionsLength);
    printTasks(tasks, tasksLength);

    fclose(file);

    return 0;
}
