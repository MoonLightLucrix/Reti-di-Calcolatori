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
#include<errno.h>
#define N 4096
#define MAX_FORM_LENGTH 32
#define backlog 254
#define database "list.txt"
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

char*ffind(FILE*fsd, char*username)
{
	rewind(fsd);
	char buffer[N];
	char*line=NULL;
	char ausername[MAX_FORM_LENGTH];
	while((line=fgets(buffer,N,fsd)))
	{
		sscanf(buffer,"%[^\t]",ausername);
		if(!strcmp(username,ausername))
		{
			break;
		}
	}
	return line;
}

char*ftfind(FILE*fsd, uint32_t token)
{
	rewind(fsd);
	char buffer[N];
	uint32_t atoken;
	char*line=NULL;
	while((line=fgets(buffer,N,fsd)))
	{
		sscanf(buffer,"%*[^\t]\t%*[^\t]\t%d",&atoken);
		if(token==atoken)
		{
			break;
		}
	}
	return line;
}

void fdeliteLine(FILE*fsd, char*line)
{
	char buffer[N];
	size_t size;
	rewind(fsd);
	FILE*ftmp=tmpfile();
	while(fgets(buffer,N,fsd))
	{
		if(strcmp(buffer,line))
		{
			fputs(buffer,ftmp);
		}
	}
	rewind(fsd);
	rewind(ftmp);
	do{
		memset(buffer,'\0',strlen(buffer));
		size=fread(buffer,1,N,ftmp);
		fwrite(buffer,1,size,fsd);
	}while(N==size);
	ftruncate(fileno(fsd),ftell(fsd));
	fclose(ftmp);
}

int signIn(int sockfd, struct sockaddr_in rAddr, socklen_t addrlen, FILE*fsd, Messaggio*messaggio, struct sockaddr_in*addr)
{
	char*lineExists=ffind(fsd,messaggio->utente.username);
	if(lineExists)
	{
		char line[strlen(lineExists)];
		strcpy(line,lineExists);
		Utente utente;
		uint32_t token;
		char isOnline;
		sscanf(line,"%[^\t]\t%[^\t]\t%u\t%d\t%c",utente.username,utente.password,&token,&utente.porta,&isOnline);
		if(!strcmp(messaggio->utente.password,utente.password))
		{
			if(isOnline=='o')
			{
				fdeliteLine(fsd,line);
				fprintf(fsd,"%s\t%s\t%u\t%d\t%c\n",utente.username,utente.password,token,utente.porta,'x');
				fflush(fsd);
				addr[token]=rAddr;
				addr[token].sin_port=htons(utente.porta);
				messaggio->token=token;
				messaggio->utente.porta=utente.porta;
				sprintf(messaggio->msg,"%s: accesso eseguito",program);
				messaggio->risultato=OK;
			}
			else
			{
				sprintf(messaggio->msg,"%s: utente già connesso",program);
				messaggio->risultato=IS_ONLINE;
			}
		}
		else
		{
			sprintf(messaggio->msg,"%s: password errata",program);
			messaggio->risultato=WRONG_PASSWORD;
		}
	}
	else
	{
		sprintf(messaggio->msg,"%s: utente non registrato",program);
		messaggio->risultato=NOT_SIGNED_UP;
	}
	if((sendto(sockfd,messaggio,sizeof(Messaggio),0,(struct sockaddr*)&rAddr,addrlen))==-1)
	{
		fprintf(stderr,"%s: sendto: %s\n",program,strerror(errno));
		return -1;
	}
	return 0;
}

int signUp(int sockfd, struct sockaddr_in rAddr, socklen_t addrlen, FILE*fsd, Messaggio*messaggio, struct sockaddr_in*addr, uint32_t*token)
{
	if(*token==backlog)
	{
		sprintf(messaggio->msg,"%s: limite di utenti gestibili dal server raggiunto",program);
		messaggio->risultato=REACHED_SERVER_LIMIT;
	}
	else
	{
		char*lineExists=ffind(fsd,messaggio->utente.username);
		if(lineExists)
		{
			sprintf(messaggio->msg,"%s: nome utente già preso",program);
			messaggio->risultato=USERNAME_USED;
		}
		else
		{
			messaggio->token=*token;
			addr[*token]=rAddr;
			addr[*token].sin_port=htons(messaggio->utente.porta);
			fprintf(fsd,"%s\t%s\t%d\t%d\t%c\n",messaggio->utente.username,messaggio->utente.password,messaggio->token,messaggio->utente.porta,'x');
			fflush(fsd);
			sprintf(messaggio->msg,"%s: registrazione effettuata",program);
			messaggio->risultato=OK;
			*token-=-1;
		}
	}
	if((sendto(sockfd,messaggio,sizeof(Messaggio),0,(struct sockaddr*)&rAddr,addrlen))==-1)
	{
		fprintf(stderr,"%s: sendto: %s\n",program,strerror(errno));
		return -1;
	}
	return 0;
}

