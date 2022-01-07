#include "save.h"
#include <stdio.h>

void save_txt(char text[], char filepath[])
{
    FILE *file;
    file = fopen(filepath, "w");
    for (int i = 0; text[i] != '\0'; i++){
    	fputc(text[i], file);
    }
    fclose(file);
}

void save_file(char text[], char filepath[], char type[])
{
    if (strcmp(type, "txt") == 0)
    {
        save_txt(text, filepath);
    }
    else
    {
        save_txt(text, filepath);
    }
}
