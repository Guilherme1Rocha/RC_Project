#include "clientCommands.h"
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
// command specifications
#define FLAGS "[-n GSIP] [-p GSport]"
#define MENU "start PLID max_playtime\ntry C1 C2 C3 C4\nshow_trials 'or' st\nscoreboard 'or' sb\nquit\nexit\ndebug PLID max_playtime C1 C2 C3 C4\n"
// connection variables
int fd,errcode;
ssize_t n;
socklen_t addrlen;
struct addrinfo hints,*res, *p;
struct sockaddr_in addr;
char hostname[1024];
char * port;
char ipstr[128];
char * ip;

char input[1024];

char buffer[1024];
// FAZER APENAS ACCEPT DO TCP DENTRO DO IF DO SELECT

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

int main(int argc, char *argv[]){
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
    printf("-> MENU:\n%s\n", MENU);
    char * command;
    char * arguments;
    int i;
    fd = socket(AF_INET,SOCK_DGRAM,0); //UDP socket
    if(fd==-1) /*error*/
        exit(1);

    memset(&hints,0,sizeof hints);
    hints.ai_family = AF_INET; //IPv4
    hints.ai_socktype=SOCK_DGRAM; //UDP socket
    errcode=getaddrinfo("tejo.tecnico.ulisboa.pt",PORT,&hints,&res);

    //wait for command
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
                    char buffer_resServer[128];
                    if (!commandTable[i].handler(arguments)){
                        //call server communication function
                        n = sendto(fd,buffer,strlen(buffer),0,res->ai_addr,res->ai_addrlen);
                        if(n == -1){
                            exit(1);
                        } /*error*/ 
                        addrlen = sizeof(addr);
                        n = recvfrom(fd,buffer_resServer,128,0,(struct sockaddr*)&addr,&(addrlen));
                        if(n == -1) /*error*/ 
                            exit(1); 
                        printf("%s\n", buffer_resServer);
                    }
                    break;
                }
            }
            if (!commandTable[i].command)
                fprintf(stderr, "-> Unknown command, please try again\n");
        }
        else
            fprintf(stderr, "-> Choose a command\n");
    }
    return 0;
}