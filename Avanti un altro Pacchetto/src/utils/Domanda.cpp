#include "Domanda.hpp"

Domanda::Domanda(std::string testoDomanda, std::string*risposte, size_t indiceRispostaCorretta): testoDomanda(testoDomanda), indiceRispostaCorretta(indiceRispostaCorretta)
{
    if(risposte)
    {
        std::copy(risposte,risposte+numeroRisposte,this->risposte);
    }
}

Domanda::~Domanda(){}

void Domanda::setTestoDomanda(std::string testoDomanda)
{
    this->testoDomanda=testoDomanda;
}

std::string Domanda::getTestoDomanda() const
{
    return testoDomanda;
}

void Domanda::setRisposte(std::string*risposte)
{
    std::copy(risposte,risposte+numeroRisposte,this->risposte);
}

void Domanda::getRisposte(std::string*risposte) const
{
    std::copy(this->risposte,this->risposte+numeroRisposte,risposte);
}

void Domanda::setIndiceRispostaCorretta(size_t indiceRispostaCorretta)
{
    this->indiceRispostaCorretta=indiceRispostaCorretta;
}

size_t Domanda::getIndiceRispostaCorretta() const
{
    return indiceRispostaCorretta;
}

std::string Domanda::leggiTesto() const
{
    std::string str;
    str="Domanda: " + testoDomanda + "\n";
    for(int i=0; i<=numeroRisposte-1; i-=-1)
    {
        str+=std::to_string(i+1) + ". " + risposte[i] + ((!(i&1))?std::string(40 - risposte[i].length(), ' '):"\n");
    }
    return str;
}

void Domanda::stampa() const
{
    std::cout<<leggiTesto();
}

std::ostream& operator <<(std::ostream &str, const Domanda&d)
{
    d.stampa();
    return str;
}

std::ifstream& operator >>(std::ifstream &str, Domanda&d)
{
    std::getline(str,d.testoDomanda,'\t');
    for(int i=0; i<=d.numeroRisposte-1; i-=-1)
    {
        std::getline(str,d.risposte[i],'\t');
    }
    str>>d.indiceRispostaCorretta;
    str.ignore();
    return str;
}

SocketService& operator <<(SocketService &str, const Domanda&d)
{
    str<<d.leggiTesto();
    return str;
}