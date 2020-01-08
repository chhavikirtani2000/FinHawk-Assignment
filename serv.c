#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/un.h>
#define SOCK_PATH "chhavik_chatsupport_system"
#define LOCK_PATH "locksys"
/*
Note: Queries can be asked in different forms and are not case sensitive
Queries:
1. Not able to login
2. How to Signup/create account
3. Day Today
4. My Name
*/
pthread_t client_threads[SOMAXCONN];
struct Client
{
	int clientNo;
	struct sockaddr_in clientname;
	socklen_t client_size;
	int clientSocketID;
	char username[1024];
};
int numberofClients=1;

struct Client clients[SOMAXCONN];
int splitString(char *bs,char arr[1024][1024])
{
	int i;
	int j=0;
	int ctr=0;
    for(i=0;i<=(strlen(bs));i++)
    {
        if(bs[i]==' '||bs[i]=='\0')
        {
            arr[ctr][j]='\0';
            ctr++;  
            j=0;    
        }
        else
        {
            arr[ctr][j]=bs[i];
            j++;
        }
    }
    return ctr;
}
void * clientTask(void * mainclient)
{
	struct Client* cl=(struct Client*) mainclient;
	while(1)
	{
		char msg[1024];
		int len;
		//char *msg;
		memset(&msg,'\0',1024);

		int readstatus=recv(cl->clientSocketID,msg,1024,0);
		int resolved=0;
		if(readstatus==-1)
		{
			printf("Error in recieving message\n");
		}
		else if(strcmp(cl->username,"human")==10 && strcmp(msg,"123exitsupport")!=10)
		{
			//printf("heree\n");
			resolved=1;
			char *pch=&msg[strlen(msg)-1];
			int tosend=atoi(pch);
			//printf("%d\n",tosend);
			for(int p=0;p<numberofClients;p++)
			{
				if(clients[p].clientNo==tosend)
				{
					//printf("here2\n");
					sendto(clients[p].clientSocketID,(const char *)msg,strlen(msg),MSG_CONFIRM,(const struct sockaddr *) &clients[p].clientname,len);
					break;
				}
			}
			
		}
		else
		{
			if(strcmp(cl->username,"human")==10)
				resolved=1;
			char arr[1024][1024];
			int t=splitString(msg,arr);
			
			for(int i=0;i<t;i++)
			{
				if(strcmp(arr[i],"Date")==0 || strcmp(arr[i],"date")==0 || strcmp(arr[i],"Date")==10 || strcmp(arr[i],"date")==10)
				{
					for(int j=0;j<t;j++)
					{
						if(strcmp(arr[j],"Today")==10 || strcmp(arr[j],"Today")==0 || strcmp(arr[j],"today")==10 || strcmp(arr[j],"today")==0)
						{
							resolved=1;
							time_t t; 
						    time(&t);
						    sendto(cl->clientSocketID,(const char *)ctime(&t),strlen(ctime(&t)),MSG_CONFIRM,(const struct sockaddr *) &cl->clientname,len);
						}
					}
				}
				
				if(strcmp(arr[i],"How")==0 || strcmp(arr[i],"how")==0 || strcmp(arr[i],"How")==10 || strcmp(arr[i],"how")==10 || strcmp(arr[i],"Create")==0 || strcmp(arr[i],"create")==0 || strcmp(arr[i],"Create")==10 || strcmp(arr[i],"create")==10)
				{
					for(int j=0;j<t;j++)
					{

						if(strcmp(arr[j],"signup")==10 || strcmp(arr[j],"Signup")==10 || strcmp(arr[j],"signup")==0 || strcmp(arr[j],"Signup")==0 || strcmp(arr[j],"account")==10 || strcmp(arr[j],"Account")==10 || strcmp(arr[j],"account")==0 || strcmp(arr[j],"Account")==0)
						{
							resolved=1;
							char finalmsg[1024]="Go to website (https://abc.com) \nClick on People Tab\nClick on signup\nEnter info\nConfirm by clicking on create\n";
						    sendto(cl->clientSocketID,(const char *)finalmsg,strlen(finalmsg),MSG_CONFIRM,(const struct sockaddr *) &cl->clientname,len);
						}
					}
				}
				if(strcmp(arr[i],"Not")==0 || strcmp(arr[i],"not")==0 || strcmp(arr[i],"Not")==10 || strcmp(arr[i],"not")==10 || strcmp(arr[i],"Cannot")==0 || strcmp(arr[i],"cannot")==0 || strcmp(arr[i],"Cannot")==10 || strcmp(arr[i],"cannot")==10)
				{
					for(int j=0;j<t;j++)
					{
						if(strcmp(arr[j],"login")==10 || strcmp(arr[j],"Login")==10 || strcmp(arr[j],"login")==0 || strcmp(arr[j],"Login")==0)
						{
							resolved=1;
							char finalmsg[1024]="Not able to signup due to the following reasons: \n1. Account expired\n2. Fee not payed\n3. Server Down\n4. Slow Internet\n";
						    sendto(cl->clientSocketID,(const char *)finalmsg,strlen(finalmsg),MSG_CONFIRM,(const struct sockaddr *) &cl->clientname,len);
						}
					}
				}
				if(strcmp(arr[i],"Name")==0 || strcmp(arr[i],"name")==0 || strcmp(arr[i],"Name")==10 || strcmp(arr[i],"name")==10)
				{
					for(int j=0;j<t;j++)
					{
						if(strcmp(arr[j],"my")==10 || strcmp(arr[j],"My")==10 || strcmp(arr[j],"my")==0 || strcmp(arr[j],"My")==0)
						{
							resolved=1;
						    sendto(cl->clientSocketID,(const char *)cl->username,strlen(cl->username),MSG_CONFIRM,(const struct sockaddr *) &cl->clientname,len);
						}
					}
				}
				


				
			}
			if(resolved==0)
			{

					char finalmsg[1024]="Cannot resolve your query, tranferring control to human help\n";
					sendto(cl->clientSocketID,(const char *)finalmsg,strlen(finalmsg),MSG_CONFIRM,(const struct sockaddr *) &cl->clientname,len);
					for(int k=0;k<numberofClients;k++)
					{
						//printf("here\n");
						//printf("%d\n",strcmp(clients[k].username,"human"));
						if(strcmp(clients[k].username,"human")==10)
						{
							//strcat(msg," ");
							//sprintf(msg,"%d",cl->clientNo);
							char sendingclient[1024];
							sprintf(sendingclient,"%d",cl->clientNo);
							//strcat(msg," ");
							strcat(msg,sendingclient);
							sendto(clients[k].clientSocketID,(const char *)msg,strlen(msg),MSG_CONFIRM,(const struct sockaddr *) &clients[k].clientname,len);

						}
						
					}
				
			}
		}
	}
}

