#include<iostream>
#include<cstdlib>
#include<cstring>
#include<libgen.h>
#include<limits>
#include<termios.h>
#include<pthread.h>
#include<csignal>
#include<cerrno>
#include "utils/SocketService.hpp"
#include "utils/Utente.hpp"
using namespace std;

void disableEcho()
{
    struct termios tty;
    tcgetattr(0,&tty);
    tty.c_lflag&=~ECHO;
    tcsetattr(0,TCSANOW,&tty);
}

void enableEcho()
{
    static bool isEnabled=false;
    if(!isEnabled)
    {
        struct termios tty;
        tcgetattr(0,&tty);
        tty.c_lflag|=ECHO;
        tcsetattr(0,TCSANOW,&tty);
        isEnabled=true;
    }
}

void signIn(Client*server)
{
    Utente utente;
    string username, password;
    getline(cin,username);
    utente.setUsername(username);
    *server<<utente.getUsername();
    //std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    disableEcho();
    getline(cin,password);
    enableEcho();
    utente.setDPassword(password);
    *server<<utente.getDPassword();
}

void*receiver(void*data)
{
    Client*server=reinterpret_cast<Client*>(data);
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
    Client*server=reinterpret_cast<Client*>(data);
    signIn(server);
    string buffer;
    while(true)
    {
        getline(cin,buffer);
        if(buffer.empty())
        {
            buffer="\n";
        }
        *server<<buffer;
    }
    pthread_exit(NULL);
}

int main(int argc, char**argv)
{
    if(argc!=3)
    {
        cout<<"\x1b[31musage: "<<basename(argv[0])<<" <indirizzo> <porta>\x1b[0m"<<endl;
    }
    else
    {
        signal(SIGINT,[](int signal){enableEcho(); exit(EXIT_SUCCESS);});
        Client client(argv[1],atoi(argv[2]));
        if(!client.init())
        {
            exit(EXIT_FAILURE);
        }
        pthread_t ts, tr;
        pthread_create(&ts,NULL,sender,reinterpret_cast<void*>(&client));
        pthread_detach(ts);
        pthread_create(&tr,NULL,receiver,reinterpret_cast<void*>(&client));
        pthread_join(tr,NULL);
        pthread_cancel(ts);
        enableEcho();
    }
    exit(EXIT_SUCCESS);
}
