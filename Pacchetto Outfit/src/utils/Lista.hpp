#ifndef LISTA
#define LISTA

using namespace std;

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
        Nodo<T>(T info, Nodo<T>*succ=nullptr, Nodo<T>*prec=nullptr): info(info), succ(succ), prec(prec) {}

        /**
         * @brief Distruttore di Nodo.
         * 
         * Questo distruttore elimina il nodo.
         */
        ~Nodo<T>(){}

        /**
         * @brief Imposta il puntatore al nodo successivo.
         * 
         * Questo metodo imposta il puntatore al nodo successivo.
         * 
         * @param succ Il puntatore al nodo successivo.
         */
        void setSucc(Nodo<T>*succ)
        {
            this->succ=succ;
        }

        /**
         * @brief Restituisce il puntatore al nodo successivo.
         * 
         * Questo metodo restituisce il puntatore al nodo successivo.
         * 
         * @return Il puntatore al nodo successivo.
         */
        Nodo<T>*getSucc() const
        {
            return succ;
        }

        /**
         * @brief Imposta il puntatore al nodo precedente.
         * 
         * Questo metodo imposta il puntatore al nodo precedente.
         * 
         * @param prec Il puntatore al nodo precedente.
         */
        void setPrec(Nodo<T>*prec)
        {
            this->prec=prec;
        }

        /**
         * @brief Restituisce il puntatore al nodo precedente.
         * 
         * Questo metodo restituisce il puntatore al nodo precedente.
         * 
         * @return Il puntatore al nodo precedente.
         */
        Nodo<T>*getPrec() const
        {
            return prec;
        }

        /**
         * @brief Imposta l'informazione del nodo.
         * 
         * Questo metodo imposta l'informazione del nodo.
         * 
         * @param info L'informazione da memorizzare nel nodo.
         */
        void setInfo(T info)
        {
            this->info=info;
        }

        /**
         * @brief Restituisce l'informazione del nodo.
         * 
         * Questo metodo restituisce l'informazione del nodo.
         * 
         * @return L'informazione del nodo.
         */
        T getInfo() const
        {
            return info;
        }
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
        Iterator(Nodo<T>*a=nullptr): a(a) {}

        /**
         * @brief Distruttore di Iterator.
         * 
         * Questo distruttore elimina l'iteratore.
         */
        ~Iterator(){}

        /**
         * @brief Operatore di incremento prefisso.
         * 
         * Questo operatore incrementa l'iteratore al nodo successivo.
         * 
         * @return L'iteratore incrementato.
         */
        Iterator& operator++()
        {
            a=a->getSucc();
            return *this;
        }

        /**
         * @brief Operatore di dereferenziazione.
         * 
         * Questo operatore restituisce l'informazione contenuta nel nodo a cui l'iteratore sta puntando.
         * 
         * @return L'informazione contenuta nel nodo a cui l'iteratore sta puntando.
         */
        T operator*()
        {
            return a->getInfo();
        }

        /**
         * @brief Operatore di confronto di uguaglianza.
         * 
         * Questo operatore confronta due iteratori per verificare se puntano allo stesso nodo.
         * 
         * @param b L'iteratore da confrontare.
         * @return `true` se i due iteratori puntano allo stesso nodo, `false` altrimenti.
         */
        bool operator!=(const Iterator&b)
        {
            return (a!=b.a);
        }
};

template<class T>
class Lista
{
    protected:
        Nodo<T>*testa;
        size_t size;

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
        Nodo<T>*find(T x)
        {
            Nodo<T>*a=nullptr;
            for(a=testa; a; a=a->getSucc())
            {
                if(a->getInfo()==x)
                {
                    break;
                }
            }
            return a;
        }
    public:

        /**
         * @brief Costruttore di Lista.
         * 
         * Questo costruttore crea una nuova lista vuota.
         */
        Lista<T>(): testa(nullptr), size(0) {}

        /**
         * @brief Distruttore di Lista.
         * 
         * Questo distruttore elimina la lista.
         */
        ~Lista<T>()
        {
            clear();
        }

        /**
         * @brief Restituisce la dimensione della lista.
         * 
         * Questo metodo restituisce la dimensione della lista.
         * 
         * @return La dimensione della lista.
         */
        size_t getSize() const
        {
            return size;
        }

        /**
         * @brief Restituisce il puntatore al nodo in testa alla lista.
         * 
         * Questo metodo restituisce il puntatore al nodo in testa alla lista.
         * 
         * @return Il puntatore al nodo in testa alla lista.
         */
        Nodo<T>*getTesta() const
        {
            return testa;
        }

