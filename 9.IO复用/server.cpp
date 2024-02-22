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
#include <vector>

#define BUFFER_SIZE 64
#define MAX_EVENT_NUMBER 1024

std::vector<int> v;

int setnonoblocking(int fd){
    int old_option=fcntl(fd,F_GETFL);
    int new_option=old_option|O_NONBLOCK;
    fcntl(fd,F_SETFL,new_option);
    return old_option;
}

void addfd(int epollfd,int fd){
    epoll_event event;
    event.data.fd=fd;
    event.events=EPOLLIN;
    epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&event);
    setnonoblocking(fd);
}

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
    int listenfd=socket(AF_INET,SOCK_STREAM,0);
    assert(listenfd>=0);
    int ret=bind(listenfd,(struct sockaddr*)&address,sizeof(address));
    assert(ret!=-1);
    ret=listen(listenfd,5);
    assert(ret!=-1);
    epoll_event events[MAX_EVENT_NUMBER];
    int epollfd=epoll_create(5);
    addfd(epollfd,listenfd);
    while(1){
        ret=epoll_wait(epollfd,events,MAX_EVENT_NUMBER,-1);
        if(ret<0){
            printf("epoll failure\n");
            break;
        }
        for(int i=0;i<ret;i++){
            int curfd=events[i].data.fd;
            if(curfd==listenfd){
                struct sockaddr_in client_address;
                socklen_t client_addrlength=sizeof(client_address);
                int connfd=accept(listenfd,(struct sockaddr*)&client_address,&client_addrlength);
                addfd(epollfd,connfd);
                v.push_back(connfd);
            }
            else if(events[i].events&EPOLLIN){
                printf("event trigger once\n");
                char buf[BUFFER_SIZE];
                memset(buf,'\0',BUFFER_SIZE);
                int ret=recv(curfd,buf,BUFFER_SIZE-1,0);
                if(ret<=0){
                    close(curfd);
                    continue;
                }
                printf("get %d bytes of content:%s\n",ret,buf);
                for(auto connfd:v){
                    if(connfd!=curfd){
                        send(connfd,buf,BUFFER_SIZE,0);
                    }
                }
            }
        }
    }
}