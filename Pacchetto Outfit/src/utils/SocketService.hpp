#ifndef SOCKETSERVICE
#define SOCKETSERVICE

#include<functional>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<pthread.h>
#include<unistd.h>
using namespace std;

class SocketService
{
    protected:
        int sockfd;
        struct sockaddr_in addr;
        socklen_t addrlen;
        in_port_t porta;
        const size_t N=1<<12;
        ssize_t bytesRead;

        /**
         * @brief Imposta le impostazioni del socket.
         * 
         * Questo metodo crea un nuovo socket e imposta le sue impostazioni di indirizzo.
         * Se viene fornito un indirizzo, viene utilizzato. Altrimenti, viene utilizzato INADDR_ANY.
         * Se la creazione del socket fallisce, viene stampato un messaggio di errore e restituito -1.
         * 
         * @param address L'indirizzo IP da utilizzare per il socket. Default è 0, che significa INADDR_ANY.
         * @return 0 se l'impostazione del socket è andata a buon fine, -1 altrimenti.
         */
        int sockaddrSettings(const char*address=0)
        {
            if((sockfd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))==-1)
            {
                cerr<<"socket: "<<strerror(errno)<<endl;
                return -1;
            }
            bzero(reinterpret_cast<char*>(&addr),addrlen);
            addr.sin_family=AF_INET;
            addr.sin_addr.s_addr=(!address)?INADDR_ANY:inet_addr(address);
            addr.sin_port=htons(porta);
            return 0;
        }
    public:

        /**
         * @brief Costruttore per la classe SocketService.
         * 
         * Questo costruttore inizializza un oggetto SocketService con la porta specificata.
         * 
         * @param porta La porta da utilizzare per il socket.
         */
        SocketService(in_port_t porta): porta(porta), addrlen(sizeof(struct sockaddr_in)){}

        /**
         * @brief Distruttore per la classe SocketService.
         * 
         * Questo distruttore chiude il socket.
         */
        ~SocketService()
        {
            close(sockfd);
        }

        /**
         * @brief Scrive un intero a 8 bit sul socket.
         * 
         * Questo metodo scrive un intero a 8 bit sul socket.
         * 
         * @param a Il byte da scrivere sul socket.
         * @return `true` se la scrittura è andata a buon fine, `false` altrimenti.
         */
        virtual bool sockWrite(const __uint8_t&a) const
        {
            return ((write(sockfd,&a,sizeof(__uint8_t)))!=-1);
        }

        /**
         * @brief Scrive un intero a 16 bit sul socket.
         * 
         * Questo metodo scrive un intero a 16 bit sul socket.
         * 
         * @param a L'intero a 16 bit da scrivere sul socket.
         * @return `true` se la scrittura è andata a buon fine, `false` altrimenti.
         */
        virtual bool sockWrite(const __uint16_t&a) const
        {
            return ((write(sockfd,&a,sizeof(__uint16_t)))!=-1);
        }

        /**
         * @brief Scrive un intero a 32 bit sul socket.
         * 
         * Questo metodo scrive un intero a 32 bit sul socket.
         * 
         * @param a L'intero a 32 bit da scrivere sul socket.
         * @return `true` se la scrittura è andata a buon fine, `false` altrimenti.
         */
        virtual bool sockWrite(const __uint32_t&a) const
        {
            return ((write(sockfd,&a,sizeof(__uint32_t)))!=-1);
        }

        /**
         * @brief Scrive un intero a 64 bit sul socket.
         * 
         * Questo metodo scrive un intero a 64 bit sul socket.
         * 
         * @param a L'intero a 64 bit da scrivere sul socket.
         * @return `true` se la scrittura è andata a buon fine, `false` altrimenti.
         */
        virtual bool sockWrite(const __uint64_t&a) const
        {
            return ((write(sockfd,&a,sizeof(__uint64_t)))!=-1);
        }

        /**
         * @brief Scrive un intero a 128 bit sul socket.
         * 
         * Questo metodo scrive un intero a 128 bit sul socket.
         * 
         * @param a L'intero a 128 bit da scrivere sul socket.
         * @return `true` se la scrittura è andata a buon fine, `false` altrimenti.
         */
        virtual bool sockWrite(const __uint128_t&a) const
        {
            return ((write(sockfd,&a,sizeof(__uint128_t)))!=-1);
        }

        /**
         * @brief Scrive un intero a 8 bit con segno sul socket.
         * 
         * Questo metodo scrive un intero a 8 bit con segno sul socket.
         * 
         * @param a Il byte con segno da scrivere sul socket.
         * @return `true` se la scrittura è andata a buon fine, `false` altrimenti.
         */
        virtual bool sockWrite(const __int8_t&a) const
        {
            return ((write(sockfd,&a,sizeof(__int8_t)))!=-1);
        }

        /**
         * @brief Scrive un intero a 16 bit con segno sul socket.
         * 
         * Questo metodo scrive un intero a 16 bit con segno sul socket.
         * 
         * @param a L'intero a 16 bit con segno da scrivere sul socket.
         * @return `true` se la scrittura è andata a buon fine, `false` altrimenti.
         */
        virtual bool sockWrite(const __int16_t&a) const
        {
            return ((write(sockfd,&a,sizeof(__int16_t)))!=-1);
        }

        /**
         * @brief Scrive un intero a 32 bit con segno sul socket.
         * 
         * Questo metodo scrive un intero a 32 bit con segno sul socket.
         * 
         * @param a L'intero a 32 bit con segno da scrivere sul socket.
         * @return `true` se la scrittura è andata a buon fine, `false` altrimenti.
         */
        virtual bool sockWrite(const __int32_t&a) const
        {
            return ((write(sockfd,&a,sizeof(__int32_t)))!=-1);
        }

        /**
         * @brief Scrive un intero a 64 bit con segno sul socket.
         * 
         * Questo metodo scrive un intero a 64 bit con segno sul socket.
         * 
         * @param a L'intero a 64 bit con segno da scrivere sul socket.
         * @return `true` se la scrittura è andata a buon fine, `false` altrimenti.
         */
        virtual bool sockWrite(const __int64_t&a) const
        {
            return ((write(sockfd,&a,sizeof(__int64_t)))!=-1);
        }

        /**
         * @brief Scrive un intero a 128 bit con segno sul socket.
         * 
         * Questo metodo scrive un intero a 128 bit con segno sul socket.
         * 
         * @param a L'intero a 128 bit con segno da scrivere sul socket.
         * @return `true` se la scrittura è andata a buon fine, `false` altrimenti.
         */
        virtual bool sockWrite(const __int128_t&a) const
        {
            return ((write(sockfd,&a,sizeof(__int128_t)))!=-1);
        }

        /**
         * @brief Scrive un booleano sul socket.
         * 
         * Questo metodo scrive un booleano sul socket.
         * 
         * @param a Il booleano da scrivere sul socket.
         * @return `true` se la scrittura è andata a buon fine, `false` altrimenti.
         */
        virtual bool sockWrite(const bool&a) const
        {
            return ((write(sockfd,&a,sizeof(bool)))!=-1);
        }

        /**
         * @brief Scrive un numero in virgola mobile a 32 bit sul socket.
         * 
         * Questo metodo scrive un numero in virgola mobile a 32 bit sul socket.
         * 
         * @param a Il numero in virgola mobile a 32 bit da scrivere sul socket.
         * @return `true` se la scrittura è andata a buon fine, `false` altrimenti.
         */
        virtual bool sockWrite(const float&a) const
        {
            return ((write(sockfd,&a,sizeof(float)))!=-1);
        }

        /**
         * @brief Scrive un numero in virgola mobile a 64 bit sul socket.
         * 
         * Questo metodo scrive un numero in virgola mobile a 64 bit sul socket.
         * 
         * @param a Il numero in virgola mobile a 64 bit da scrivere sul socket.
         * @return `true` se la scrittura è andata a buon fine, `false` altrimenti.
         */
        virtual bool sockWrite(const double&a) const
        {
            return ((write(sockfd,&a,sizeof(double)))!=-1);
        }

        /**
         * @brief Scrive un numero in virgola mobile a 128 bit sul socket.
         * 
         * Questo metodo scrive un numero in virgola mobile a 128 bit sul socket.
         * 
         * @param a Il numero in virgola mobile a 128 bit da scrivere sul socket.
         * @return `true` se la scrittura è andata a buon fine, `false` altrimenti.
         */
        virtual bool sockWrite(const long double&a) const
        {
            return ((write(sockfd,&a,sizeof(long double)))!=-1);
        }

        /**
         * @brief Scrive una stringa sul socket.
         * 
         * Questo metodo scrive una stringa sul socket.
         * 
         * @param a La stringa da scrivere sul socket.
         * @return `true` se la scrittura è andata a buon fine, `false` altrimenti.
         */
        virtual bool sockWrite(const string&a) const
        {
            return ((write(sockfd,a.c_str(),strlen(a.c_str())))!=-1);
        }

        /**
         * @brief Scrive un carattere sul socket.
         * 
         * Questo metodo scrive un carattere sul socket.
         * 
         * @param a Il carattere da scrivere sul socket.
         * @return `true` se la scrittura è andata a buon fine, `false` altrimenti.
         */
        virtual bool sockWrite(const char&a) const
        {
            return ((write(sockfd,&a,sizeof(char)))!=-1);
        }

        /**
         * @brief Scrive una stringa sul socket.
         * 
         * Questo metodo scrive una stringa sul socket.
         * 
         * @param a La stringa da scrivere sul socket.
         * @return `true` se la scrittura è andata a buon fine, `false` altrimenti.
         */
        virtual bool sockWrite(const char*a) const
        {
            return ((write(sockfd,a,strlen(a)))!=-1);
        }

        /**
         * @brief Legge un intero a 8 bit dal socket.
         * 
         * Questo metodo legge un intero a 8 bit dal socket.
         * 
         * @param a Il byte letto dal socket.
         * @return `true` se la lettura è andata a buon fine, `false` altrimenti.
         */
        virtual bool sockRead(__uint8_t&a)
        {
            memset(reinterpret_cast<char*>(&a),0,sizeof(__uint8_t));
            return ((bytesRead=read(sockfd,&a,sizeof(__uint8_t)))!=-1);
        }

        /**
         * @brief Legge un intero a 16 bit dal socket.
         * 
         * Questo metodo legge un intero a 16 bit dal socket.
         * 
         * @param a L'intero a 16 bit letto dal socket.
         * @return `true` se la lettura è andata a buon fine, `false` altrimenti.
         */
        virtual bool sockRead(__uint16_t&a)
        {
            memset(reinterpret_cast<char*>(&a),0,sizeof(__uint16_t));
            return ((bytesRead=read(sockfd,&a,sizeof(__uint16_t)))!=-1);
        }

        /**
         * @brief Legge un intero a 32 bit dal socket.
         * 
         * Questo metodo legge un intero a 32 bit dal socket.
         * 
         * @param a L'intero a 32 bit letto dal socket.
         * @return `true` se la lettura è andata a buon fine, `false` altrimenti.
         */
        virtual bool sockRead(__uint32_t&a)
        {
            memset(reinterpret_cast<char*>(&a),0,sizeof(__uint32_t));
            return ((bytesRead=read(sockfd,&a,sizeof(__uint32_t)))!=-1);
        }

        /**
         * @brief Legge un intero a 64 bit dal socket.
         * 
         * Questo metodo legge un intero a 64 bit dal socket.
         * 
         * @param a L'intero a 64 bit letto dal socket.
         * @return `true` se la lettura è andata a buon fine, `false` altrimenti.
         */
        virtual bool sockRead(__uint64_t&a)
        {
            memset(reinterpret_cast<char*>(&a),0,sizeof(__uint64_t));
            return ((bytesRead=read(sockfd,&a,sizeof(__uint64_t)))!=-1);
        }

        /**
         * @brief Legge un intero a 128 bit dal socket.
         * 
         * Questo metodo legge un intero a 128 bit dal socket.
         * 
         * @param a L'intero a 128 bit letto dal socket.
         * @return `true` se la lettura è andata a buon fine, `false` altrimenti.
         */
        virtual bool sockRead(__uint128_t&a)
        {
            memset(reinterpret_cast<char*>(&a),0,sizeof(__uint128_t));
            return ((bytesRead=read(sockfd,&a,sizeof(__uint128_t)))!=-1);
        }

        /**
         * @brief Legge un intero a 8 bit con segno dal socket.
         * 
         * Questo metodo legge un intero a 8 bit con segno dal socket.
         * 
         * @param a Il byte con segno letto dal socket.
         * @return `true` se la lettura è andata a buon fine, `false` altrimenti.
         */
        virtual bool sockRead(__int8_t&a)
        {
            memset(reinterpret_cast<char*>(&a),0,sizeof(__int8_t));
            return ((bytesRead=read(sockfd,&a,sizeof(__int8_t)))!=-1);
        }

        /**
         * @brief Legge un intero a 16 bit con segno dal socket.
         * 
         * Questo metodo legge un intero a 16 bit con segno dal socket.
         * 
         * @param a L'intero a 16 bit con segno letto dal socket.
         * @return `true` se la lettura è andata a buon fine, `false` altrimenti.
         */
        virtual bool sockRead(__int16_t&a)
        {
            memset(reinterpret_cast<char*>(&a),0,sizeof(__int16_t));
            return ((bytesRead=read(sockfd,&a,sizeof(__int16_t)))!=-1);
        }

        /**
         * @brief Legge un intero a 32 bit con segno dal socket.
         * 
         * Questo metodo legge un intero a 32 bit con segno dal socket.
         * 
         * @param a L'intero a 32 bit con segno letto dal socket.
         * @return `true` se la lettura è andata a buon fine, `false` altrimenti.
         */
        virtual bool sockRead(__int32_t&a)
        {
            memset(reinterpret_cast<char*>(&a),0,sizeof(__int32_t));
            return ((bytesRead=read(sockfd,&a,sizeof(__int32_t)))!=-1);
        }

        /**
         * @brief Legge un intero a 64 bit con segno dal socket.
         * 
         * Questo metodo legge un intero a 64 bit con segno dal socket.
         * 
         * @param a L'intero a 64 bit con segno letto dal socket.
         * @return `true` se la lettura è andata a buon fine, `false` altrimenti.
         */
        virtual bool sockRead(__int64_t&a)
        {
            memset(reinterpret_cast<char*>(&a),0,sizeof(__int64_t));
            return ((bytesRead=read(sockfd,&a,sizeof(__int64_t)))!=-1);
        }

        /**
         * @brief Legge un intero a 128 bit con segno dal socket.
         * 
         * Questo metodo legge un intero a 128 bit con segno dal socket.
         * 
         * @param a L'intero a 128 bit con segno letto dal socket.
         * @return `true` se la lettura è andata a buon fine, `false` altrimenti.
         */
        virtual bool sockRead(__int128_t&a)
        {
            memset(reinterpret_cast<char*>(&a),0,sizeof(__int128_t));
            return ((bytesRead=read(sockfd,&a,sizeof(__int128_t)))!=-1);
        }

        /**
         * @brief Legge un booleano dal socket.
         * 
         * Questo metodo legge un booleano dal socket.
         * 
         * @param a Il booleano letto dal socket.
         * @return `true` se la lettura è andata a buon fine, `false` altrimenti.
         */
        virtual bool sockRead(bool&a)
        {
            memset(reinterpret_cast<char*>(&a),0,sizeof(bool));
            return ((bytesRead=read(sockfd,&a,sizeof(bool)))!=-1);
        }

        /**
         * @brief Legge un numero in virgola mobile a 32 bit dal socket.
         * 
         * Questo metodo legge un numero in virgola mobile a 32 bit dal socket.
         * 
         * @param a Il numero in virgola mobile a 32 bit letto dal socket.
         * @return `true` se la lettura è andata a buon fine, `false` altrimenti.
         */
        virtual bool sockRead(float&a)
        {
            memset(reinterpret_cast<char*>(&a),0,sizeof(float));
            return ((bytesRead=read(sockfd,&a,sizeof(float)))!=-1);
        }

        /**
         * @brief Legge un numero in virgola mobile a 64 bit dal socket.
         * 
         * Questo metodo legge un numero in virgola mobile a 64 bit dal socket.
         * 
         * @param a Il numero in virgola mobile a 64 bit letto dal socket.
         * @return `true` se la lettura è andata a buon fine, `false` altrimenti.
         */
        virtual bool sockRead(double&a)
        {
            memset(reinterpret_cast<char*>(&a),0,sizeof(double));
            return ((bytesRead=read(sockfd,&a,sizeof(double)))!=-1);
        }

        /**
         * @brief Legge un numero in virgola mobile a 128 bit dal socket.
         * 
         * Questo metodo legge un numero in virgola mobile a 128 bit dal socket.
         * 
         * @param a Il numero in virgola mobile a 128 bit letto dal socket.
         * @return `true` se la lettura è andata a buon fine, `false` altrimenti.
         */
        virtual bool sockRead(long double&a)
        {
            memset(reinterpret_cast<char*>(&a),0,sizeof(long double));
            return ((bytesRead=read(sockfd,&a,sizeof(long double)))!=-1);
        }

        /**
         * @brief Legge una stringa dal socket.
         * 
         * Questo metodo legge una stringa dal socket.
         * 
         * @param a La stringa letta dal socket.
         * @return `true` se la lettura è andata a buon fine, `false` altrimenti.
         */
        virtual bool sockRead(string&a)
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

        /**
         * @brief Legge un carattere dal socket.
         * 
         * Questo metodo legge un carattere dal socket.
         * 
         * @param a Il carattere letto dal socket.
         * @return `true` se la lettura è andata a buon fine, `false` altrimenti.
         */
        virtual bool sockRead(char&a)
        {
            memset(reinterpret_cast<char*>(&a),0,sizeof(char));
            return ((bytesRead=read(sockfd,&a,sizeof(char)))!=-1);
        }

        /**
         * @brief Legge una stringa dal socket.
         * 
         * Questo metodo legge una stringa dal socket.
         * 
         * @param a La stringa letta dal socket.
         * @return `true` se la lettura è andata a buon fine, `false` altrimenti.
         */
        virtual bool sockRead(char*a)
        {
            memset(a,'\0',strlen(a));
            if((bytesRead=read(sockfd,a,N))!=-1)
            {
                a[bytesRead]='\0';
            }
            return (bytesRead!=-1);
        }

        friend SocketService& operator <<(SocketService &ss, const __uint8_t&a)
        {
            if(!ss.sockWrite(a))
            {
                cerr<<"write: "<<strerror(errno)<<endl;
            }
            return ss;
        }

        friend SocketService& operator <<(SocketService &ss, const __uint16_t&a)
        {
            if(!ss.sockWrite(a))
            {
                cerr<<"write: "<<strerror(errno)<<endl;
            }
            return ss;
        }

        friend SocketService& operator <<(SocketService &ss, const __uint32_t&a)
        {
            if(!ss.sockWrite(a))
            {
                cerr<<"write: "<<strerror(errno)<<endl;
            }
            return ss;
        }

        friend SocketService& operator <<(SocketService &ss, const __uint64_t&a)
        {
            if(!ss.sockWrite(a))
            {
                cerr<<"write: "<<strerror(errno)<<endl;
            }
            return ss;
        }

        friend SocketService& operator <<(SocketService &ss, const __uint128_t&a)
        {
            if(!ss.sockWrite(a))
            {
                cerr<<"write: "<<strerror(errno)<<endl;
            }
            return ss;
        }

        friend SocketService& operator <<(SocketService &ss, const __int8_t&a)
        {
            if(!ss.sockWrite(a))
            {
                cerr<<"write: "<<strerror(errno)<<endl;
            }
            return ss;
        }

        friend SocketService& operator <<(SocketService &ss, const __int16_t&a)
        {
            if(!ss.sockWrite(a))
            {
                cerr<<"write: "<<strerror(errno)<<endl;
            }
            return ss;
        }

        friend SocketService& operator <<(SocketService &ss, const __int32_t&a)
        {
            if(!ss.sockWrite(a))
            {
                cerr<<"write: "<<strerror(errno)<<endl;
            }
            return ss;
        }

        friend SocketService& operator <<(SocketService &ss, const __int64_t&a)
        {
            if(!ss.sockWrite(a))
            {
                cerr<<"write: "<<strerror(errno)<<endl;
            }
            return ss;
        }

        friend SocketService& operator <<(SocketService &ss, const __int128_t&a)
        {
            if(!ss.sockWrite(a))
            {
                cerr<<"write: "<<strerror(errno)<<endl;
            }
            return ss;
        }

        friend SocketService& operator <<(SocketService &ss, const bool&a)
        {
            if(!ss.sockWrite(a))
            {
                cerr<<"write: "<<strerror(errno)<<endl;
            }
            return ss;
        }

        friend SocketService& operator <<(SocketService &ss, const float&a)
        {
            if(!ss.sockWrite(a))
            {
                cerr<<"write: "<<strerror(errno)<<endl;
            }
            return ss;
        }

        friend SocketService& operator <<(SocketService &ss, const double&a)
        {
            if(!ss.sockWrite(a))
            {
                cerr<<"write: "<<strerror(errno)<<endl;
            }
            return ss;
        }

        friend SocketService& operator <<(SocketService &ss, const long double&a)
        {
            if(!ss.sockWrite(a))
            {
                cerr<<"write: "<<strerror(errno)<<endl;
            }
            return ss;
        }

        friend SocketService& operator <<(SocketService &ss, const string&a)
        {
            if(!ss.sockWrite(a))
            {
                cerr<<"write: "<<strerror(errno)<<endl;
            }
            return ss;
        }

        friend SocketService& operator <<(SocketService &ss, const char&a)
        {
            if(!ss.sockWrite(a))
            {
                cerr<<"write: "<<strerror(errno)<<endl;
            }
            return ss;
        }

        friend SocketService& operator <<(SocketService &ss,const char*a)
        {
            if(!ss.sockWrite(a))
            {
                cerr<<"write: "<<strerror(errno)<<endl;
            }
            return ss;
        }

        friend SocketService& operator >>(SocketService &ss, __uint8_t&a)
        {
            if(!ss.sockRead(a))
            {
                cerr<<"read: "<<strerror(errno)<<endl;
            }
            return ss;
        }

        friend SocketService& operator >>(SocketService &ss, __uint16_t&a)
        {
            if(!ss.sockRead(a))
            {
                cerr<<"read: "<<strerror(errno)<<endl;
            }
            return ss;
        }

        friend SocketService& operator >>(SocketService &ss, __uint32_t&a)
        {
            if(!ss.sockRead(a))
            {
                cerr<<"read: "<<strerror(errno)<<endl;
            }
            return ss;
        }

        friend SocketService& operator >>(SocketService &ss, __uint64_t&a)
        {
            if(!ss.sockRead(a))
            {
                cerr<<"read: "<<strerror(errno)<<endl;
            }
            return ss;
        }

        friend SocketService& operator >>(SocketService &ss, __uint128_t&a)
        {
            if(!ss.sockRead(a))
            {
                cerr<<"read: "<<strerror(errno)<<endl;
            }
            return ss;
        }

        friend SocketService& operator >>(SocketService &ss, __int8_t&a)
        {
            if(!ss.sockRead(a))
            {
                cerr<<"read: "<<strerror(errno)<<endl;
            }
            return ss;
        }

        friend SocketService& operator >>(SocketService &ss, __int16_t&a)
        {
            if(!ss.sockRead(a))
            {
                cerr<<"read: "<<strerror(errno)<<endl;
            }
            return ss;
        }

        friend SocketService& operator >>(SocketService &ss, __int32_t&a)
        {
            if(!ss.sockRead(a))
            {
                cerr<<"read: "<<strerror(errno)<<endl;
            }
            return ss;
        }

        friend SocketService& operator >>(SocketService &ss, __int64_t&a)
        {
            if(!ss.sockRead(a))
            {
                cerr<<"read: "<<strerror(errno)<<endl;
            }
            return ss;
        }

        friend SocketService& operator >>(SocketService &ss, __int128_t&a)
        {
            if(!ss.sockRead(a))
            {
                cerr<<"read: "<<strerror(errno)<<endl;
            }
            return ss;
        }

        friend SocketService& operator >>(SocketService &ss, bool&a)
        {
            if(!ss.sockRead(a))
            {
                cerr<<"read: "<<strerror(errno)<<endl;
            }
            return ss;
        }

        friend SocketService& operator >>(SocketService &ss, float&a)
        {
            if(!ss.sockRead(a))
            {
                cerr<<"read: "<<strerror(errno)<<endl;
            }
            return ss;
        }

        friend SocketService& operator >>(SocketService &ss, double&a)
        {
            if(!ss.sockRead(a))
            {
                cerr<<"read: "<<strerror(errno)<<endl;
            }
            return ss;
        }

        friend SocketService& operator >>(SocketService &ss, long double&a)
        {
            if(!ss.sockRead(a))
            {
                cerr<<"read: "<<strerror(errno)<<endl;
            }
            return ss;
        }
        
        friend SocketService& operator >>(SocketService &ss, string&a)
        {
            if(!ss.sockRead(a))
            {
                cerr<<"read: "<<strerror(errno)<<endl;
            }
            return ss;
        }

        friend SocketService& operator >>(SocketService &ss, char&a)
        {
            if(!ss.sockRead(a))
            {
                cerr<<"read: "<<strerror(errno)<<endl;
            }
            return ss;
        }

        friend SocketService& operator >>(SocketService &ss, char*a)
        {
            if(!ss.sockRead(a))
            {
                cerr<<"read: "<<strerror(errno)<<endl;
            }
            return ss;
        }
};

