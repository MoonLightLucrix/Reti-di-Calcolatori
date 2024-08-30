#include "Prodotto.hpp"

namespace Prodotto
{
    Prodotto::Prodotto(ID id, std::string nome, double prezzo, Quantità quantità): id(id), nome(nome), prezzo(prezzo), quantità(quantità) {}

    Prodotto::~Prodotto(){}

    void Prodotto::setID(ID id)
    {
        this->id=id;
    }

    ID Prodotto::getID() const
    {
        return id;
    }

    void Prodotto::setNome(std::string nome)
    {
        this->nome=nome;
    }

    std::string Prodotto::getNome() const
    {
        return nome;
    }

    void Prodotto::setPrezzo(double prezzo)
    {
        this->prezzo=prezzo;
    }

    double Prodotto::getPrezzo() const
    {
        return prezzo;
    }

    void Prodotto::setQuantità(Quantità quantità)
    {
        this->quantità=quantità;
    }

    Quantità Prodotto::getQuantità() const
    {
        return quantità;
    }

    std::string Prodotto::leggiProdotto() const
    {
        std::string prezzo2=std::to_string(prezzo);
        prezzo2=prezzo2.substr(0,prezzo2.find(".")+3);
        return "ID: " + std::to_string(id) + "\tnome: " + nome + "\tprezzo: €" + prezzo2 + "\tquantità: " + std::to_string(quantità);
    }

    void Prodotto::stampa() const
    {
        std::cout<<leggiProdotto()<<std::endl;
    }

    std::istream &operator >>(std::istream &str, Prodotto&p)
    {
        str>>p.id;
        str.ignore();
        std::getline(str,p.nome,'\t');
        str>>p.prezzo;
        str.ignore();
        str>>p.quantità;
        str.ignore();
        return str;
    }

    std::ostream &operator <<(std::ostream &str, Prodotto&p)
    {
        str<<p.leggiProdotto();
        return str;
    }

    std::fstream &operator >>(std::fstream &str, Prodotto&p)
    {
        str>>p.id;
        str.ignore();
        std::getline(str,p.nome,'\t');
        str>>p.prezzo;
        str.ignore();
        str>>p.quantità;
        str.ignore();
        return str;
    }

    std::fstream &operator <<(std::fstream &str, Prodotto&p)
    {
        str<<p.getID()<<"\t"<<p.getNome()<<"\t"<<std::fixed<<std::setprecision(2)<<p.getPrezzo()<<"\t"<<p.getQuantità();
        return str;
    }

    SocketService &operator <<(SocketService &str, const Prodotto&p)
    {
        str<<p.leggiProdotto();
        return str;
    }
};