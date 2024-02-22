#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
    pid_t pid=fork();
    if(pid<0){
        std::cout<<"fork error"<<std::endl;
        exit(0);
    }
    else if(pid>0){
        exit(0);
    }
    umask(0);
    pid_t sid=setsid();
    if(sid<0){
        std::cout<<"setsid error"<<std::endl;
        exit(0);
    }
    chdir("/");

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    open("/dev/null",O_RDONLY);
    open("/dev/null",O_RDWR);
    open("/dev/null",O_RDWR);
}