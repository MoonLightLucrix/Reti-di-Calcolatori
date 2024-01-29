#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<libgen.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<errno.h>
#define N 1024
#define MAX_FORM_LENGTH 32
typedef __uint32_t ID;
typedef struct
{
    ID id;
    char username[MAX_FORM_LENGTH];
    char lettera[N];
} Client;
typedef enum{SEND,LIST,EDIT,CANCEL,QUIT,NONE} Request;
typedef enum{OK,CONTINUE,NOTFOUND,TERMINATE,ERROR=-1} Reply;
typedef struct
{
    Client client;
    Request request;
    Reply reply;
    char msg[N];
} Messaggio;
char program[FILENAME_MAX];

/**
 * @brief Setta tutti le varie impostazioni per la socket e la struct sockaddr_in.
 * @param sockfd Socket da settare.
 * @param addr Struct sockaddr_in da settare.
 * @param addrlen Dimensione della struct sockaddr_in da settare.
 * @param address Indirizzo IPv4 a cui mandare pacchetti, se viene passata come NULL verrà impostata a INADDR_ANY.
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
    bzero((char*)addr,*addrlen);
    addr->sin_family=AF_INET;
    addr->sin_addr.s_addr=(!address)?INADDR_ANY:inet_addr(address);
    addr->sin_port=htons(porta);
    return 0;
}

/**
 * @brief Funzione che viene utilizzata come client nella comunicazione, usa un menù, e la richiesta con le altre informazioni viene mandata al Server per l'elaborazione, il Server risponderà con la risorsa e la risposta per il Client, il protocollo al livello trasporto: User Datagram Protocol.
 * @param username Username scelto dal Client per identificarsi con il Server.
 * @param address Indirizzo IPv4 con il quale il client comunica col in server.
 * @param porta Porta sulla quale vengono reindirizzati i pacchetti in entrata.
 * @return Restituisce -1 in caso di errore, 0 altrimenti.
*/
int client(char*username, char*address, in_port_t porta)
{
    int sockfd;
    struct sockaddr_in rAddr;
    socklen_t addrlen;
    if((sockaddrSettings(&sockfd,&rAddr,&addrlen,address,porta))==-1)
    {
        return -1;
    }
    Messaggio messaggio;
    char buffer[N];
    int e=0;
    bool m;
    printf("   \x1b[31m___           _          _   _            \x1b[32m___ _          _     _                       \n  \x1b[31m/ _ \\__ _  ___| |__   ___| |_| |_ ___     \x1b[32m/ __\\ |__  _ __(_)___| |_ _ __ ___   __ _ ___ \n \x1b[31m/ /_)/ _` |/ __| '_ \\ / _ \\ __| __/ _ \\   \x1b[32m/ /  | '_ \\| '__| / __| __| '_ ` _ \\ / _` / __|\n\x1b[31m/ ___/ (_| | (__| | | |  __/ |_| || (_) | \x1b[32m/ /___| | | | |  | \\__ \\ |_| | | | | | (_| \\__ \\\n\x1b[31m\\/    \\__,_|\\___|_| |_|\\___|\\__|\\__\\___/  \x1b[32m\\____/|_| |_|_|  |_|___/\\__|_| |_| |_|\\__,_|___/\n                                                                                          \x1b[0m\n\x1b[31mBuone Feste!\x1b[0m\n\n\n");
    while(true)
    {
        if(messaggio.request!=EDIT)
        {
            if(strcmp(buffer,"\n"))
            {
                printf("+------------------------+\n| s - manda un messaggio |\n| l - lista messaggi     |\n| m - modifica messaggio |\n| c - cancella messaggio |\n| q - esci               |\n+------------------------+\n\n\n\n\n\n\nScelta: ");
            }
            else
            {
                printf("Scelta: ");
            }
            fflush(stdout);
            bzero(buffer,strlen(buffer));
            fgets(buffer,N,stdin);
            buffer[strcspn(buffer,"\n")]='\0';
        }
        else
        {
            buffer[0]='s';
        }
        bzero((char*)&messaggio,sizeof(Messaggio));
        strcpy(messaggio.client.username,username);
        if(!strcmp(buffer,"s"))
        {
            printf("%s la letterina: ",(!m)?"Inserisci":"Modifica");
            fflush(stdout);
            fgets(messaggio.client.lettera,N,stdin);
            messaggio.client.lettera[strcspn(messaggio.client.lettera,"\n")]='\0';
            //printf("strlen(messaggio.client.lettera): %lu\n",strlen(messaggio.client.lettera));
            messaggio.request=SEND;
        }
        else if(!strcmp(buffer,"l"))
        {
            messaggio.request=LIST;
        }
        else if((m=(!strcmp(buffer,"m"))))
        {
            printf("Inserisci l'id del messaggio da modificare: ");
            fflush(stdout);
            fgets(buffer,N,stdin);
            buffer[strcspn(buffer,"\n")]='\0';
            messaggio.client.id=atoi(buffer);
            messaggio.request=EDIT;
        }
        else if(!strcmp(buffer,"c"))
        {
            printf("Inserisci l'id del messaggio da cancellare: ");
            fflush(stdout);
            fgets(buffer,N,stdin);
            buffer[strcspn(buffer,"\n")]='\0';
            messaggio.client.id=atoi(buffer);
            messaggio.request=CANCEL;
        }
        else if(!strcmp(buffer,"q"))
        {
            messaggio.request=QUIT;
        }
        else
        {
            if(buffer[0]!='\0')
            {
                printf("Comando sconosciuto\n");
            }
            else
            {
                buffer[0]='\n';
            }
            continue;
        }
        if((sendto(sockfd,&messaggio,sizeof(Messaggio),0,(struct sockaddr*)&rAddr,addrlen))==-1)
        {
            fprintf(stderr,"%s: sendto: %s\n",program,strerror(errno));
            e=-1;
            break;
        }
        do{
            bzero((char*)&messaggio,sizeof(Messaggio));
            if((recvfrom(sockfd,&messaggio,sizeof(Messaggio),0,(struct sockaddr*)&rAddr,&addrlen))==-1)
            {
                fprintf(stderr,"%s: recvfrom: %s\n",program,strerror(errno));
                e=-1;
                break;
            }
            printf("%s",messaggio.msg);
            if(((messaggio.reply==CONTINUE) || (messaggio.request==EDIT) || (messaggio.request==CANCEL)) && (messaggio.reply!=NOTFOUND))
            {
                printf("%d\t%s\n",messaggio.client.id,messaggio.client.lettera);
            }
        }while(messaggio.reply==CONTINUE);
        if((messaggio.reply==TERMINATE) || (messaggio.reply==ERROR))
        {
            break;
        }
        if((messaggio.request==EDIT) && (messaggio.reply==NOTFOUND))
        {
            m^=m;
            messaggio.request=NONE;
        }
    }
    close(sockfd);
    return e;
}

int main(int argc, char**argv)
{
    extern int errno;
    strcpy(program,basename(argv[0]));
    if(argc!=4)
    {
        printf("usage: %s <username> <address> <porta>\n",program);
    }
    else
    {
        if((client(argv[1],argv[2],atoi(argv[3])))==-1)
        {
            exit(EXIT_FAILURE);
        }
    }
    exit(EXIT_SUCCESS);
}