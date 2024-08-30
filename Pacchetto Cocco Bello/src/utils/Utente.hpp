#ifndef UTENTE
#define UTENTE

#include<iostream>
#include<fstream>
#include<sstream>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include<openssl/sha.h>
#include "SocketService.hpp"

class Utente
{
    private:
        std::string username;
        std::string password;
        std::string dPassword;
        std::string numero;

        /**
         * @brief Calcola l'hash SHA-256 di una password.
         *
         * Questo metodo prende una stringa di password come input e calcola il suo hash SHA-256.
         * Restituisce l'hash come stringa esadecimale.
         *
         * @param password La password da cui fare hash.
         * @return L'hash SHA-256 della password come stringa esadecimale.
         */
        std::string getSHA256(std::string password);

    public:

        /**
         * @brief Costruttore della classe Utente.
         *
         * Inizializza un'istanza di Utente con il nome utente, la password e il numero specificati.
         * Se la password non è vuota, viene calcolato il suo hash SHA-256 e memorizzato in dPassword.
         * La password originale viene quindi cancellata.
         *
         * @param username Il nome utente.
         * @param password La password dell'utente.
         * @param numero Il numero associato all'utente.
         */
        Utente(std::string username="", std::string password="", std::string numero="");

        /**
         * @brief Distruttore della classe Utente.
         *
         * Questo metodo viene chiamato automaticamente quando un'istanza di Utente viene distrutta.
         */
        ~Utente();

        /**
         * @brief Imposta il nome utente.
         *
         * Questo metodo imposta il nome utente con il valore specificato.
         *
         * @param username Il nuovo nome utente.
         */
        void setUsername(std::string username);

        /**
         * @brief Restituisce il nome utente.
         *
         * Questo metodo restituisce il nome utente dell'istanza corrente.
         *
         * @return Il nome utente.
         */
        std::string getUsername() const;

        /**
         * @brief Imposta l'hash della password.
         *
         * Questo metodo prende una password in chiaro, calcola il suo hash SHA-256 e lo memorizza
         * in dPassword. La password originale viene quindi cancellata.
         *
         * @param password La password in chiaro da cui generare l'hash e impostare.
         */
        void setDPassword(std::string&password);
        
        /**
         * @brief Restituisce l'hash della password.
         *
         * Questo metodo restituisce l'hash della password dell'istanza corrente.
         *
         * @return L'hash della password.
         */
        std::string getDPassword() const;

        /**
         * @brief Imposta il numero associato all'utente.
         *
         * Questo metodo imposta il numero con il valore specificato.
         *
         * @param numero Il nuovo numero associato all'utente.
         */
        void setNumero(std::string numero);

        /**
         * @brief Restituisce il numero associato all'utente.
         *
         * Questo metodo restituisce il numero associato all'utente dell'istanza corrente.
         *
         * @return Il numero associato all'utente.
         */
        std::string getNumero() const;

        /**
         * @brief Confronta l'hash della password con un'altra hash della password.
         *
         * Questo metodo confronta l'hash della password memorizzata nell'istanza corrente con
         * un'altro hash di una password passata come parametro.
         *
         * @param dPassword L'hash della password da confrontare.
         * @return `true` se i due hash sono uguali, `false` altrimenti.
         */
        bool compare(std::string password);

        /**
         * @brief Restituisce una stringa con le informazioni dell'utente.
         *
         * Questo metodo restituisce una stringa contenente il nome utente e il numero associato
         * all'istanza corrente dell'utente.
         *
         * @return Una stringa con il nome utente e il numero.
         */
        std::string leggiUtente() const;

        /**
         * @brief Stampa le informazioni dell'utente.
         *
         * Questo metodo stampa le informazioni dell'utente, inclusi il nome utente e il numero.
         */
        void stampa() const;

        friend std::istream& operator >>(std::istream &str, Utente&u);

        friend std::ostream& operator <<(std::ostream &str, Utente&u);

        friend std::fstream& operator >>(std::fstream &str, Utente&u);
        
        friend std::fstream& operator <<(std::fstream &str, Utente&u);
};

#endif