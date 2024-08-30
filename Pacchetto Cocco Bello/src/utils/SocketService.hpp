#ifndef SOCKETSERVICE
#define SOCKETSERVICE

#include<iostream>
#include<cstdlib>
#include<cstring>
#include<functional>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<pthread.h>
#include<unistd.h>
#include<csignal>
#include<cerrno>

class SocketService
{
    protected:
        int sockfd;
        struct sockaddr_in addr;
        socklen_t addrlen;
        in_port_t porta;
        const size_t N=8192;
        ssize_t bytesRead;

        /**
         * @brief Imposta le impostazioni del socket.
         * 
         * Questo metodo crea un nuovo socket e imposta le sue impostazioni di indirizzo.
         * Se viene fornito un indirizzo, viene utilizzato. Altrimenti, viene utilizzato INADDR_ANY.
         * Se la creazione del socket fallisce, viene stampato un messaggio di errore e restituito -1.
         * 
         * @param address L'indirizzo IP da utilizzare per il socket. Default è 0, che significa INADDR_ANY.
         * @return 0 se l'impostazione del socket è andata a buon fine, -1 altrimenti.
         */
        int sockaddrSettings(const char*address=0);
    public:

        /**
         * @brief Costruttore per la classe SocketService.
         * 
         * Questo costruttore inizializza un oggetto SocketService con la porta specificata.
         * 
         * @param porta La porta da utilizzare per il socket.
         */
        SocketService(in_port_t porta=0);

        /**
         * @brief Distruttore per la classe SocketService.
         * 
         * Questo distruttore chiude il socket.
         */
        ~SocketService();

        /**
         * @brief Imposta il file descriptor del socket.
         * 
         * Questo metodo assegna il valore del file descriptor del socket all'attributo sockfd della classe.
         * Il file descriptor è utilizzato per identificare il socket all'interno del sistema operativo.
         * 
         * @param sockfd Il file descriptor del socket da impostare.
         */
        void setSockfd(int sockfd);

        /**
         * @brief Restituisce il file descriptor del socket.
         * 
         * Questo metodo restituisce il valore del file descriptor del socket associato a questa istanza di SocketService.
         * Il file descriptor è utilizzato per identificare il socket all'interno del sistema operativo e per effettuare operazioni sul socket.
         * 
         * @return Il file descriptor del socket.
         */
        int getSockfd() const;

        /**
         * @brief Imposta l'indirizzo del socket.
         * 
         * Questo metodo assegna l'indirizzo del socket, specificato dal parametro addr, all'attributo addr della classe.
         * L'indirizzo è utilizzato per configurare il socket in operazioni di bind, listen, ecc.
         * 
         * @param addr L'indirizzo del socket da impostare.
         */
        void setAddr(struct sockaddr_in addr);

        /**
         * @brief Restituisce l'indirizzo del socket.
         * 
         * Questo metodo restituisce l'indirizzo del socket associato a questa istanza di SocketService.
         * L'indirizzo è utilizzato per identificare il socket nel contesto di operazioni di rete come bind o connect.
         * 
         * @return L'indirizzo del socket.
         */
        struct sockaddr_in getAddr() const;

        /**
         * @brief Imposta la lunghezza dell'indirizzo del socket.
         * 
         * Questo metodo assegna la lunghezza dell'indirizzo del socket, specificata dal parametro addrlen, all'attributo addrlen della classe.
         * La lunghezza dell'indirizzo è utilizzata in operazioni di rete come bind o accept per specificare la dimensione della struttura dell'indirizzo.
         * 
         * @param addrlen La lunghezza dell'indirizzo del socket da impostare.
         */
        void setAddrlen(socklen_t addrlen);

        /**
         * @brief Restituisce la lunghezza dell'indirizzo del socket.
         * 
         * Questo metodo restituisce la lunghezza dell'indirizzo del socket associato a questa istanza di SocketService.
         * La lunghezza dell'indirizzo è utilizzata in operazioni di rete come bind o accept per specificare la dimensione della struttura dell'indirizzo.
         * 
         * @return La lunghezza dell'indirizzo del socket.
         */
        socklen_t getAddrlen() const;

        /**
         * @brief Scrive un intero a 8 bit sul socket.
         * 
         * Questo metodo scrive un intero a 8 bit sul socket.
         * 
         * @param a Il byte da scrivere sul socket.
         * @return `true` se la scrittura è andata a buon fine, `false` altrimenti.
         */
        bool sockWrite(const __uint8_t&a) const;

