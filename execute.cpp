#include "smsh.h"
#include <sys/wait.h>

void execute2(char *arglist[]){
    execvp(arglist[0],arglist);
    perror("execute failed");
    exit(1);
}

// 使用fork（）创建新进程，使得能够循环执行命令
void execute3(char *arglist[]){
    int pid,exitstatus;

    pid = fork();
    switch (pid) {
    case -1:
        perror("fork failed");
        exit(1);
    case 0:
        execvp(arglist[0],arglist);
        perror("execvp failed");
        exit(1);
    default:
        while (wait(&exitstatus) != pid) {}
//        printf("child exited with status %d,%d\n",exitstatus>>8,exitstatus&0377);
        std::cout<<"child exited with status"<<(exitstatus>>8)<<","<<(exitstatus&0377)<<std::endl;
    }
}


int execute4(char *arglist[]){
    int pid;
    int child_info = -1;

    if(arglist[0]==NULL)
        return 0;
    if((pid = fork()) == -1)
        perror("fork failed");
    else if (pid == 0) {
        signal(SIGINT,SIG_DFL);
        signal(SIGQUIT,SIG_DFL);
        execvp(arglist[0],arglist);
        perror("execvp failed");
        exit(1);
    }
    else {
        if(wait(&child_info) == -1){
            perror("wait");
        }
        return child_info;
    }
}
