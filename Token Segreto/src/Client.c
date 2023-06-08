#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<stdbool.h>
#include<string.h>
#include<libgen.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<sys/wait.h>
#include<signal.h>
#include<termios.h>
#include<getopt.h>
#include<errno.h>
#define N 4096
#define MAX_FORM_LENGTH 32
#define usage "usage: %s [--login] -u <username> -a <indirizzo ip> -p <porta>\n       %s [--registra] -u <username> -P <porta di ascolto> -a <indirizzo ip> -p <porta>\n"
typedef struct
{
	char username[MAX_FORM_LENGTH];
	char password[MAX_FORM_LENGTH];
	int porta;
} Utente;
typedef enum{SIGN_UP,SIGN_IN,REPLY_MESSAGE,QUIT} Operazione;
typedef enum{OK,NOT_SIGNED_UP,WRONG_PASSWORD,IS_ONLINE,USERNAME_USED,REACHED_SERVER_LIMIT,TERMINATE,ERROR=-1} Risultato;
typedef struct
{
	Utente utente;
	uint32_t token;
	char msg[N];
	Operazione operazione;
	Risultato risultato;
} Messaggio;
char program[FILENAME_MAX];

int reciver(int sockfd, struct sockaddr_in addr, socklen_t addrlen, Messaggio messaggio)
{
	int e=0;
	if((sockfd=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP))==-1)
	{
		fprintf(stderr,"%s: socket: %s\n",program,strerror(errno));
		return -1;
	}
	addr.sin_port=htons(messaggio.utente.porta);
	if((bind(sockfd,(struct sockaddr*)&addr,addrlen))==-1)
	{
		fprintf(stderr,"%s: bind: %s\n",program,strerror(errno));
		close(sockfd);
		return -1;
	}
	while(true)
	{
		memset((char*)&messaggio,0,sizeof(Messaggio));
		if((recvfrom(sockfd,&messaggio,sizeof(Messaggio),0,(struct sockaddr*)&addr,&addrlen))==-1)
		{
			fprintf(stderr,"%s: recvfrom: %s\n",program,strerror(errno));
			e=-1;
			break;
		}
		//printf("token: %u\n",messaggio.token);
		fflush(stdout);
		if((messaggio.risultato==TERMINATE) || (messaggio.risultato==ERROR))
		{
			printf("%s\n",messaggio.msg);
			fflush(stdout);
		}
		else
		{
			printf("\n%s\nInserisci un messaggio (\"quit\" per uscire): ",messaggio.msg);
			fflush(stdout);
		}
		if(messaggio.risultato!=OK)
		{
			e=(messaggio.risultato==TERMINATE)?0:-1;
			break;
		}
	}
	close(sockfd);
	return e;
}

int sender(int sockfd, struct sockaddr_in addr, socklen_t addrlen, Messaggio messaggio)
{
	char buffer[N];
	int e=0;
	while(true)
	{
		printf("Inserisci un messaggio (\"quit\" per uscire): ");
		memset(buffer,'\0',strlen(buffer));
		fgets(buffer,N,stdin);
		if(buffer[strlen(buffer)-1]=='\n')
		{
			buffer[strlen(buffer)-1]='\0';
		}
		if(buffer[0]=='\0')
		{
			continue;
		}
		messaggio.operazione=(!strcmp(buffer,"quit"))?QUIT:REPLY_MESSAGE;
		memset(messaggio.msg,'\0',strlen(messaggio.msg));
		strcpy(messaggio.msg,buffer);
		if((sendto(sockfd,&messaggio,sizeof(Messaggio),0,(struct sockaddr*)&addr,addrlen))==-1)
		{
			fprintf(stderr,"%s: sendto: %s\n",program,strerror(errno));
			e=-1;
			break;
		}
		if(messaggio.operazione==QUIT)
		{
			break;
		}
	}
	return e;
}

int sockaddrSettings(int*sockfd, struct sockaddr_in*addr, socklen_t*addrlen, char*address, int porta)
{
	*addrlen=sizeof(struct sockaddr);
	if((*sockfd=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP))==-1)
	{
		fprintf(stderr,"%s: socket: %s\n",program,strerror(errno));
		return -1;
	}
	memset((char*)addr,0,*addrlen);
	addr->sin_family=AF_INET;
	addr->sin_addr.s_addr=(!address)?htonl(INADDR_ANY):inet_addr(address);
	addr->sin_port=htons(porta);
	return 0;
}

