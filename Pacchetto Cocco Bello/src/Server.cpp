#include<iostream>
#include<cstdlib>
#include<cstring>
#include<csignal>
#include<cerrno>
#include "utils/SocketService.hpp"
#include "utils/ConnectionHandler.hpp"
using namespace std;

int main(int argc, char**argv)
{
    signal(SIGINT,[](int signal){sem_unlink("/semMutexProdotto");sem_unlink("/semMutexUtente");kill(0,SIGTERM);});
    Server server;
    if(argc==2)
    {
        if(!server.init(atoi(argv[1])))
        {
            exit(EXIT_FAILURE);
        }
    }
    else if(argc==3)
    {
        if(!server.init(atoi(argv[1]),atoi(argv[2])))
        {
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        if(!server.init())
        {
            exit(EXIT_FAILURE);
        }
    }
    if(!server.serveForever([](Server&server){ConnectionHandler c; return c.connection(server);}))
    {
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}