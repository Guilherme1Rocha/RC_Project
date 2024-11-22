#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"

char * getNextArg(char ** remainingArgs){
    if (!*remainingArgs)
        return NULL;
    char * argToken = strtok(*remainingArgs, " ");

    *remainingArgs = strtok(NULL,"\0");
    return argToken;
}

int validColor (char * color){
    for (int i = 0; i < VALID_COLORS; i++){
        if (!strcmp(color, colors[i]))
            return 1;
    }
    return 0;
}

/*
Note: example: 111A11, atoi() will return 111 
(the number before the first non-numeric element)
*/

int start(char * args){
    if (!args){
        fprintf(stderr, "-> This command needs arguments\n");
        return 1;
    }
    char * playerID = getNextArg(&args);
    char * endptr; 
    strtol(playerID,&endptr, 10);
    if (strlen(playerID) != PLAYER_ID_SIZE || !strcmp(endptr,playerID) || *endptr != '\0') {
        fprintf(stderr,"-> PLayer ID must be 6 digits (and positive)\n");
        return 1;
    }
    char * maxPlaytime = getNextArg(&args);

    if (!maxPlaytime){
        fprintf(stderr, "-> Not enough arguments (max_playtime missing)\n");
        return 1;
    }
    strtol(maxPlaytime,&endptr, 10);
    if (strlen(maxPlaytime) != MAX_PLAYTIME_SIZE || !strcmp(endptr,maxPlaytime) || *endptr != '\0'){
        fprintf(stderr,"-> Max Playtime must be 3 digits (and positive)\n");
        return 1;
    }
    if (args){
        fprintf(stderr,"-> Too many arguments (playerID and max_playtime)\n");
        return 1;
    }
    snprintf(buffer, sizeof(buffer), "SNG %s %s\n", playerID, maxPlaytime);
    return 0;
}


int try(char * args){
    if (!args){
        fprintf(stderr, "-> This command needs arguments\n");
        return 1;
    }
    char * move[COLORS_MOVE];
    char * color;
    for (int i = 0; i < COLORS_MOVE; i++){
        color = getNextArg(&args);
        if (!color){
            fprintf(stderr, "-> colore not valid\n");
            return 1;
        }
        if (!validColor(color)){
            fprintf(stderr, "-> Color %s not valid\n", color);
            return 1;
        }
        move[i] = color;
    }
    if (args){
        fprintf(stderr, "-> Too many arguments (4 colors for a valid move)\n");
        return 1;
    }
    //snprintf(buffer, sizeof(buffer), "SNG %s %s\n", playerID, maxPlaytime);
    return 0;
}

int show_trials(char * args){
    if (args){
        fprintf(stderr, "-> This command doesn't take any arguments");
        return 1;
    }
    return 0;
}
int scoreboard(char * args){
    if (args){
        fprintf(stderr, "-> This command doesn't take any arguments");
        return 1;
    }
    return 0;
}
int quit(char * args){
    if (args){
        fprintf(stderr, "-> This command doesn't take any arguments\n");
        return 1;
    }
    return 0;
}
int exit_client(char * args){
    if (args){
        fprintf(stderr, "-> This command doesn't take any arguments\n");
        return 1;
    }
    return 0;
}
int unknown(char * args){
    if (args)
        fprintf(stderr,"-> Unknown command and arguments, please try again:\nMENU");
    else 
        fprintf(stderr,"-> Unknown command, please try again:\nMENU");
    return 0;
}