        /**
         * @brief Scrive un intero a 16 bit sul socket.
         * 
         * Questo metodo scrive un intero a 16 bit sul socket.
         * 
         * @param a L'intero a 16 bit da scrivere sul socket.
         * @return `true` se la scrittura è andata a buon fine, `false` altrimenti.
         */
        bool sockWrite(const __uint16_t&a) const;

        /**
         * @brief Scrive un intero a 32 bit sul socket.
         * 
         * Questo metodo scrive un intero a 32 bit sul socket.
         * 
         * @param a L'intero a 32 bit da scrivere sul socket.
         * @return `true` se la scrittura è andata a buon fine, `false` altrimenti.
         */
        bool sockWrite(const __uint32_t&a) const;

        /**
         * @brief Scrive un intero a 64 bit sul socket.
         * 
         * Questo metodo scrive un intero a 64 bit sul socket.
         * 
         * @param a L'intero a 64 bit da scrivere sul socket.
         * @return `true` se la scrittura è andata a buon fine, `false` altrimenti.
         */
        bool sockWrite(const __uint64_t&a) const;

        /**
         * @brief Scrive un intero a 128 bit sul socket.
         * 
         * Questo metodo scrive un intero a 128 bit sul socket.
         * 
         * @param a L'intero a 128 bit da scrivere sul socket.
         * @return `true` se la scrittura è andata a buon fine, `false` altrimenti.
         */
        bool sockWrite(const __uint128_t&a) const;

        /**
         * @brief Scrive un intero a 8 bit con segno sul socket.
         * 
         * Questo metodo scrive un intero a 8 bit con segno sul socket.
         * 
         * @param a Il byte con segno da scrivere sul socket.
         * @return `true` se la scrittura è andata a buon fine, `false` altrimenti.
         */
        bool sockWrite(const __int8_t&a) const;

        /**
         * @brief Scrive un intero a 16 bit con segno sul socket.
         * 
         * Questo metodo scrive un intero a 16 bit con segno sul socket.
         * 
         * @param a L'intero a 16 bit con segno da scrivere sul socket.
         * @return `true` se la scrittura è andata a buon fine, `false` altrimenti.
         */
        bool sockWrite(const __int16_t&a) const;

        /**
         * @brief Scrive un intero a 32 bit con segno sul socket.
         * 
         * Questo metodo scrive un intero a 32 bit con segno sul socket.
         * 
         * @param a L'intero a 32 bit con segno da scrivere sul socket.
         * @return `true` se la scrittura è andata a buon fine, `false` altrimenti.
         */
        bool sockWrite(const __int32_t&a) const;

        /**
         * @brief Scrive un intero a 64 bit con segno sul socket.
         * 
         * Questo metodo scrive un intero a 64 bit con segno sul socket.
         * 
         * @param a L'intero a 64 bit con segno da scrivere sul socket.
         * @return `true` se la scrittura è andata a buon fine, `false` altrimenti.
         */
        bool sockWrite(const __int64_t&a) const;

        /**
         * @brief Scrive un intero a 128 bit con segno sul socket.
         * 
         * Questo metodo scrive un intero a 128 bit con segno sul socket.
         * 
         * @param a L'intero a 128 bit con segno da scrivere sul socket.
         * @return `true` se la scrittura è andata a buon fine, `false` altrimenti.
         */
        bool sockWrite(const __int128_t&a) const;

        /**
         * @brief Scrive un booleano sul socket.
         * 
         * Questo metodo scrive un booleano sul socket.
         * 
         * @param a Il booleano da scrivere sul socket.
         * @return `true` se la scrittura è andata a buon fine, `false` altrimenti.
         */
        bool sockWrite(const bool&a) const;

        /**
         * @brief Scrive un numero in virgola mobile a 32 bit sul socket.
         * 
         * Questo metodo scrive un numero in virgola mobile a 32 bit sul socket.
         * 
         * @param a Il numero in virgola mobile a 32 bit da scrivere sul socket.
         * @return `true` se la scrittura è andata a buon fine, `false` altrimenti.
         */
        bool sockWrite(const float&a) const;

