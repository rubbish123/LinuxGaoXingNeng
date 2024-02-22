#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
#include<assert.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>


int main(){
    int sock=socket(AF_INET,SOCK_STREAM,0);
    assert(sock>=0);
    int reuse=1;
    // 设置重用本地地址
    setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse));
    struct sockaddr_in address;
    bzero(&address,sizeof(address));
    address.sin_family=AF_INET;
    inet_pton(AF_INET,"127.0.0.1",&address.sin_addr);
    address.sin_port=htons(9999);
    int ret=bind(sock,(struct sockaddr*)&address,sizeof(address));
}