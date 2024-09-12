#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#include "video.h"

int main()
{


    
    // // // 2)触摸和获取传感器数据创建两个线程工作

    // //创建获取传感器数据线程
    pthread_t tid;
    if (pthread_create( &tid, NULL, play_video, NULL) != 0)
    {
        perror("pthread error:");
        exit(1);
    }

    // pthread_t touch;
    // if( pthread_create( &touch, NULL, get_touch, NULL) !=0)
    // {
    //     perror("pthread error:");
    //     exit(1);
    // }
    
    // // 等待子线程完成
    pthread_join(tid, NULL);
    // pthread_join(touch, NULL);

    // //关闭
    // lcd_close();
    return 0;
}