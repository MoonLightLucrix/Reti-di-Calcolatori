#ifndef PRODOTTO
#define PRODOTTO

#include<iostream>
#include<fstream>
#include<cstdlib>
#include<iomanip>
#include<cstring>
#include "SocketService.hpp"

namespace Prodotto
{
    using ID=__uint16_t;
    using Quantità=__uint32_t;
    class Prodotto
    {
        private:
            ID id;
            std::string nome;
            double prezzo;
            Quantità quantità;
        public:

            /**
             * @brief Costruttore della classe Prodotto.
             * 
             * @param id Identificativo del prodotto. Valore predefinito è 0.
             * @param nome Nome del prodotto. Valore predefinito è una stringa vuota.
             * @param prezzo Prezzo del prodotto. Valore predefinito è 0.
             * @param quantità Quantità del prodotto. Valore predefinito è 0.
             */
            Prodotto(ID id=0, std::string nome="", double prezzo=0, Quantità quantità=0);

            /**
             * @brief Distruttore della classe Prodotto.
             */
            ~Prodotto();

            /**
             * @brief Imposta l'ID del prodotto.
             * 
             * @param id Nuovo ID del prodotto.
             */
            void setID(ID id);

            /**
             * @brief Restituisce l'ID del prodotto.
             * 
             * @return ID del prodotto.
             */
            ID getID() const;

            /**
             * @brief Imposta il nome del prodotto.
             * 
             * @param nome Nuovo nome del prodotto.
             */
            void setNome(std::string nome);

            /**
             * @brief Restituisce il nome del prodotto.
             * 
             * @return Nome del prodotto.
             */
            std::string getNome() const;

            /**
             * @brief Imposta il prezzo del prodotto.
             * 
             * @param prezzo Nuovo prezzo del prodotto.
             */
            void setPrezzo(double prezzo);

            /**
             * @brief Restituisce il prezzo del prodotto.
             * 
             * @return Prezzo del prodotto.
             */
            double getPrezzo() const;

            /**
             * @brief Imposta la quantità del prodotto.
             * 
             * @param quantità Nuova quantità del prodotto.
             */
            void setQuantità(Quantità quantità);

            /**
             * @brief Restituisce la quantità del prodotto.
             * 
             * @return Quantità del prodotto.
             */
            Quantità getQuantità() const;

            /**
             * @brief Restituisce una stringa contenente le informazioni del prodotto.
             * 
             * @return Una stringa formattata con ID, nome, prezzo e quantità del prodotto.
             */
            std::string leggiProdotto() const;

            /**
             * @brief Stampa le informazioni del prodotto.
             */
            void stampa() const;

            friend std::istream& operator >>(std::istream &str, Prodotto&p);

            friend std::ostream& operator <<(std::ostream &str, Prodotto&p);

            friend std::fstream& operator >>(std::fstream &str, Prodotto&p);

            friend std::fstream& operator <<(std::fstream &str, Prodotto&p);

            friend SocketService& operator <<(SocketService &str, const Prodotto&p);
    };
};

#endif