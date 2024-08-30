#ifndef LISTA
#define LISTA

#include<functional>
#include<type_traits>

template<class T>
class Nodo
{
    private:
        Nodo<T>*succ;
        Nodo<T>*prec;
        T info;
    public:

        /**
         * @brief Costruttore di Nodo.
         * 
         * Questo costruttore crea un nuovo nodo con l'informazione data e i puntatori al nodo successivo e precedente.
         * Se non vengono forniti puntatori al nodo successivo e precedente, vengono impostati a `nullptr`.
         * 
         * @param info L'informazione da memorizzare nel nodo.
         * @param succ Il puntatore al nodo successivo. Default è `nullptr`.
         * @param prec Il puntatore al nodo precedente. Default è `nullptr`.
         */
        Nodo<T>(T info, Nodo<T>*prec=nullptr, Nodo<T>*succ=nullptr);

        /**
         * @brief Distruttore di Nodo.
         * 
         * Questo distruttore elimina il nodo.
         */
        ~Nodo<T>();

        /**
         * @brief Imposta il puntatore al nodo precedente.
         * 
         * Questo metodo imposta il puntatore al nodo precedente.
         * 
         * @param prec Il puntatore al nodo precedente.
         */
        void setPrec(Nodo<T>*prec);

        /**
         * @brief Restituisce il puntatore al nodo precedente.
         * 
         * Questo metodo restituisce il puntatore al nodo precedente.
         * 
         * @return Il puntatore al nodo precedente.
         */
        Nodo<T>*getPrec() const;

        /**
         * @brief Imposta il puntatore al nodo successivo.
         * 
         * Questo metodo imposta il puntatore al nodo successivo.
         * 
         * @param succ Il puntatore al nodo successivo.
         */
        void setSucc(Nodo<T>*succ);

        /**
         * @brief Restituisce il puntatore al nodo successivo.
         * 
         * Questo metodo restituisce il puntatore al nodo successivo.
         * 
         * @return Il puntatore al nodo successivo.
         */
        Nodo<T>*getSucc() const;

        /**
         * @brief Imposta l'informazione del nodo.
         * 
         * Questo metodo imposta l'informazione del nodo.
         * 
         * @param info L'informazione da memorizzare nel nodo.
         */
        void setInfo(T info);

        /**
         * @brief Restituisce l'informazione del nodo.
         * 
         * Questo metodo restituisce l'informazione del nodo.
         * 
         * @return L'informazione del nodo.
         */
        T getInfo() const;
};

template<class T>
class Iterator
{
    private:
        Nodo<T>*a;
    public:

        /**
         * @brief Costruttore di Iterator.
         * 
         * Questo costruttore crea un nuovo iteratore che punta al nodo fornito.
         * Se non viene fornito alcun nodo, l'iteratore punta a `nullptr`.
         * 
         * @param a Il nodo a cui l'iteratore dovrebbe puntare. Default è `nullptr`.
         */
        Iterator<T>(Nodo<T>*a=nullptr);

        /**
         * @brief Distruttore di Iterator.
         * 
         * Questo distruttore elimina l'iteratore.
         */
        ~Iterator<T>();

        /**
         * @brief Operatore di incremento prefisso.
         * 
         * Questo operatore incrementa l'iteratore al nodo successivo.
         * 
         * @return L'iteratore incrementato.
         */
        Iterator<T>& operator++();

        /**
         * @brief Operatore di dereferenziazione.
         * 
         * Questo operatore restituisce l'informazione contenuta nel nodo a cui l'iteratore sta puntando.
         * 
         * @return L'informazione contenuta nel nodo a cui l'iteratore sta puntando.
         */
        T operator*();

        /**
         * @brief Operatore di confronto di uguaglianza.
         * 
         * Questo operatore confronta due iteratori per verificare se puntano allo stesso nodo.
         * 
         * @param b L'iteratore da confrontare.
         * @return `true` se i due iteratori puntano allo stesso nodo, `false` altrimenti.
         */
        bool operator!=(const Iterator&b);
};

template<class T>
class Lista
{
    protected:
        Nodo<T>*testa;
        size_t s;

        /**
         * @brief Trova un nodo nella lista.
         * 
         * Questo metodo cerca un nodo nella lista che contiene l'informazione fornita.
         * Se il nodo viene trovato, viene restituito un puntatore a quel nodo.
         * Se il nodo non viene trovato, viene restituito un puntatore nullo.
         * 
         * @param x L'informazione da cercare nella lista.
         * @return Un puntatore al nodo che contiene l'informazione, se trovato. Altrimenti, `nullptr`.
         */
        Nodo<T>*find(T x) const;

