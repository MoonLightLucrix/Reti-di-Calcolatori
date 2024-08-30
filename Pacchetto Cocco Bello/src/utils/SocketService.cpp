#include "SocketService.hpp"

int SocketService::sockaddrSettings(const char*address)
{
    if((sockfd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))==-1)
    {
        std::cerr<<"socket: "<<strerror(errno)<<std::endl;
        return -1;
    }
    bzero(reinterpret_cast<char*>(&addr),addrlen);
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=(!address)?INADDR_ANY:inet_addr(address);
    addr.sin_port=htons(porta);
    return 0;
}
        
SocketService::SocketService(in_port_t porta): porta(porta), addrlen(sizeof(struct sockaddr_in)){}

SocketService::~SocketService()
{
    if(sockfd!=-1)
    {
        close(sockfd);
        sockfd=-1;
    }
}

void SocketService::setSockfd(int sockfd)
{
    this->sockfd=sockfd;
}

int SocketService::getSockfd() const
{
    return sockfd;
}

void SocketService::setAddr(struct sockaddr_in addr)
{
    this->addr=addr;
}

struct sockaddr_in SocketService::getAddr() const
{
    return addr;
}

void SocketService::setAddrlen(socklen_t addrlen)
{
    this->addrlen=addrlen;
}

socklen_t SocketService::getAddrlen() const
{
    return addrlen;
}

bool SocketService::sockWrite(const __uint8_t&a) const
{
    return ((write(sockfd,&a,sizeof(__uint8_t)))!=-1);
}

bool SocketService::sockWrite(const __uint16_t&a) const
{
    return ((write(sockfd,&a,sizeof(__uint16_t)))!=-1);
}

bool SocketService::sockWrite(const __uint32_t&a) const
{
    return ((write(sockfd,&a,sizeof(__uint32_t)))!=-1);
}

bool SocketService::sockWrite(const __uint64_t&a) const
{
    return ((write(sockfd,&a,sizeof(__uint64_t)))!=-1);
}

bool SocketService::sockWrite(const __uint128_t&a) const
{
    return ((write(sockfd,&a,sizeof(__uint128_t)))!=-1);
}

bool SocketService::sockWrite(const __int8_t&a) const
{
    return ((write(sockfd,&a,sizeof(__int8_t)))!=-1);
}

bool SocketService::sockWrite(const __int16_t&a) const
{
    return ((write(sockfd,&a,sizeof(__int16_t)))!=-1);
}

bool SocketService::sockWrite(const __int32_t&a) const
{
    return ((write(sockfd,&a,sizeof(__int32_t)))!=-1);
}

bool SocketService::sockWrite(const __int64_t&a) const
{
    return ((write(sockfd,&a,sizeof(__int64_t)))!=-1);
}

bool SocketService::sockWrite(const __int128_t&a) const
{
    return ((write(sockfd,&a,sizeof(__int128_t)))!=-1);
}

bool SocketService::sockWrite(const bool&a) const
{
    return ((write(sockfd,&a,sizeof(bool)))!=-1);
}

bool SocketService::sockWrite(const float&a) const
{
    return ((write(sockfd,&a,sizeof(float)))!=-1);
}

bool SocketService::sockWrite(const double&a) const
{
    return ((write(sockfd,&a,sizeof(double)))!=-1);
}

bool SocketService::sockWrite(const long double&a) const
{
    return ((write(sockfd,&a,sizeof(long double)))!=-1);
}

bool SocketService::sockWrite(const std::string&a) const
{
    return ((write(sockfd,a.c_str(),strlen(a.c_str())))!=-1);
}

bool SocketService::sockWrite(const char&a) const
{
    return ((write(sockfd,&a,sizeof(char)))!=-1);
}

bool SocketService::sockWrite(const char*a) const
{
    return ((write(sockfd,a,strlen(a)))!=-1);
}

