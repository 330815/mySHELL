#include <QCoreApplication>
#include <string>
#include <iostream>
#include <stdlib.h>
#include "smsh.h"

#define MAXARGS 20  //cmdline args
#define ARGLEN 100  //token length

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    //v1.0
    /* 如何执行命令：execvp（progname,arglist），其中arglist的第一个元素是程序的名称，最后一个元素必须为null */
    //    char *arglist[3];

    //    arglist[0] = "ls";
    //    arglist[1] = "-l";
    //    arglist[2] = 0;

    //    printf("***About to exec ls -l\n");
    //    execvp("ls",arglist);
    //    printf("*** ls is done.bye\n");


    //v2.0
    /* 单独地输入命令字符串，将字符串一个一个地加入arglist字符串数组中 */
    char *arglist[MAXARGS + 1];
    int numargs;
    char argbuf[ARGLEN];
    numargs = 0;

    while(numargs < MAXARGS){
        std::cout<<">"<<numargs;
        if(fgets(argbuf,ARGLEN,stdin) && *argbuf != '\n')   //单独地输入每个命令，直到输入为换行符
            arglist[numargs++] = makestring(argbuf);
        else {
            if(numargs >0){
                arglist[numargs] = NULL;
//                execute2(arglist);
                execute3(arglist);
                numargs = 0;
            }
        }
    }

    return a.exec();
}









