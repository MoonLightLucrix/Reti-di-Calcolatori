#include<iostream>
#include<cstdlib>
#include<cstring>
#include<libgen.h>
#include<csignal>
#include<cerrno>
#include "utils/SocketService.hpp"
using namespace std;

sig_atomic_t running=1;

/**
 * @brief Funzione del thread del ricevitore.
 * 
 * Questa funzione è destinata ad essere eseguita come un thread separato.
 * Continuamente riceve dati dal client e li stampa sullo standard output.
 * 
 * @param data Un puntatore al client da cui ricevere i dati.
 * @return `NULL`.
 */
void*receiver(void*data)
{
    Client client=*((Client*)data);
    string buffer;
    while(true)
    {
        client>>buffer;
        cout<<buffer;
        fflush(stdout);
    }
    pthread_exit(NULL);
}

/**
 * @brief Funzione del thread del mittente.
 * 
 * Questa funzione è destinata ad essere eseguita come un thread separato.
 * Continuamente legge i dati dallo standard input e li invia al client.
 * 
 * @param data Un puntatore al client a cui inviare i dati.
 * @return `NULL`.
 */
void*sender(void*data)
{
    Client client=*((Client*)data);
    string buffer;
    while(true)
    {
        if(running)
        {
            cin>>buffer;
        }
        client<<((running)?(buffer):(buffer="FINE"));
        if(buffer=="FINE")
        {
            break;
        }
    }
    pthread_exit(NULL);
}

int main(int argc, char**argv)
{
    if(argc!=3)
    {
        cout<<"usage: "<<basename(argv[0])<<" <address> <porta>"<<endl;
    }
    else
    {
        signal(SIGINT,[](int signal){running=0;});
        pthread_t thSender, thReceiver;
        Client client(argv[1],atoi(argv[2]));
        if(!client.init())
        {
            exit(EXIT_FAILURE);
        }
        pthread_create(&thSender,NULL,sender,(void*)&client);
        pthread_create(&thReceiver,NULL,receiver,(void*)&client);
        pthread_detach(thReceiver);
        pthread_join(thSender,NULL);
        pthread_cancel(thReceiver);
    }
    exit(EXIT_SUCCESS);
}