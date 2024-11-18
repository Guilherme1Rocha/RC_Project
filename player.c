#include "player.h"
int fd,errcode;
ssize_t n;
socklen_t addrlen;
struct addrinfo hints,*res, *p;
char buffer[128], hostname[1024];
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
        fprintf(stderr, "Failed to get hostname\n");
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
    char flags[] = "[-n GSIP] [-p GSport]";

    switch (argc){
        case 1:
            // same IP as the server and definied port (5800+GN)
            port = PORT;
            getIPAddress();
            break;
        case 3:
            if (!strcmp(argv[1], "-n")){
                ip = argv[2];
                //printf("IP optional: %s\n", ip_address);
                port = PORT;
            }
            else {
                if (!strcmp(argv[1], "-p")){
                    port = argv[2];
                    getIPAddress();
                    //printf("PORT optional: %s\n", port);
                }
                else{
                    fprintf(stderr,"Flag not defined, flags:\n  %s\n", flags);
                    return -1;
                }
            }
            break;
        case 5:
            //check flags
            if (strcmp(argv[1],"-n") || strcmp(argv[3],"-p")){
                fprintf(stderr, "Flag not defined or not ordered correctly, flags:\n    %s\n", flags);
                return -1;
            }
            ip = argv[2];
            port = argv[4];
            break;
            
        default:
            fprintf(stderr, "Wrong number of arguments, flags:\n    %s\n", flags);
            return -1;
            break;
    }
    printf("IP: %s  PORT: %s\n", ip, port);
}