class Server: public SocketService
{
    private:
        int backlog;
        int sockfd2;
        struct sockaddr_in addr2;
        pid_t pid;

        /**
         * @brief Imposta le impostazioni del server.
         * 
         * Questo metodo lega il socket a un indirizzo e inizia ad ascoltare le connessioni in entrata.
         * Se la bind fallisce, viene stampato un messaggio di errore e restituisce -1.
         * Il numero di connessioni in attesa che il socket può tenere è impostato a 5 se il backlog è 0, altrimenti è impostato al valore del backlog.
         * 
         * @return 0 se l'impostazione del server è andata a buon fine, -1 altrimenti.
         */
        int serverSettings()
        {
            if((::bind(sockfd,reinterpret_cast<struct sockaddr*>(&addr),addrlen))==-1)
            {
                cerr<<"bind: "<<strerror(errno)<<endl;
                return -1;
            }
            listen(sockfd,((!backlog)?5:backlog));
            return 0;
        }
    public:

        /**
         * @brief Costruttore per la classe Server.
         * 
         * Questo costruttore inizializza un oggetto Server con la porta e il backlog specificati.
         * 
         * @param porta La porta da utilizzare per il socket.
         * @param backlog Il numero di connessioni in attesa che il socket può tenere.
         */
        Server(in_port_t porta=0, int backlog=0): SocketService(porta), backlog(backlog){}

