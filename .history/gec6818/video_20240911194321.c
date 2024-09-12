
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
// void *get_touch(void *arg)

void *play_video(void *arg) {
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    system("mkfifo /tmp/mplayer_control");
    if (fork() == 0) {
        system("mplayer -input file=/tmp/mplayer_control -slave -quiet -zoom -x 800 -y 480 -idle 0 canju.mp4");
        pthread_exit(NULL); // Exit thread after playing the video
    }
    return NULL;
}


void stop_video() {
    system("echo -n 'pause\n' > /tmp/mplayer_control"); // 暂停视频
}

void quit_video() {
    system("pkill mplayer"); 
    // system("echo -n 'quit\n' > /tmp/mplayer_control"); // 退出 mplayer
}

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
