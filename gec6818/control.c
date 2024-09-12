#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include "control.h"



int led_beep_ctrl(char *filename, int state)
{
    // printf("led_beep open success\n %s", filename);
    // 1.打开设备文件
    int fd = open(filename, O_RDWR);
    if (fd == -1)
    {
        perror("led_beep open error :");
        return -1;
    }
    
    // 2.操作
    // 写 1 点亮
    // 写 0 熄灭
    if (write(fd, &state, 4) == -1)
    {
        perror("led_beep write error :");
        return -1;
    }

    // 3.关闭文件
    close(fd);
    return 0;
}