        /**
         * @brief Distruttore per la classe Server.
         * 
         * Questo distruttore chiude il socket.
         */
        ~Server(){}

        /**
         * @brief Inizializza il server.
         * 
         * Questo metodo inizializza il server con la porta e il backlog specificati.
         * 
         * @return `true` se l'inizializzazione è andata a buon fine, `false` altrimenti.
         */
        bool init()
        {
            return init(this->porta, this->backlog);
        }

        /**
         * @brief Inizializza il server.
         * 
         * Questo metodo inizializza il server con la porta specificata.
         * 
         * @param porta La porta da utilizzare per il socket.
         * @return `true` se l'inizializzazione è andata a buon fine, `false` altrimenti.
         */
        bool init(in_port_t porta)
        {
            return init(porta, this->backlog);
        }

        /**
         * @brief Inizializza il server.
         * 
         * Questo metodo inizializza il server con la porta e il backlog specificati.
         * Prima imposta le impostazioni del socket e poi le impostazioni del server.
         * Se una di queste operazioni fallisce, il metodo restituisce `false`.
         * 
         * @param porta La porta da utilizzare per il socket.
         * @param backlog Il numero massimo di connessioni che possono essere messe in coda.
         * @return `true` se l'inizializzazione è andata a buon fine, `false` altrimenti.
         */
        bool init(in_port_t porta, int backlog)
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

