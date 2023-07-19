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
#define MAX_CLIENTS 2
#define lato 3
#define vuoto ' '
#define turno 88
#define offset 9
typedef struct
{
    in_addr_t address;
    in_port_t porta;
} Client;
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
 * @brief Inizializza la stringa str con la stampa della griglia, l'equivalente del metodo toString.
 * @param griglia Griglia di gioco dove effettuare il controllo.
 * @param str Stringa dove stampare la griglia.
*/
void strGriglia(char griglia[lato][lato], char*str)
{
    for(int i=0; i<=lato-1; i-=-1)
    {
        for(int j=-1; j<=lato-1; j-=-1)
        {
            (j==-1)?sprintf(str,"%s%d|",str,i+1):sprintf(str,"%s%c|",str,griglia[i][j]);
        }
        sprintf(str,"%s\n",str);
    }
    sprintf(str,"%s  ",str);
    for(int i=0; i<=lato-1; i-=-1)
    {
        sprintf(str,"%s%d ",str,i+1);
    }
    sprintf(str,"%s\n",str);
}

/**
 * @brief Effettua un controllo su tutta la line orizzontale della riga in cui il client ha effettuato l'inserimento se la riga contiene 3 segni uguali di fila il gioco termina ed il clien n-esimo vince.
 * @param griglia Griglia di gioco dove effettuare il controllo.
 * @param c Segno che il client ha inserito.
 * @param riga Riga dove effettuare il controllo.
 * @return TRUE se la riga possiede 3 segni uguali (dello stesso client) di fila, FALSE altrimenti.
*/
bool controllaOrrizontale(char griglia[lato][lato], char c, __int8_t riga)
{
    bool check=true;
    for(int i=0; i<=lato-1; i-=-1)
    {
        check&=(c==griglia[riga][i]);
    }
    printf("%s",(check)?"orrizontale\n":"");
    return check;
}

/**
 * @brief Effettua un controllo su tutta la line verticale della colonna in cui il client ha effettuato l'inserimento se la colonna contiene 3 segni uguali di fila il gioco termina ed il clien n-esimo vince.
 * @param griglia Griglia di gioco dove effettuare il controllo.
 * @param c Segno che il client ha inserito.
 * @param colonna Colonna dove effettuare il controllo.
 * @return TRUE se la riga possiede 3 segni uguali (dello stesso client) di fila, FALSE altrimenti.
*/
bool controllaVerticale(char griglia[lato][lato], char c, __int8_t colonna)
{
    bool check=true;
    for(int i=0; i<=lato-1; i-=-1)
    {
        check&=(c==griglia[i][colonna]);
    }
    printf("%s",(check)?"verticale\n":"");
    return check;
}

/**
 * @brief Effettua un controllo su tutta la diagonale della colonna e riga in cui il client ha effettuato l'inserimento se la diagonale contiene 3 segni uguali di fila il gioco termina ed il clien n-esimo vince.
 * @param griglia Griglia di gioco dove effettuare il controllo.
 * @param c Segno che il client ha inserito.
 * @param riga Riga dove è stato inserito il segno.
 * @param colonna Colonna dove è stato inserito il segno.
 * @return TRUE se la diagonale possiede 3 segni uguali (dello stesso client) di fila, FALSE altrimenti.
*/
bool controllaDiagonale(char griglia[lato][lato], char c, __int8_t riga, __int8_t colonna)
{
    int i,j;
    bool check=true;
    i=-(j=colonna-riga);
    for(i=(i<=-1)?0:i, j=(j<=-1)?0:j; (i<=lato-1) && (j<=lato-1); i-=-1, j-=-1)
    {
        check&=(c==griglia[i][j]);
    }
    printf("%s",(check)?"diagonale\n":"");
    return check&=((i==lato) && (j==lato));
}

