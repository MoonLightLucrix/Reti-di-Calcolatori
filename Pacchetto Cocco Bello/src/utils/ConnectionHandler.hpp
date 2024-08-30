#ifndef CONNECTIONHANDLER
#define CONNECTIONHANDLER

#include<iostream>
#include<cstdlib>
#include<cstring>
#include "SocketService.hpp"
#include "Prodotto.hpp"
#include "Utente.hpp"
#include "DatabaseManager.hpp"

class ConnectionHandler
{
    private:
        DatabaseManager dbProdotto;
        DatabaseManager dbUtente;
        const std::string filenameProdotto="/tmp/tableProdotto.txt";
        const std::string semNameProdotto="/semMutexProdotto";
        const std::string filenameUtente="/tmp/tableUtente.txt";
        const std::string semNameUtente="/semMutexUtente";
        const std::string titolo="\x1b[94m.-..-.      .----.  .--.   .---.  .---. .-. .-..----..---.  .---.  .----. \n| || |      | {}  }/ {} \\ /  ___}/  ___}| {_} || {_ {_   _}{_   _}/  {}  \\\n| || `--.   | .--'/  /\\  \\\\     }\\     }| { } || {__  | |    | |  \\      /\n`-'`----'   `-'   `-'  `-' `---'  `---' `-' `-'`----' `-'    `-'   `----' \n\x1b[33m .---.  .----.  .---.  .---.  .----.\x1b[37m    .----. .----..-.   .-.    .----.  \n\x1b[33m/  ___}/  {}  \\/  ___}/  ___}/  {}  \\\x1b[37m   | {}  }| {_  | |   | |   /  {}  \\ \n\x1b[33m\\     }\\      /\\     }\\     }\\      /\x1b[37m   | {}  }| {__ | `--.| `--.\\      / \n\x1b[33m `---'  `----'  `---'  `---'  `----'\x1b[37m    `----' `----'`----'`----' `----'  \x1b[0m\n";
        const std::string menù="+--------------------+\n| l - lista prodotti |\n| a - acquista       |\n| q - esci           |\n+--------------------+\n\n\n\n\n\n\n\n\n";
        Utente utente;

        /**
         * @brief Gestisce il processo di autenticazione dell'utente.
         *
         * Questo metodo richiede all'utente di inserire il proprio username e password.
         * Verifica se l'username esiste nel database e se l'hash della password inserita
         * corrisponde a quella memorizzata.
         *
         * @param client Riferimento al client per la comunicazione.
         * @return `true` se l'autenticazione ha successo, `false` altrimenti.
         */
        bool signIn(Server&client);

        /**
         * @brief Fornisce una lista di prodotti al client.
         *
         * Questo metodo recupera la lista dei prodotti dal database e la invia al client.
         * Ogni prodotto viene letto dal database, convertito in un oggetto Prodotto e
         * inviato al client in formato leggibile.
         *
         * @param client Riferimento al client per la comunicazione.
         */
        void listaProdotti(Server&client);

        /**
         * @brief Gestisce il processo di acquisto di un prodotto da parte dell'utente.
         *
         * Questo metodo richiede all'utente di inserire l'ID e la quantità del prodotto
         * che desidera acquistare. Verifica se il prodotto esiste nel database e se la
         * quantità richiesta è disponibile. Se l'acquisto ha successo, il metodo aggiorna
         * la quantità del prodotto nel database e invia un messaggio di conferma al client
         * con il costo totale dell'acquisto. In caso di errore, invia un messaggio di errore
         * appropriato al client.
         *
         * @param client Riferimento al client per la comunicazione.
         * @return `true` se l'acquisto ha successo, `false` altrimenti.
         */
        bool acquista(Server&client);

    public:

        /**
         * @brief Costruttore della classe ConnectionHandler.
         *
         * Inizializza le risorse necessarie per la gestione delle connessioni, inclusi
         * i semafori e i file di database per i prodotti e gli utenti. Se l'apertura
         * di un semaforo o di un file fallisce, il programma termina con un errore.
         */
        ConnectionHandler();

        /**
         * @brief Distruttore della classe ConnectionHandler.
         *
         * Questo distruttore viene chiamato quando un oggetto ConnectionHandler viene distrutto.
         */
        ~ConnectionHandler();

        /**
         * @brief Gestisce la connessione e l'interazione con il client.
         *
         * Questo metodo gestisce il processo di autenticazione dell'utente e fornisce
         * un menù di comandi per interagire con il sistema. L'utente può visualizzare
         * la lista dei prodotti, acquistare prodotti o terminare la sessione. Se
         * l'autenticazione fallisce, il metodo termina la connessione con il client.
         *
         * @param client Riferimento al client per la comunicazione.
         * @return `true` se la connessione è stata gestita correttamente, `false` altrimenti.
         */
        bool connection(Server&client);
};

#endif