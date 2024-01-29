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
#define tableLista "lista.txt"
#define MAX_FORM_LENGTH 32
typedef __uint32_t ID;
typedef struct Client
{
    ID id;
    char username[MAX_FORM_LENGTH];
    char lettera[N];
} Client;
typedef enum Request{SEND,LIST,EDIT,CANCEL,QUIT,NONE} Request;
typedef enum Reply{OK,CONTINUE,NOTFOUND,TERMINATE,ERROR=-1} Reply;
typedef struct Messaggio
{
    Client client;
    Request request;
    Reply reply;
    char msg[N];
} Messaggio;
char program[FILENAME_MAX];

/**
 * @brief Aggiunge un nuovo elemento alla tabella Lista.
 * @param client Tutte le informazioni della lettera.
 * @param fsd File descriptor stream del file dove vengono inserite le new entry.
*/
void fadd(Client client, FILE*fsd)
{
    fprintf(fsd,"%d\t%s\t%s\n",client.id,client.username,client.lettera);
}

/**
 * @brief Trova la riga nel database in base alla chiave primaria.
 * @param key Chiave primaria da cercare, questa è univoca per ogni riga.
 * @param fsd File descriptor stream del file dove viene richiesta la ricerca.
 * @return Viene restituito un puntatore al primo char della tupla trovata, altrimenti restituisce NULL se la tupla non esiste.
*/
char*ffind(ID key, FILE*fsd)
{
    rewind(fsd);
    ID akey;
    char line[sizeof(Client)];
    while(fgets(line,sizeof(Client),fsd))
    {
        sscanf(line,"%d",&akey);
        if(!(key^akey)) //==
        {
            return strdup(line); //SELECT * FROM Lista WHERE key=akey
        }
    }
    return NULL;
}

/**
 * @brief Elimina la riga richiesta come parametro se questa viene trovata.
 * @param row Riga da eliminare.
 * @param fsd File descriptor stream del file dove viene richiesta la ricerca.
*/
void fdelete(char*line, FILE*fsd)
{
    rewind(fsd);
    char aline[sizeof(Client)];
    size_t size;
    FILE*ftmp=tmpfile();
    while(fgets(aline,sizeof(Client),fsd))
    {
        if(strcmp(line,aline))
        {
            fputs(aline,ftmp);
        }
    }
    rewind(fsd);
    rewind(ftmp);
    do{
        bzero(aline,strlen(aline));
        size=fread(aline,1,sizeof(Client),ftmp);
        fwrite(aline,1,size,fsd);
    }while(sizeof(Client)==size);
    ftruncate(fileno(fsd),ftell(fsd));
    fclose(ftmp);
}

/**
 * @brief Restituisce i campi di una tupla all'interno di un tipo Client e poi procede ad eliminare la tupla.
 * @param client Se la tupla viene trovata la struct viene riempita con tutti i campi della tupla.
 * @param key Chiave primaria della tupla da cercare.
 * @param fsd File descriptor stream del file dove viene richiesta la ricerca.
 * @return Restituisce true se l'operazione è andata a buon fine, false altrimenti.
*/
bool fpop(Client*client, ID key, FILE*fsd)
{
    char*row;
    bool found=false;
    if((found=(row=ffind(key,fsd))))
    {
        char line[strlen(row)];
        strcpy(line,row);
        free(row);
        sscanf(line,"%d\t%[^\t]\t%[^\n]",&client->id,client->username,client->lettera);
        fdelete(line,fsd);
    }
    return found;
}

/**
 * @brief Conta tutte le tuple della tabella Lista.
 * @param fsd File descriptor stream del file dove vengono contate tutte le tuple.
 * @return Numero di tuple della tabella Lista.
*/
ID fcount(FILE*fsd)
{
    ID id;
    char line[sizeof(Client)];
    for(id=0; fgets(line,sizeof(Client),fsd); id-=-1){}
    return id;
}

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
 * @brief Inserisce una nuova letterina e le altre informazioni alla tabella Lista.
 * @param messaggio Struct contenente tutte le informazioni della letterina ed altre informazioni riguardanti richieste dal Client al quale la funzione risponderà.
 * @return In caso di errore verrà restituito -1, altrimenti 0.
*/
int newMsg(Messaggio*messaggio)
{
    FILE*fsd;
    if(!(fsd=fopen(tableLista,"r+")))
    {
        fprintf(stderr,"%s: fopen: %s\n",program,strerror(errno));
        messaggio->reply=ERROR;
        return -1;
    }
    messaggio->client.id=fcount(fsd);
    fadd(messaggio->client,fsd);
    fclose(fsd);
    messaggio->reply=OK;
    sprintf(messaggio->msg,"%s: Letterina aggiunta!\n",program);
    return 0;
}

