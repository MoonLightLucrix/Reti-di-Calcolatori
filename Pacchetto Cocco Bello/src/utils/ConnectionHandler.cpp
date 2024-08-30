#include "ConnectionHandler.hpp"

bool ConnectionHandler::signIn(Server&client)
{
    std::stringstream ss;
    std::string username, strUtente, dPassword;
    client<<"Inserisci Username: ";
    client>>username;
    bool e;
    if((e=(!(strUtente=dbUtente.find(username)).empty())))
    {
        ss.str(strUtente);
        ss>>utente;
        client<<"Inserisci Password: ";
        client>>dPassword;
        if((e=utente.compare(dPassword)))
        {
            return e;
        }
        else
        {
            client<<"\nPassword Errata!\n";
        }
    }
    else
    {
        client<<"Username non trovato!\n";
    }
    return e;
}

void ConnectionHandler::listaProdotti(Server&client)
{
    Prodotto::Prodotto prodotto;
    std::stringstream ss;
    std::string strProdotto;
    client<<"Lista prodotti:\n";
    while(!(strProdotto=dbProdotto.nextLine()).empty())
    {
        ss.str(strProdotto);
        ss>>prodotto;
        client<<prodotto<<'\n';
        ss.clear();
    }
    client<<'\n';
}

bool ConnectionHandler::acquista(Server&client)
{
    Prodotto::Prodotto prodotto;
    std::stringstream ss;
    std::string strProdotto, strPrezzo, selezione, strCostoTotale;
    Prodotto::ID id=0;
    Prodotto::Quantità quantità=0;
    bool e=true;
    while(true)
    {
        client<<"Inserisci l'ID e la quantità del prodotto da acquistare come \"ID Quantità\" separati da uno spazio (q - per uscire): ";
        client>>selezione;
        if(selezione=="q")
        {
            break;
        }
        else if(selezione=="\n")
        {
            continue;
        }
        ss.str(selezione);
        ss>>id;
        ss>>quantità;
        if((e=(!(strProdotto=dbProdotto.find(id)).empty())))
        {
            ss.clear();
            ss.str(strProdotto);
            ss>>prodotto;
            if((e=(prodotto.getQuantità()>=quantità)))
            {
                prodotto.setQuantità(prodotto.getQuantità()-quantità);
                strPrezzo=std::to_string(prodotto.getPrezzo());
                strPrezzo=strPrezzo.substr(0,strPrezzo.find(".")+3);
                if((e=dbProdotto.deleteOrEditLine(strProdotto,std::to_string(prodotto.getID()) + "\t" + prodotto.getNome() + "\t" + strPrezzo + "\t" + std::to_string(prodotto.getQuantità()))))
                {
                    strCostoTotale=std::to_string(prodotto.getPrezzo()*quantità);
                    client<<"Acquisto effettuato da "<<utente.getUsername()<<" del prodotto \""<<prodotto.getNome()<<"\" effettuato con successo, costo totale: €"<<strCostoTotale.substr(0,strCostoTotale.find(".")+3)<<'\n';
                }
                else
                {
                    client<<"Errore durante l'acquisto\n";
                }
                break;
            }
            else
            {
                client<<"Quantità insufficiente\n";
            }
        }
        else
        {
            client<<"Prodotto non trovato\n";
        }
    }
    return e;
}

ConnectionHandler::ConnectionHandler()
{
    if(!dbProdotto.openSemaphore(semNameProdotto))
    {
        exit(EXIT_FAILURE);
    }
    if(!dbProdotto.openFile(filenameProdotto))
    {
        exit(EXIT_FAILURE);
    }
    if(!dbUtente.openSemaphore(semNameUtente))
    {
        exit(EXIT_FAILURE);
    }
    if(!dbUtente.openFile(filenameUtente))
    {
        exit(EXIT_FAILURE);
    }
}

ConnectionHandler::~ConnectionHandler(){}

bool ConnectionHandler::connection(Server&client)
{
    if(!signIn(client))
    {
        client<<"TERMINATE";
        return false;
    }
    client<<'\n'<<titolo<<"\n";
    bool e=true;
    std::string selezione;
    do{
        client<<menù;
        client<<"Inserisci un comando: ";
        client>>selezione;
        if(selezione=="l")
        {
            listaProdotti(client);
        }
        else if(selezione=="a")
        {
            e=acquista(client);
        }
        else if(selezione=="q")
        {
            client<<"Arrivederci!\n";
            break;
        }
        else if(selezione=="\n")
        {
            continue;
        }
        else
        {
            client<<"Comando sconosciuto\n";
        }
    }while(e);
    client<<"TERMINATE";
    return e;
}