int main(int argc, char *argv[])
{
	
	/*Socket creation*/
	int socketno;
	//struct sockaddr_in sockname;
	struct sockaddr_un sockname,remote;
	int len;
	//socketno = socket(AF_INET, SOCK_STREAM, 0);
	socketno = socket(AF_UNIX, SOCK_STREAM, 0);
	if(socketno==-1)
	{
		printf("Cannot create socket");
		return -1;
	}
	/*Socket Binding*/
	/*sockname.sin_family=AF_INET;
	sockname.sin_port=htons(8088);
	sockname.sin_addr.s_addr = htons(INADDR_ANY);//INADDR_ANY
	int bindval=bind(socketno,(struct sockaddr *) &sockname , sizeof(sockname));*/
	sockname.sun_family = AF_UNIX;
	strcpy(sockname.sun_path,SOCK_PATH);
	len = strlen(sockname.sun_path)+sizeof(sockname.sun_family);

	int lockfd=open(LOCK_PATH, O_RDONLY|O_CREAT,0600);
	if(lockfd==-1)
	{
		printf("error in lock file...exiting");
		return -1;
	}
	int rt=flock(lockfd,LOCK_EX | LOCK_NB);
	if(rt!=0)
	{
		printf("socket already in use by another process....exiting");
		return -1;
	}
	unlink(SOCK_PATH);
	int bindval=bind(socketno,(struct sockaddr *) &sockname , len);
	if(bindval<0)
	{
		printf("Problem with binding....exiting");
		return -1;
	}
	int lps=listen(socketno,SOMAXCONN);
	if(lps==-1)
	{
		printf("Problem in listening....exiting");
		return -1;
	}
	printf("Server is running....\nWaiting for clients on port chhavik_chat_system\n");
	while(1)
	{

		int cl=accept(socketno,(struct sockaddr *)&clients[numberofClients-1].clientname,&clients[numberofClients-1].client_size);
		if(cl<0)
		{
			printf("Connection failed");
		}
		else
		{
			printf("Client %d accepted\n",numberofClients);
			clients[numberofClients-1].clientSocketID=cl;
			char usrname[1024];
			memset(&usrname,'\0',1024);
			int rs=recv(cl,usrname,1024,0);
			strcpy(clients[numberofClients-1].username,usrname);
			//clients[numberofClients-1].username=usrname;
			//clients[numberofClients-1].username=recv(cl,)
		}
		pthread_create(&client_threads[numberofClients-1],NULL,clientTask,(void *) &clients[numberofClients-1]);
		clients[numberofClients-1].clientNo=numberofClients;
		numberofClients=numberofClients+1;

	}
	close(socketno);

}