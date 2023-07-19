#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<libgen.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<errno.h>
#define N 4096
char program[FILENAME_MAX];

/**
 * @brief Setta tutti le varie impostazioni per la socket e la struct sockaddr_in.
 * @param sockfd File descriptor della socket.
 * @param addr Struct dove settare tutte le informazioni legate all'indirizzo ip, numero di porta e famiglia della socket.
 * @param addrlen Lunghezza della struct sockaddr_in o struct sockaddr (hanno lo stesso numero di byte).
 * @param addess Indirizzo IPv4 a cui mandare pacchetti, se viene passata come NULL verrà impostata a INADDR_ANY.
 * @param porta Porta sulla quale indirizzare i pacchetti entranti.
 * @return In caso di errore verrà restituito -1, altrimenti 0.
*/
int sockaddrSettings(int*sockfd, struct sockaddr_in*addr, socklen_t*addrlen, char*address, in_port_t porta)
{
    *addrlen=sizeof(struct sockaddr);
    if((*sockfd=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP))==-1)
    {
        fprintf(stderr,"%s: socket: %s\n",program,strerror(errno));
        return -1;
    }
    memset((char*)addr,0,*addrlen);
    addr->sin_family=AF_INET;
    addr->sin_addr.s_addr=(!address)?INADDR_ANY:inet_addr(address);
    addr->sin_port=htons(porta);
    return 0;
}

/**
 * @brief Funzione che viene utilizzata come client nella comunicazione, manda un messaggio di riconoscimento al server e dopo si mette in ascolto ed esegue varie istruzioni da parte del server, la comunicazione sfrutta il protocollo al livello trasporto: User Datagram Protocol
 * @param address Indirizzo IPv4 con il quale il client comunica col in server.
 * @param porta Porta che il server utilizza per reindirizzare tutti i pacchetti in entrata.
 * @return Restituisce -1 in caso di errore, 0 altrimenti.
*/
int client(char*address, in_port_t porta)
{
    int sockfd;
    struct sockaddr_in addr;
    socklen_t addrlen;
    if((sockaddrSettings(&sockfd,&addr,&addrlen,address,porta))==-1)
    {
        return -1;
    }
    char buffer[N];
    ssize_t size;
    memset(buffer,'\0',strlen(buffer));
    buffer[0]='\n';
    if((sendto(sockfd,buffer,strlen(buffer),0,(struct sockaddr*)&addr,addrlen))==-1)
    {
        fprintf(stderr,"%s: sendto: %s\n",program,strerror(errno));
        close(sockfd);
        return -1;
    }
    while(true)
    {
        memset(buffer,'\0',strlen(buffer));
        if((size=recvfrom(sockfd,buffer,N,0,(struct sockaddr*)&addr,&addrlen))==-1)
        {
            fprintf(stderr,"%s: recvfrom: %s\n",program,strerror(errno));
            close(sockfd);
            return -1;
        }
        buffer[size]='\0';
        if((write(1,buffer,strlen(buffer)))==-1)
        {
            fprintf(stderr,"%s: write: %s\n",program,strerror(errno));
            close(sockfd);
            return -1;
        }
        fgets(buffer,N,stdin);
        buffer[strcspn(buffer,"\n")]='\0';
        if((sendto(sockfd,buffer,strlen(buffer),0,(struct sockaddr*)&addr,addrlen))==-1)
        {
            fprintf(stderr,"%s: sendto: %s\n",program,strerror(errno));
            close(sockfd);
            return -1;
        }
        memset(buffer,'\0',strlen(buffer));
        if((size=recvfrom(sockfd,buffer,N,0,(struct sockaddr*)&addr,&addrlen))==-1)
        {
            fprintf(stderr,"%s: recvfrom: %s\n",program,strerror(errno));
            close(sockfd);
            return -1;
        }
        buffer[size]='\0';
        if((write(1,buffer,strlen(buffer)))==-1)
        {
            fprintf(stderr,"%s: write: %s\n",program,strerror(errno));
            close(sockfd);
            return -1;
        }
    }
    close(sockfd);
    return 0;
}

int main(int argc, char**argv)
{
    extern int errno;
    strcpy(program,basename(argv[0]));
    if(argc!=3)
    {
        printf("\x1b[31musage: %s <address> <porta>\x1b[0m\n",program);
    }
    else
    {
        if((client(argv[1],atoi(argv[2])))==-1)
        {
            exit(EXIT_FAILURE);
        }
    }
    exit(EXIT_SUCCESS);
}