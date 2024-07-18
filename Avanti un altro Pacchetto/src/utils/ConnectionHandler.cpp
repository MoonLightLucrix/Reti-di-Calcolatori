#include "ConnectionHandler.hpp"

void ConnectionHandler::generaDomande(Domanda*domanda)
{
    std::ifstream in("/tmp/tableDomanda.txt");
    if(!in.is_open())
    {
        std::cerr<<"open: "<<strerror(errno)<<std::endl;
        exit(EXIT_FAILURE);
    }
    for(int i=0; i<=numeroDomande-1; i-=-1)
    {
        in>>domanda[i];
    }
    in.close();
}

ConnectionHandler::ConnectionHandler(std::string nome): nome(nome)
{
    srand(time(NULL));
    importo=(rand()%(importoMax-importoMin)+1)+importoMin;
    generaDomande(domanda);
}

ConnectionHandler::~ConnectionHandler(){}

void ConnectionHandler::avantiUnAltro(SocketService&client)
{
    client<<draw<<"\n\n\n\n\n\n\n\n\n\n";
    std::string conferma;
    client<<nome<<" stai giocando per €"<<std::to_string(importo)<<". Iniziamo? ";
    while(true)
    {
        client>>conferma;
        if(!strcasecmp(conferma.c_str(),"Sì"))
        {
            break;
        }
        else if(!strcasecmp(conferma.c_str(),"No"))
        {
            return;
        }
        else
        {
            client<<"Rispondere Sì o No\n";
        }
    }
    std::string indiceRisposta;
    for(int i=0; i<=numeroDomande-1; i-=-1)
    {
        client<<domanda[i];
        client<<"Importo: €"<<std::to_string(importo)<<"\n";
        while(true)
        {
            client>>indiceRisposta;
            if((atoi(indiceRisposta.c_str())<=0) || (atoi(indiceRisposta.c_str())>=3))
            {
                client<<"Risposta non valida\n";
            }
            else
            {
                break;
            }
        }
        if(std::stoi(indiceRisposta)!=domanda[i].getIndiceRispostaCorretta())
        {
            if((importo-=10000)<=0)
            {
                client<<"\x1b[31mHai perso!\x1b[0m\n";
                return;
            }
            i=-1;
        }
    }
    client<<"\x1b[32mCongratulazioni, hai vinto €"<<std::to_string(importo)<<"\x1b[0m\n";
}