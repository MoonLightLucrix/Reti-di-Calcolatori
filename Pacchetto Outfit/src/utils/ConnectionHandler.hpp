#ifndef CONNECTIONHANDLER
#define CONNECTIONHANDLER

using namespace std;

class ConnectionHandler
{
    private:
        Abito abito;
        DatabaseManager db;
        const string filename="/tmp/tableAbito.txt";
        const string draw=" ____   __    ___  ___  _  _  ____  ____  ____  __  \n(  _ \\ / _\\  / __)/ __)/ )( \\(  __)(_  _)(_  _)/  \\ \n ) __//    \\( (__( (__ ) __ ( ) _)   )(    )( (  O )\n(__)  \\_/\\_/ \\___)\\___)\\_)(_/(____) (__)  (__) \\__/ \n  __   _  _  ____  ____  __  ____                   \n /  \\ / )( \\(_  _)(  __)(  )(_  _)                  \n(  O )) \\/ (  )(   ) _)  )(   )(                    \n \\__/ \\____/ (__) (__)  (__) (__)                   \n";
        const string menu="\n\n\n\n\n\n\n\n\n\n+---------------------------+\n| l - lista abiti           |\n| a - acquista abiti        |\n| r - reso                  |\n| FINE - chiudi connessione |\n+---------------------------+\n\n\n\n\n\n\n\n";

        /**
         * @brief Invia la lista di abiti al client.
         * 
         * Questo metodo legge tutte le righe dal database, una alla volta, 
         * e le invia al client. Ogni riga del database rappresenta un abito.
         * 
         * @param server Stream col quale il server comunica col client a cui invia la lista di abiti.
         */
        void lista(Server&server)
        {
            string line;
            stringstream ss;
            while((line=db.nextLine())!="")
            {
                ss.str(line);
                ss>>abito;
                server<<abito<<"\n";
                ss.clear();
            }
        }

        /**
         * @brief Acquista abiti.
         * 
         * Questo metodo permette all'utente di acquistare abiti. 
         * L'utente può inserire l'ID dell'abito e la quantità che vuole acquistare.
         * Gli abiti selezionati vengono aggiunti al carrello dell'utente.
         * Alla fine, l'utente può confermare l'acquisto e il totale viene calcolato e mostrato.
         * 
         * @param server Stream col quale il server comunica col client.
         * @return `true` se l'acquisto è andato a buon fine, `false` altrimenti.
         */
        bool acquista(Server&server)
        {
            string buffer;
            __uint16_t id;
            __uint32_t quantità;
            double costoTotale=0;
            stringstream ss;
            string line;
            ListaDoppia<Abito> carrello;
            bool isInList;
            while(true)
            {
                server<<"Inserisci l'ID dell'abito da acquistare (\"q\" per terminare): ";
                server>>buffer;
                if(buffer=="q")
                {
                    break;
                }
                id=stoi(buffer);
                if((line=db.find(id))=="")
                {
                    server<<"\""<<to_string(id)<<"\""<<" ID non trovato.\n";
                    continue;
                }
                ss.str(line);
                ss>>abito;
                ss.clear();
                server<<"Abito selezionato:\n"<<abito<<"\n";
                server<<"Inserisci quantità: ";
                server>>buffer;
                quantità=stoi(buffer);
                for(Abito i:carrello)
                {
                    if((isInList=(i==abito)))
                    {
                        if((i.getQuantità()+quantità)<=abito.getQuantità())
                        {
                            i.setQuantità(i.getQuantità()+quantità);
                            i.setPrezzo(abito.getPrezzo()*i.getQuantità());
                        }
                        else
                        {
                            server<<"Quantità non disponibile\n";
                        }
                        break;
                    }
                }
                if(!isInList)
                {
                    if(quantità<=abito.getQuantità())
                    {
                        carrello.append(Abito(abito.getId(),abito.getNome(),abito.getTaglia(),quantità,abito.getPrezzo()*quantità));
                    }
                    else
                    {
                        server<<"Quantità non disponibile\n";
                    }
                }
            }
            server<<"Carrello:\n";
            for(Abito i:carrello)
            {
                server<<i<<"\n";
                costoTotale-=-i.getPrezzo();
            }
            string costoTotaleStr=to_string(costoTotale);
            costoTotaleStr=costoTotaleStr.substr(0,costoTotaleStr.find(".")+3);
            server<<"Costo totale: €"<<costoTotaleStr<<"\n";
            while(true)
            {
                server<<"Sei sicuro di voler confermare l'operazione? ";
                server>>buffer;
                if(!strcasecmp(buffer.c_str(),"si"))
                {
                    for(Abito i:carrello)
                    {
                        line=db.find(i.getId());
                        ss.str(line);
                        ss>>abito;
                        if(i.getQuantità()<=abito.getQuantità())
                        {
                            abito.setQuantità(abito.getQuantità()-i.getQuantità());
                            if(!db.deleteOrEditLine(line,&abito))
                            {
                                server<<"Errore durante l'acquisto\n";
                                return false;
                            }
                        }
                        else
                        {
                            server<<i<<"\nQuantità insufficiente all'acquisto!\n";
                        }
                        ss.clear();
                        buffer="Operazione effettuata\n";
                    }
                }
                else if(!strcasecmp(buffer.c_str(),"no"))
                {
                    buffer="Operazione annullata\n";
                }
                else
                {
                    server<<"Rispondi con \"Si\" o \"No\"\n";
                    continue;
                }
                server<<buffer;
                break;
            }
            return true;
        }

