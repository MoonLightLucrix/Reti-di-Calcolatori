#ifndef DATABASEMANAGER
#define DATABASEMANAGER

#include<iostream>
#include<fstream>
#include<sstream>
#include<cstdlib>
#include<cstring>
#include<fcntl.h>
#include<libgen.h>
#include<sys/stat.h>
#include<semaphore.h>
#include<unistd.h>
#include<cerrno>

class DatabaseManager
{
    private:
        std::fstream database;
        std::string filename;
        std::string semName;
        std::string path;
        sem_t*mutex;
    public:

        /**
         * @brief Costruttore della classe DatabaseManager.
         *
         * Inizializza un'istanza di DatabaseManager con il nome del file e il nome del semaforo specificati.
         * Se il nome del semaforo non è vuoto, tenta di aprire il semaforo. Se il nome del file non è vuoto,
         * tenta di aprire il file. Se una di queste operazioni fallisce, il programma termina con un errore.
         *
         * @param filename Nome del file del database.
         * @param semName Nome del semaforo per la sincronizzazione.
         */
        DatabaseManager(std::string filename="", std::string semName="");

        /**
         * @brief Distruttore per la classe DatabaseManager.
         * 
         * Questo distruttore chiude il file aperto e il semaforo POSIX.
         * Se il file non è aperto, non fa nulla.
         * Se il semaforo non è aperto, non fa nulla.
         */
        ~DatabaseManager();
        
        /**
         * @brief Apre il file del database specificato.
         *
         * Questo metodo tenta di aprire il file del database con il nome specificato. Se il nome del file
         * non è stato precedentemente impostato, viene assegnato. Se il file non è già aperto, viene aperto
         * in modalità lettura e scrittura. Se l'apertura del file fallisce, viene stampato un messaggio di errore.
         *
         * @param filename Nome del file del database da aprire.
         * @return `true` se il file è stato aperto con successo, `false` altrimenti.
         */
        bool openFile(std::string filename);

        /**
         * @brief Apre un semaforo con il nome specificato.
         *
         * Questo metodo tenta di aprire un semaforo con il nome specificato. Se il nome del semaforo
         * non è stato precedentemente impostato, viene assegnato. Se un semaforo è già aperto, viene
         * stampato un messaggio di errore. Se l'apertura del semaforo fallisce, viene stampato un
         * messaggio di errore e il metodo restituisce `false`.
         *
         * @param semName Nome del semaforo da aprire.
         * @return `true` se il semaforo è stato aperto con successo, `false` altrimenti.
         */
        bool openSemaphore(std::string semName);

        /**
         * @brief Inserisce una linea nel database.
         *
         * Questo metodo inserisce una linea di testo alla fine del file di database.
         * Utilizza un semaforo per garantire che l'accesso al database sia sicuro tra più processi.
         *
         * @param line La linea di testo da inserire nel database.
         */
        void insert(const std::string line);

        /**
         * @brief Inserisce una riga nel database.
         *
         * Questo metodo inserisce una riga di testo, rappresentata da un oggetto `std::stringstream`,
         * alla fine del file di database. Utilizza un semaforo per garantire che l'accesso al database
         * sia sicuro tra più processi.
         *
         * @param row La riga di testo da inserire nel database, rappresentata come `std::stringstream`.
         */
        void insert(std::stringstream&row);

        /**
         * @brief Trova una riga nel database in base all'ID.
         *
         * Questo metodo cerca una riga nel file di database che corrisponde all'ID specificato.
         * Utilizza un semaforo per garantire che l'accesso al database sia sicuro tra più processi.
         *
         * @param id L'ID da cercare nel database.
         * @return La riga corrispondente all'ID specificato, oppure una stringa vuota se l'ID non viene trovato.
         */
        std::string find(__uint32_t id);

        /**
         * @brief Trova una stringa nel database corrispondente all'ID specificato.
         *
         * Questo metodo cerca nel file del database una stringa che corrisponde all'ID specificato.
         * Se trova una corrispondenza, restituisce la riga completa. Utilizza un semaforo per
         * garantire l'accesso sincronizzato al database.
         *
         * @param id L'ID del record da trovare.
         * @return La riga del database corrispondente all'ID specificato, o una stringa vuota se non trovata.
         */
        std::string find(std::string id);

        /**
         * @brief Legge la prossima riga dal database.
         *
         * Questo metodo legge la prossima riga dal database. Se è la prima volta che viene chiamato,
         * acquisisce un semaforo e riposiziona il puntatore del file all'inizio. Se c'è una riga da leggere,
         * la restituisce. Altrimenti, rilascia il semaforo e restituisce una stringa vuota.
         *
         * @return La prossima riga del database come stringa. Se non ci sono più righe, restituisce una stringa vuota.
         */
        std::string nextLine();

        /**
         * @brief Elimina o modifica una linea nel database.
         *
         * Questo metodo cerca un record nel database che inizia con l'ID specificato.
         * Se trova un record con l'ID specificato, lo sostituisce con `newLine` se `newLine` non è vuoto.
         * Se `newLine` è vuoto, il record viene eliminata.
         *
         * @param id L'ID del record da eliminare o modificare.
         * @param newLine La nuova linea da sostituire alla linea esistente. Se vuoto, la linea viene eliminata.
         * @return `true` se l'operazione è riuscita, `false` se l'operazione è fallita.
         */
        bool deleteOrEditLine(__uint32_t id, std::string newLine="");

        /**
         * @brief Elimina o modifica una linea nel database.
         *
         * Questo metodo cerca un record nel database che corrisponde alla stringa specificata.
         * Se trova un record che corrisponde, lo sostituisce con `newLine` se `newLine` non è vuoto.
         * Se `newLine` è vuoto, il record viene eliminata.
         *
         * @param line Il record da eliminare o modificare.
         * @param newLine La nuova linea da sostituire alla linea esistente. Se vuoto, la linea viene eliminata.
         * @return `true` se l'operazione è riuscita, `false` se l'operazione è fallita.
         */
        bool deleteOrEditLine(std::string line, std::string newLine="");
};

#endif
