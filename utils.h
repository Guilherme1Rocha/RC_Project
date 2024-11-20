#ifndef UTILS_H
#define UTILS_H

#define COLORS_MOVE 4
#define PLAYER_ID_SIZE 6
#define MAX_PLAYTIME_SIZE 3

#define VALID_COLORS 6

#define RED "R"
#define GREEN "G"
#define BLUE "B"
#define YELLOW "Y"
#define ORANGE "O"
#define PURPLE "P"

char *colors[] = {RED, GREEN, BLUE, YELLOW, ORANGE, PURPLE};

//buffer for server communication
extern char buffer[1024];

#endif

