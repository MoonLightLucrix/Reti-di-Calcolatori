#ifndef DOMANDA
#define DOMANDA

#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include "SocketService.hpp"

class Domanda
{
    private:
        static const size_t numeroRisposte=2;
        std::string testoDomanda;
        std::string risposte[numeroRisposte];
        size_t indiceRispostaCorretta;
    public:

        /**
         * @brief Costruttore della classe Domanda.
         * 
         * Questo costruttore inizializza un oggetto Domanda con il testo della domanda, un array di risposte e l'indice della risposta corretta.
         * Se l'array di risposte non è nullo, le risposte vengono copiate nell'oggetto Domanda.
         * 
         * @param testoDomanda Stringa che rappresenta il testo della domanda.
         * @param risposte Puntatore a un array di stringhe che rappresentano le possibili risposte. Può essere nullo.
         * @param indiceRispostaCorretta Indice della risposta corretta nell'array di risposte.
         */
        Domanda(std::string testoDomanda="", std::string*risposte=nullptr, size_t indiceRispostaCorretta=0);

        /**
         * @brief Distruttore della classe Domanda.
         * 
         * Questo distruttore viene chiamato automaticamente quando un oggetto Domanda viene distrutto.
         * Si occupa di rilasciare le risorse allocate dall'oggetto, se necessario.
         */
        ~Domanda();

        /**
         * @brief Imposta il testo della domanda.
         * 
         * Questo metodo permette di modificare il testo della domanda per un oggetto Domanda esistente.
         * 
         * @param testoDomanda Stringa che rappresenta il nuovo testo della domanda.
         */
        void setTestoDomanda(std::string testoDomanda);

        /**
         * @brief Restituisce il testo della domanda.
         * 
         * Questo metodo consente di ottenere il testo della domanda di un oggetto Domanda.
         * 
         * @return Una stringa che rappresenta il testo della domanda.
         */
        std::string getTestoDomanda() const; 

        /**
         * @brief Imposta le risposte per la domanda.
         * 
         * Questo metodo permette di modificare l'array di risposte per un oggetto Domanda esistente.
         * Le risposte vengono copiate dall'array fornito in input all'array interno dell'oggetto.
         * 
         * @param risposte Puntatore all'array di stringhe che rappresentano le nuove risposte. Deve avere una dimensione pari a `numeroRisposte`.
         */
        void setRisposte(std::string*risposte);

        /**
         * @brief Ottiene le risposte della domanda.
         * 
         * Questo metodo consente di copiare le risposte dell'oggetto Domanda in un array esterno fornito dall'utente.
         * L'array di destinazione deve essere sufficientemente grande da contenere tutte le risposte (dimensione `numeroRisposte`).
         * 
         * @param risposte Puntatore all'array di stringhe che verrà popolato con le risposte. Deve avere una dimensione pari a `numeroRisposte`.
         */
        void getRisposte(std::string*risposte) const;

        /**
         * @brief Imposta l'indice della risposta corretta.
         * 
         * Questo metodo permette di modificare l'indice della risposta corretta per un oggetto Domanda esistente.
         * 
         * @param indiceRispostaCorretta L'indice (basato su zero) della risposta corretta nell'array di risposte.
         */
        void setIndiceRispostaCorretta(size_t indiceRispostaCorretta);

        /**
         * @brief Restituisce l'indice della risposta corretta.
         * 
         * Questo metodo consente di ottenere l'indice della risposta corretta per un oggetto Domanda.
         * 
         * @return L'indice della risposta corretta.
         */
        size_t getIndiceRispostaCorretta() const;

        /**
         * @brief Genera una stringa contenente il testo della domanda e le risposte formattate.
         * 
         * Questo metodo costruisce una stringa che inizia con il testo della domanda seguito da un elenco numerato delle risposte.
         * Ogni risposta dispari nella lista è seguita da una serie di spazi per allineare le risposte su due colonne, 
         * mentre ogni risposta pari termina con un ritorno a capo, formattando così le risposte in modo più leggibile.
         * 
         * @return Una stringa che rappresenta il testo della domanda e le risposte formattate.
         */
        std::string leggiTesto() const;

        /**
         * @brief Stampa il testo della domanda e le risposte formattate.
         * 
         * Questo metodo utilizza `leggiTesto` per generare una stringa contenente il testo della domanda e le risposte formattate,
         * quindi stampa questa stringa sullo standard output tramite `std::cout`.
         */
        void stampa() const;

        friend std::ostream& operator <<(std::ostream &str, const Domanda&d);

        friend std::ifstream& operator >>(std::ifstream &str, Domanda&d);
        
        friend SocketService& operator <<(SocketService &str, const Domanda&d);
};

#endif