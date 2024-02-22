#include <iostream>
#include <unistd.h>

int main(){
    char buf[1024];
    getcwd(buf,1024);
    std::cout<<buf<<std::endl;
    return 0;
}