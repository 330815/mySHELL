#include "smsh.h"
#include <sys/wait.h>
#include <sstream>
#include <fcntl.h>

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
    std::vector<std::string> args;
    std::string infile, outfile;

    size_t size;
    for (size = 0; arglist[size] != NULL; ++size) {
    }
    for (size_t j = 0; j <size; ++j) {

        if (*arglist[j] == '<' && j + 1 < size) {
            infile = arglist[++j];
        } else if (*arglist[j] == '>' && j + 1 < size) {
            outfile = arglist[++j];
        } else {
            args.push_back(arglist[j]);
        }
    }

    if(arglist[0]==NULL)
        return 0;
    if((pid = fork()) == -1)
        perror("fork failed");
    else if (pid == 0) {
        signal(SIGINT,SIG_DFL);
        signal(SIGQUIT,SIG_DFL);
        if (!infile.empty()) {
            int in_fd = open(infile.c_str(), O_RDONLY);
            dup2(in_fd, STDIN_FILENO);
            close(in_fd);
        }
        if (!outfile.empty()) {
            int out_fd = open(outfile.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0666);
            dup2(out_fd, STDOUT_FILENO);
            close(out_fd);
        }
        std::vector<char*> c_args;
        for (auto& arg : args) {
            c_args.push_back(&arg[0]);
        }
        c_args.push_back(nullptr);
        execvp(c_args[0], c_args.data());
//        execvp(arglist[0],arglist);
        perror("execvp failed");
        exit(1);
    }
    else {
        if(wait(&child_info) == -1){
            perror("wait");
        }
        return child_info;
    }
    return 0;
}