        /**
         * @brief Scrive un numero in virgola mobile a 64 bit sul socket.
         * 
         * Questo metodo scrive un numero in virgola mobile a 64 bit sul socket.
         * 
         * @param a Il numero in virgola mobile a 64 bit da scrivere sul socket.
         * @return `true` se la scrittura è andata a buon fine, `false` altrimenti.
         */
        bool sockWrite(const double&a) const;

        /**
         * @brief Scrive un numero in virgola mobile a 128 bit sul socket.
         * 
         * Questo metodo scrive un numero in virgola mobile a 128 bit sul socket.
         * 
         * @param a Il numero in virgola mobile a 128 bit da scrivere sul socket.
         * @return `true` se la scrittura è andata a buon fine, `false` altrimenti.
         */
        bool sockWrite(const long double&a) const;

        /**
         * @brief Scrive una stringa sul socket.
         * 
         * Questo metodo scrive una stringa sul socket.
         * 
         * @param a La stringa da scrivere sul socket.
         * @return `true` se la scrittura è andata a buon fine, `false` altrimenti.
         */
        bool sockWrite(const std::string&a) const;

        /**
         * @brief Scrive un carattere sul socket.
         * 
         * Questo metodo scrive un carattere sul socket.
         * 
         * @param a Il carattere da scrivere sul socket.
         * @return `true` se la scrittura è andata a buon fine, `false` altrimenti.
         */
        bool sockWrite(const char&a) const;

        /**
         * @brief Scrive una stringa sul socket.
         * 
         * Questo metodo scrive una stringa sul socket.
         * 
         * @param a La stringa da scrivere sul socket.
         * @return `true` se la scrittura è andata a buon fine, `false` altrimenti.
         */
        bool sockWrite(const char*a) const;

        /**
         * @brief Legge un intero a 8 bit dal socket.
         * 
         * Questo metodo legge un intero a 8 bit dal socket.
         * 
         * @param a Il byte letto dal socket.
         * @return `true` se la lettura è andata a buon fine, `false` altrimenti.
         */
        bool sockRead(__uint8_t&a);

        /**
         * @brief Legge un intero a 16 bit dal socket.
         * 
         * Questo metodo legge un intero a 16 bit dal socket.
         * 
         * @param a L'intero a 16 bit letto dal socket.
         * @return `true` se la lettura è andata a buon fine, `false` altrimenti.
         */
        bool sockRead(__uint16_t&a);

        /**
         * @brief Legge un intero a 32 bit dal socket.
         * 
         * Questo metodo legge un intero a 32 bit dal socket.
         * 
         * @param a L'intero a 32 bit letto dal socket.
         * @return `true` se la lettura è andata a buon fine, `false` altrimenti.
         */
        bool sockRead(__uint32_t&a);

        /**
         * @brief Legge un intero a 64 bit dal socket.
         * 
         * Questo metodo legge un intero a 64 bit dal socket.
         * 
         * @param a L'intero a 64 bit letto dal socket.
         * @return `true` se la lettura è andata a buon fine, `false` altrimenti.
         */
        bool sockRead(__uint64_t&a);

        /**
         * @brief Legge un intero a 128 bit dal socket.
         * 
         * Questo metodo legge un intero a 128 bit dal socket.
         * 
         * @param a L'intero a 128 bit letto dal socket.
         * @return `true` se la lettura è andata a buon fine, `false` altrimenti.
         */
        bool sockRead(__uint128_t&a);

        /**
         * @brief Legge un intero a 8 bit con segno dal socket.
         * 
         * Questo metodo legge un intero a 8 bit con segno dal socket.
         * 
         * @param a Il byte con segno letto dal socket.
         * @return `true` se la lettura è andata a buon fine, `false` altrimenti.
         */
        bool sockRead(__int8_t&a);

        /**
         * @brief Legge un intero a 16 bit con segno dal socket.
         * 
         * Questo metodo legge un intero a 16 bit con segno dal socket.
         * 
         * @param a L'intero a 16 bit con segno letto dal socket.
         * @return `true` se la lettura è andata a buon fine, `false` altrimenti.
         */
        bool sockRead(__int16_t&a);

        /**
         * @brief Legge un intero a 32 bit con segno dal socket.
         * 
         * Questo metodo legge un intero a 32 bit con segno dal socket.
         * 
         * @param a L'intero a 32 bit con segno letto dal socket.
         * @return `true` se la lettura è andata a buon fine, `false` altrimenti.
         */
        bool sockRead(__int32_t&a);