bool SocketService::sockRead(__uint8_t&a)
{
    memset(reinterpret_cast<char*>(&a),0,sizeof(__uint8_t));
    return ((bytesRead=read(sockfd,&a,sizeof(__uint8_t)))!=-1);
}

bool SocketService::sockRead(__uint16_t&a)
{
    memset(reinterpret_cast<char*>(&a),0,sizeof(__uint16_t));
    return ((bytesRead=read(sockfd,&a,sizeof(__uint16_t)))!=-1);
}

bool SocketService::sockRead(__uint32_t&a)
{
    memset(reinterpret_cast<char*>(&a),0,sizeof(__uint32_t));
    return ((bytesRead=read(sockfd,&a,sizeof(__uint32_t)))!=-1);
}

bool SocketService::sockRead(__uint64_t&a)
{
    memset(reinterpret_cast<char*>(&a),0,sizeof(__uint64_t));
    return ((bytesRead=read(sockfd,&a,sizeof(__uint64_t)))!=-1);
}

bool SocketService::sockRead(__uint128_t&a)
{
    memset(reinterpret_cast<char*>(&a),0,sizeof(__uint128_t));
    return ((bytesRead=read(sockfd,&a,sizeof(__uint128_t)))!=-1);
}

bool SocketService::sockRead(__int8_t&a)
{
    memset(reinterpret_cast<char*>(&a),0,sizeof(__int8_t));
    return ((bytesRead=read(sockfd,&a,sizeof(__int8_t)))!=-1);
}

bool SocketService::sockRead(__int16_t&a)
{
    memset(reinterpret_cast<char*>(&a),0,sizeof(__int16_t));
    return ((bytesRead=read(sockfd,&a,sizeof(__int16_t)))!=-1);
}

bool SocketService::sockRead(__int32_t&a)
{
    memset(reinterpret_cast<char*>(&a),0,sizeof(__int32_t));
    return ((bytesRead=read(sockfd,&a,sizeof(__int32_t)))!=-1);
}

bool SocketService::sockRead(__int64_t&a)
{
    memset(reinterpret_cast<char*>(&a),0,sizeof(__int64_t));
    return ((bytesRead=read(sockfd,&a,sizeof(__int64_t)))!=-1);
}

bool SocketService::sockRead(__int128_t&a)
{
    memset(reinterpret_cast<char*>(&a),0,sizeof(__int128_t));
    return ((bytesRead=read(sockfd,&a,sizeof(__int128_t)))!=-1);
}

bool SocketService::sockRead(bool&a)
{
    memset(reinterpret_cast<char*>(&a),0,sizeof(bool));
    return ((bytesRead=read(sockfd,&a,sizeof(bool)))!=-1);
}

bool SocketService::sockRead(float&a)
{
    memset(reinterpret_cast<char*>(&a),0,sizeof(float));
    return ((bytesRead=read(sockfd,&a,sizeof(float)))!=-1);
}

bool SocketService::sockRead(double&a)
{
    memset(reinterpret_cast<char*>(&a),0,sizeof(double));
    return ((bytesRead=read(sockfd,&a,sizeof(double)))!=-1);
}

bool SocketService::sockRead(long double&a)
{
    memset(reinterpret_cast<char*>(&a),0,sizeof(long double));
    return ((bytesRead=read(sockfd,&a,sizeof(long double)))!=-1);
}

bool SocketService::sockRead(std::string&a)
{
    //size_t maxSize=static_cast<size_t>(a.max_size());
    char buffer[N];
    memset(buffer,'\0',strlen(buffer));
    if((bytesRead=read(sockfd,buffer,N))!=-1)
    {
        buffer[bytesRead]='\0';
        a.assign(buffer);
    }
    return (bytesRead!=-1);
}

bool SocketService::sockRead(char&a)
{
    memset(reinterpret_cast<char*>(&a),0,sizeof(char));
    return ((bytesRead=read(sockfd,&a,sizeof(char)))!=-1);
}

