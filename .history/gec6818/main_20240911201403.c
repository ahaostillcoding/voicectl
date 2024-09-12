#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include "video.h"

int main()
{
    // // pthread_t tid;
    // // if (pthread_create( &tid, NULL, play_video, NULL) != 0)
    // // {
    // //     perror("pthread error:");
    // //     exit(1);
    // // }
    // // 给线程一些时间来执行
    // // sleep(2000);
    // // 取消线程
    // // if (pthread_cancel(tid) != 0) {
    // //     perror("pthread_cancel error:");
    // //     exit(1);
    // // }
    while (1)
    {
        play_video
        // stop_video();
        sleep(3000);
        
        // quit_video();
    }
    
    // // quit_video(); // 退出播放
    // // pthread_join(tid, NULL);
    // // return 0;
    
}