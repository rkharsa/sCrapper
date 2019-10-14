#include "header.h"
/*
 * Permet de lire le fichier config
 * */
void Lecture(){
    char str[100];
    FILE* Lecture=fopen("config.sconfig","r");
    if(Lecture!=NULL){
        char* c=fgets(str,100,Lecture);
        while (*c!=EOF){

            printf("%s",str);
            c=fgets(str,100,Lecture);
        }

        fclose(Lecture);
    }
}
/*
 * Permet de vider la saisie et evite les buffer owerflow
 * */
void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}
/*
 * Fonction de saisie plus securisé que la fonction scanf
 * */
int lire(char *chaine, int longueur)
{
    char *positionEntree = NULL;
    if (fgets(chaine, longueur, stdin) != NULL)
    {
        positionEntree = strchr(chaine, '\n');
        if (positionEntree != NULL)
        {
            *positionEntree = '\0';
        }
        else
        {
            viderBuffer();
        }
        return 1;
    }
    else
    {
        viderBuffer();
        return 0;
    }
}
/*
 * ecriture des actions dans le fichier txt
 * */
void action(FILE * fileConfig){

    char name[20],url[20],option[20];
    fputs("=\n",fileConfig);
    printf("Nom de l'action : ");
    lire(name,20);
    fprintf(fileConfig,"{name -> %s}\n",name);
    printf("Url : ");
    lire(url,20);
    fprintf(fileConfig,"{url -> %s}\n",url);
    fputs("+\n",fileConfig);
    int i  =0;
    do{
        printf("le type d'option  (taper 0  si vous avez fini) :");
        lire(option,20);
        if(strcmp(option,"0")){

            fprintf(fileConfig,"{option%d -> %s}\n",i,option);
        }

        i++;
    }while(strcmp(option,"0"));
    fputs("\n",fileConfig);
}
/*
 * ecriture des taches dans le fichier txt
 * */
void aTask(FILE * fileConfig){
    char name[20],value[20],second[20],minute[20],hours[20],siteWeb[20];
    printf("Nom de la tache :");
    lire(name,20);
    printf("Heure :");
    lire(hours,20);
    printf("Minute :");
    lire(minute,20);
    printf("Seconde:");
    lire(second,20);
    fputs("== # Lance la requete HTTP toutes les ...\n",fileConfig);
    fprintf(fileConfig,"{name -> %s}\n",name);
    if(strcmp(hours,"0")){
        fprintf(fileConfig,"{hour -> %s}\n",hours);
    }
    if(strcmp(minute,"0")){
        fprintf(fileConfig,"{minute -> %s}\n",minute);
    }
    if(strcmp(second,"0")){
        fprintf(fileConfig,"{second -> %s}\n",second);
    }
    fputs("+\n",fileConfig);
    printf("Quel site web à associer (Séparer d'une virgule entre chaque site) :");
    fprintf(fileConfig,"(%s)",siteWeb);

}
/*
 * creation du fichier config
 * */
void  createConfig(){
    FILE * fileConfig=fopen("config.sconfig","w");
    if(fileConfig!=NULL){
        int howManyAction=0;
        int  howManyTask=0;
        //une action

        printf("Combien d'action desirez-vous?\n");
        scanf("%d",&howManyAction);
        for (int i = 0; i < howManyAction; ++i) {
            viderBuffer();
            action(fileConfig);
        }
        printf("Combien de tache desiez-vous?");
        scanf("%d",&howManyTask);
        for (int i = 0; i < howManyTask; ++i) {
            viderBuffer();
            aTask(fileConfig);
        }
        fclose(fileConfig);
    }else{
        printf("je n'existe pas ");
    }
}