/**
 * @brief Effettua un controllo su tutta la diagonale secondaria della colonna e riga in cui il client ha effettuato l'inserimento se la diagonale secondaria contiene 3 segni uguali di fila il gioco termina ed il clien n-esimo vince.
 * @param c Segno che il client ha inserito.
 * @param griglia Griglia di gioco dove effettuare il controllo.
 * @param riga Riga dove è stato inserito il gettone
 * @param colonna Colonna dove è stato inserito il gettone
 * @return TRUE se la diagonale secondaria possiede 3 segni uguali (dello stesso client) di fila, FALSE altrimenti.
*/
bool controllaSDiagonale(char griglia[lato][lato], char c, __int8_t riga, __int8_t colonna)
{
    int i,j;
    bool check=true;
    i=-(j=((lato-1)-colonna)-riga);
    for(i=(i<=-1)?0:i, j=(j<=-1)?lato-1:(lato-1)-j; (i<=lato-1) && (j>=0); i-=-1, j--)
    {
        check&=(c==griglia[i][j]);
    }
    printf("%s",(check)?"sdiagonale\n":"");
    return check&=((i==lato) && (j==-1));
}

/**
 * @brief Controlla che ci sia almeno una casella vuota nella griglia, se esiste la partita non è ancora finita, se non esiste la partita è finita in parità.
 * @param griglia Griglia di gioco dove effettuare il controllo.
 * @return TRUE se non esistono spazi vuoti nella griglia, FALSE altrimenti.
*/
bool controllaDraw(char griglia[lato][lato])
{
    for(int i=0; i<=lato-1; i-=-1)
    {
        for(int j=0; j<=lato-1; j-=-1)
        {
            if(griglia[i][j]==vuoto)
            {
                return false;
            }
        }
    }
    return true;
}

/**
 * @brief In base alla scelta fatta dal client inserisce il segno e restituisce ai client la mossa fatta da client corrente.
 * @param sockfd sockfd File descriptor della socket.
 * @param addr Struct che contiene tutte le informazioni legate all'indirizzo ip, numero di porta e famiglia della socket.
 * @param addrlen Lunghezza della struct sockaddr_in o struct sockaddr (hanno lo stesso numero di byte).
 * @param riga Riga dove inserire il segno.
 * @param colonna Colonna dove inserire il segno.
 * @param griglia Griglia di gioco dove effettuare l'inserimento.
 * @param n Client corrente.
 * @param thereIsAWinner TRUE se è l'ultimo Client che ha effettuato l'inserimento ha vinto, FALSE altrimenti.
 * @param gameOver TRUE se la griglia è piena, quindi la partita finisce in pareggio, FALSE altrimenti.
 * @return In caso di errore verrà restituito -1, altrimenti 0.
*/
int tris(int sockfd, struct sockaddr_in addr, socklen_t addrlen, __int8_t riga, __int8_t colonna, char griglia[lato][lato], int n, bool*thereIsAWinner, bool*gameOver)
{
    char buffer[N];
    riga-=1;
    colonna-=1;
    int e=0;
    memset(buffer,'\0',strlen(buffer));
    if((riga<=-1) || (riga>=lato))
    {
        sprintf(buffer,"%s: La riga non esiste\n",program);
        e=-1;
    }
    if((colonna<=-1) || (colonna>=lato))
    {
        sprintf(buffer,"%s%s: La colonna non esiste\n",buffer,program);
        e=-1;
    }
    if(((0<=riga) && (riga<=lato-1)) && ((0<=colonna) && (colonna<=lato-1)))
    {
        if(griglia[riga][colonna]==vuoto)
        {
            griglia[riga][colonna]=(char)turno-(n*offset);
            strGriglia(griglia,buffer);
            if((*thereIsAWinner=((controllaOrrizontale(griglia,griglia[riga][colonna],riga)) || (controllaVerticale(griglia,griglia[riga][colonna],colonna)) || (controllaDiagonale(griglia,griglia[riga][colonna],riga,colonna)) || (controllaSDiagonale(griglia,griglia[riga][colonna],riga,colonna)))))
            {
                sprintf(buffer,"%s%s: Hai vinto!\n",buffer,program);
            }
            else
            {
                *gameOver=controllaDraw(griglia);
            }
        }
        else
        {
            sprintf(buffer,"%s: Riga e colonna non disponibile\n",program);
            e=-1;
        }
    }
    sprintf(buffer,"%s\n",buffer);
    if((sendto(sockfd,buffer,strlen(buffer),0,(struct sockaddr*)&addr,addrlen))==-1)
    {
        fprintf(stderr,"%s: sendto: %s\n",program,strerror(errno));
        return -1;
    }
    return e;
}