/**
 * @brief Restituisce al Client la lista di tutte le sue letterine inviate al Server.
 * @param sockfd File descriptor della socket che viene usata per la comunicazione col Client.
 * @param addr Struct sockaddr_in contenente le informazioni per comunicare col Client.
 * @param addrlen Dimensione della struct sockaddr_in che viene utilizzata per comunicare col Client.
 * @param messaggio Struct contenente l'username del Client ed altre informazioni riguardanti richieste dal Client al quale la funzione risponderà.
 * @return In caso di errore verrà restituito -1, altrimenti 0.
*/
int getListMsg(int sockfd, struct sockaddr_in addr, socklen_t addrlen, Messaggio*messaggio)
{
    FILE*fsd;
    if(!(fsd=fopen(tableLista,"r")))
    {
        fprintf(stderr,"%s: fopen: %s\n",program,strerror(errno));
        messaggio->reply=ERROR;
        return -1;
    }
    char line[sizeof(Client)];
    Client client;
    while(fgets(line,sizeof(Client),fsd))
    {
        bzero((char*)&client,sizeof(Client));
        sscanf(line,"%d\t%[^\t]\t%[^\n]",&client.id,client.username,client.lettera);
        if(!strcmp(messaggio->client.username,client.username))
        {
            //printf("messaggio->client.username: %s\nclient.username: %s\n",messaggio->client.username,client.username);
            messaggio->client.id=client.id;
            strcpy(messaggio->client.lettera,client.lettera);
            //printf("messaggio->client.lettera: %s\n",messaggio->client.lettera);
            messaggio->reply=CONTINUE;
            if((sendto(sockfd,messaggio,sizeof(Messaggio),0,(struct sockaddr*)&addr,addrlen))==-1)
            {
                fprintf(stderr,"%s: sendto: %s\n",program,strerror(errno));
                messaggio->reply=ERROR;
                return -1;
            }
            /*if(messaggio->reply==CONTINUE)
            {
                printf("messaggio->reply: CONTINUE\n");
            }*/
        }
    }
    fclose(fsd);
    messaggio->reply=OK;
    return 0;
}

/**
 * @brief Effettua viene estratta la tupla selezionata dall'id dalla tabella Lista e viene restituita al Client.
 * @param messaggio Struct contenente l'id della letterina e l'username del Client ed altre informazioni riguardanti richieste dal Client al quale la funzione risponderà.
 * @return In caso di errore verrà restituito -1, altrimenti 0.
*/
int getMsg(Messaggio*messaggio)
{
    FILE*fsd;
    if(!(fsd=fopen(tableLista,"r+")))
    {
        fprintf(stderr,"%s: fopen: %s\n",program,strerror(errno));
        messaggio->reply=ERROR;
        return -1;
    }
    Client client;
    if(fpop(&client,messaggio->client.id,fsd))
    {
        if(!strcmp(client.username,messaggio->client.username))
        {
            messaggio->reply=OK;
            sprintf(messaggio->msg,"%s: Messaggio selezionato:\n",program);
            strcpy(messaggio->client.lettera,client.lettera);
            return 0;
        }
        else
        {
            fadd(client,fsd);
        }
    }
    fclose(fsd);
    messaggio->reply=NOTFOUND;
    sprintf(messaggio->msg,"%s: Il messaggio cercato non è stato trovato :(\n",program);
    return 0;
}

/**
 * @brief Funzione che viene utilizzata come server nella comunicazione, attende che un Client effettui una richiesta, la esegue e viene restituita la risorsa al Client insieme ad una risposta, il protocollo utilizzato è User Datagram Protocol.
 * @param porta Porta sulla quale vengono reindirizzati i pacchetti in entrata.
 * @return Restituisce -1 in caso di errore, 0 altrimenti.
*/
int server(in_port_t porta)
{
    int sockfd;
    struct sockaddr_in lAddr, rAddr;
    socklen_t addrlen;
    if((sockaddrSettings(&sockfd,&lAddr,&addrlen,NULL,porta))==-1)
    {
        return -1;
    }
    if((bind(sockfd,(struct sockaddr*)&lAddr,addrlen))==-1)
    {
        fprintf(stderr,"%s: bind: %s\n",program,strerror(errno));
        close(sockfd);
        return -1;
    }
    if((creat(tableLista, S_IRUSR | S_IWUSR| S_IRGRP | S_IROTH))==-1) //644 rw-r--r--
    {
        fprintf(stderr,"%s: creat: %s\n",program,strerror(errno));
        close(sockfd);
        return -1;
    }
    Messaggio messaggio;
    int e=0;
    printf("%s: Attendo connessioni sulla porta %d\n",program,ntohs(lAddr.sin_port));
    while(true)
    {
        bzero((char*)&messaggio,sizeof(Messaggio));
        if((recvfrom(sockfd,&messaggio,sizeof(Messaggio),0,(struct sockaddr*)&rAddr,&addrlen))==-1)
        {
            fprintf(stderr,"%s: recvfrom: %s\n",program,strerror(errno));
            e=-1;
            break;
        }
        if(messaggio.request==LIST)
        {
            //printf("messaggio.request: LIST\n");
            e=getListMsg(sockfd,rAddr,addrlen,&messaggio);
        }
        else if(messaggio.request==SEND)
        {
            e=newMsg(&messaggio);
        }
        else if((messaggio.request==EDIT) || (messaggio.request==CANCEL))
        {
            e=getMsg(&messaggio);
        }
        else if(messaggio.request==QUIT)
        {
            sprintf(messaggio.msg,"Arrivederci %s!\n",messaggio.client.username);
            messaggio.reply=TERMINATE;
        }
        if((sendto(sockfd,&messaggio,sizeof(Messaggio),0,(struct sockaddr*)&rAddr,addrlen))==-1)
        {
            fprintf(stderr,"%s: sendto: %s\n",program,strerror(errno));
            e=-1;
            break;
        }
        if(e==-1)
        {
            break;
        }
    }
    close(sockfd);
    return e;
}

int main(int argc, char**argv)
{
    extern int errno;
    strcpy(program,basename(argv[0]));
    if(argc!=2)
    {
        printf("usage: %s <porta>\n",program);
    }
    else
    {
        if((server(atoi(argv[1])))==-1)
        {
            exit(EXIT_FAILURE);
        }
    }
    exit(EXIT_SUCCESS);
}