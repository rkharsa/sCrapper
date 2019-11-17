#include "header.h"
#include "file.h"
#include "parser.h"


void commandInFile(char* command, char* file) {

    char* cmd = malloc(sizeof(char) * (strlen(command) + strlen(file)) + 20);
    sprintf(cmd, "%s %s > temp.txt", command, file);
    system(cmd);

    sprintf(cmd, "rmdir /Q  /S %s", file);
    system(cmd);

    sprintf(cmd, "mv temp.txt %s", file);
    system(cmd);
}



void firstWave(char* url) {

    char* codeHtml = getHtmlCode(url);
    removeDirectory("tmp");
    createDirectory("tmp", 0777);

    CounterFile counterFile = initCounterFile();
    FILE* fp = fopen("tmp/vague0.txt", "w+");
    if (fp != NULL) {
        extractLink(codeHtml, fp, "a", &counterFile, "tmp", "0");

        int filtersLength = 0;
        char** filters = strToArrayStr(".png,.svg,.jpeg,.gif,.jpg", &filtersLength, ",");
        filterLinesFile(fp, "tmp/vague0.txt", filters, filtersLength);
        fp = fopen("tmp/vague0.txt", "r+");
        removeDuplicateLines(fp, "tmp/vague0.txt");
    }
}



void nextWave(int waveDeph) {
    char filename1[200], filename2[200];
    // fichier a lire
    CounterFile counterFile = initCounterFile();
    sprintf(filename1, "tmp/vague%d.txt", waveDeph);
    // copier les resultas dans ce fichier
    sprintf(filename2, "tmp/vague%d.txt", waveDeph + 1);
    char* url = malloc(sizeof(char) * 400);
    char caractereActuel;
    int counter = 0;
    FILE* fp = fopen(filename1, "r");
    if (fp != NULL) {
        FILE* file = fopen(filename2, "w+");
        if (file != NULL) {
            do {
                caractereActuel = fgetc(fp);
                if(caractereActuel=='\n') {
                    url[counter] = '\0';
                    char *codeHtml = getHtmlCode(url);
                    extractLink(codeHtml, file, "a", &counterFile, "tmp",url,"0");
                    counter = 0;
                } else {
                    url[counter] = caractereActuel;
                    counter++;
                }
            } while (caractereActuel != EOF);


            int filtersLength = 0;
            char** filters = strToArrayStr(".png,.svg,.jpeg,.gif,.jpg", &filtersLength, ",");
            filterLinesFile(file, filename2, filters, filtersLength);
            file = fopen(filename2, "r+");
            removeDuplicateLines(file, filename2);
        }
        fclose(fp);
    }
}