        bool sockWrite(const __uint8_t&a) const override
        {
            return ((write(sockfd2,&a,sizeof(__uint8_t)))!=-1);
        }

        bool sockWrite(const __uint16_t&a) const override
        {
            return ((write(sockfd2,&a,sizeof(__uint16_t)))!=-1);
        }

        bool sockWrite(const __uint32_t&a) const override
        {
            return ((write(sockfd2,&a,sizeof(__uint32_t)))!=-1);
        }

        bool sockWrite(const __uint64_t&a) const override
        {
            return ((write(sockfd2,&a,sizeof(__uint64_t)))!=-1);
        }

        bool sockWrite(const __uint128_t&a) const override
        {
            return ((write(sockfd2,&a,sizeof(__uint128_t)))!=-1);
        }

        bool sockWrite(const __int8_t&a) const override
        {
            return ((write(sockfd2,&a,sizeof(__int8_t)))!=-1);
        }

        bool sockWrite(const __int16_t&a) const override
        {
            return ((write(sockfd2,&a,sizeof(__int16_t)))!=-1);
        }

        bool sockWrite(const __int32_t&a) const override
        {
            return ((write(sockfd2,&a,sizeof(__int32_t)))!=-1);
        }
        
        bool sockWrite(const __int64_t&a) const override
        {
            return ((write(sockfd2,&a,sizeof(__int64_t)))!=-1);
        }