int client(char*username, char*password, int aporta, char*address, int porta)
{
	//printf("aporta: %d\n",aporta);
	int sockfd, rsockfd;
	struct sockaddr_in rAddr, addr;
	socklen_t addrlen;
	if((sockaddrSettings(&sockfd,&rAddr,&addrlen,address,porta))==-1)
	{
		return -1;
	}
	addr=rAddr;
	Messaggio messaggio;
	strcpy(messaggio.utente.username,username);
	strcpy(messaggio.utente.password,password);
	messaggio.utente.porta=aporta;
	messaggio.operazione=(!aporta)?SIGN_IN:SIGN_UP;
	if((sendto(sockfd,&messaggio,sizeof(messaggio),0,(struct sockaddr*)&rAddr,addrlen))==-1)
	{
		fprintf(stderr,"%s: sendto: %s\n",program,strerror(errno));
		close(sockfd);
		return -1;
	}
	memset((char*)&messaggio,0,sizeof(Messaggio));
	if((recvfrom(sockfd,&messaggio,sizeof(Messaggio),0,(struct sockaddr*)&rAddr,&addrlen))==-1)
	{
		fprintf(stderr,"%s: recvfrom: %s\n",program,strerror(errno));
		close(sockfd);
		return -1;
	}
	printf("%s\n",messaggio.msg);
	fflush(stdout);
	int e=0;
	if(messaggio.risultato==OK)
	{
		pid_t pid;
		if((pid=fork())==-1)
		{
			fprintf(stderr,"%s: fork: %s\n",program,strerror(errno));
			close(sockfd);
			return -1;
		}
		if(!pid)
		{
			if((reciver(rsockfd,addr,addrlen,messaggio))==-1)
			{
				kill(getppid(),SIGTERM);
				exit(EXIT_FAILURE);
			}
			exit(EXIT_SUCCESS);
		}
		if((sender(sockfd,rAddr,addrlen,messaggio))==-1)
		{
			e=-1;
		}
	}
	fflush(stdout);
	close(sockfd);
	return e;
}

void maskPassword(char*password, int maxLength)
{
	struct termios oldSettings, newSettings;
	tcgetattr(0,&oldSettings);
    newSettings=oldSettings;
    newSettings.c_lflag&=(~ECHO);
    tcsetattr(0,TCSAFLUSH,&newSettings);
    fgets(password,maxLength,stdin);
    tcsetattr(0,TCSAFLUSH,&oldSettings);
    if(password[strlen(password)-1]=='\n')
    {
    	password[strlen(password)-1]='\0';
    }
    printf("\n");
}

int main(int argc, char**argv)
{
	extern int errno;
	strcpy(program,basename(argv[0]));
	if(argc==1)
	{
		printf(usage,program,program);
	}
	else
	{
		int opt;
		char username[MAX_FORM_LENGTH];
		char password[MAX_FORM_LENGTH];
		int aporta=0;
		char address[INET_ADDRSTRLEN];
		int porta=0;
		int login=-1;
		int c=0;
		struct option options[]={{"registra",no_argument,NULL,'r'},{"login",no_argument,NULL,'l'},{"username",required_argument,NULL,'u'},{"listenerport",required_argument,NULL,'P'},{"address",required_argument,NULL,'a'},{"port",required_argument,NULL,'p'},{NULL,0,NULL,0}};
		while((opt=getopt_long_only(argc,argv,"rlu:P:a:p:",options,NULL))!=-1)
		{
			switch(opt)
			{
				case 'l':
					login=(login==-1)?1:3;
					break;
				case 'r':
					login=(login==-1)?0:3;
					break;
				case 'u':
					strcpy(username,optarg);
					c-=-1;
					break;
				case 'P':
					if(login)
					{
						printf("%s: Illegal option --login --registra\n",program);
						login=3;
					}
					else
					{
						aporta=atoi(optarg);
						c-=-1;
					}
					break;
				case 'a':
					strcpy(address,optarg);
					c-=-1;
					break;
				case 'p':
					porta=atoi(optarg);
					c-=-1;
					break;
				case '?':
					break;
			}
		}
		if((login==-1) || (login==3))
		{
			printf(usage,program,program);
		}
		else if((!login) && (c==4))
		{
			printf("Password:");
			fflush(stdout);
			maskPassword(password,MAX_FORM_LENGTH);
			char sPassword[MAX_FORM_LENGTH];
			printf("Conferma password:");
			fflush(stdout);
			maskPassword(sPassword,MAX_FORM_LENGTH);
			if(strcmp(password,sPassword))
			{
				printf("%s: le due password non coincidono\n",program);
			}
			else
			{
				if((client(username,password,aporta,address,porta))==-1)
				{
					exit(EXIT_FAILURE);
				}
			}
		}
		else if((login) && (c==3))
		{
			printf("Password:");
			fflush(stdout);
			maskPassword(password,MAX_FORM_LENGTH);
			if((client(username,password,aporta,address,porta))==-1)
			{
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			printf(usage,program,program);
		}
	}
	exit(EXIT_SUCCESS);
}