bool SocketService::sockRead(char*a)
{
    memset(a,'\0',strlen(a));
    if((bytesRead=read(sockfd,a,N))!=-1)
    {
        a[bytesRead]='\0';
    }
    return (bytesRead!=-1);
}

SocketService& operator <<(SocketService &ss, const __uint8_t&a)
{
    if(!ss.sockWrite(a))
    {
        std::cerr<<"write: "<<strerror(errno)<<std::endl;
    }
    return ss;
}

SocketService& operator <<(SocketService &ss, const __uint16_t&a)
{
    if(!ss.sockWrite(a))
    {
        std::cerr<<"write: "<<strerror(errno)<<std::endl;
    }
    return ss;
}

SocketService& operator <<(SocketService &ss, const __uint32_t&a)
{
    if(!ss.sockWrite(a))
    {
        std::cerr<<"write: "<<strerror(errno)<<std::endl;
    }
    return ss;
}

SocketService& operator <<(SocketService &ss, const __uint64_t&a)
{
    if(!ss.sockWrite(a))
    {
        std::cerr<<"write: "<<strerror(errno)<<std::endl;
    }
    return ss;
}

SocketService& operator <<(SocketService &ss, const __uint128_t&a)
{
    if(!ss.sockWrite(a))
    {
        std::cerr<<"write: "<<strerror(errno)<<std::endl;
    }
    return ss;
}

SocketService& operator <<(SocketService &ss, const __int8_t&a)
{
    if(!ss.sockWrite(a))
    {
        std::cerr<<"write: "<<strerror(errno)<<std::endl;
    }
    return ss;
}

SocketService& operator <<(SocketService &ss, const __int16_t&a)
{
    if(!ss.sockWrite(a))
    {
        std::cerr<<"write: "<<strerror(errno)<<std::endl;
    }
    return ss;
}

SocketService& operator <<(SocketService &ss, const __int32_t&a)
{
    if(!ss.sockWrite(a))
    {
        std::cerr<<"write: "<<strerror(errno)<<std::endl;
    }
    return ss;
}

SocketService& operator <<(SocketService &ss, const __int64_t&a)
{
    if(!ss.sockWrite(a))
    {
        std::cerr<<"write: "<<strerror(errno)<<std::endl;
    }
    return ss;
}

SocketService& operator <<(SocketService &ss, const __int128_t&a)
{
    if(!ss.sockWrite(a))
    {
        std::cerr<<"write: "<<strerror(errno)<<std::endl;
    }
    return ss;
}

SocketService& operator <<(SocketService &ss, const bool&a)
{
    if(!ss.sockWrite(a))
    {
        std::cerr<<"write: "<<strerror(errno)<<std::endl;
    }
    return ss;
}

SocketService& operator <<(SocketService &ss, const float&a)
{
    if(!ss.sockWrite(a))
    {
        std::cerr<<"write: "<<strerror(errno)<<std::endl;
    }
    return ss;
}

SocketService& operator <<(SocketService &ss, const double&a)
{
    if(!ss.sockWrite(a))
    {
        std::cerr<<"write: "<<strerror(errno)<<std::endl;
    }
    return ss;
}

SocketService& operator <<(SocketService &ss, const long double&a)
{
    if(!ss.sockWrite(a))
    {
        std::cerr<<"write: "<<strerror(errno)<<std::endl;
    }
    return ss;
}

SocketService& operator <<(SocketService &ss, const std::string&a)
{
    if(!ss.sockWrite(a))
    {
        std::cerr<<"write: "<<strerror(errno)<<std::endl;
    }
    return ss;
}

SocketService& operator <<(SocketService &ss, const char&a)
{
    if(!ss.sockWrite(a))
    {
        std::cerr<<"write: "<<strerror(errno)<<std::endl;
    }
    return ss;
}

SocketService& operator <<(SocketService &ss,const char*a)
{
    if(!ss.sockWrite(a))
    {
        std::cerr<<"write: "<<strerror(errno)<<std::endl;
    }
    return ss;
}

