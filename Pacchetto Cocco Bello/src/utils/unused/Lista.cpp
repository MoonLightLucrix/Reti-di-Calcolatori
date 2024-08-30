#include "Lista.hpp"

template<class T>
Nodo<T>::Nodo(T info, Nodo<T>*prec, Nodo<T>*succ): info(info), prec(prec), succ(succ) {}

template<class T>
Nodo<T>::~Nodo(){}

template<class T>
void Nodo<T>::setPrec(Nodo<T>*prec)
{
    this->prec=prec;
}

template<class T>
Nodo<T>* Nodo<T>::getPrec() const
{
    return prec;
}

template<class T>
void Nodo<T>::setSucc(Nodo<T>*succ)
{
    this->succ=succ;
}

template<class T>
Nodo<T>* Nodo<T>::getSucc() const
{
    return succ;
}

template<class T>
void Nodo<T>::setInfo(T info)
{
    this->info=info;
}

template<class T>
T Nodo<T>::getInfo() const
{
    return info;
}

template<class T>
Iterator<T>::Iterator(Nodo<T>*a): a(a) {}

template<class T>
Iterator<T>::~Iterator(){}

template<class T>
Iterator<T>& Iterator<T>::operator++()
{
    a=a->getSucc();
    return *this;
}

template<class T>
T Iterator<T>::operator*()
{
    return a->getInfo();
}

template<class T>
bool Iterator<T>::operator!=(const Iterator<T>&b)
{
    return (a!=b.a);
}

template<class T>
Lista<T>::Lista(): testa(nullptr), s(0) {}

template<class T>
Lista<T>::~Lista()
{
    clear();
}

template<class T>
template<class U=T>
typename std::enable_if<!std::is_pointer<U>::value, Nodo<T>* >::type
Lista<T>::find(T x) const
{
    Nodo<T>*a;
    for(a=testa; a; a=a->getSucc())
    {
        if(a->getInfo()==x)
        {
            break;
        }
    }
    return a;
}

template<class T>
template<class U=T>
typename std::enable_if<std::is_pointer<U>::value, Nodo<T>* >::type
Lista<T>::find(T x) const
{
    Nodo<T>*a;
    for(a=testa; a; a=a->getSucc())
    {
        if(*a->getInfo()==x)
        {
            break;
        }
    }
    return a;
}

template<class T>
Iterator<T> Lista<T>::begin() const
{
    return Iterator<T>(testa);
}

template<class T>
Iterator<T> Lista<T>::end() const
{
    return Iterator<T>();
}

template<class T>
Lista<T>* Lista<T>::clear()
{
    Nodo<T>*a;
    while(testa)
    {
        a=testa;
        testa=testa->getSucc();
        delete a;
        s-=1;
    }
    return this;
}

template<class T>
size_t Lista<T>::getSize() const
{
    return s;
}

template<class T>
template<class U=T>
typename std::enable_if<!std::is_pointer<U>::value, Lista<T>* >::type
Lista<T>::map(std::function<T(T)> lambda)
{
    for(Nodo<T>*a=testa; a; a=a->getSucc())
    {
        a->setInfo(lambda(a->getInfo()));
    }
    return this;
}

template<class T>
template<class U=T>
typename std::enable_if<std::is_pointer<U>::value, Lista<T>* >::type
Lista<T>::map(std::function<T(T)> lambda)
{
    for(Nodo<T>*a=testa; a; a=a->getSucc())
    {
        a->setInfo(lambda(*a->getInfo()));
    }
    return this;
}

template<class T>
template<class U=T>
typename std::enable_if<!std::is_pointer<U>::value, Lista<T>* >::type
Lista<T>::filter(std::function<bool(T)> predicate)
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