int replyMessage(int sockfd, struct sockaddr_in*addr, socklen_t addrlen, FILE*fsd, Messaggio*messaggio, uint32_t tokenMax)
{
	Messaggio amessaggio;
	uint32_t token;
	char isOnline;
	char*lineExists;
	//printf("msg: %s\n",messaggio->msg);
	for(token=0; token<=tokenMax-1; token-=-1)
	{
		if(token==messaggio->token)
		{
			continue;
		}
		memset((char*)&amessaggio,0,sizeof(Messaggio));
		if((lineExists=ftfind(fsd,token)))
		{
			char line[strlen(lineExists)];
			strcpy(line,lineExists);
			sscanf(line,"%[^\t]\t%[^\t]\t%u\t%d\t%c",amessaggio.utente.username,amessaggio.utente.password,&amessaggio.token,&amessaggio.utente.porta,&isOnline);
			if(isOnline=='x')
			{
				sprintf(amessaggio.msg,"%s: %s",messaggio->utente.username,messaggio->msg);
				amessaggio.risultato=OK;
				if((sendto(sockfd,&amessaggio,sizeof(Messaggio),0,(struct sockaddr*)addr+token,addrlen))==-1)
				{
					fprintf(stderr,"%s: sendto: %s\n",program,strerror(errno));
					return -1;
				}
			}
		}
	}
	return 0;
}

int signOut(int sockfd, struct sockaddr_in addr, socklen_t addrlen, FILE*fsd, Messaggio*messaggio)
{
	char*lineExists=ffind(fsd,messaggio->utente.username);
	if(lineExists)
	{
		char line[strlen(lineExists)];
		strcpy(line,lineExists);
		Utente utente;
		uint32_t token;
		sscanf(line,"%[^\t]\t%[^\t]\t%u\t%d",utente.username,utente.password,&token,&utente.porta);
		fdeliteLine(fsd,line);
		fprintf(fsd,"%s\t%s\t%u\t%d\t%c\n",utente.username,utente.password,token,utente.porta,'o');
		fflush(fsd);
		sprintf(messaggio->msg,"%s: disconesso",program);
		messaggio->risultato=TERMINATE;
	}
	else
	{
		sprintf(messaggio->msg,"%s: errore, utente non trovato\n",program);
		messaggio->risultato=ERROR;
	}
	if((sendto(sockfd,messaggio,sizeof(Messaggio),0,(struct sockaddr*)&addr,addrlen))==-1)
	{
		fprintf(stderr,"%s: sendto: %s\n",program,strerror(errno));
		return -1;
	}
	return 0;
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

int server(int porta)
{
	int sockfd;
	struct sockaddr_in lAddr, rAddr, addr[backlog];
	socklen_t addrlen;
	if((sockaddrSettings(&sockfd,&lAddr,&addrlen,NULL,porta))==-1)
	{
		return -1;
	}
	if((bind(sockfd,(struct sockaddr*)&lAddr,addrlen))==-1)
	{
		fprintf(stderr,"%s: bind: %s\n",program,strerror(errno));
		close(sockfd);
		return -1;
	}
	FILE*fsd;
	if(!(fsd=fopen(database,"w+")))
	{
		fprintf(stderr,"%s: fopen: %s\n",program,strerror(errno));
		close(sockfd);
		return -1;
	}
	fclose(fsd);
	Messaggio messaggio;
	uint32_t token=0;
	int e=0;
	printf("%s: Attendo connessioni sulla porta %d…\n",program,ntohs(lAddr.sin_port));
	while(true)
	{
		memset((char*)&messaggio,0,sizeof(Messaggio));
		if((recvfrom(sockfd,&messaggio,sizeof(Messaggio),0,(struct sockaddr*)&rAddr,&addrlen))==-1)
		{
			fprintf(stderr,"%s: recvfrom: %s\n",program,strerror(errno));
			e=-1;
			fclose(fsd);
			break;
		}
		if(!(fsd=fopen(database,(messaggio.risultato==REPLY_MESSAGE)?"r":"r+")))
		{
			fprintf(stderr,"%s: fopen: %s\n",program,strerror(errno));
			e=-1;
			fclose(fsd);
			break;
		}
		if(messaggio.operazione==SIGN_IN)
		{
			if((signIn(sockfd,rAddr,addrlen,fsd,&messaggio,addr))==-1)
			{
				e=-1;
				fclose(fsd);
				break;
			}
		}
		else if(messaggio.operazione==SIGN_UP)
		{
			if((signUp(sockfd,rAddr,addrlen,fsd,&messaggio,addr,&token))==-1)
			{
				e=-1;
				fclose(fsd);
				break;
			}
		}
		else if(messaggio.operazione==REPLY_MESSAGE)
		{
			if((replyMessage(sockfd,addr,addrlen,fsd,&messaggio,token))==-1)
			{
				e=-1;
				fclose(fsd);
				break;
			}
		}
		else if(messaggio.operazione==QUIT)
		{
			if((signOut(sockfd,addr[messaggio.token],addrlen,fsd,&messaggio))==-1)
			{
				e=-1;
				fclose(fsd);
				break;
			}
		}
		fclose(fsd);
	}
	close(sockfd);
	return e;
}

int main(int argc, char**argv)
{
	extern int errno;
	strcpy(program,basename(argv[0]));
	if(argc!=2)
	{
		printf("usage: %s <porta>\n",program);
	}
	else
	{
		if((server(atoi(argv[1])))==-1)
		{
			exit(EXIT_FAILURE);
		}
	}
	exit(EXIT_SUCCESS);
}