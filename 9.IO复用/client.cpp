#define _GNU_SOURCE 1
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <fcntl.h>

#define BUFFER_SIZE 64
#define MAX_EVENT_NUMBER 1024

void addfd(int epollfd,int fd){
    epoll_event event;
    event.data.fd=fd;
    event.events=EPOLLIN;
    epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&event);
}

int main(int argc,char *argv[]){
    if(argc<=2){
        printf("missing parameters\n");
        return 1;
    }
    const char *ip=argv[1];
    int port=atoi(argv[2]);
    struct sockaddr_in server_address;
    bzero(&server_address,sizeof(server_address));
    server_address.sin_family=AF_INET;
    inet_pton(AF_INET,ip,&server_address.sin_addr);
    server_address.sin_port=htons(port);
    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    assert(sockfd>=0);
    if(connect(sockfd,(struct sockaddr*)&server_address,sizeof(server_address))<0){
        printf("connection failed\n");
        close(sockfd);
        return 1;
    }
    epoll_event events[MAX_EVENT_NUMBER];
    int epollfd=epoll_create(10);
    addfd(epollfd,0);
    addfd(epollfd,sockfd);
    char read_buf[BUFFER_SIZE];
    int pipefd[2];
    int ret=pipe(pipefd);
    assert(ret!=-1);
    while(1){
        ret=epoll_wait(epollfd,events,MAX_EVENT_NUMBER,-1);
        if(ret<0){
            printf("epoll failure\n");
            break;
        }
        for(int i=0;i<ret;i++){
            if(events[i].events&EPOLLIN){
                int curfd=events[i].data.fd;
                if(curfd==0){
                    ret=splice(0,NULL,pipefd[1],NULL,32768,
                            SPLICE_F_MORE|SPLICE_F_MOVE);
                    ret=splice(pipefd[0],NULL,sockfd,NULL,32768,
                            SPLICE_F_MORE|SPLICE_F_MOVE);
                }
                else if(curfd==sockfd){
                    printf("event trigger once\n");
                    memset(read_buf,'\0',BUFFER_SIZE);
                    ret=recv(sockfd,read_buf,BUFFER_SIZE-1,0);
                    printf("get %d bytes of content:%s\n",ret,read_buf);
                }
            }
        }
    }
    close(sockfd);
    return 0;
}