        /**
         * @brief Legge un intero a 64 bit con segno dal socket.
         * 
         * Questo metodo legge un intero a 64 bit con segno dal socket.
         * 
         * @param a L'intero a 64 bit con segno letto dal socket.
         * @return `true` se la lettura è andata a buon fine, `false` altrimenti.
         */
        bool sockRead(__int64_t&a);

        /**
         * @brief Legge un intero a 128 bit con segno dal socket.
         * 
         * Questo metodo legge un intero a 128 bit con segno dal socket.
         * 
         * @param a L'intero a 128 bit con segno letto dal socket.
         * @return `true` se la lettura è andata a buon fine, `false` altrimenti.
         */
        bool sockRead(__int128_t&a);

        /**
         * @brief Legge un booleano dal socket.
         * 
         * Questo metodo legge un booleano dal socket.
         * 
         * @param a Il booleano letto dal socket.
         * @return `true` se la lettura è andata a buon fine, `false` altrimenti.
         */
        bool sockRead(bool&a);

        /**
         * @brief Legge un numero in virgola mobile a 32 bit dal socket.
         * 
         * Questo metodo legge un numero in virgola mobile a 32 bit dal socket.
         * 
         * @param a Il numero in virgola mobile a 32 bit letto dal socket.
         * @return `true` se la lettura è andata a buon fine, `false` altrimenti.
         */
        bool sockRead(float&a);

        /**
         * @brief Legge un numero in virgola mobile a 64 bit dal socket.
         * 
         * Questo metodo legge un numero in virgola mobile a 64 bit dal socket.
         * 
         * @param a Il numero in virgola mobile a 64 bit letto dal socket.
         * @return `true` se la lettura è andata a buon fine, `false` altrimenti.
         */
        bool sockRead(double&a);

        /**
         * @brief Legge un numero in virgola mobile a 128 bit dal socket.
         * 
         * Questo metodo legge un numero in virgola mobile a 128 bit dal socket.
         * 
         * @param a Il numero in virgola mobile a 128 bit letto dal socket.
         * @return `true` se la lettura è andata a buon fine, `false` altrimenti.
         */
        bool sockRead(long double&a);

        /**
         * @brief Legge una stringa dal socket.
         * 
         * Questo metodo legge una stringa dal socket.
         * 
         * @param a La stringa letta dal socket.
         * @return `true` se la lettura è andata a buon fine, `false` altrimenti.
         */
        bool sockRead(std::string&a);

        /**
         * @brief Legge un carattere dal socket.
         * 
         * Questo metodo legge un carattere dal socket.
         * 
         * @param a Il carattere letto dal socket.
         * @return `true` se la lettura è andata a buon fine, `false` altrimenti.
         */
        bool sockRead(char&a);

        /**
         * @brief Legge una stringa dal socket.
         * 
         * Questo metodo legge una stringa dal socket.
         * 
         * @param a La stringa letta dal socket.
         * @return `true` se la lettura è andata a buon fine, `false` altrimenti.
         */
        bool sockRead(char*a);

        friend SocketService& operator <<(SocketService &ss, const __uint8_t&a);

        friend SocketService& operator <<(SocketService &ss, const __uint16_t&a);

        friend SocketService& operator <<(SocketService &ss, const __uint32_t&a);

        friend SocketService& operator <<(SocketService &ss, const __uint64_t&a);

        friend SocketService& operator <<(SocketService &ss, const __uint128_t&a);

        friend SocketService& operator <<(SocketService &ss, const __int8_t&a);

        friend SocketService& operator <<(SocketService &ss, const __int16_t&a);

        friend SocketService& operator <<(SocketService &ss, const __int32_t&a);

        friend SocketService& operator <<(SocketService &ss, const __int64_t&a);

        friend SocketService& operator <<(SocketService &ss, const __int128_t&a);

        friend SocketService& operator <<(SocketService &ss, const bool&a);

        friend SocketService& operator <<(SocketService &ss, const float&a);

        friend SocketService& operator <<(SocketService &ss, const double&a);

        friend SocketService& operator <<(SocketService &ss, const long double&a);

        friend SocketService& operator <<(SocketService &ss, const std::string&a);

        friend SocketService& operator <<(SocketService &ss, const char&a);

        friend SocketService& operator <<(SocketService &ss,const char*a);

        friend SocketService& operator >>(SocketService &ss, __uint8_t&a);

