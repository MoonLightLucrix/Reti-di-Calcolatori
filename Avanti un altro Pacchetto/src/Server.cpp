#include<iostream>
#include<cstdlib>
#include<cstring>
#include<csignal>
#include<algorithm>
#include "utils/SocketService.hpp"
#include "utils/ConnectionHandler.hpp"
using namespace std;

int main(int argc, char**argv)
{
    Server server;
    bool e;
    e=(argc==2)?server.init(atoi(argv[1])):server.init();
    if(!e)
    {
        exit(EXIT_FAILURE);
    }
    const size_t numeroPartecipanti=1;
    SocketService aClient[numeroPartecipanti];
    server.serveFor(aClient,numeroPartecipanti);
    string nome;
    for(SocketService&client: aClient)
    {
        client>>nome;
        ConnectionHandler c(nome);
        c.avantiUnAltro(client);
        client<<"TERMINATE";
    }
    exit(EXIT_SUCCESS);
}