SocketService& operator >>(SocketService &ss, __uint8_t&a)
{
    if(!ss.sockRead(a))
    {
        std::cerr<<"read: "<<strerror(errno)<<std::endl;
    }
    return ss;
}

SocketService& operator >>(SocketService &ss, __uint16_t&a)
{
    if(!ss.sockRead(a))
    {
        std::cerr<<"read: "<<strerror(errno)<<std::endl;
    }
    return ss;
}

SocketService& operator >>(SocketService &ss, __uint32_t&a)
{
    if(!ss.sockRead(a))
    {
        std::cerr<<"read: "<<strerror(errno)<<std::endl;
    }
    return ss;
}

SocketService& operator >>(SocketService &ss, __uint64_t&a)
{
    if(!ss.sockRead(a))
    {
        std::cerr<<"read: "<<strerror(errno)<<std::endl;
    }
    return ss;
}

SocketService& operator >>(SocketService &ss, __uint128_t&a)
{
    if(!ss.sockRead(a))
    {
        std::cerr<<"read: "<<strerror(errno)<<std::endl;
    }
    return ss;
}

SocketService& operator >>(SocketService &ss, __int8_t&a)
{
    if(!ss.sockRead(a))
    {
        std::cerr<<"read: "<<strerror(errno)<<std::endl;
    }
    return ss;
}

SocketService& operator >>(SocketService &ss, __int16_t&a)
{
    if(!ss.sockRead(a))
    {
        std::cerr<<"read: "<<strerror(errno)<<std::endl;
    }
    return ss;
}

SocketService& operator >>(SocketService &ss, __int32_t&a)
{
    if(!ss.sockRead(a))
    {
        std::cerr<<"read: "<<strerror(errno)<<std::endl;
    }
    return ss;
}

SocketService& operator >>(SocketService &ss, __int64_t&a)
{
    if(!ss.sockRead(a))
    {
        std::cerr<<"read: "<<strerror(errno)<<std::endl;
    }
    return ss;
}

SocketService& operator >>(SocketService &ss, __int128_t&a)
{
    if(!ss.sockRead(a))
    {
        std::cerr<<"read: "<<strerror(errno)<<std::endl;
    }
    return ss;
}

SocketService& operator >>(SocketService &ss, bool&a)
{
    if(!ss.sockRead(a))
    {
        std::cerr<<"read: "<<strerror(errno)<<std::endl;
    }
    return ss;
}

SocketService& operator >>(SocketService &ss, float&a)
{
    if(!ss.sockRead(a))
    {
        std::cerr<<"read: "<<strerror(errno)<<std::endl;
    }
    return ss;
}

SocketService& operator >>(SocketService &ss, double&a)
{
    if(!ss.sockRead(a))
    {
        std::cerr<<"read: "<<strerror(errno)<<std::endl;
    }
    return ss;
}

SocketService& operator >>(SocketService &ss, long double&a)
{
    if(!ss.sockRead(a))
    {
        std::cerr<<"read: "<<strerror(errno)<<std::endl;
    }
    return ss;
}

SocketService& operator >>(SocketService &ss, std::string&a)
{
    if(!ss.sockRead(a))
    {
        std::cerr<<"read: "<<strerror(errno)<<std::endl;
    }
    return ss;
}

SocketService& operator >>(SocketService &ss, char&a)
{
    if(!ss.sockRead(a))
    {
        std::cerr<<"read: "<<strerror(errno)<<std::endl;
    }
    return ss;
}

SocketService& operator >>(SocketService &ss, char*a)
{
    if(!ss.sockRead(a))
    {
        std::cerr<<"read: "<<strerror(errno)<<std::endl;
    }
    return ss;
}