        bool sockWrite(const __int128_t&a) const override
        {
            return ((write(sockfd2,&a,sizeof(__int128_t)))!=-1);
        }

        bool sockWrite(const bool&a) const override
        {
            return ((write(sockfd2,&a,sizeof(bool)))!=-1);
        }

        bool sockWrite(const float&a) const override
        {
            return ((write(sockfd2,&a,sizeof(float)))!=-1);
        }

        bool sockWrite(const double&a) const override
        {
            return ((write(sockfd2,&a,sizeof(double)))!=-1);
        }

        bool sockWrite(const long double&a) const override
        {
            return ((write(sockfd2,&a,sizeof(long double)))!=-1);
        }

        bool sockWrite(const string&a) const override
        {
            return ((write(sockfd2,a.c_str(),a.length()))!=-1);
        }

        bool sockWrite(const char&a) const override
        {
            return ((write(sockfd2,&a,sizeof(char)))!=-1);
        }

        bool sockWrite(const char*a) const override
        {
            return ((write(sockfd2,a,strlen(a)))!=-1);
        }

        bool sockRead(__uint8_t&a) override
        {
            memset(reinterpret_cast<char*>(&a),0,sizeof(__uint8_t));
            return ((bytesRead=read(sockfd2,&a,sizeof(__uint8_t)))!=-1);
        }

