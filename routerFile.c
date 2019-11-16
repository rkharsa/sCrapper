#include "header.h"

/**
 * @author Rani Kharsa
 * @param type
 * @param i
 * @return path
 * @brief permit to redirect toward the path
 */

char* filenameDynamicTxt(char* folder, char* tag, int i) {
    char* str = malloc(sizeof(char) * 50);

    if (!strcmp("a", tag)) {
        sprintf(str, "%s/linkOfAllTag/link%d.txt", folder, i);
    } else if (!strcmp("img", tag)) {
        sprintf(str, "%s/linkOfAllTag/img%d.txt", folder, i);
    } else if (!strcmp("link", tag)) {
        sprintf(str, "%s/linkOfAllTag/css%d.txt", folder, i);
    } else if (!strcmp("script", tag)) {
        sprintf(str, "%s/linkOfAllTag/js%d.txt", folder, i);
    } else if (!strcmp("source", tag)) {
        sprintf(str, "%s/linkOfAllTag/video%d.txt", folder, i);
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
char* filenameDynamicContainer(char* folder, char* tag, int i, char* ext) {
    char* str = malloc(sizeof(char) * 50);
    if (!strcmp("img", tag)) {
        if (!strcmp(ext, " ")) {
            sprintf(str, "%s/imgTag/image%i", folder, i);
        } else {
            sprintf(str, "%s/imgTag/image%i.%s", folder, i, ext);
        }
    } else if (!strcmp("source", tag)) {
        sprintf(str, "%s/sourceTag/video%d.%s", folder, i, ext);
    } else if (!strcmp("link", tag)) {
        if (!strcmp(ext, " ")) {
            sprintf(str, "%s/linkTag/link%d.txt", folder, i);
        } else {
            sprintf(str, "%s/linkTag/link%d.%s", folder, i, ext);
        }
    } else if (!strcmp("script", tag)) {
        sprintf(str, "%s/scriptTag/js%d.js", folder, i);
    } else {
        sprintf(str, "%s/content/%s%i.txt", folder, tag, i);
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


void deleteFolder(char* folderName) {
    char* command = malloc(sizeof(char) * 200);
    sprintf(command, "rmdir /Q  /S %s", folderName);
    system(command);
}

void createFolder(char* folderName) {

    char* command = malloc(sizeof(char) * 200);
    sprintf(command, "mkdir %s && "
                     "cd %s && mkdir content && mkdir imgTag "
                     "&& mkdir scriptTag "
                     "&& mkdir linkofAllTag "
                     "&& mkdir linkTag "
                     "&& mkdir sourceTag ", folderName, folderName);
    system(command);

}