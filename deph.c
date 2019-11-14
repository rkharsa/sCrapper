#include "header.h"

void commandInFile(char* command, char* file) {

    char* cmd = malloc(sizeof(char) * (strlen(command) + strlen(file)) + 20);
    sprintf(cmd, "%s %s > temp.txt", command, file);
    system(cmd);

    sprintf(cmd, "rm %s", file);
    system(cmd);

    sprintf(cmd, "mv temp.txt %s", file);
    system(cmd);
}



void firstWave(char* url) {
    char* codeHtml = getHtmlCode(url);
    system("rmdir /Q  /S  tmp");
    system("mkdir tmp");
    CounterFile counterFile = initCounterFile();
    FILE* fp = fopen("tmp/vague0.txt", "w+");
    if (fp != NULL) {
        extractLink(codeHtml, fp, "a", &counterFile, "tmp");
        fclose(fp);
    }

    commandInFile("egrep -v \".png|.jpeg|.svg\"", "tmp/vague0.txt");
    commandInFile("sort -u", "tmp/vague0.txt");
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

                if (caractereActuel == '\n') {
                    url[counter] = '\0';
                    printf(" url :%s", url);
                    char* codeHtml = getHtmlCode(url);
                    extractLink(codeHtml, file, "a", &counterFile, "tmp");
                    counter = 0;
                } else {
                    url[counter] = caractereActuel;
                    counter++;
                }
            } while (caractereActuel != EOF);
            fclose(file);
        }
        fclose(fp);
        commandInFile("egrep -v \".png|.jpeg|.svg|.gif\"", filename2);
        commandInFile("sort -u", filename2);
    }
}

