#include <unistd.h>
#include <iostream>

int main(){
    uid_t uid=getuid();
    uid_t euid=geteuid();
    printf("UID is %d, EUID is %d\n",uid,euid);
    return 0;
}