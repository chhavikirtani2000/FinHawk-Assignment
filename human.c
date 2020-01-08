#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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
struct sockaddr_un clname;
char msg[1024];
int reqclient;

void * clientserverTask(void * cs){

	int clientno= *((int *) cs);
	int t=0;
	int len;
	while(1){
		if(t!=0)
		{
			
			int ind = recv(clientno,msg,1024,0);
			if(ind==-1)
			{
				printf("Error in recieving message\n");
			}
			else
			{
				msg[ind] = '\0';
				printf("%s\n",msg);
				//printf("here\n");
				//printf("%c\n",msg[strlen(msg)-1]);
				//int reqclient=(int) (msg[strlen(msg)-1]);
				char *pchar=&msg[strlen(msg)-1];
				reqclient=atoi(pchar);
				//printf("%d\n",reqclient);
				//char finalmsg[1024];
				//strncpy(finalmsg,msg,strlen(msg)-2);
				//slice_str(msg,finalmsg,0,strlen(msg)-2);
				//printf("%s\n",finalmsg);
			}
		}
		else
		{
			t++;
		}

	}

}

int main(){

	int cs = socket(AF_UNIX, SOCK_STREAM, 0);
	if(cs==-1)
	{
		printf("Cannot create socket");
		return -1;
	}
	//struct sockaddr_in clname;

	/*clname.sin_family = AF_INET;
	clname.sin_port = htons(8088);
	clname.sin_addr.s_addr = htonl(INADDR_ANY);*/
	clname.sun_family=AF_UNIX;
	strcpy(clname.sun_path,SOCK_PATH);
	int len =strlen(clname.sun_path)+sizeof(clname.sun_family);
	printf("Enter your username:\n");
	char *nameinp=malloc(1024);
	fgets(nameinp,1024,stdin);
	int clientconnect=connect(cs, (struct sockaddr*) &clname, len);
	if(clientconnect == -1)
	{
		printf("Problem in connection...exiting");
		return 0;
	}

	printf("Connection established to port chhavik_chatsupport_system\n");

	pthread_t clientthread;
	pthread_create(&clientthread, NULL, clientserverTask, (void *) &cs);
	send(cs,nameinp,1024,0);

	while(1)
	{

		char *input=malloc(1024);
		fgets(input,1024,stdin);
		char clientt[1024];
		sprintf(clientt,"%d",reqclient);
		strcat(input,clientt);
		send(cs,input,1024,0);

	
	}
	close(cs);

}