        bool sockRead(__uint16_t&a) override
        {
            memset(reinterpret_cast<char*>(&a),0,sizeof(__uint16_t));
            return ((bytesRead=read(sockfd2,&a,sizeof(__uint16_t)))!=-1);
        }

        bool sockRead(__uint32_t&a) override
        {
            memset(reinterpret_cast<char*>(&a),0,sizeof(__uint32_t));
            return ((bytesRead=read(sockfd2,&a,sizeof(__uint32_t)))!=-1);
        }

        bool sockRead(__uint64_t&a) override
        {
            memset(reinterpret_cast<char*>(&a),0,sizeof(__int64_t));
            return ((bytesRead=read(sockfd2,&a,sizeof(__uint64_t)))!=-1);
        }

        bool sockRead(__uint128_t&a) override
        {
            memset(reinterpret_cast<char*>(&a),0,sizeof(__uint128_t));
            return ((bytesRead=read(sockfd2,&a,sizeof(__uint128_t)))!=-1);
        }

        bool sockRead(__int8_t&a) override
        {
            memset(reinterpret_cast<char*>(&a),0,sizeof(__int8_t));
            return ((bytesRead=read(sockfd2,&a,sizeof(__int8_t)))!=-1);
        }

        bool sockRead(__int16_t&a) override
        {
            memset(reinterpret_cast<char*>(&a),0,sizeof(__int16_t));
            return ((bytesRead=read(sockfd2,&a,sizeof(__int16_t)))!=-1);
        }

