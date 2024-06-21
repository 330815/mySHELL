#include <QCoreApplication>
#include "smsh.h"

#define MAXARGS 20  //cmdline args
#define ARGLEN 100  //token length
#define DEL_PROMPT ">"

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
//    char *arglist[MAXARGS + 1];
//    int numargs;
//    char argbuf[ARGLEN];
//    numargs = 0;

//    while(numargs < MAXARGS){
//        std::cout<<">"<<numargs;
//        if(fgets(argbuf,ARGLEN,stdin) && *argbuf != '\n')   //单独地输入每个命令，直到输入为换行符
//            arglist[numargs++] = makestring(argbuf);
//        else {
//            if(numargs >0){
//                arglist[numargs] = NULL;
////                execute2(arglist);  //v2.0
//                execute3(arglist);    //v3.0
//                numargs = 0;
//            }
//        }
//    }


    //v4.0

//    char *cmdline,**arglist;
//    int result;
//    void setup();

//    const char *prompt = DEL_PROMPT;
//    setup();

//    while ((cmdline = next_cmd(prompt,stdin)) != NULL) {
//        if((arglist = splitline(cmdline)) != NULL){
//            result = execute4(arglist);
//            freelist(arglist);
//        }
//        free(cmdline);
//    }

//    return a.exec();

    //v5.0
        char *cmdline,**arglist;
        int result;
        void setup();

        const char *prompt = DEL_PROMPT;
        setup();

        while ((cmdline = next_cmd(prompt,stdin)) != NULL) {
            if((arglist = splitline(cmdline)) != NULL){
                result = execute5(arglist);
                freelist(arglist);
            }
            free(cmdline);
        }

        return a.exec();

}

void setup(){
    signal(SIGINT,SIG_IGN);
    signal(SIGQUIT,SIG_IGN);
}

void fatal(const char *s1,const char *s2,int n){
    std::fprintf(stderr,"Error:%s,%s\n",s1,s2);
    exit(n);
}