        /**
         * @brief Restituisce un iteratore all'inizio della lista.
         * 
         * Questo metodo restituisce un iteratore che punta al primo nodo della lista.
         * 
         * @return Un iteratore all'inizio della lista.
         */
        Iterator<T> begin()
        {
            return Iterator<T>(testa);
        }

        /**
         * @brief Restituisce un iteratore alla fine della lista.
         * 
         * Questo metodo restituisce un iteratore che punta alla fine della lista.
         * 
         * @return Un iteratore alla fine della lista.
         */
        Iterator<T> end()
        {
            return Iterator<T>();
        }

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
         * @brief Aggiunge un elemento all'inizio della lista.
         * 
         * Questo metodo aggiunge un elemento all'inizio della lista.
         * 
         * @param x L'elemento da aggiungere alla lista.
         * @return Un puntatore alla lista.
         */
        virtual Lista<T>*push(T x)=0;

        /**
         * @brief Rimuove un elemento dall'inizio della lista.
         * 
         * Questo metodo rimuove un elemento dall'inizio della lista.
         * 
         * @return Un puntatore alla lista.
         */
        virtual Lista<T>*pop()=0;

        /**
         * @brief Controlla se un elemento è presente nella lista.
         * 
         * Questo metodo controlla se un elemento è presente nella lista.
         * 
         * @param x L'elemento da cercare nella lista.
         * @return `true` se l'elemento è presente nella lista, `false` altrimenti.
         */
        bool contains(T x) const
        {
            return (find(x));
        }


        /**
         * @brief Svuota la lista.
         * 
         * Questo metodo rimuove tutti i nodi dalla lista, liberando la memoria allocata per ciascuno di essi.
         * Dopo che questo metodo è stato chiamato, la lista è vuota.
         * 
         * @return Un puntatore a questa lista, che ora è vuota.
         */
        Lista<T>*clear()
        {
            Nodo<T>*a;
            while(testa)
            {
                a=testa;
                testa=testa->getSucc();
                delete a;
                size-=1;
            }
            return this;
        }

        /*Lista<T>*clear()
        {
            while(size)
            {
                remove(testa->getInfo());
            }
            return this;
        }*/

        /**
         * @brief Applica una funzione a tutti gli elementi della lista.
         * 
         * Questo metodo applica una funzione a tutti gli elementi della lista.
         * 
         * @param lambda La funzione da applicare a tutti gli elementi della lista.
         * @return Un puntatore alla lista.
         */
        Lista<T>*map(function<T(T)> lambda)
        {
            for(Nodo<T>*a=testa; a; a=a->getSucc())
            {
                a->setInfo(lambda(a->getInfo()));
            }
            return this;
        }

        /**
         * @brief Filtra gli elementi della lista.
         * 
         * Questo metodo filtra gli elementi della lista in base a un predicato.
         * 
         * @param predicate Il predicato da utilizzare per filtrare gli elementi della lista.
         * @return Un puntatore alla lista.
         */
        Lista<T>*filter(function<bool(T)> predicate)
        {
            Nodo<T>*a=testa;
            while(a) 
            {
                if(predicate(a->getInfo())) 
                {
                    T dataToRemove=a->getInfo();
                    a=a->getSucc();
                    remove(dataToRemove);
                }
                else
                {
                    a=a->getSucc();
                }
            }
            return this;
        }

        /**
         * @brief Restituisce un array con tutti gli elementi della lista.
         * 
         * Questo metodo restituisce un array con tutti gli elementi della lista.
         * 
         * @return Un array con tutti gli elementi della lista.
         */
        T*toArray() const
        {
            T*vett=new T[size];
            Nodo<T>*a=testa;
            for(int i=0; i<=size-1; i-=-1)
            {
                vett[i]=a->getInfo();
                a=a->getSucc();
            }
            return vett;
        }

        /**
         * @brief Restituisce un array con tutti gli elementi della lista.
         * 
         * Questo metodo restituisce un array con tutti gli elementi della lista.
         * 
         * @param vett L'array in cui memorizzare gli elementi della lista.
         */
        void toArray(T*vett) const
        {
            size_t vSize=sizeof(vett)/sizeof(T);
            Nodo<T>*a=testa;
            for(int i=0; i<=vSize-1; i-=-1)
            {
                vett[i]=a->getInfo();
                a=a->getSucc();
            }
        }

