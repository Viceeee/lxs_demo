#include <stdlib.h>  
#include <stdio.h>  
#include <stddef.h>  
#include <sys/socket.h>  
#include <sys/un.h>  
#include <errno.h>  
#include <string.h>  
#include <unistd.h>  
 
#define MAXLINE 2048
 
char *client_path = "client.socket";  
char *server_path = "server.socket";  
 
typedef struct test{
	int a;
};

static struct test test_void;
//static int a = NULL;

int main() {  
    struct  sockaddr_un cliun, serun;  
    int len;  
    char buf[100];  
    int sockfd, n;  
    int rc;
 
    memset(&test_void, 0, sizeof(test_void));
    test_void.a = 5;    

    if ((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0){  
        perror("client socket error");  
        exit(1);  
    }  
    memset(&cliun, 0, sizeof(cliun));
    cliun.sun_family = AF_UNIX;
    strcpy(cliun.sun_path, client_path);
    len = offsetof(struct sockaddr_un, sun_path) + strlen(cliun.sun_path);
    unlink(cliun.sun_path);
    if (bind(sockfd, (struct sockaddr *)&cliun, len) < 0) {
        perror("bind error");
        exit(1);
    }

    printf("test_void.a = %d\n",test_void.a);
    memset(&serun, 0, sizeof(serun));
    serun.sun_family = AF_UNIX;
    strcpy(serun.sun_path, server_path);
    len = offsetof(struct sockaddr_un, sun_path) + strlen(serun.sun_path);
    if (connect(sockfd, (struct sockaddr *)&serun, len) < 0){
        perror("connect error");
        exit(1);
    }

	if((&test_void.a) != NULL){
		rc = sendto(sockfd,&test_void,sizeof(&test_void),0,NULL, 0);
		printf("rc= %d,and test_void is %d\n",rc,test_void.a);
		test_void.a = 20;
		printf("change void.a from 5 to  20\n");
		rc = sendto(sockfd,&test_void,sizeof(&test_void),0,NULL, 0);
		printf("rc= %d,and test_void is %d\n",rc,test_void.a);
	}
    close(sockfd);
    return 0;
}

