// // 播放MP3

// //             madplay 用来播放指定的MP3音乐

// //                 语法：
// //                         madplay -Q  xxx.mp3         //播放
// //                         madplay -Q  xxx.mp3 &       //后台播放

// //                         killall -STOP madplay       //暂停
// //                         killall -CONT madplay       //继续

// //                         killall madplay             //关闭

// //             system() 用来执行指定的程序或者命令
// //                 NAME
// //                     system - execute a shell command
// //                 SYNOPSIS
// //                     #include <stdlib.h>
// //                     int system(const char *command);

// //                 例子：
// //                     system("ls");

// //                     system("madplay -Q  01.mp3 &");

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "video.h"

video_stop = 0;

// 信号处理函数：当ctrl+c时，退出
void handle_viedo_signal(int signo)
{
    if (signo == SIGINT)
    {
        video_stop = 1;
    }
}
void *play_video(void *arg)
{
    signal(SIGINT, handle_viedo_signal); // 注册信号处理函数
    // 执行系统调用以运行 mplayer
    if (video_stop == 0)
    {
        int ret = system("mplayer -slave -quiet -zoom -x 800 -y 480 canju.mp4");
        if (ret != 0)
        {
            fprintf(stderr, "failed to play video\n");
        }
    }else
    {
        exit(0);
    }
    return NULL;
}

int *video_init(int argc, char const *argv[])
{
    pthread_t video_thread_id;
    pthread_attr_t attr;
    // 初始化线程属性
    pthread_attr_init(&attr);
    // 设置线程分离
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    // 创建线程
    if (pthread_create(&video_thread_id, &attr, play_video, NULL) != 0)
    {
        perror("failed to create video thread");
        return NULL;
    }

    pthread_attr_destroy(&attr);
    return 0;
}