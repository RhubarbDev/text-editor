#include "crawler.h"
#include <dirent.h>
#include <stdio.h>

void get_all_dirs(char * uri)
{
    char* path = uri + 7;
    DIR *d;
    struct dirent *dir;
    d = opendir(path);
    if (d) {
      while ((dir = readdir(d)) != NULL){
        if (dir->d_type == DT_REG){
          printf("%s\n", dir-> d_name);
        }
      }
      closedir(d);
    }
}