        friend SocketService& operator >>(SocketService &ss, __uint16_t&a);

        friend SocketService& operator >>(SocketService &ss, __uint32_t&a);

        friend SocketService& operator >>(SocketService &ss, __uint64_t&a);

        friend SocketService& operator >>(SocketService &ss, __uint128_t&a);

        friend SocketService& operator >>(SocketService &ss, __int8_t&a);

        friend SocketService& operator >>(SocketService &ss, __int16_t&a);

        friend SocketService& operator >>(SocketService &ss, __int32_t&a);

        friend SocketService& operator >>(SocketService &ss, __int64_t&a);

        friend SocketService& operator >>(SocketService &ss, __int128_t&a);

        friend SocketService& operator >>(SocketService &ss, bool&a);

        friend SocketService& operator >>(SocketService &ss, float&a);

        friend SocketService& operator >>(SocketService &ss, double&a);

        friend SocketService& operator >>(SocketService &ss, long double&a);
        
        friend SocketService& operator >>(SocketService &ss, std::string&a);

        friend SocketService& operator >>(SocketService &ss, char&a);

        friend SocketService& operator >>(SocketService &ss, char*a);
};

class Server: public SocketService
{
    private:
        int backlog;
        int sockfd2;
        struct sockaddr_in addr2;
        pid_t pid;
        bool isWaitingForConnection;

        /**
         * @brief Imposta le impostazioni del server.
         * 
         * Questo metodo lega il socket a un indirizzo e inizia ad ascoltare le connessioni in entrata.
         * Se la bind fallisce, viene stampato un messaggio di errore e restituisce -1.
         * Il numero di connessioni in attesa che il socket può tenere è impostato a 5 se il backlog è 0, altrimenti è impostato al valore del backlog.
         * 
         * @return 0 se l'impostazione del server è andata a buon fine, -1 altrimenti.
         */
        int serverSettings();
    public:

        /**
         * @brief Costruttore per la classe Server.
         * 
         * Questo costruttore inizializza un oggetto Server con la porta e il backlog specificati.
         * 
         * @param porta La porta da utilizzare per il socket.
         * @param backlog Il numero di connessioni in attesa che il socket può tenere.
         */
        Server(in_port_t porta=8080, int backlog=5);

        /**
         * @brief Distruttore per la classe Server.
         * 
         * Questo distruttore chiude il socket.
         */
        ~Server();

        /**
         * @brief Inizializza il server.
         * 
         * Questo metodo inizializza il server con la porta e il backlog specificati.
         * 
         * @return `true` se l'inizializzazione è andata a buon fine, `false` altrimenti.
         */
        bool init();

        /**
         * @brief Inizializza il server.
         * 
         * Questo metodo inizializza il server con la porta specificata.
         * 
         * @param porta La porta da utilizzare per il socket.
         * @return `true` se l'inizializzazione è andata a buon fine, `false` altrimenti.
         */
        bool init(in_port_t porta);

        /**
         * @brief Inizializza il server.
         * 
         * Questo metodo inizializza il server con la porta e il backlog specificati.
         * Prima imposta le impostazioni del socket e poi le impostazioni del server.
         * Se una di queste operazioni fallisce, il metodo restituisce `false`.
         * 
         * @param porta La porta da utilizzare per il socket.
         * @param backlog Il numero massimo di connessioni che possono essere messe in coda.
         * @return `true` se l'inizializzazione è andata a buon fine, `false` altrimenti.
         */
        bool init(in_port_t porta, int backlog);

        /**
         * @brief Stabilisce una connessione con un numero specificato di client e li serve.
         * 
         * Questo metodo avvia l'ascolto sulla porta specificata dall'oggetto Server e attende
         * la connessione da parte di un numero definito di client. Per ogni client che si connette,
         * accetta la connessione, imposta i dettagli della connessione per il client corrispondente
         * e continua ad aspettare il prossimo client fino a raggiungere il numero di client specificato.
         * 
         * @param client Puntatore all'array di oggetti SocketService che rappresentano i client da servire.
         * @param numClients Il numero di client che il server intende servire.
         * @return Ritorna true se tutte le connessioni sono state accettate con successo, false in caso di errore.
         * 
         * @note Questo metodo modifica lo stato degli oggetti SocketService passati come clienti,
         * impostando i dettagli della connessione per ciascuno di essi.
         */
        bool serveFor(SocketService*client, size_t NumClients);
          
