#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/file.h>
#include<libgen.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<signal.h>
#include<errno.h>
#define N 4096
#define MAX_FORM_LENGTH 32
#define tableCaffe "../Caffe.txt"
#define backlog 10
typedef __uint32_t ID;
typedef struct Caffe
{
    ID id;
    char nome[MAX_FORM_LENGTH];
    double prezzo;
    __uint32_t quantità;
} Caffe;
typedef struct SocketInfo
{
    int sockfd;
    struct sockaddr_in addr;
    socklen_t addrlen;
} SocketInfo;
char program[FILENAME_MAX];

/**
 * @brief Funzione che viene evocata al ricezione del signal interrupt evita che ci siano processi zombie in esecuzione quando si vuole terminare il programma.
 * @param signal Tipo di signal registrato sulla quale la funzione signal viene impostata sulla cattura, in questo caso il signal di tipo SIGINT. 
*/
void signalHandler(int signal)
{
    kill(0,SIGTERM);
}

/**
 * @brief Aggiunge un nuovo caffé alla tabella Caffe.
 * @param caffe Tutte le informazioni del caffé.
 * @param fsd File descriptor stream del file dove vengono inserite le new entry.
*/
void fadd(Caffe caffe, FILE*fsd)
{
    fprintf(fsd,"%d\t%s\t%.2f\t%d\n",caffe.id,caffe.nome,caffe.prezzo,caffe.quantità);
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
    char line[N];
    ID akey;
    while(fgets(line,N,fsd))
    {
        sscanf(line,"%d",&akey);
        if(!(key^akey))
        {
            return strdup(line);
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
    char aline[N];
    size_t size;
    FILE*ftmp=tmpfile();
    while(fgets(aline,N,fsd))
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
        size=fread(aline,1,N,ftmp);
        fwrite(aline,1,size,fsd);
    }while(size==N);
    ftruncate(fileno(fsd),ftell(fsd));
    fclose(ftmp);
}

/**
 * @brief Restituisce i campi di una tupla all'interno di un tipo Caffe e poi procede ad eliminare la tupla.
 * @param caffe Se la tupla viene trovata la struct viene riempita con tutti i campi della tupla.
 * @param key Chiave primaria della tupla da cercare.
 * @param fsd File descriptor stream del file dove viene richiesta la ricerca.
 * @return Restituisce true se l'operazione è andata a buon fine, false altrimenti.
*/
bool fpop(Caffe*caffe, ID key, FILE*fsd)
{
    char*row;
    bool found=false;
    if((found=(row=ffind(key,fsd))))
    {
        char line[strlen(row)];
        strcpy(line,row);
        free(row);
        sscanf(line,"%d\t%[^\t]\t%lf\t%d\n",&caffe->id,caffe->nome,&caffe->prezzo,&caffe->quantità);
        fdelete(line,fsd);
    }
    return found;
}

/**
 * @brief Setta tutti le varie impostazioni per la socket e la struct sockaddr_in.
 * @param sockaddr SocketInfo da settare.
 * @param address Indirizzo IPv4 a cui mandare pacchetti, se viene passata come NULL verrà impostata a INADDR_ANY.
 * @param porta Porta sulla quale indirizzare i pacchetti entranti.
 * @return In caso di errore verrà restituito -1, altrimenti 0.
*/
int sockaddrSettings(SocketInfo*sockaddr, char*address, in_port_t porta)
{
    sockaddr->addrlen=sizeof(struct sockaddr_in);
    if((sockaddr->sockfd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))==-1)
    {
        fprintf(stderr,"%s: socket: %s\n",program,strerror(errno));
        return -1;
    }
    bzero((char*)&sockaddr->addr,sockaddr->addrlen);
    sockaddr->addr.sin_family=AF_INET;
    sockaddr->addr.sin_addr.s_addr=(!address)?INADDR_ANY:inet_addr(address);
    sockaddr->addr.sin_port=htons(porta);
    return 0;
}

/**
 * @brief Invia al Client la lista completa delle bevande con quantità maggiore di 0.
 * @param remote Struct contenente tutte le informazioni della socket.
 * @return Restituisce -1 ed un messaggio di errno se si è verificato un problema, 0 altrimenti.
*/
int lista(SocketInfo remote)
{
    char line[N];
    ssize_t size;
    __uint32_t quantità;
    FILE*fsd;
    if(!(fsd=fopen(tableCaffe,"r")))
    {
        fprintf(stderr,"%s: fopen: %s\n",program,strerror(errno));
        return -1;
    }
    flock(fileno(fsd),LOCK_EX);
    Caffe caffe;
    while(fgets(line,N,fsd))
    {
        bzero((char*)&caffe,sizeof(Caffe));
        sscanf(line,"%d\t%[^\t]\t%lf\t%d\n",&caffe.id,caffe.nome,&caffe.prezzo,&caffe.quantità);
        bzero(line,strlen(line));
        //printf("%d\n",caffe.id);
        sprintf(line,"%d, %s, €%.2f, %d\n",caffe.id,caffe.nome,caffe.prezzo,caffe.quantità);
        if((write(remote.sockfd,line,strlen(line)))==-1)
        {
            fprintf(stderr,"%s: write: %s\n",program,strerror(errno));
            flock(fileno(fsd),LOCK_UN);
            fclose(fsd);
            return -1;
        }
    }
    flock(fileno(fsd),LOCK_UN);
    fclose(fsd);
    return 0;
}

