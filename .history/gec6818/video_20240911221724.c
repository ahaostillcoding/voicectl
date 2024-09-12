// video_player.c
#include "video_player.h"
#include <stdio.h>
#include <stdlib.h>

void* play_video(void* arg) {
    // 执行系统调用以运行 mplayer
    int ret = system("mplayer /path/to/video.mp4");
    
    // 检查 system 调用的返回值
    if (ret != 0) {
        fprintf(stderr, "Failed to play video\n");
    }

    // 线程函数返回
    return NULL;
}
