#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "configuration.c"
void Lecture();
void action(FILE * fileConfig);
void viderBuffer();
int lire(char *chaine, int longueur);
void aTask(FILE * fileConfig);
void createConfig();
#endif // HEADER_H_INCLUDED