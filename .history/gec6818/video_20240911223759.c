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
    //初始化
    signal(SIGINT, handle_signal); // 注册信号处理函数
    // 执行系统调用以运行 mplayer
    if (video_stop == 0)
    {
        int ret = system("mplayer -slave -quiet -zoom -x 800 -y 480 canju.mp4");

        // 检查 system 调用的返回值
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

// int play_video()
// {

//     // // 创建FIFO文件，用于与mplayer通信
//     // system("mkfifo /tmp/mplayer_control");
//     // // 使用mplayer通过FIFO管道播放视频（非阻塞方式）
//     // if (fork() == 0) {
//     //     system("mplayer -input file=/tmp/mplayer_control -slave -quiet -zoom -x 800 -y 480 -idle 0 canju.mp4");
//     //     return 0;
//     // }
//     // // system("mplayer -zoom -x 800 -y 480 canju.mp4");
//     system( "mplayer -zoom -x 800 -y 480 canju.mp4 \n" );
// }

// int stop_video() {
//     system("echo -n 'pause\n' > /tmp/mplayer_control"); // 暂停视频
// }

// int quit_video() {
//     system("echo -n 'quit\n' > /tmp/mplayer_control"); // 退出 mplayer
// }

// int main()
// {
//     play_music();
//     sleep(2);
//     stop_video();
//     sleep(2);
//     quit_video();
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <fcntl.h>
// #include <sys/mman.h>
// #include <sys/ioctl.h>
// #include <linux/fb.h>
// #include <string.h>

// pid_t pid;  // 全局变量，用来存储mplayer的进程ID

// // 播放视频函数
// int play_video() {
//     // 创建FIFO文件用于mplayer控制（如果已经存在，不会覆盖）
//     system("mkfifo /tmp/mplayer_control");

//     // 使用fork()启动mplayer
//     pid = fork();
//     if (pid == 0) {
//         // 子进程：启动mplayer
//         execlp("mplayer", "mplayer", "-input", "file=/tmp/mplayer_control", "canju.mp4", (char *)NULL);
//         // 如果execlp失败，返回错误
//         perror("execlp failed");
//         exit(1);
//     }

//     if (pid > 0) {
//         printf("MPlayer started with PID: %d\n", pid);
//     }

//     return 0;
// }

// // 暂停/继续视频函数
// int stop_video() {
//     // 向 mplayer 发送 'pause' 命令来暂停/继续播放
//     system("echo -n 'pause\n' > /tmp/mplayer_control");
//     return 0;
// }

// void clear_framebuffer() {
//     int fbfd = 0;
//     struct fb_var_screeninfo vinfo;
//     long int screensize = 0;
//     char *fbp = 0;

//     // 打开帧缓冲设备
//     fbfd = open("/dev/fb0", O_RDWR);
//     if (fbfd == -1) {
//         perror("Error: cannot open framebuffer device");
//         exit(1);
//     }

//     // 获取帧缓冲的变量信息
//     if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo)) {
//         perror("Error reading variable information");
//         exit(1);
//     }

//     // 计算屏幕大小（以字节为单位）
//     screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

//     // 映射帧缓冲到内存
//     fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
//     if ((int)fbp == -1) {
//         perror("Error: failed to map framebuffer device to memory");
//         exit(1);
//     }

//     // 清除屏幕（将所有像素设置为黑色）
//     memset(fbp, 0, screensize);

//     // 释放内存映射和关闭帧缓冲设备
//     munmap(fbp, screensize);
//     close(fbfd);
// }

// // 结束视频播放函数
// int quit_video() {
//     if (pid > 0) {
//         // 发送 SIGKILL 信号强制结束 mplayer 进程
//         kill(pid, SIGKILL);  // 可以使用 SIGTERM 优雅终止
//         // kill(pid, SIGTERM);  // 优雅地终止进程
//         clear_framebuffer();
//         printf("MPlayer with PID: %d terminated.\n", pid);
//     }
//     return 0;
// }

// int main()
// {
//     play_video();
//     sleep(2);
//     stop_video();
//     sleep(2);
//     stop_video();
//     sleep(2);
//     quit_video();
// }
