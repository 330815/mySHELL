#ifndef SMSH_H
#define SMSH_H
#include <string>
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <QCoreApplication>

char *makestring(char *buf);    //获取输入的每个命令
void execute2(char *arglist[]);   //执行命令2.0
void execute3(char *arglist[]);  //执行命令3.0
#endif // SMSH_H