        /**
         * @brief Restituisci abiti.
         * 
         * Questo metodo permette all'utente di restituire abiti. 
         * L'utente può inserire l'ID dell'abito e la quantità che vuole restituire.
         * Gli abiti selezionati vengono aggiunti al carrello dell'utente.
         * Alla fine, l'utente può confermare il reso e il totale viene calcolato e mostrato.
         * 
         * @param server Stream col quale il server comunica col client.
         * @return `true` se il reso è andato a buon fine, `false` altrimenti.
         */
        bool reso(Server&server)
        {
            string buffer;
            __uint16_t id;
            __uint32_t quantità;
            double costoTotale=0;
            stringstream ss;
            string line;
            ListaDoppia<Abito> carrello;
            bool isInList;
            while(true)
            {
                server<<"Inserisci l'ID dell'abito da cui fare il reso (\"q\" per terminare): ";
                server>>buffer;
                if(buffer=="q")
                {
                    break;
                }
                id=stoi(buffer);
                if((line=db.find(id))=="")
                {
                    server<<"\""<<to_string(id)<<"\""<<" ID non trovato.\n";
                    continue;
                }
                ss.str(line);
                ss>>abito;
                ss.clear();
                server<<"Abito selezionato:\n"<<abito<<"\n";
                server<<"Inserisci quantità da restituire: ";
                server>>buffer;
                quantità=stoi(buffer);
                for(Abito i:carrello)
                {
                    if((isInList=(i==abito)))
                    {
                        i.setQuantità(i.getQuantità()+quantità);
                        i.setPrezzo(abito.getPrezzo()*i.getQuantità());
                    }
                }
                if(!isInList)
                {
                    carrello.append(Abito(abito.getId(),abito.getNome(),abito.getTaglia(),quantità,abito.getPrezzo()*quantità));
                }
            }
            server<<"Carrello:\n";
            for(Abito i:carrello)
            {
                server<<i<<"\n";
                costoTotale-=-i.getPrezzo();
            }
            string costoTotaleStr=to_string(costoTotale);
            costoTotaleStr=costoTotaleStr.substr(0,costoTotaleStr.find(".")+3);
            server<<"Costo totale: €"<<costoTotaleStr<<"\n";
            while(true)
            {
                server<<"Sei sicuro di voler confermare l'operazione? ";
                server>>buffer;
                if(!strcasecmp(buffer.c_str(),"si"))
                {
                    for(Abito i:carrello)
                    {
                        line=db.find(i.getId());
                        ss.str(line);
                        ss>>abito;
                        abito.setQuantità(abito.getQuantità()+i.getQuantità());
                        if(!db.deleteOrEditLine(line,&abito))
                        {
                            server<<"Errore durante il reso\n";
                            return false;
                        }
                        ss.clear();
                        buffer="Reso effettuato\n";
                    }
                }
                else if(!strcasecmp(buffer.c_str(),"no"))
                {
                    buffer="Reso annullato\n";
                }
                else
                {
                    server<<"Rispondi con \"Si\" o \"No\"\n";
                    continue;
                }
                server<<buffer;
                break;
            }
            return true;
        }
    public:

        /**
         * @brief Costruttore per la classe ConnectionHandler.
         * 
         * Apre il file `filename`.
         */
        ConnectionHandler()
        {
            db.openFile(filename);
        }

        /**
         * @brief Distruttore per la classe ConnectionHandler.
         * 
         * Chiude il file `filename`.
         */
        ~ConnectionHandler(){}

        /**
         * @brief Connessione con il client.
         * 
         * Questo metodo permette di comunicare con il client.
         * Il client può selezionare un comando tra:
         * - `l` per visualizzare la lista di abiti;
         * - `a` per acquistare abiti;
         * - `r` per restituire abiti;
         * - `FINE` per chiudere la connessione.
         * 
         * @param server Stream col quale il server comunica col client.
         * @return `true` se la connessione è andata a buon fine, `false` altrimenti.
         */
        bool connection(Server&server)
        {
            server<<draw;
            string selezione;
            bool e=true;
            while(true)
            {
                server<<menu;
                server<<"Seleziona un comando: ";
                server>>selezione;
                if(selezione=="l")
                {
                    lista(server);
                }
                else if(selezione=="a")
                {
                    e=acquista(server);
                }
                else if(selezione=="r")
                {
                    e=reso(server);
                }
                else if(selezione=="FINE")
                {
                    server<<"Arrivederci\n";
                    break;
                }
                else if(selezione[0]=='\n')
                {
                    continue;
                }
                else
                {
                    server<<"\""<<selezione<<"\""<<": comando non valido\n";
                }
                if(!e)
                {
                    break;
                }
            }
            return e;
        }
};

#endif