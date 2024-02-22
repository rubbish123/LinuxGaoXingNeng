#ifndef TIMER_WHEEL_TIMER
#define TIMER_WHEEL_TIMER

#include <time.h>
#include <netinet/in.h>
#include <stdio.h>
#define BUFFER_SIZE 64

class tw_timer;
struct client_data{
    sockaddr_in address;
    int sockfd;
    char buf[BUFFER_SIZE];
    tw_timer *timer;
};

class tw_timer{
public:
    tw_timer(int rot,int ts):next(NULL),prev(NULL),
        rotation(rot),time_slot(ts){}
public:
    // 记录定时器在时间轮转多少圈后生效
    int rotation;
    // 记录定时器属于时间轮上的哪个槽
    int time_slot;
    void (*cb_func)(client_data*);
    client_data *user_data;
    tw_timer *next;
    tw_timer *prev;
};

class time_wheel{
public:
    time_wheel():cur_slot(0){
        for(int i=0;i<N;i++){
            slots[i]=NULL;
        }
    }
    ~time_wheel(){
        for(int i=0;i<N;i++){
            tw_timer *tmp=slots[i];
            while(tmp){
                slots[i]=tmp->next;
                delete tmp;
                tmp=slots[i];
            }
        }
    }
    // 根据定时值创建定时器并将其插入合适的槽中
    tw_timer *add_timer(int timeout){
        if(timeout<0){
            return NULL;
        }
        /*
            根据超时值计算多少的tick之后会被触发,
            timeout小于SI的话向上折合为1，否则向下折合为timeout/SI
        */
        int ticks=0;
        if(timeout<SI){
            ticks=1;
        }
        else{
            ticks=timeout/SI;
        }
        // 计算要转多少圈触发
        int rotation=ticks/N;
        // 计算应该插入哪个槽，ticks=timeout/SI
        int ts=(cur_slot+(ticks%N))%N;
        tw_timer *timer=new tw_timer(rotation,ts);
        // 如果这个槽中话没有定时器，就将其插入并设置为头节点
        if(!slots[ts]){
            printf("add timer, rotation is %d, ts is %d, cur_slot is %d\n",
                    rotation,ts,cur_slot);
            slots[ts]=timer;
        }
        // 否则就普通插入
        else{
            timer->next=slots[ts];
            slots[ts]->prev=timer;
            slots[ts]=timer;
        }
        return timer;
    }
    // 删除目标定时器timer
    void del_timer(tw_timer *timer){
        if(!timer){
            return;
        }
        int ts=timer->time_slot;
        // 如果要删除的timer是这个槽的头节点，需要重置头节点
        if(timer==slots[ts]){
            slots[ts]=slots[ts]->next;
            if(slots[ts]){
                slots[ts]->prev=NULL;
            }
            delete timer;
        }
        else{
            timer->prev->next=timer->next;
            // 如果他不是最后一个，把他next的prev也改一下
            if(timer->next){
                timer->next->prev=timer->prev;
            }
            delete timer;
        }
    }
    // SI时间到，调用该函数，时间轮向前滚动一个槽
    void tick(){
        tw_timer *tmp=slots[cur_slot];
        printf("current slot is %d\n",cur_slot);
        while(tmp){
            printf("tick the timer once\n");
            // 如果rotation值大于0，则它不该在这一轮被执行
            if(tmp->rotation>0){
                tmp->rotation--;
                tmp=tmp->next;
            }
            // 否则说明定时器已到期，执行定时任务，删除定时器
            else{
                tmp->cb_func(tmp->user_data);
                // 如果要删的是头节点，重置头节点
                if(tmp==slots[cur_slot]){
                    printf("delete header in cur_slot\n");
                    slots[cur_slot]=tmp->next;
                    delete tmp;
                    if(slots[cur_slot]){
                        slots[cur_slot]->prev=NULL;
                    }
                    tmp=slots[cur_slot];
                }
                else{
                    tmp->prev->next=tmp->next;
                    if(tmp->next){
                        tmp->next->prev=tmp->prev;
                    }
                    tw_timer *tmp2=tmp->next;
                    delete tmp;
                    tmp=tmp2;
                }
            }
        }
        // 槽向后移动一格
        cur_slot=++cur_slot%N;
    }
private:
    // 槽数 
    static const int N=60;
    // 槽间隔
    static const int SI=1;
    tw_timer *slots[N];
    // 时间轮当前槽
    int cur_slot;
};

#endif