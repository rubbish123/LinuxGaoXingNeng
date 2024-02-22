#include <iostream>
#include <signal.h>
#include <unistd.h>

void f1(int sig){
    if(sig==SIGINT){
        std::cout<<"SIGINT"<<std::endl;
    }
}

int main(){
    signal(SIGINT,f1);
    while(1){
        std::cout<<"waiting"<<std::endl;
        sleep(1);
    }
    return 0;
}