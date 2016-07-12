#pragma once

#define _GNU_SOURCE

#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <sys/wait.h>

#define messageMaxSize 100

struct Message {
  long type;
  char text[messageMaxSize];
};
