#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>

int main(){
    int fd[2];
    pipe(fd);
    int sockpipe[2];
    socketpair(AF_UNIX,SOCK_STREAM,0,sockpipe);
}