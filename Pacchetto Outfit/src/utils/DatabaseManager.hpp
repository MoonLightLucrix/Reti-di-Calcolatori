#ifndef DATABASEMANAGER
#define DATABASEMANAGER

#include<fcntl.h>
#include<sys/stat.h>
#include<semaphore.h>
using namespace std;

class DatabaseManager
{
    private:
        fstream database;
        string filename;
        const char*semName="/SemMutex";
        sem_t*mutex;
    public:

        /**
         * @brief Costruttore per la classe DatabaseManager.
         * 
         * Questo costruttore inizializza un oggetto DatabaseManager con un nome di file specificato.
         * Se non viene fornito alcun nome di file, il nome del file viene impostato come stringa vuota.
         * Inoltre, il costruttore tenta di aprire un semaforo POSIX con nome. Se l'apertura del semaforo fallisce,
         * stampa un messaggio di errore e termina il programma.
         * Se viene fornito un nome di file, il costruttore tenta di aprire il file corrispondente.
         * 
         * @param filename Il nome del file da aprire. Se non specificato, viene impostato come stringa vuota.
         */
        DatabaseManager(string filename=""): filename(filename)
        {
            if((mutex=sem_open(semName,O_CREAT,S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH,1))==SEM_FAILED)
            {
                cerr<<"sem_open: "<<strerror(errno)<<endl;
                exit(EXIT_FAILURE);
            }
            if(this->filename!="")
            {
                openFile(filename);
            }
        }

        /**
         * @brief Distruttore per la classe DatabaseManager.
         * 
         * Questo distruttore chiude il file aperto e il semaforo POSIX.
         * Se il file non è aperto, non fa nulla.
         * Se il semaforo non è aperto, non fa nulla.
         */
        ~DatabaseManager()
        {
            sem_close(mutex);
            if(database.is_open())
            {
                database.close();
            }
        }

        /**
         * @brief Apre un file specificato.
         * 
         * Questo metodo tenta di aprire un file con il nome specificato in modalità lettura e scrittura.
         * Se il nome del file non è stato precedentemente impostato, il metodo imposta il nome del file.
         * Se l'apertura del file fallisce, stampa un messaggio di errore e restituisce false.
         * 
         * @param filename Il nome del file da aprire.
         * @return `true` se il file viene aperto con successo, `false` altrimenti.
         */
        bool openFile(string filename)
        {
            if(this->filename=="")
            {
                this->filename=filename;
            }
            database.open(filename,ios::in | ios::out); 
            if(!database.is_open())
            {
                cerr<<"open: "<<strerror(errno)<<endl;
                return false;
            }
            return true;
        }

        /**
         * @brief Inserisce un oggetto Abito nel database.
         * 
         * Questo metodo inserisce un oggetto Abito nel database. Prima dell'inserimento, 
         * il metodo attende che il semaforo sia disponibile, garantendo così l'accesso esclusivo al database.
         * Dopo l'inserimento, il semaforo viene rilasciato, permettendo ad altri processi di accedere al database.
         * 
         * @param abito L'oggetto Abito da inserire nel database.
         */
        void insert(Abito abito)
        {
            sem_wait(mutex);
            database.clear();
            database.seekg(0,ios::end);
            database<<abito;
            sem_post(mutex);
        }

        /**
         * @brief Cerca un abito nel database per ID.
         * 
         * Questo metodo cerca un abito nel database utilizzando l'ID fornito. 
         * Prima della ricerca, il metodo attende che il semaforo sia disponibile, 
         * garantendo così l'accesso esclusivo al database. Dopo la ricerca, 
         * il semaforo viene rilasciato, permettendo ad altri processi di accedere al database.
         * 
         * @param id L'ID dell'abito da cercare.
         * @return La stringa che rappresenta l'abito se trovato, altrimenti una stringa vuota.
         */
        string find(__uint16_t id)
        {
            sem_wait(mutex);
            database.clear();
            database.seekg(0);
            string line;
            stringstream ss;
            __uint16_t aid;
            while(getline(database,line))
            {
                ss.str(line);
                ss>>aid;
                if(id==aid)
                {
                    sem_post(mutex);
                    return line;
                }
                ss.clear();
            }
            sem_post(mutex);
            return "";
        }

        /**
         * @brief Legge la prossima riga dal database.
         * 
         * Questo metodo legge la prossima riga dal database. Alla prima chiamata, 
         * il metodo resetta il cursore del database all'inizio. 
         * In ogni chiamata successiva, il metodo continua a leggere dal punto in cui si è fermato.
         * Se non ci sono più righe da leggere, il metodo resetta il cursore all'inizio per la prossima chiamata.
         * 
         * Prima della lettura, il metodo attende che il semaforo sia disponibile, 
         * garantendo così l'accesso esclusivo al database. Dopo la lettura, 
         * il semaforo viene rilasciato, permettendo ad altri processi di accedere al database.
         * 
         * @return La prossima riga del database se disponibile, altrimenti una stringa vuota.
         */
        string nextLine()
        {
            sem_wait(mutex);
            static bool firstTime=true;
            if(firstTime)
            {
                database.clear();
                database.seekg(0);
                firstTime=false;
            }
            string line;
            if(getline(database,line))
            {
                sem_post(mutex);
                return line;
            }
            else
            {
                firstTime=true;
            }
            sem_post(mutex);
            return "";
        }

        /**
         * @brief Modifica o elimina una riga dal database.
         * 
         * Questo metodo modifica o elimina una riga dal database. 
         * Prima della modifica o eliminazione, il metodo attende che il semaforo sia disponibile, 
         * garantendo così l'accesso esclusivo al database. Dopo la modifica o eliminazione, 
         * il semaforo viene rilasciato, permettendo ad altri processi di accedere al database.
         * 
         * @param line La riga da modificare o eliminare.
         * @param abito L'oggetto Abito da utilizzare per la modifica. Se non specificato, la riga viene eliminata.
         * @return `true` se la riga viene modificata o eliminata con successo, `false` altrimenti.
         */
        bool deleteOrEditLine(string line, Abito*abito=nullptr)
        {
            sem_wait(mutex);
            database.seekg(0);
            fstream tmpOut("tmpFile",ios::out);
            string aline;
            while(getline(database,aline))
            {
                if(line!=aline)
                {
                    tmpOut<<aline<<endl;
                }
                else
                {
                    if(abito)
                    {
                        tmpOut<<*abito;
                    }
                }
            }
            database.close();
            tmpOut.close();
            rename("tmpFile",filename.c_str());
            if(!openFile(filename))
            {
                sem_post(mutex);
                return false;
            }
            sem_post(mutex);
            return true;
        }
        
        /**
         * @brief Rimuove un abito dal database.
         * 
         * Questo metodo rimuove un abito dal database. Prima della rimozione, 
         * il metodo attende che il semaforo sia disponibile, garantendo così l'accesso esclusivo al database.
         * Dopo la rimozione, il semaforo viene rilasciato, permettendo ad altri processi di accedere al database.
         * 
         * @param abito L'oggetto Abito da rimuovere dal database.
         * @return `true` se l'abito viene rimosso con successo, `false` altrimenti.
         */
        bool pop(Abito&abito, __uint16_t id)
        {
            sem_wait(mutex);
            string line;
            bool found;
            if((found=((line=find(id))!="")))
            {
                stringstream ss(line);
                ss>>abito;
                deleteOrEditLine(line);
            }
            sem_post(mutex);
            return found;
        }
};

#endif