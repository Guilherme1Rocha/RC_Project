#ifndef CLIENTCOMMANDS_H
#define CLIENTCOMMANDS_H

#include <stdio.h>

char buffer[1024];

typedef int (*CommandHandler)(char *args);

typedef struct {
    char *command;
    CommandHandler handler;
} Command;

int start(char * args);
int try(char * args);
int show_trials(char * args);
int scoreboard(char * args);
int quit(char * args);
int exit_client(char * args);
int unknown(char * args);

Command commandTable[] = {
    {"start", start},
    {"debug", start},
    {"try", try},
    {"show_trials", show_trials},
    {"st", show_trials},
    {"scoreboard", scoreboard},
    {"sb", scoreboard},
    {"quit", quit},
    {"exit", exit_client},
    {NULL, unknown}  // Default case
};


#endif