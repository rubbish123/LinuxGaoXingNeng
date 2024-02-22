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

#define BUF_SIZE 1024

int main(int argc,char *argv[]){
    if(argc<=2){
        printf("missing parameters\n");
        return 1;
    }
    const char *ip=argv[1];
    int port=atoi(argv[2]);
    struct sockaddr_in address;
    bzero(&address,sizeof(address));
    address.sin_family=AF_INET;
    inet_pton(AF_INET,ip,&address.sin_addr);
    address.sin_port=htons(port);
    int sock=socket(AF_INET,SOCK_STREAM,0);
    assert(sock>=0);
    int ret=bind(sock,(struct sockaddr*)&address,sizeof(address));
    assert(ret!=-1);
    ret=listen(sock,5);
    assert(ret!=-1);
    struct sockaddr_in client;
    socklen_t client_addrlength=sizeof(client);
    int connfd=accept(sock,(struct sockaddr*)&client,&client_addrlength);
    if(connfd<0){
        printf("errno is %d\n",errno);
    }
    else{
        char buf[BUF_SIZE];
        memset(buf,'\0',BUF_SIZE);
        ret=recv(connfd,buf,BUF_SIZE-1,0);
        printf("got %d bytes of normal data '%s'\n",ret,buf);
        memset(buf,'\0',BUF_SIZE);
        ret=recv(connfd,buf,BUF_SIZE-1,MSG_OOB);
        printf("got %d bytes of oob data '%s'\n",ret,buf);
        memset(buf,'\0',BUF_SIZE);
        ret=recv(connfd,buf,BUF_SIZE-1,0);
        printf("got %d bytes of normal data '%s'\n",ret,buf);
        struct sockaddr_in local,remote;
        socklen_t local_lenght=sizeof(local);
        socklen_t remote_length=sizeof(remote);
        // 获取自身的和远端的sock的地址信息
        getsockname(connfd,(struct sockaddr*)&local,&local_lenght);
        printf("local:\n");
        printf("ip:%s\n",inet_ntoa(local.sin_addr));
        printf("port:%d\n",ntohs(local.sin_port));
        getpeername(connfd,(struct sockaddr*)&remote,&remote_length);
        printf("remote:\n");
        printf("ip:%s\n",inet_ntoa(remote.sin_addr));
        printf("port:%d\n",ntohs(remote.sin_port));
        close(connfd);
    }
    close(sock);
    return 0;
}