    public:

        /**
         * @brief Costruttore di Lista.
         * 
         * Questo costruttore crea una nuova lista vuota.
         */
        Lista<T>();

        /**
         * @brief Distruttore di Lista.
         * 
         * Questo distruttore elimina la lista.
         */
        ~Lista<T>();

        /**
         * @brief Restituisce un iteratore all'inizio della lista.
         * 
         * Questo metodo restituisce un iteratore che punta al primo nodo della lista.
         * 
         * @return Un iteratore all'inizio della lista.
         */
        Iterator<T> begin() const;

        /**
         * @brief Restituisce un iteratore alla fine della lista.
         * 
         * Questo metodo restituisce un iteratore che punta alla fine della lista.
         * 
         * @return Un iteratore alla fine della lista.
         */
        Iterator<T> end() const;
        
        /**
         * @brief Svuota la lista.
         * 
         * Questo metodo rimuove tutti i nodi dalla lista, liberando la memoria allocata per ciascuno di essi.
         * Dopo che questo metodo è stato chiamato, la lista è vuota.
         * 
         * @return Un puntatore a questa lista, che ora è vuota.
         */
        Lista<T>*clear();

        /**
         * @brief Restituisce la dimensione della lista.
         * 
         * Questo metodo restituisce la dimensione della lista.
         * 
         * @return La dimensione della lista.
         */
        size_t getSize() const;

        /**
         * @brief Aggiunge un elemento alla fine della lista.
         * 
         * Questo metodo aggiunge un elemento alla fine della lista.
         * 
         * @param x L'elemento da aggiungere alla lista.
         * @return Un puntatore alla lista.
         */
        virtual Lista<T>*append(T x)=0;

        /**
         * @brief Rimuove un elemento dalla lista.
         * 
         * Questo metodo rimuove un elemento dalla lista.
         * 
         * @param x L'elemento da rimuovere dalla lista.
         * @return Un puntatore alla lista.
         */
        virtual Lista<T>*remove(T x)=0;

        /**
         * @brief Applica una funzione a tutti gli elementi della lista.
         * 
         * Questo metodo applica una funzione a tutti gli elementi della lista.
         * 
         * @param lambda La funzione da applicare a tutti gli elementi della lista.
         * @return Un puntatore alla lista.
         */
        Lista<T>*map(function<T(T)> lambda);

        /**
         * @brief Filtra gli elementi della lista.
         * 
         * Questo metodo filtra gli elementi della lista in base a un predicato.
         * 
         * @param predicate Il predicato da utilizzare per filtrare gli elementi della lista.
         * @return Un puntatore alla lista.
         */
        Lista<T>*filter(function<bool(T)> predicate);

        /**
         * @brief Riduce la lista a un valore.
         * 
         * Questo metodo riduce la lista a un singolo valore, utilizzando una funzione lambda.
         * 
         * @param lambda La funzione lambda da utilizzare per ridurre la lista.
         * @return Il valore ridotto della lista.
         */
        template<class U>
        U reduce(std::function<U(T,U)> lambda);

        /**
         * @brief Controlla se un elemento è presente nella lista.
         * 
         * Questo metodo controlla se un elemento è presente nella lista.
         * 
         * @param x L'elemento da cercare nella lista.
         * @return `true` se l'elemento è presente nella lista, `false` altrimenti.
         */
        bool contains(T x) const;

        /**
         * @brief Stampa la lista.
         * 
         * Questo metodo stampa la lista.
         */
        void stampa() const;

        template<class T>
        friend std::ostream& operator <<(std::ostream &str, const Lista<T>&a);
};

template<class T>
class LinkedList: public Lista<T>
{
    private:
        using Lista<T>::testa;
        using Lista<T>::s;
        using Lista<T>::find;
    public:
        using Lista<T>::begin;
        using Lista<T>::end;
        using Lista<T>::clear;
        using Lista<T>::getSize;
        using Lista<T>::map;
        using Lista<T>::filter;
        using Lista<T>::reduce;
        using Lista<T>::contains;
        using Lista<T>::stampa;

        /**
         * @brief Costruttore per la classe LinkedList.
         *
         * Inizializza una nuova istanza di LinkedList chiamando il costruttore della classe base Lista.
         */
        LinkedList<T>();

        /**
         * @brief Distruttore della classe LinkedList.
         *
         * Libera la memoria allocata per la lista collegata.
         */
        ~LinkedList<T>();

