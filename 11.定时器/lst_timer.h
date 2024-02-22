#ifndef LST_TIMER
#define LST_TIMER

#include <iostream>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#define BUFFER_SIZE 64

class util_timer;
struct client_data{
    sockaddr_in address;
    int sockfd;
    char buf[BUFFER_SIZE];
    util_timer *timer;
};
class util_timer{
public:
    util_timer():prev(nullptr),next(nullptr){}
public:
    // 超时时间
    time_t expire;
    // 回调函数
    void(*cb_func)(client_data*);
    // 回调函数处理的瀛湖数据
    client_data *user_data;
    util_timer *prev;
    util_timer *next;
};
class sort_timer_lst{
public:
    sort_timer_lst():head(nullptr),tail(nullptr){}
    ~sort_timer_lst(){
        util_timer *tmp=head;
        while(tmp!=nullptr){
            head=tmp->next;
            delete tmp;
            tmp=head;
        }
    }
    void add_timer(util_timer *timer){
        if(timer==nullptr){
            return;
        }
        if(head==nullptr){
            head=tail=timer;
            return;
        }
        if(timer->expire<head->expire){
            timer->next=head;
            head->prev=head;
            head=timer;
            return;
        }
        add_timer(timer,head);
    }
    void adjust_timer(util_timer *timer){
        if(timer==nullptr){
            return;
        }
        util_timer *tmp=timer->next;
        if(tmp==nullptr||(timer->expire<tmp->expire)){
            return;
        }
        if(timer==head){
            head=head->next;
            head->prev=nullptr;
            timer->next=nullptr;
            add_timer(timer,head);
        }
        else{
            timer->prev->next=timer->next;
            timer->next->prev=timer->prev;
            add_timer(timer,timer->next);
        }
    }
    void del_timer(util_timer *timer){
        if(timer==nullptr){
            return;
        }
        if((timer==head)&&(timer==tail)){
            delete timer;
            head=nullptr;
            tail=nullptr;
            return;
        }
        if(timer==head){
            head=head->next;
            head->prev=nullptr;
            delete timer;
            return;
        }
        if(timer==tail){
            tail=tail->prev;
            tail->next=nullptr;
            delete timer;
            return;
        }
        timer->prev->next=timer->next;
        timer->next->prev=timer->prev;
        delete timer;
    }
    void tick(){
        if(head==nullptr){
            return;
        }
        std::cout<<"timer tick\n"<<std::endl;
        time_t cur=time(NULL);
        util_timer *tmp=head;
        while(tmp!=nullptr){
            /*
                每个定时器都是用绝对时间作为超时值，因此可以将定时器的超时值和
                系统当前时间比较以判断定时器是否超时
                此外由于链表是按超时时间升序排列的，因此如果遇到一个尚未到期的
                定时器，就代表后面所有的定时器都没有超时，因此可以直接break
            */
            if(cur<tmp->expire){
                break;
            }
            tmp->cb_func(tmp->user_data);
            // 定时任务执行完就把节点从链表中删去并重置链表头节点
            head=tmp->next;
            if(head!=nullptr){
                head->prev==nullptr;
            }
            delete tmp;
            tmp=head;
        }
    }
private:
    void add_timer(util_timer *timer,util_timer *lst_head){
        util_timer *prev=lst_head;
        util_timer *tmp=prev->next;
        while(tmp!=nullptr){
            if(timer->expire<tmp->expire){
                prev->next=timer;
                timer->next=tmp;
                tmp->prev=timer;
                timer->prev=prev;
                break;
            }
            prev=tmp;
            tmp=tmp->next;
        }
        if(tmp==nullptr){
            prev->next=timer;
            timer->prev=prev;
            timer->next=nullptr;
            tail=timer;
        }
    }
private:
    util_timer *head;
    util_timer *tail;
};
#endif