template<class T>
template<class U=T>
typename std::enable_if<std::is_pointer<U>::value, Lista<T>* >::type
Lista<T>::filter(std::function<bool(T)> predicate)
{
    Nodo<T>*a=testa;
    while(a) 
    {
        if(predicate(*a->getInfo())) 
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

template<class T>
template<class U>
template<class V=T>
typename std::enable_if<!std::is_pointer<V>::value, U>::value
Lista<T>::reduce(std::function<U(T, U)> lambda)
{
    U accumulator=U();
    Nodo<T>*a;
    for(a=testa; a; a=a->getSucc())
    {
        accumulator=lambda(a->getInfo(),accumulator);
    }
    return accumulator;
}

template<class T>
template<class U>
template<class V=T>
typename std::enable_if<std::is_pointer<V>::value, U>::value
Lista<T>::reduce(std::function<U(T, U)> lambda)
{
    U accumulator=U();
    Nodo<T>*a;
    for(a=testa; a; a=a->getSucc())
    {
        accumulator=lambda(*a->getInfo(),accumulator);
    }
    return accumulator;
}

template<class T>
bool Lista<T>::contains(T x) const
{
    return (find(x));
}

template<class T>
template<class U=T>
typename std::enable_if<!std::is_pointer<U>::value, void>::type
Lista<T>::stampa() const
{
    Nodo<T>*a;
    std::cout<<"[";
    for(a=testa; a; a=a->getSucc())
    {
        std::cout<<a->getInfo()<<((a->getSucc())?", ":"");
    }
    std::cout<<"]";
}

template<class T>
template<class U=T>
typename std::enable_if<std::is_pointer<U>::value, void>::type
Lista<T>::stampa() const
{
    Nodo<T>*a;
    std::cout<<"[";
    for(a=testa; a; a=a->getSucc())
    {
        std::cout<<*a->getInfo()<<((a->getSucc())?", ":"");
    }
    std::cout<<"]";
}

template<class T>
std::ostream& operator <<(std::ostream &str, const Lista<T>&a)
{
    a.stampa();
    return str;
}

template<class T>
LinkedList<T>::LinkedList(): Lista<T>() {}

template<class T>
LinkedList<T>::~LinkedList(){}

template<class T>
Lista<T>* LinkedList<T>::append(T x)
{
    Nodo<T>*a=new Nodo<T>(x);
    if(!s)
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
    s-=-1;
    return this;
}

template<class T>
Lista<T>* LinkedList<T>::remove(T x)
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
        s-=1;
    }
    return this;
}

template<class T>
ListaDoppia<T>::ListaDoppia(): Lista<T>(), coda(nullptr) {}

template<class T>
ListaDoppia<T>::~ListaDoppia(){}

template<class T>
Lista<T>* ListaDoppia<T>::append(T x)
{
    Nodo<T>*a=new Nodo<T>(x);
    if(!s)
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
    s-=-1;
    return this;
}

template<class T>
Lista<T>* ListaDoppia<T>::remove(T x)
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
        s-=1;
    }
    return this;
}

template<class T>
OrderedList<T>::OrderedList(): Lista<T>(), coda(nullptr) {}

template<class T>
OrderedList<T>::~OrderedList(){}

template<class T>
template<class U=T>
typename std::enable_if<!std::is_pointer<U>::value, Lista<T>* >::type
OrderedList<T>::append(T x)
{
    Nodo<T>*a=new Nodo<T>(x);
    if(!s)
    {
        testa=coda=a;
    }
    else
    {
        if(x<=testa->getInfo())
        {
            a->setSucc(testa);
            testa->setPrec(a);
            a->setPrec(nullptr);
            testa=a;
        }
        else if(coda->getInfo()<=x)
        {
            a->setPrec(coda);
            coda->setSucc(a);
            a->setSucc(nullptr);
            coda=a;
        }
        else
        {
            for(Nodo<T>*b=testa; b->getSucc(); b=b->getSucc())
            {
                if(x<=b->getSucc()->getInfo())
                {
                    a->setSucc(b->getSucc());
                    a->setPrec(b);
                    b->getSucc()->setPrec(a);
                    b->setSucc(a);
                    break;
                }
            }
        }
    }
    s-=-1;
    return this;
}

template<class T>
template<class U=T>
typename std::enable_if<std::is_pointer<U>::value, Lista<T>* >::type
OrderedList<T>::append(T x)
{
    Nodo<T>*a=new Nodo<T>(x);
    if(!s)
    {
        testa=coda=a;
    }
    else
    {
        if(*x<=*testa->getInfo())
        {
            a->setSucc(testa);
            testa->setPrec(a);
            a->setPrec(nullptr);
            testa=a;
        }
        else if(*coda->getInfo()<=*x)
        {
            a->setPrec(coda);
            coda->setSucc(a);
            a->setSucc(nullptr);
            coda=a;
        }
        else
        {
            for(Nodo<T>*b=testa; b->getSucc(); b=b->getSucc())
            {
                if(*x<=*b->getSucc()->getInfo())
                {
                    a->setSucc(b->getSucc());
                    a->setPrec(b);
                    b->getSucc()->setPrec(a);
                    b->setSucc(a);
                    break;
                }
            }
        }
    }
    s-=-1;
    return this;
}

template<class T>
Lista<T>* OrderedList<T>::remove(T x)
{
    Nodo<T>*a=find(x);
    if(a)
    {
        if(a==testa)
        {
            testa=testa->getSucc();
            testa->setPrec(nullptr);
        }
        else if(a==coda)
        {
            coda=coda->getPrec();
            coda->setSucc(nullptr);
        }
        else
        {
            a->getPrec()->setSucc(a->getSucc());
            a->getSucc()->setPrec(a->getPrec());
        }
        delete a;
        s-=1;
    }
    return this;
}