        /**
         * @brief Aggiunge un nuovo elemento alla fine della lista collegata.
         * 
         * @param x L'elemento da aggiungere alla lista.
         * @return Un puntatore alla lista aggiornata.
         */
        Lista<T>*append(T x) override;

        /**
         * @brief Rimuove un nodo contenente il valore specificato dalla lista collegata.
         *
         * Questo metodo cerca il primo nodo nella lista collegata che contiene il valore `x`.
         * Se il nodo viene trovato, viene rimosso dalla lista e la memoria allocata per il nodo viene liberata.
         * La dimensione della lista viene decrementata di 1.
         *
         * @param x Il valore da rimuovere dalla lista.
         * @return Un puntatore alla lista aggiornata.
         */
        Lista<T>*remove(T x) override;
};

template<class T>
class ListaDoppia: public Lista<T>
{
    private:
        using Lista<T>::testa;
        using Lista<T>::s;
        using Lista<T>::find;
        Nodo<T>*coda;
    public:
        using Lista<T>::begin;
        using Lista<T>::end;
        using Lista<T>::clear;
        using Lista<T>::getSize;
        using Lista<T>::map;
        using Lista<T>::filter;
        using Lista<T>::reduce;
        using Lista<T>::contains;
        using Lista<T>::stampa;

        /**
         * @brief Costruttore di default per la classe ListaDoppia.
         *
         * Inizializza una nuova istanza di ListaDoppia chiamando il costruttore della classe base Lista.
         */
        ListaDoppia<T>();

        /**
         * @brief Distruttore della classe ListaDoppia.
         *
         * Libera la memoria allocata per la lista doppiamente collegata.
         */
        ~ListaDoppia<T>();

        /**
         * @brief Aggiunge un nuovo nodo con il valore specificato alla fine della lista doppiamente collegata.
         *
         * Questo metodo crea un nuovo nodo contenente il valore `x` e lo aggiunge alla fine della lista.
         * Se la lista è vuota, il nuovo nodo diventa sia la testa che la coda della lista.
         * Altrimenti, il nuovo nodo viene collegato alla coda attuale e diventa la nuova coda.
         * La dimensione della lista viene incrementata di 1.
         *
         * @param x Il valore da aggiungere alla lista.
         * @return Un puntatore alla lista aggiornata.
         */
        Lista<T>*append(T x) override;

        /**
         * @brief Rimuove un nodo contenente il valore specificato dalla lista doppiamente collegata.
         *
         * Questo metodo cerca un nodo contenente il valore `x` e lo rimuove dalla lista.
         * Se il nodo da rimuovere è la testa, la testa viene aggiornata.
         * Se il nodo da rimuovere è la coda, la coda viene aggiornata.
         * Altrimenti, il nodo viene scollegato dai suoi nodi precedenti e successivi.
         * La dimensione della lista viene decrementata di 1.
         *
         * @param x Il valore del nodo da rimuovere dalla lista.
         * @return Un puntatore alla lista aggiornata.
         */
        Lista<T>*remove(T x) override;
};

template<class T>
class OrderedList: public Lista<T>
{
    private:
        using Lista<T>::testa;
        using Lista<T>::s;
        using Lista<T>::find;
        Nodo<T>*coda;
    public:
        using Lista<T>::begin;
        using Lista<T>::end;
        using Lista<T>::clear;
        using Lista<T>::getSize;
        using Lista<T>::map;
        using Lista<T>::filter;
        using Lista<T>::reduce;
        using Lista<T>::contains;
        using Lista<T>::stampa;

        /**
         * @brief Costruttore di OrderedList.
         * 
         * Questo costruttore crea una nuova lista ordinata vuota.
         */
        OrderedList<T>();

        /**
         * @brief Distruttore di OrderedList.
         * 
         * Questo distruttore elimina la lista ordinata.
         */
        ~OrderedList<T>();

        /**
         * @brief Inserisce un elemento nella lista ordinata.
         * 
         * Questo metodo inserisce un nuovo elemento nella lista mantenendo l'ordine degli elementi.
         * L'elemento viene inserito nella posizione corretta in base al criterio di ordinamento definito per la lista.
         * 
         * @param x L'elemento da inserire nella lista.
         * @return Un puntatore alla lista dopo l'inserimento dell'elemento.
         */
        Lista<T>*append(T x) override;

        /**
         * @brief Rimuove un elemento dalla lista ordinata.
         * 
         * Questo metodo rimuove un elemento dalla lista ordinata.
         * 
         * @param x L'elemento da rimuovere dalla lista.
         * @return Un puntatore alla lista dopo la rimozione dell'elemento.
         */
        Lista<T>*remove(T x) override;
};

#include "Lista.cpp"

#endif