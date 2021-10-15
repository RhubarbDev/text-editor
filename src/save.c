#include "save.h"
#include <stdio.h>

void save_file(char text[], char filepath[])
{
    //
    FILE *file;
    file = fopen(filepath, "w");
    for (int i = 0; text[i] != '\0'; i++){
    	fputc(text[i], file);
    }
    fclose(file);
}

