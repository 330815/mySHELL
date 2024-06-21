#include "smsh.h"
int execute(char *arglist[]){
    execvp(arglist[0],arglist);
    perror("execute failed");
    exit(1);
}

int execute1(char *arglist[]){

}
