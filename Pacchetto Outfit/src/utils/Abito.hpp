#ifndef ABITO
#define ABITO

#include<iomanip>
using namespace std;

class Abito
{
    private:
        __uint16_t id;
        string nome;
        string taglia;
        __uint32_t quantità;
        double prezzo;
    public:

        /**
         * @brief Costruttore di Abito.
         * 
         * Questo costruttore crea un nuovo abito con l'ID, il nome, la taglia, la quantità e il prezzo forniti.
         * Se non vengono forniti valori, vengono utilizzati i valori di default.
         * 
         * @param id L'ID dell'abito. Default è 0.
         * @param nome Il nome dell'abito. Default è una stringa vuota.
         * @param taglia La taglia dell'abito. Default è una stringa vuota.
         * @param quantità La quantità dell'abito. Default è 0.
         * @param prezzo Il prezzo dell'abito. Default è 0.
         */
        Abito(__uint16_t id=0, string nome="", string taglia="", __uint16_t quantità=0, double prezzo=0): id(id), nome(nome), taglia(taglia), quantità(quantità), prezzo(prezzo) {}
        
        /**
         * @brief Distruttore di Abito.
         * 
         * Questo distruttore elimina l'oggetto Abito.
         */
        ~Abito(){}

        /**
         * @brief Imposta l'ID dell'abito.
         * 
         * Questo metodo imposta l'ID dell'abito con il valore fornito.
         * 
         * @param id Il nuovo ID dell'abito.
         */
        void setId(__uint16_t id)
        {
            this->id=id;
        }

        /**
         * @brief Restituisce l'ID dell'abito.
         * 
         * Questo metodo restituisce l'ID dell'abito.
         * 
         * @return L'ID dell'abito.
         */
        __uint16_t getId() const
        {
            return id;
        }

        /**
         * @brief Imposta il nome dell'abito.
         * 
         * Questo metodo imposta il nome dell'abito con il valore fornito.
         * 
         * @param nome Il nuovo nome dell'abito.
         */
        void setNome(string nome)
        {
            this->nome=nome;
        }

        /**
         * @brief Restituisce il nome dell'abito.
         * 
         * Questo metodo restituisce il nome dell'abito.
         * 
         * @return Il nome dell'abito.
         */
        string getNome() const
        {
            return nome;
        }

        /**
         * @brief Imposta la taglia dell'abito.
         * 
         * Questo metodo imposta la taglia dell'abito con il valore fornito.
         * 
         * @param taglia La nuova taglia dell'abito.
         */
        void setTaglia(string taglia)
        {
            this->taglia=taglia;
        }

        /**
         * @brief Restituisce la taglia dell'abito.
         * 
         * Questo metodo restituisce la taglia dell'abito.
         * 
         * @return La taglia dell'abito.
         */
        string getTaglia() const
        {
            return taglia;
        }

        /**
         * @brief Imposta la quantità dell'abito.
         * 
         * Questo metodo imposta la quantità dell'abito con il valore fornito.
         * 
         * @param quantità La nuova quantità dell'abito.
         */
        void setQuantità(__uint32_t quantità)
        {
            this->quantità=quantità;
        }

        /**
         * @brief Restituisce la quantità dell'abito.
         * 
         * Questo metodo restituisce la quantità dell'abito.
         * 
         * @return La quantità dell'abito.
         */
        __uint32_t getQuantità() const
        {
            return quantità;
        }

        /**
         * @brief Imposta il prezzo dell'abito.
         * 
         * Questo metodo imposta il prezzo dell'abito con il valore fornito.
         * 
         * @param prezzo Il nuovo prezzo dell'abito.
         */
        void setPrezzo(double prezzo)
        {
            this->prezzo=prezzo;
        }

        /**
         * @brief Restituisce il prezzo dell'abito.
         * 
         * Questo metodo restituisce il prezzo dell'abito.
         * 
         * @return Il prezzo dell'abito.
         */
        double getPrezzo() const
        {
            return prezzo;
        }

        friend bool operator >(const Abito&a, const Abito&b)
        {
            return (a.id>b.id);
        }

        friend bool operator >=(const Abito&a, const Abito&b)
        {
            return (a.id>=b.id);
        }

        friend bool operator <(const Abito&a, const Abito&b)
        {
            return (a.id<b.id);
        }

        friend bool operator <=(const Abito&a, const Abito&b)
        {
            return (a.id<=b.id);
        }

        friend bool operator ==(const Abito&a, const Abito&b)
        {
            return (a.id==b.id);
        }

        friend bool operator !=(const Abito&a, const Abito&b)
        {
            return (a.id!=b.id);
        }

        friend istream& operator >>(istream &str, Abito&a)
        {
            str>>a.id;
            str.ignore();
            getline(str,a.nome,'\t');
            getline(str,a.taglia,'\t');
            str>>a.quantità;
            str.ignore();
            str>>a.prezzo;
            return str;
        }

        friend ostream& operator <<(ostream &str, const Abito&a)
        {
            str<<"ID: "<<a.id<<" nome: "<<a.nome<<" taglia: "<<a.taglia<<" quantità: "<<a.quantità<<" prezzo: €"<<fixed<<setprecision(2)<<a.prezzo;
            return str;
        }

        friend fstream& operator >>(fstream &str, Abito&a)
        {
            str>>a.id;
            str.ignore();
            getline(str,a.nome,'\t');
            getline(str,a.taglia,'\t');
            str>>a.quantità;
            str.ignore();
            str>>a.prezzo;
            return str;
        }

        friend fstream& operator <<(fstream &str, const Abito&a)
        {
            str<<a.id<<"\t"<<a.nome<<"\t"<<a.taglia<<"\t"<<a.quantità<<"\t"<<a.prezzo<<endl;
            return str;
        }

        friend SocketService& operator >>(SocketService &str, Abito&a)
        {
            str>>a.id>>a.nome>>a.taglia>>a.quantità>>a.prezzo;
            return str;
        }
        
        friend SocketService& operator <<(SocketService &str, const Abito&a)
        {
            string prezzo2=to_string(a.prezzo);
            prezzo2=prezzo2.substr(0,prezzo2.find(".")+3);
            str<<"ID: "<<to_string(a.id)<<"\tnome: "<<a.nome<<"\ttaglia: "<<a.taglia<<"\tquantità: "<<to_string(a.quantità)<<"\tprezzo: €"<<prezzo2;
            return str;
        }
};

#endif