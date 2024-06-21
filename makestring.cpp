#include "smsh.h"
char *makestring(char *buf){
    char *cp;

    buf[strlen(buf)-1] = '\0';
    cp = (char *)malloc(strlen(buf)+1);
    if (cp == NULL){
        fprintf(stderr,"no memory\n");
        exit(1);
    }
    strcpy(cp,buf);
    return cp;
}