        /**
         * @brief Avvia il server per servire le richieste in modo continuo.
         * 
         * Questo metodo avvia il server per accettare e gestire le connessioni in entrata in un ciclo infinito.
         * Per ogni connessione accettata, viene creato un nuovo processo figlio per gestire la connessione.
         * Se l'accettazione della connessione o la creazione del processo figlio falliscono, viene stampato un messaggio di errore e restituito -1.
         * 
         * @return 0 se il server è stato avviato con successo, -1 se c'è stato un errore.
         */
        pid_t serveForever();

        /**
         * @brief Avvia il server per accettare connessioni e gestirle indefinitamente.
         *
         * Questo metodo avvia un ciclo infinito che accetta connessioni in arrivo e crea un processo figlio
         * per gestire ciascuna connessione. Il processo figlio esegue l'azione specificata dalla funzione
         * passata come parametro.
         *
         * @param action Una funzione che viene eseguita per gestire ciascuna connessione. La funzione riceve
         *               un riferimento al server come parametro e restituisce un valore booleano che indica
         *               se l'azione è stata eseguita con successo.
         * @return `true` se il server è stato avviato correttamente e ha accettato almeno una connessione, 
         *         `false` se si è verificato un errore durante l'accettazione delle connessioni o la creazione
         *          dei processi figli.
         */
        bool serveForever(std::function<bool(Server&)> action);

        /**
         * @brief Termina il processo padre del server se in attesa di connessione.
         * 
         * Questo metodo controlla se il server è attualmente in attesa di una connessione.
         * Se lo è, invia un segnale `SIGTERM` al processo padre, richiedendo la sua terminazione.
         * 
         * @return `true` se il server è in attesa di connessione e il segnale `SIGTERM` è stato inviato con successo al processo padre, `false` altrimenti, quindi se il server non è in attesa di una connessione, il metodo restituisce direttamente `false`.
         */
        bool shutdown();
};

class Client: public SocketService
{
    private:
        const char*address;
    public:

        /**
         * @brief Costruttore di Client.
         * 
         * Questo costruttore crea un nuovo client con l'indirizzo e la porta specificati.
         * Se non vengono forniti valori, vengono utilizzati i valori di default.
         * 
         * @param address L'indirizzo IP del server a cui connettersi. Default è 0, che significa INADDR_ANY.
         * @param porta La porta del server a cui connettersi. Default è 0.
         */
        Client(const char*address=0, in_port_t porta=0);

        /**
         * @brief Distruttore di Client.
         * 
         * Questo distruttore chiude il socket.
         */
        ~Client();

        /**
         * @brief Inizializza il client.
         * 
         * Questo metodo inizializza il client con l'indirizzo e la porta specificati.
         * 
         * @return `true` se l'inizializzazione è andata a buon fine, `false` altrimenti.
         */
        bool init();

        /**
         * @brief Inizializza il client.
         * 
         * Questo metodo inizializza il client con l'indirizzo specificato.
         * Prima imposta le impostazioni del socket e poi si connette al server.
         * Se una di queste operazioni fallisce, il metodo restituisce `false`.
         * 
         * @param address L'indirizzo IP del server a cui connettersi.
         * @return `true` se l'inizializzazione è andata a buon fine, `false` altrimenti.
         */
        bool init(const char*address);

        /**
         * @brief Inizializza il client.
         * 
         * Questo metodo inizializza il client con la porta specificata.
         * Prima imposta le impostazioni del socket e poi si connette al server.
         * Se una di queste operazioni fallisce, il metodo restituisce `false`.
         * 
         * @param porta La porta del server a cui connettersi.
         * @return `true` se l'inizializzazione è andata a buon fine, `false` altrimenti.
         */
        bool init(in_port_t porta);

        /**
         * @brief Inizializza il client.
         * 
         * Questo metodo inizializza il client con l'indirizzo e la porta specificati.
         * Prima imposta le impostazioni del socket e poi si connette al server.
         * Se una di queste operazioni fallisce, il metodo restituisce `false`.
         * 
         * @param address L'indirizzo IP del server a cui connettersi.
         * @param porta La porta del server a cui connettersi.
         * @return `true` se l'inizializzazione è andata a buon fine, `false` altrimenti.
         */
        bool init(const char*address, in_port_t porta);
};

#endif