/**
 * @brief Permette al client di acquistare una bevanda se la quantità richiesta dal client è minore di quella presenta nel Database, se no manda un messaggio di errore al client.
 * @param remote Struct contenente tutte le informazioni della socket.
 * @param id ID della bevanda che il client richiedono l'erogazione, nel caso in cui la bevanda non esiste verrà mandato al client un messaggio di errore.
 * @return Restituisce 0 se l'operazione è andata a buon fine, -1 altrimenti.
*/
int acquisto(SocketInfo remote, ID id, __uint32_t quantità)
{
    Caffe caffe;
    char buffer[N];
    ssize_t size;
    FILE*fsd;
    if(!(fsd=fopen(tableCaffe,"r+")))
    {
        fprintf(stderr,"%s: fopen: %s\n",program,strerror(errno));
        return -1;
    }
    flock(fileno(fsd),LOCK_EX);
    if((fpop(&caffe,id,fsd)))
    {
        if((caffe.quantità>=quantità) && (quantità>=1))
        {
            dprintf(remote.sockfd,"%s: Prodotto erogato\n",program);
            caffe.quantità-=quantità;
        }
        else
        {
            dprintf(remote.sockfd,"%s: quantità non disponibile\n",program);
        }
        fadd(caffe,fsd);
    }
    else
    {
        dprintf(remote.sockfd,"%s: Errore: bevanda non trovata\n",program);
    }
    flock(fileno(fsd),LOCK_UN);
    fclose(fsd);
    return 0;
}

/**
 * @brief Gestisce la connessione col Client.
 * @param remote Struct contenente tutte le informazioni della socket.
 * @return Restituisce -1 in caso di errore, 0 altrimenti.
*/
int connection(SocketInfo remote)
{
    Caffe caffe;
    char buffer[N];
    ssize_t size;
    ID id;
    __uint32_t quantità;
    dprintf(remote.sockfd,"   \x1b[33m____       __  __      _   \x1b[31m____  __  __ ___ \n  \x1b[33m/ ___|__ _ / _|/ _| ___( ) \x1b[31m|  _ \\|  \\/  |_ _|\n \x1b[33m| |   / _` | |_| |_ / _ \\/  \x1b[31m| | | | |\\/| || | \n \x1b[33m| |__| (_| |  _|  _|  __/   \x1b[31m| |_| | |  | || | \n  \x1b[33m\\____\\__,_|_| |_|  \\___|   \x1b[31m|____/|_|  |_|___|\x1b[0m\n\n\n\n\n\n");
    int e=0;
    do{
        if((lista(remote))==-1)
        {
            close(remote.sockfd);
            return -1;
        }
        bzero(buffer,strlen(buffer));
        dprintf(remote.sockfd,"%s: Inserisci l'ID e quantità della bevanda da erogare (ID prodotto, quantità): ",program);
        if((size=read(remote.sockfd,buffer,N))==-1)
        {
            fprintf(stderr,"%s: read: %s\n",program,strerror(errno));
            e=-1;
            break;
        }
        buffer[size]='\0';
        sscanf(buffer,"%d, %d",&id,&quantità);
        if((acquisto(remote,id,quantità))==-1)
        {
            e=-1;
            break;
        }
        while(true)
        {
            bzero(buffer,strlen(buffer));
            dprintf(remote.sockfd,"%s: Premi q per concludere l'acquisto\n        Premi c per effettuare un nuovo acquisto\n%s: Scelta: ",program,program);
            if((size=read(remote.sockfd,buffer,N))==-1)
            {
                fprintf(stderr,"%s: read: %s\n",program,strerror(errno));
                e=-1;
                break;
            }
            buffer[size]='\0';
            if((strcmp(buffer,"c")) && (strcmp(buffer,"q")))
            {
                dprintf(remote.sockfd,"%s: Comando sconosciuto\n",program);
            }
            else
            {
                break;
            }
        }
    }while(buffer[0]=='c');
    close(remote.sockfd);
    return e;
}

/**
 * @brief Funzione che viene utilizzata come server nella comunicazione, attende che sia effettuata l'accept per creare una connessione che continuerà la comunicazione col client, mentre il processo padre si rimette in ascolto, il protocollo utilizzato è Trasmission Control Protocol.
 * @param porta Porta sulla quale vengono reindirizzati i pacchetti in entrata.
 * @return Restituisce -1 in caso di errore, 0 altrimenti.
*/
int server(in_port_t porta)
{
    SocketInfo locale, remote;
    if((sockaddrSettings(&locale,NULL,porta))==-1)
    {
        return -1;
    }
    if((bind(locale.sockfd,(struct sockaddr*)&locale.addr,locale.addrlen))==-1)
    {
        fprintf(stderr,"%s: bind: %s\n",program,strerror(errno));
        close(remote.sockfd);
        return -1;
    }
    listen(locale.sockfd,backlog);
    int e=0;
    pid_t pid;
    printf("%s: Attendo connessioni sulla porta %d…\n",program,ntohs(locale.addr.sin_port));
    while(true)
    {
        if((remote.sockfd=accept(locale.sockfd,(struct sockaddr*)&remote.addr,&remote.addrlen))==-1)
        {
            fprintf(stderr,"%s: accept: %s\n",program,strerror(errno));
            e=-1;
            break;
        }
        if((pid=fork())==-1)
        {
            fprintf(stderr,"%s: fork: %s\n",program,strerror(errno));
            close(remote.sockfd);
            e=-1;
            break;
        }
        if(!pid)
        {
            close(locale.sockfd);
            if((connection(remote))==-1)
            {
                exit(EXIT_FAILURE);
            }
            exit(EXIT_SUCCESS);
        }
        close(remote.sockfd);
    }
    close(locale.sockfd);
    return e;
}

int main(int argc, char**argv)
{
    extern int errno;
    strcpy(program,basename(argv[0]));
    signal(SIGINT,signalHandler);
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