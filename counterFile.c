#include "header.h"
/**
 * permit to  count all the file without loose the number
 */

/**
 * @author Rani Kharsa
 * @return CounterFile
 * @brief init the struct
 */

CounterFile initCounterFile() {
    CounterFile counterFile;
    counterFile.nbLink = 0;
    counterFile.nbJs = 0;
    counterFile.nbVideo = 0;
    counterFile.nbContent = 0;
    counterFile.nbLinkTag = 0;
    counterFile.nbImg = 0;
    return counterFile;
}

/**
 * @author Rani Kharsa
 * @param counterFile
 * @param tag
 * @return adress of  attribut in the strcut
 */
int* routerCounter(CounterFile* counterFile, char* tag) {
    if (!strcmp(tag, "img")) {
        return &counterFile->nbImg;
    } else if (!strcmp(tag, "source")) {
        return &counterFile->nbVideo;
    } else if (!strcmp(tag, "link")) {
        return &counterFile->nbLinkTag;
    } else if (!strcmp(tag, "script")) {
        return &counterFile->nbJs;
    } else if (!strcmp(tag, "content")) {
        return &counterFile->nbContent;
    } else {
        return &counterFile->nbLink;
    }
}

/**
 * @autor Rani Kharsa
 * @param counterFile
 * @param tag
 * @brief increm the counter
 */
void counterIncrem(CounterFile* counterFile, char* tag) {
    *routerCounter(counterFile, tag) += 1;
}