int Server::serverSettings()
{
    if((bind(sockfd,reinterpret_cast<struct sockaddr*>(&addr),addrlen))==-1)
    {
        std::cerr<<"bind: "<<strerror(errno)<<std::endl;
        return -1;
    }
    listen(sockfd,backlog);
    return 0;
}

Server::Server(in_port_t porta, int backlog): SocketService(porta), backlog(backlog), isWaitingForConnection(false){}

Server::~Server(){}

bool Server::init()
{
    return init(this->porta, this->backlog);
}

bool Server::init(in_port_t porta)
{
    return init(porta, this->backlog);
}

bool Server::init(in_port_t porta, int backlog)
{
    this->porta=porta;
    this->backlog=backlog;
    if((sockaddrSettings())==-1)
    {
        return false;
    }
    if((serverSettings())==-1)
    {
        return false;
    }
    return true;
}

bool Server::serveFor(SocketService*client, size_t numClients)
{
    bool e;
    std::cout<<"Ascolto sulla porta "<<ntohs(addr.sin_port)<<"…"<<std::endl;
    for(int i=0; i<=numClients-1; i-=-1)
    {
        std::cout<<"Attendo Client numero "<<i+1<<std::endl;
        if((e=((sockfd2=accept(sockfd,reinterpret_cast<struct sockaddr*>(&addr2),&addrlen))==-1)))
        {
            std::cerr<<"accept: "<<strerror(errno)<<std::endl;
            return e;
        }
        client[i].setSockfd(sockfd2);
        client[i].setAddr(addr2);
        client[i].setAddrlen(addrlen);
    }
    return e;
}

pid_t Server::serveForever()
{
    std::cout<<"Ascolto sulla porta "<<ntohs(addr.sin_port)<<"…"<<std::endl;
    while(true)
    {
        isWaitingForConnection=true;
        if((sockfd2=accept(sockfd,reinterpret_cast<struct sockaddr*>(&addr2),&addrlen))==-1)
        {
            std::cerr<<"accept: "<<strerror(errno)<<std::endl;
            return -1;
        }
        if((pid=fork())==-1)
        {
            std::cerr<<"fork: "<<strerror(errno)<<std::endl;
            return -1;
        }
        if(!pid)
        {
            close(sockfd);
            dup(sockfd2);
            close(sockfd2);
            return pid;
        }
        close(sockfd2);
    }
    return 0;
}

bool Server::serveForever(std::function<bool(Server&)> action)
{
    std::cout<<"Ascolto sulla porta "<<ntohs(addr.sin_port)<<"…"<<std::endl;
    while(true)
    {
        isWaitingForConnection=true;
        if((sockfd2=accept(sockfd,reinterpret_cast<struct sockaddr*>(&addr2),&addrlen))==-1)
        {
            std::cerr<<"accept: "<<strerror(errno)<<std::endl;
            return false;
        }
        if((pid=fork())==-1)
        {
            std::cerr<<"fork: "<<strerror(errno)<<std::endl;
            return false;
        }
        if(!pid)
        {
            close(sockfd);
            dup(sockfd2);
            close(sockfd2);
            return action(*this);
        }
        close(sockfd2);
    }
    return true;
}

bool Server::shutdown()
{
    return (isWaitingForConnection?((kill(getppid(),SIGTERM))!=-1):false);
}

Client::Client(const char*address, in_port_t porta): address(address), SocketService(porta) {}

Client::~Client(){}

bool Client::init()
{
    return init(this->address, this->porta);
}

bool Client::init(const char*address)
{
    return init(address, this->porta);
}

bool Client::init(in_port_t porta)
{
    return init(this->address, porta);
}

bool Client::init(const char*address, in_port_t porta)
{
    this->address=address;
    this->porta=porta;
    if((sockaddrSettings(address))==-1)
    {
        return false;
    }
    if((connect(sockfd,reinterpret_cast<struct sockaddr*>(&addr),addrlen))==-1)
    {
        std::cerr<<"connect: "<<strerror(errno)<<std::endl;
        return false;
    }
    return true;
}