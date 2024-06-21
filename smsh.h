#ifndef SMSH_H
#define SMSH_H
#include <string>
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <QCoreApplication>
#include <signal.h>

char *makestring(char *buf);    //获取输入的每个命令
void execute2(char *arglist[]);   //执行命令2.0
void execute3(char *arglist[]);  //执行命令3.0
int execute4(char *arglist[]);  //执行命令4.0

char *next_cmd(const char *prompt,FILE *fp);
char **splitline(char *line);
void *emalloc(size_t n);
void fatal(const char *s1,const char *s2,int n);
void freelist(char **list);
#endif // SMSH_H
