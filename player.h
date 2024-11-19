#ifndef PLAYER_H
#define PLAYER_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define PORT "58011"
#define DEBUG 1
#define FLAGS "[-n GSIP] [-p GSport]"
#define MENU "start PLID max_playtime\ntry C1 C2 C3 C4\nshow_trials 'or' st\nscoreboard 'or' sb\nquit\nexit\ndebug PLID max_playtime C1 C2 C3 C4\n"

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

typedef void (*CommandHandler)(char *args);

typedef struct {
    char *command;
    CommandHandler handler;
} Command;

void start(char * args);
void try(char * args);
void show_trials(char * args);
void scoreboard(char * args);
void quit(char * args);
void exit_client(char * args);
void unknown(char * args);

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

void getIPAddress();

#endif