/**
 * @brief Funzione che viene utilizzata come server nella comunicazione, setta tutte le impostazioni iniziali ed aspetta che tutti i client si connettino per far partire il gioco, il protocollo utilizzato è User Datagram Protocol.
 * @param porta Porta sulla quale vengono reindirizzati i pacchetti in entrata.
 * @return Restituisce -1 in caso di errore, 0 altrimenti.
*/
int server(in_port_t porta)
{
    int sockfd;
    struct sockaddr_in locale, remote[MAX_CLIENTS];
    socklen_t addrlen;
    if((sockaddrSettings(&sockfd,&locale,&addrlen,NULL,porta))==-1)
    {
        return -1;
    }
    if((bind(sockfd,(struct sockaddr*)&locale,addrlen))==-1)
    {
        fprintf(stderr,"%s: bind: %s\n",program,strerror(errno));
        close(sockfd);
        return -1;
    }
    Client client[MAX_CLIENTS];
    int e=0;
    bool gameStarted=false, gameOver=false, thereIsAWinner=false;
    char griglia[lato][lato];
    memset(griglia,vuoto,lato*lato);
    char buffer[N];
    ssize_t size;
    __int8_t riga, colonna;
    int n;
    printf("Attendo i %d giocatori…\n",MAX_CLIENTS);
    for(n=0; (!thereIsAWinner) && (!gameOver); n-=-1)
    {
        if(gameStarted)
        {
            n%=MAX_CLIENTS;
            memset(buffer,'\0',strlen(buffer));
            strGriglia(griglia,buffer);
            sprintf(buffer,"%s%s: inserisci la riga e la colonna dove vuoi inserire separati da uno spazio: ",buffer,program);
            if((sendto(sockfd,buffer,strlen(buffer),0,(struct sockaddr*)remote+n,addrlen))==-1)
            {
                fprintf(stderr,"%s: sendto: %s\n",program,strerror(errno));
                e=-1;
                break;
            }
        }
        memset(buffer,'\0',strlen(buffer));
        if((size=recvfrom(sockfd,buffer,N,0,(struct sockaddr*)remote+n,&addrlen))==-1)
        {
            fprintf(stderr,"%s: recvfrom: %s\n",program,strerror(errno));
            e=-1;
            break;
        }
        buffer[size]='\0';
        if(!gameStarted)
        {
            client[n].address=remote[n].sin_addr.s_addr;
            client[n].porta=ntohs(remote[n].sin_port);
            gameStarted=(n==MAX_CLIENTS-1);
            printf("Attendo il giocatore %d…\n",n+2);
        }
        else
        {
            riga=atoi(&buffer[0]);
            colonna=atoi(&buffer[2]);
            //printf("buffer: %s\nriga: %d\ncolonna: %d\n",buffer,riga,colonna);
            if((tris(sockfd,remote[n],addrlen,riga,colonna,griglia,n,&thereIsAWinner,&gameOver))==-1)
            {
                n--;
            }
        }
    }
    if(thereIsAWinner)
    {
        n--;
        for(int i=0; i<=MAX_CLIENTS-1; i-=-1)
        {
            if(i==n)
            {
                continue;
            }
            memset(buffer,'\0',strlen(buffer));
            strGriglia(griglia,buffer);
            sprintf(buffer,"%s%s: Hai Perso!\n",buffer,program);
            if((sendto(sockfd,buffer,strlen(buffer),0,(struct sockaddr*)remote+i,addrlen))==-1)
            {
                fprintf(stderr,"%s: sendto: %s\n",program,strerror(errno));
                close(sockfd);
                return -1;
            }
        }
    }
    else if(gameOver)
    {
        for(int i=0; i<=MAX_CLIENTS-1; i-=-1)
        {
            memset(buffer,'\0',strlen(buffer));
            strGriglia(griglia,buffer);
            sprintf(buffer,"%s%s: Non ci sono ne vinti ne vincitori solo un senzo di amara delusione nei volti dei due sfidanti…\n",buffer,program);
            if((sendto(sockfd,buffer,strlen(buffer),0,(struct sockaddr*)remote+i,addrlen))==-1)
            {
                fprintf(stderr,"%s: sendto: %s\n",program,strerror(errno));
                close(sockfd);
                return -1;
            }
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
        printf("\x1b[31musage: %s <porta>\x1b[0m\n",program);
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