        bool sockRead(__int32_t&a) override
        {
            memset(reinterpret_cast<char*>(&a),0,sizeof(__int32_t));
            return ((bytesRead=read(sockfd2,&a,sizeof(__int32_t)))!=-1);
        }

        bool sockRead(__int64_t&a) override
        {
            memset(reinterpret_cast<char*>(&a),0,sizeof(__int64_t));
            return ((bytesRead=read(sockfd2,&a,sizeof(__int64_t)))!=-1);
        }

        bool sockRead(__int128_t&a) override
        {
            memset(reinterpret_cast<char*>(&a),0,sizeof(__int128_t));
            return ((bytesRead=read(sockfd2,&a,sizeof(__int128_t)))!=-1);
        }

        bool sockRead(bool&a) override
        {
            memset(reinterpret_cast<char*>(&a),0,sizeof(bool));
            return ((bytesRead=read(sockfd2,&a,sizeof(bool)))!=-1);
        }

        bool sockRead(float&a) override
        {
            memset(reinterpret_cast<char*>(&a),0,sizeof(float));
            return ((bytesRead=read(sockfd2,&a,sizeof(float)))!=-1);
        }

        bool sockRead(double&a) override
        {
            memset(reinterpret_cast<char*>(&a),0,sizeof(double));
            return ((bytesRead=read(sockfd2,&a,sizeof(double)))!=-1);
        }

        bool sockRead(long double&a) override
        {
            memset(reinterpret_cast<char*>(&a),0,sizeof(long double));
            return ((bytesRead=read(sockfd2,&a,sizeof(long double)))!=-1);
        }

        bool sockRead(string&a) override
        {
            //size_t maxSize=static_cast<size_t>(a.max_size());
            char buffer[N];
            memset(buffer,'\0',strlen(buffer));
            if((bytesRead=read(sockfd2,buffer,N))!=-1)
            {
                buffer[bytesRead]='\0';
                a.assign(buffer);
            }
            return (bytesRead!=-1);
        }

        bool sockRead(char&a) override
        {
            memset(reinterpret_cast<char*>(&a),0,sizeof(char));
            return ((bytesRead=read(sockfd2,&a,sizeof(char)))!=-1);
        }
        
        bool sockRead(char*a) override
        {
            memset(a,'\0',strlen(a));
            if((bytesRead=read(sockfd2,a,N))!=-1)
            {
                a[bytesRead]='\0';
            }
            return (bytesRead!=-1);
        }
        
        /**
         * @brief Avvia il server per servire le richieste in modo continuo.
         * 
         * Questo metodo avvia il server per accettare e gestire le connessioni in entrata in un ciclo infinito.
         * Per ogni connessione accettata, viene creato un nuovo processo figlio per gestire la connessione.
         * Se l'accettazione della connessione o la creazione del processo figlio falliscono, viene stampato un messaggio di errore e restituito -1.
         * 
         * @return 0 se il server è stato avviato con successo, -1 se c'è stato un errore.
         */
        pid_t serveForever()
        {
            cout<<"Ascolto sulla porta "<<ntohs(addr.sin_port)<<"…"<<endl;
            while(true)
            {
                if((sockfd2=accept(sockfd,reinterpret_cast<struct sockaddr*>(&addr2),&addrlen))==-1)
                {
                    cerr<<"accept: "<<strerror(errno)<<endl;
                    return -1;
                }
                if((pid=fork())==-1)
                {
                    cerr<<"fork: "<<strerror(errno)<<endl;
                    return -1;
                }
                if(!pid)
                {
                    close(sockfd);
                    return pid;
                }
                close(sockfd2);
            }
            return 0;
        }

