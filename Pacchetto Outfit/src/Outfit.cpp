#include<iostream>
#include<fstream>
#include<sstream>
#include<cstdlib>
#include<cstring>
#include<libgen.h>
#include<signal.h>
#include<cerrno>
#include "utils/SocketService.hpp"
#include "utils/Abito.hpp"
#include "utils/Lista.hpp"
#include "utils/DatabaseManager.hpp"
#include "utils/ConnectionHandler.hpp"
using namespace std;

int main(int argc, char**argv)
{
    if(argc!=2)
    {
        cout<<"usage: "<<basename(argv[0])<<" <porta>"<<endl;
    }
    else
    {
        signal(SIGINT,[](int signal){sem_unlink("/semMutex");kill(0,SIGTERM);});
        Server server;
        if(!server.init(atoi(argv[1])))
        {
            exit(EXIT_FAILURE);
        }
        if(!server.serveForever([](Server&server){ConnectionHandler c; return c.connection(server);}))
        {
            exit(EXIT_FAILURE);
        }
    }
    exit(EXIT_SUCCESS);
}