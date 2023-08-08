/*这个serversuccess和clientsuccess是为了测试UDS能否传输结构体指针为void *的类型而设置的*/
#include <stdlib.h>  
#include <stdio.h>  
#include <stddef.h>  
#include <sys/socket.h>  
#include <sys/un.h>  
#include <errno.h>  
#include <string.h>  
#include <unistd.h>  
#include <ctype.h>   
 
#define MAXLINE 2048  
 
char *socket_path = "server.socket";  
 
typedef struct test{
	int a[6];
};
static struct test test_void;

int main(void)  
{  
    struct sockaddr_un serun, cliun;  
    socklen_t cliun_len;  
    int listenfd, connfd, size;  
    char buf[MAXLINE];  
    int i, n;  
    volatile int len = 0;
 
    memset(&test_void, 0, sizeof(test_void));
    
    if ((listenfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {  
        perror("socket error");  
        exit(1);  
    }  
 
    memset(&serun, 0, sizeof(serun));  
    serun.sun_family = AF_UNIX;  
    strcpy(serun.sun_path, socket_path);  
    size = offsetof(struct sockaddr_un, sun_path) + strlen(serun.sun_path);  
    unlink(socket_path);  
    if (bind(listenfd, (struct sockaddr *)&serun, size) < 0) {  
        perror("bind error");  
        exit(1);  
    }  
    printf("UNIX domain socket bound\n");  
      
    if (listen(listenfd, 20) < 0) {  
        perror("listen error");  
        exit(1);          
    }  
    printf("Accepting connections ...\n");  

    memset(&buf, 0, sizeof(buf));  
        cliun_len = sizeof(cliun);         
        if ((connfd = accept(listenfd, (struct sockaddr *)&cliun, &cliun_len)) < 0){  
            perror("accept error");  
        }  
            n = recvfrom(connfd, &test_void.a, sizeof(&test_void), 0, NULL, NULL );  
            if (n < 0) {  
                perror("read error");  
            } else if(n == 0) {  
                printf("EOF\n");  
            }  
            printf("received all the bytes: %d\n", n);  
            printf("received struct test_void.a: %d\n", test_void.a[0]);  
            n = recvfrom(connfd, &test_void.a, sizeof(&test_void), 0, NULL, NULL );  
            printf("received all the bytes: %d\n", n);  
            printf("received struct test_void.a: %d\n", test_void.a[0]);  
	    memset(&buf, 0, sizeof(buf));  
	    //把这一行加入后清除buffer就OK了

        close(connfd);  
    close(listenfd);  
    return 0;  
}
