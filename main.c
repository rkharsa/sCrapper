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

  /*  char* filePath = "../configFile.sconf";//getFilePath();// à remplacer par getFilePath() mais là on gagne du temps pour les tests

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

    fclose(file);*/
  CounterFile counterFile=initCounterFile();
    extractAll("https://www.marmiton.org/recettes/recette_oeuf-cocotte-en-fromage_347098.aspx","img",&counterFile,"download","image/png");
   /*char *ct = NULL;
    int res;
    char*url ="https://www.marmiton.org/reloaded/front/img/nav/nav_cocacola.png ";
    CURL *curl = curl_easy_init();
    if(curl) {



        curl_easy_setopt(curl, CURLOPT_URL, url);//work on this url
        curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
        res = curl_easy_perform(curl);

        if(res==CURLE_OK) {

            res = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &ct);
            if(!res && ct) {
                printf("Content-Type: %s\n", ct);
            }
        }else{
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

    }
    curl_easy_cleanup(curl);*/

   return EXIT_SUCCESS;
}
