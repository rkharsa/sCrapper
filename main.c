#include "header.h"

int main(int argc, char *argv[])
{
    char *string = getHtmlCode("https://www.ecosia.org/search/?q=mac+ls+permission+denied&addon=safari&addonversion=4.1.1.32");
    printf("resultat :\n%s\n", string);
    return 0;
}