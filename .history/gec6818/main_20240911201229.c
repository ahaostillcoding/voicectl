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
    // // while (1)
    // // {
    //     // play_video
    //     // stop_video();
    //     system("mplayer -slave -quiet -zoom -x 800 -y 480 canju.mp4");
    //     sleep(3000);
    //     system("pkill -9 mplayer");
    //     // quit_video();
    // // }
    
    // // quit_video(); // 退出播放
    // // pthread_join(tid, NULL);
    // // return 0;
    #include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    FILE *mplayer;
    char *video_file = "example.mp4";
    
    // 以 slave 模式启动 mplayer，并准备接收来自 stdin 的命令
    mplayer = popen("mplayer -slave -quiet -input file=/dev/stdin canju.mp4", "w");
    if (mplayer == NULL) {
        perror("Error opening mplayer");
        return -1;
    }

    // 等待 5 秒，播放视频
    sleep(5);

    // 向 mplayer 发送暂停命令
    fprintf(mplayer, "pause\n");
    fflush(mplayer);  // 确保命令被立即发送
    printf("Paused the video.\n");

    // 等待 5 秒，暂停状态
    sleep(5);

    // 向 mplayer 发送恢复播放命令
    fprintf(mplayer, "pause\n");
    fflush(mplayer);
    printf("Resumed the video.\n");

    // 再等待 5 秒
    sleep(5);

    // 向 mplayer 发送停止播放的命令
    fprintf(mplayer, "quit\n");
    fflush(mplayer);

    // 关闭管道
    pclose(mplayer);
    return 0;
}

}