        /**
         * @brief Avvia il server per servire le richieste in modo continuo.
         * 
         * Questo metodo avvia il server per accettare e gestire le connessioni in entrata in un ciclo infinito.
         * Per ogni connessione accettata, viene creato un nuovo processo figlio per gestire la connessione.
         * Se l'accettazione della connessione o la creazione del processo figlio falliscono, viene stampato un messaggio di errore e restituito -1.
         * 
         * @param action La funzione da eseguire per gestire la connessione.
         * @return 0 se il server è stato avviato con successo, -1 se c'è stato un errore.
         */
        bool serveForever(function<bool(Server&)> action)
        {
            cout<<"Ascolto sulla porta "<<ntohs(addr.sin_port)<<"…"<<endl;
            while(true)
            {
                if((sockfd2=accept(sockfd,reinterpret_cast<struct sockaddr*>(&addr2),&addrlen))==-1)
                {
                    cerr<<"accept: "<<strerror(errno)<<endl;
                    return -1;
                }
                if((pid=fork())==-1)
                {
                    cerr<<"fork: "<<strerror(errno)<<endl;
                    return -1;
                }
                if(!pid)
                {
                    close(sockfd);
                    return action(*this);
                }
                close(sockfd2);
            }
            return 0;
        }
};

class Client: public SocketService
{
    private:
        const char*address;
        /*pthread_t threadSender, threadReceiver;
        static void*senderWrapper(void*obj)
        {
            return ((Client*)obj)->sender(NULL);
        }
        void*sender(void*dummy)
        {
            char buffer[N];
            while(true)
            {
                int a;
                cin>>a;
                if(!sockWrite(a))
                {
                    cerr<<"write: "<<strerror(errno)<<endl;
                    break;
                }
            }
            pthread_exit(NULL);
        }
        static void*receiverWrapper(void*obj)
        {
            return ((Client*)obj)->receiver(NULL);
        }
        void*receiver(void*dummy)
        {
            char buffer[N];
            while(true)
            {
                if(!sockRead(buffer))
                {
                    cerr<<"read: "<<strerror(errno)<<endl;
                    break;
                }
                buffer[bytesRead]='\0';
                if((write(1,buffer,bytesRead))==-1)
                {
                    cerr<<"write: "<<strerror(errno)<<endl;
                    break;
                }
            }
            pthread_exit(NULL);
        }*/
    public:

        /**
         * @brief Costruttore di Client.
         * 
         * Questo costruttore crea un nuovo client con l'indirizzo e la porta specificati.
         * Se non vengono forniti valori, vengono utilizzati i valori di default.
         * 
         * @param address L'indirizzo IP del server a cui connettersi. Default è 0, che significa INADDR_ANY.
         * @param porta La porta del server a cui connettersi. Default è 0.
         */
        Client(const char*address=0, in_port_t porta=0): address(address), SocketService(porta){}

        /**
         * @brief Distruttore di Client.
         * 
         * Questo distruttore chiude il socket.
         */
        ~Client(){}

        /**
         * @brief Inizializza il client.
         * 
         * Questo metodo inizializza il client con l'indirizzo e la porta specificati.
         * 
         * @return `true` se l'inizializzazione è andata a buon fine, `false` altrimenti.
         */
        bool init()
        {
            return init(this->address, this->porta);
        }

        /**
         * @brief Inizializza il client.
         * 
         * Questo metodo inizializza il client con l'indirizzo specificato.
         * Prima imposta le impostazioni del socket e poi si connette al server.
         * Se una di queste operazioni fallisce, il metodo restituisce `false`.
         * 
         * @param address L'indirizzo IP del server a cui connettersi.
         * @return `true` se l'inizializzazione è andata a buon fine, `false` altrimenti.
         */
        bool init(const char*address)
        {
            return init(address, this->porta);
        }

        /**
         * @brief Inizializza il client.
         * 
         * Questo metodo inizializza il client con la porta specificata.
         * Prima imposta le impostazioni del socket e poi si connette al server.
         * Se una di queste operazioni fallisce, il metodo restituisce `false`.
         * 
         * @param porta La porta del server a cui connettersi.
         * @return `true` se l'inizializzazione è andata a buon fine, `false` altrimenti.
         */
        bool init(in_port_t porta)
        {
            return init(this->address, porta);
        }

        /**
         * @brief Inizializza il client.
         * 
         * Questo metodo inizializza il client con l'indirizzo e la porta specificati.
         * Prima imposta le impostazioni del socket e poi si connette al server.
         * Se una di queste operazioni fallisce, il metodo restituisce `false`.
         * 
         * @param address L'indirizzo IP del server a cui connettersi.
         * @param porta La porta del server a cui connettersi.
         * @return `true` se l'inizializzazione è andata a buon fine, `false` altrimenti.
         */
        bool init(const char*address, in_port_t porta)
        {
            this->address=address;
            this->porta=porta;
            if((sockaddrSettings(address))==-1)
            {
                return false;
            }
            if((connect(sockfd,reinterpret_cast<struct sockaddr*>(&addr),addrlen))==-1)
            {
                cerr<<"connect: "<<strerror(errno)<<endl;
                return false;
            }
            return true;
        }
        /*int run()
        {
            if((connect(sockfd,(struct sockaddr*)&addr,addrlen))==-1)
            {
                cerr<<"connect: "<<strerror(errno)<<endl;
                return -1;
            }
            pthread_create(&threadSender,NULL,&Client::senderWrapper,this);
            pthread_create(&threadReceiver,NULL,&Client::receiverWrapper,this);
            pthread_detach(threadReceiver);
            pthread_join(threadSender,NULL);
            pthread_cancel(threadReceiver);
            return 0;
        }*/
};

#endif