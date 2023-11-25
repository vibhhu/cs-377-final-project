#ifndef _SIMPLE_SHELL_H
#define _SIMPLE_SHELL_H

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>

class simple_shell {
 public:
  void parse_command(char* cmd, char** cmdTokens);
  void exec_command(char** argv);
  bool isQuit(char* cmd);
};

#endif