#include "header.h"

/**
 * @author Rani Kharsa
 * @param type
 * @param i
 * @return path
 * @brief permit to redirect toward the path
 */

char* filenameDynamicTxt(char* repositorie, char* tag, int i) {
    char* str = malloc(sizeof(char) * 50);

    if (!strcmp("a", tag)) {
        sprintf(str, "%s/linkOfAllTag/link%d.txt", repositorie, i);
    } else if (!strcmp("img", tag)) {
        sprintf(str, "%s/linkOfAllTag/img%d.txt", repositorie, i);
    } else if (!strcmp("link", tag)) {
        sprintf(str, "%s/linkOfAllTag/css%d.txt", repositorie, i);
    } else if (!strcmp("script", tag)) {
        sprintf(str, "%s/linkOfAllTag/js%d.txt", repositorie, i);
    } else if (!strcmp("source", tag)) {
        sprintf(str, "%s/linkOfAllTag/video%d.txt", repositorie, i);
    }
    return str;
}

/**
 * @author Rani Kharsa
 * @param type
 * @param i
 * @param ext
 * @return path
 * @brief permit to redirect toward the path
 */
char* filenameDynamicContainer(char* repositorie, char* tag, int i, char* ext) {
    char* str = malloc(sizeof(char) * 50);

    if (!strcmp("img", tag)) {
        if (!strcmp(ext, " ")) {
            sprintf(str, "%s/imgTag/image%i", repositorie, i);
        } else {
            sprintf(str, "%s/imgTag/image%i.%s", repositorie, i, ext);
        }
    } else if (!strcmp("source", tag)) {
        sprintf(str, "%s/sourceTag/video%d.%s", repositorie, i, ext);
    } else if (!strcmp("link", tag)) {
        if (!strcmp(ext, " ")) {
            sprintf(str, "%s/linkTag/link%d.txt", repositorie, i);
        } else {
            sprintf(str, "%s/linkTag/link%d.%s", repositorie, i, ext);
        }
    } else if (!strcmp("script", tag)) {
        sprintf(str, "%s/scriptTag/js%d.js", repositorie, i);
    } else {
        sprintf(str, "%s/content/%s%i.txt", repositorie, tag, i);
    }

    return str;
}

/**
 * @author Rani kharsa
 * @param tag
 * @return src or href
 */
char* hrefOrSrcRouter(char* tag) {
    char* str = malloc(sizeof(char) * 50);
    if (!strcmp("a", tag) || !strcmp("link", tag)) {
        sprintf(str, "href");
    } else if (!strcmp("script", tag) || !strcmp("source", tag) || !strcmp("img", tag)) {
        sprintf(str, "src");
    }

    return str;
}


void deleteRepositorie(char* repositorieName) {
    char* command = malloc(sizeof(char) * 200);
    sprintf(command, "rmdir /Q  /S %s", repositorieName);
    system(command);
}

void createRepositorie(char* repositorieName) {

    char* command = malloc(sizeof(char) * 200);
    sprintf(command, "mkdir %s && "
                     "cd %s && mkdir content && mkdir imgTag "
                     "&& mkdir scriptTag "
                     "&& mkdir linkofAllTag "
                     "&& mkdir linkTag "
                     "&& mkdir sourceTag ", repositorieName, repositorieName);
    system(command);

}