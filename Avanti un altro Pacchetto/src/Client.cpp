#include<iostream>
#include<cstdlib>
#include<cstring>
#include<libgen.h>
#include<pthread.h>
#include<csignal>
#include<cerrno>
#include "utils/SocketService.hpp"
using namespace std;

void*receiver(void*data)
{
    Client*server=(Client*)data;
    string buffer;
    size_t pos;
    while(true)
    {
        *server>>buffer;
        if((pos=buffer.find("TERMINATE"))!=string::npos)
        {
            cout<<buffer.substr(0,pos);
            break;
        }
        cout<<buffer;
        fflush(stdout);
    }
    pthread_exit(NULL);
}

void*sender(void*data)
{
    Client*server=(Client*)data;
    string buffer;
    while(true)
    {
        cin>>buffer;
        *server<<buffer;
    }
    pthread_exit(NULL);
}

int main(int argc, char**argv)
{
    if(argc!=4)
    {
        cout<<"\x1b[31musage: "<<basename(argv[0])<<" <nome> <indirizzo> <porta>\x1b[0m"<<endl;
    }
    else
    {
        Client client(argv[2],atoi(argv[3]));
        client.init();
        client<<argv[1]; //in realtà lo sta mandando al server
        pthread_t ts, tr;
        pthread_create(&ts,NULL,sender,reinterpret_cast<void*>(&client));
        pthread_detach(ts);
        pthread_create(&tr,NULL,receiver,reinterpret_cast<void*>(&client));
        pthread_join(tr,NULL);
        pthread_cancel(ts);
    }
    exit(EXIT_SUCCESS);
}