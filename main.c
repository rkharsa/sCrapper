/**
 * sCrapper by Jérémy Ternisien, Rani Kharsa and Frantz Nestan
 * This application allows you to make web scraping and save websites data in your hard drive
 * To take full advantage of it, make sure to create a well constructed configuration file with the .sconf extension
 * Enjoy
 */


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

    char* filePath = getFilePath();// à remplacer par getFilePath() mais là on gagne du temps pour les tests

    FILE* file = fopen(filePath, "r");
    if (file == NULL) {
        return EXIT_FAILURE;
    }


    int actionsLength = 0;
    int tasksLength = 0;
    Action* actions = getActions(file, &actionsLength);
    Task* tasks = getTasks(file, &tasksLength, actions, actionsLength);

    printf("\n\nSCRAPING WEBISTES...\n\n");

    for (int i = 0; i < tasksLength; ++i) {
        for (int j = 0; j < tasks[i].actionsLength; ++j) {
            executeAction(tasks[i], tasks[i].actions[j]);
        }
    }

    fclose(file);
    //CounterFile counterFile = initCounterFile();
    //extractAll("https://www.marmiton.org/recettes/recette_oeuf-cocotte-en-fromage_347098.aspx","img",&counterFile,"download","image/png");

    printf("\n\nSCRAPING SUCCESS !\n\n");

    return EXIT_SUCCESS;
}
