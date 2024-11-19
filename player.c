#include "player.h"
int fd,errcode;
ssize_t n;
socklen_t addrlen;
struct addrinfo hints,*res, *p;
char input[1024], hostname[1024];
char * port;
char ipstr[128];
char * ip;

/* 
"If  this  argument  is  omitted,  the  GS  should  be running on the same machine."
    then we get the IP address from the machine that is running the player?
    Can't we just assume 127.0.1.1?
    To be safe created getIPAddress to get it.
*/ 
void getIPAddress(){
    if (gethostname(hostname, sizeof(hostname)) != 0) {
        fprintf(stderr, "-> Failed to get hostname\n");
        return;
    }
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET; // Only IPv4 for simplicity
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(hostname, NULL, &hints, &res) != 0) {
        fprintf(stderr, "Failed to get address info\n");
        return;
    }
    for (p = res; p != NULL; p = p->ai_next) {
        struct sockaddr_in *addr = (struct sockaddr_in *)p->ai_addr;
        inet_ntop(p->ai_family, &(addr->sin_addr), ipstr, sizeof(ipstr));
        ip = strdup(ipstr); // Copy the IP address to ip
        break;
    }
}

void start(char * args){
    if (!args){
        fprintf(stderr, "-> This command needs arguments\n");
        return;
    }
    printf("%s\n", args);
}
void try(char * args){
    if (!args){
        fprintf(stderr, "-> This command needs arguments\n");
        return;
    }
    printf("%s\n", args);
}
void show_trials(char * args){
    if (args){
        fprintf(stderr, "-> This command doesn't take any arguments");
        return;
    }
}
void scoreboard(char * args){
    if (args){
        fprintf(stderr, "-> This command doesn't take any arguments");
        return;
    }
}
void quit(char * args){
    if (args){
        fprintf(stderr, "-> This command doesn't take any arguments\n");
        return;
    }
}
void exit_client(char * args){
    if (args){
        fprintf(stderr, "-> This command doesn't take any arguments\n");
        return;
    }
}
void unknown(char * args){
    if (args)
        fprintf(stderr,"-> Unknown command and arguments, please try again:\nMENU");
    else 
        fprintf(stderr,"-> Unknown command, please try again:\nMENU");
}

int main(int argc, char *argv[]){
    printf("-> MENU:\n%s\n", MENU);
    switch (argc){
        case 1:
            // same IP as the server and definied port (5800+GN)
            port = PORT;
            getIPAddress();
            break;
        case 3:
            if (!strcmp(argv[1], "-n")){
                ip = argv[2];
                port = PORT;
            }
            else {
                if (!strcmp(argv[1], "-p")){
                    port = argv[2];
                    getIPAddress();
                }
                else{
                    fprintf(stderr,"-> Flag not defined, flags:\n  %s\n", FLAGS);
                    return -1;
                }
            }
            break;
        case 5:
            //check flags
            if (strcmp(argv[1],"-n") || strcmp(argv[3],"-p")){
                fprintf(stderr, "-> Flag not defined or not ordered correctly, flags:\n    %s\n", FLAGS);
                return -1;
            }
            ip = argv[2];
            port = argv[4];
            break;
            
        default:
            fprintf(stderr, "-> Wrong number of arguments, flags:\n    %s\n", FLAGS);
            return -1;
            break;
    }
    char * command;
    char * arguments;
    int i;

    //commands
    while (1){
        if (!fgets(input, sizeof(input)-1, stdin)){
            fprintf(stderr, "-> Unable to read command, please try again\n");
        }
        input[strlen(input) - 1] = '\0';

        command = strtok(input, " ");
        if (command){
            arguments = strtok(NULL,"\0");
            for (i = 0; commandTable[i].command != NULL; i++) {
                if (!strcmp(command, commandTable[i].command)){
                    commandTable[i].handler(arguments);
                    break;
                }
            }
            if (!commandTable[i].command)
                fprintf(stderr, "-> Unknown command, please try again\n");
        }
        else
            fprintf(stderr, "-> Choose a command\n");
    }
}