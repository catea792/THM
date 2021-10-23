#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <stdbool.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <netdb.h>
#include <arpa/inet.h>
#include <ctype.h>

void getIP(char *s,struct hostent *hostIF){
    struct in_addr **AliasIPs;   
    hostIF = gethostbyname(s);
    if(hostIF == NULL) { 
        printf("Not found information\n\n"); 
    }else{
        printf("Official address: %s\n", inet_ntoa(*(struct in_addr*)hostIF->h_addr));
        printf("Alias IP: \n");
        AliasIPs = (struct in_addr **)hostIF->h_addr_list;
        for(int i = 0; AliasIPs[i] != NULL; i++) {
            printf("%s\n", inet_ntoa(*AliasIPs[i]));
        }
        printf("\n");
    }
             
}

void getDomain(char* s, struct in_addr addr){
    struct hostent *hostIF; 
    inet_aton(s, &addr);
    hostIF = gethostbyaddr(&addr, sizeof(addr), AF_INET);
    if (hostIF == NULL) { 
        printf("Not found information\n\n"); 
        
    }else{
        printf("Host name: %s\n", hostIF->h_name);
        printf("Alias name: \n");
        if (hostIF->h_aliases[0] == NULL)
        {
            printf("NULL\n\n");
        }
        else
        {
            for (int i = 0; hostIF->h_aliases[i] != NULL; i++){
                printf("\t%s\n", hostIF->h_aliases[i]);
            }
        }
    }
}

int main(int argc ,const char *argv[]){
    struct hostent *hostIF;
    struct in_addr **AliasIP;
    struct in_addr addr;

    int check;  // check parameter2
    
    sscanf(argv[1],"%d",&check);
    if (argc == 3)
    {
        if(check == 2){
            char* temp = argv[2];  // check IP or Domain
            if (atoi(temp)==0){
                getIP(temp,hostIF);
            }
            else {
                printf("Wrong parameter\n\n");
            }
        }

        if(check == 1){
            char *temp=argv[2];  // check IP or Domain
            
            if (atoi(temp)!=0)
            {
               getDomain(temp,addr);
            }
            else printf("Wrong parameter\n\n");
        }

    }else printf("Invalid Input! Please enter follow format! \n\n");
    
}