        /**
         * @brief Stampa la lista.
         * 
         * Questo metodo stampa la lista.
         */
        void stampa() const
        {
            cout<<"[";
            for(Nodo<T>*a=testa; a; a=a->getSucc())
            {
                cout<<a->getInfo()<<((a->getSucc())?", ":"");
            }
            cout<<"]";
        }
        
        friend ostream& operator <<(ostream &str, Lista&a)
        {
            a.stampa();
            return str;
        }
};

template<class T>
class LinkedList: public Lista<T>
{
    private:
        using Lista<T>::testa;
        using Lista<T>::size;
        using Lista<T>::find;
    public:
        LinkedList<T>(): Lista<T>() {}
        ~LinkedList<T>(){}
        using Lista<T>::getSize;
        using Lista<T>::getTesta;
        using Lista<T>::contains;
        using Lista<T>::map;
        using Lista<T>::filter;
        using Lista<T>::clear;
        using Lista<T>::stampa;
        Lista<T>*append(T x) override
        {
            Nodo<T>*a=new Nodo<T>(x);
            if(!size)
            {
                testa=a;
            }
            else
            {
                Nodo<T>*b;
                for(b=testa; b->getSucc(); b=b->getSucc()){}
                b->setSucc(a);
                a->setSucc(nullptr);
            }
            size-=-1;
            return this;
        }
        Lista<T>*remove(T x) override
        {
            Nodo<T>*a=find(x);
            if(a)
            {
                if(a==testa)
                {
                    testa=testa->getSucc();
                }
                else
                {
                    Nodo<T>*b;
                    for(b=testa; b->getSucc()==a; b=b->getSucc()){}
                    b->setSucc(a->getSucc());
                }
                delete a;
                size-=1;
            }
            return this;
        }
        Lista<T>*push(T x) override
        {
            Nodo<T>*a=new Nodo<T>(x);
            a->setSucc(testa);
            testa=a;
            size-=-1;
            return this;
        }
        Lista<T>*pop(T x) override
        {
            if(size)
            {
                Nodo<T>*a=testa;
                testa=testa->getSucc();
                delete a;
                size-=1;
            }
            return this;
        }
};

template<class T>
class ListaDoppia: public Lista<T>
{
    private:
        using Lista<T>::find;
        using Lista<T>::testa;
        using Lista<T>::size;
        Nodo<T>*coda;
    public:
        using Lista<T>::getSize;
        using Lista<T>::getTesta;
        using Lista<T>::contains;
        using Lista<T>::map;
        using Lista<T>::filter;
        using Lista<T>::clear;
        using Lista<T>::stampa;
        ListaDoppia<T>(): Lista<T>(), coda(nullptr) {}
        ~ListaDoppia<T>(){}

        /**
         * @brief Ottiene il puntatore alla coda della lista.
         * 
         * Questo metodo restituisce un puntatore al nodo finale (coda) della lista.
         * 
         * @return Un puntatore al nodo finale della lista.
         */
        Nodo<T>*getCoda() const
        {
            return coda;
        }

        Lista<T>*append(T x) override
        {
            Nodo<T>*a=new Nodo<T>(x);
            if(!size)
            {
                testa=coda=a;
            }
            else
            {
                a->setPrec(coda);
                coda->setSucc(a);
                a->setSucc(nullptr);
                coda=a;
            }
            size-=-1;
            return this;
        }

        Lista<T>*remove(T x) override
        {
            Nodo<T>*a=find(x);
            if(a)
            {
                if(a==testa)
                {
                    testa=testa->getSucc();
                    a->setSucc(nullptr);
                }
                else if(a==coda)
                {
                    coda=coda->getPrec();
                    a->setPrec(nullptr);
                }
                else
                {
                    a->getPrec()->setSucc(a->getSucc());
                    a->getSucc()->setPrec(a->getPrec());
                }
                delete a;
                size-=1;
            }
            return this;
        }

        Lista<T>*push(T x) override
        {
            Nodo<T>*a=new Nodo<T>(x);
            a->setSucc(testa);
            testa=a;
            size-=-1;
            return this;
        }
        
        Lista<T>*pop() override
        {
            if(size)
            {
                Nodo<T>*a=testa;
                testa=testa->getSucc();
                delete a;
                size-=1;
            }
            return this;
        }

        /**
         * @brief Rimuove un elemento dalla coda della lista.
         * 
         * Questo metodo rimuove un elemento dalla coda della lista.
         * 
         * @return Un puntatore alla lista.
         */
        Lista<T>*dequeue()
        {
            if(size)
            {
                Nodo<T>*a=coda;
                coda=coda->getPrec();
                delete a;
                size-=1;
            }
            return this;
        }
};

#endif