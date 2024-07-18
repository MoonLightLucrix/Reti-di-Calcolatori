#ifndef CONNECTIONHANDLER
#define CONNECTIONHANDLER

#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include "SocketService.hpp"
#include "Domanda.hpp"

class ConnectionHandler
{
    using Montepremi=__int64_t;
    private:
        static const size_t numeroDomande=10;
        Domanda domanda[numeroDomande];
        std::string nome;
        static const Montepremi importoMax=300000;
        static const Montepremi importoMin=10000;
        Montepremi importo;
        const std::string draw="\x1b[33m     _                   _   _                    _    _ _                  \n    / \\__   ____ _ _ __ | |_(_)  _   _ _ __      / \\  | | |_ _ __ ___       \n   / _ \\ \\ / / _` | '_ \\| __| | | | | | '_ \\    / _ \\ | | __| '__/ _ \\      \n  / ___ \\ V / (_| | | | | |_| | | |_| | | | |  / ___ \\| | |_| | | (_) | _ _ \n /_/__ \\_\\_/ \\__,_|_| |_|\\__|_|  \\__,_|_| |_| /_/   \\_\\_|\\__|_|  \\___(_|_|_)\n\x1b[93m |  _ \\ __ _  ___ ___| |__   ___| |_| |_ ___                                \n | |_) / _` |/ __/ __| '_ \\ / _ \\ __| __/ _ \\                               \n |  __/ (_| | (_| (__| | | |  __/ |_| || (_) |                              \n |_|   \\__,_|\\___\\___|_| |_|\\___|\\__|\\__\\___/                               \n                                                                            \x1b[0m\n";
        
        /**
         * @brief Carica le domande da un file e le assegna all'array fornito.
         * 
         * Questo metodo apre il file "/tmp/tableDomanda.txt" e legge le domande da esso, assegnandole all'array di domande passato come parametro.
         * Se il file non può essere aperto, stampa un messaggio di errore e termina il programma.
         * 
         * @param domanda Puntatore all'array di oggetti Domanda dove le domande lette dal file verranno salvate.
         */
        void generaDomande(Domanda*domanda);

    public:
        
        /**
         * @brief Costruttore della classe ConnectionHandler.
         * 
         * Questo costruttore inizializza un oggetto ConnectionHandler con un nome specificato.
         * Imposta inoltre un valore casuale per l'importo, compreso tra `importoMin` e `importoMax`, e genera le domande
         * chiamando il metodo `generaDomande`.
         * 
         * @param nome Il nome da assegnare all'oggetto ConnectionHandler.
         */
        ConnectionHandler(std::string nome);

        /**
         * @brief Distruttore della classe ConnectionHandler.
         * 
         * Questo distruttore viene chiamato automaticamente quando un oggetto ConnectionHandler viene distrutto.
         * Si occupa di rilasciare le risorse allocate dall'oggetto, se necessario.
         */
        ~ConnectionHandler();

        /**
         * @brief Gestisce il gioco "Avanti un altro" con il client.
         * 
         * Questo metodo inizia presentando il gioco al client, chiedendo se desidera iniziare a giocare.
         * Se il client risponde "Sì", il gioco procede presentando le domande una alla volta e chiedendo le risposte.
         * Se il client risponde correttamente, passa alla domanda successiva; altrimenti, l'importo del premio viene ridotto.
         * Se l'importo del premio scende a zero, il gioco termina e il client perde.
         * Se il client risponde correttamente a tutte le domande, vince l'importo del premio.
         * 
         * @param client Riferimento a SocketService per la comunicazione con il client.
         */
        void avantiUnAltro(SocketService&client);
};

#endif