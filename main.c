#include "header.h"

int main(int argc, char *argv[]) {
    /* char *string = getHtmlCode("https://www.ecosia.org/search/?q=mac+ls+permission+denied&addon=safari&addonversion=4.1.1.32");
     printf("resultat :\n%s\n", string);*/
    Action *a = malloc(sizeof(Action));
    a->name = "test";
    a->url = "mon url";
    Action *a2 = malloc(sizeof(Action));
    a2->name = "test2";
    a2->url = "mon url2";


    Task *task1 = malloc(sizeof(Task));
    task1->Action = a;
    task1->Action[1] = *a2;
    task1->hours = 0;
    task1->minutes = 0;
    task1->seconds = 5;
    task1->nextOccurence = 0;

    Task *task2 = malloc(sizeof(Task));
    task2->hours = 0;
    task2->minutes = 0;
    task2->seconds = 5;
    task2->nextOccurence = 0;

    Task *taskLst = malloc(sizeof(Task) * 2);
    taskLst = task1;
    taskLst[1] = *task2;
    task(taskLst);
    return 0;
}