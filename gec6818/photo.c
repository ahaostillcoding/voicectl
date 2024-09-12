#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include "lcd.h"
#include "photo.h"


int show_bmp(int x0, int y0, char * filename)
{

    int fd_bmp = open(filename, O_RDWR);

    if (fd_bmp == -1)
    {
        perror("open error:");
        return -1;
    }
    // printf("fd_bmp = %d \n", fd_bmp);

    // 图片宽度
    int width=0;
    lseek(fd_bmp, 0x12, SEEK_SET);
    read(fd_bmp, &width, 4);

    // 图片高度
    int height=0;
    lseek(fd_bmp, 0x16, SEEK_SET);
    read(fd_bmp, &height, 4);

    // 图片色深
    int depth=0;
    lseek(fd_bmp, 0x1C, SEEK_SET);
    read(fd_bmp, &depth, 2);

    // printf("width = %d, height = %d, depth = %d \n", width, height, depth);
    // //调色板(可有可无)


    //像素数据(小端存储，b g r)
    int laizi = 0;     // 表示要填充的字节数
    int line_size = 0; // 实际的字节数

    laizi = 4 - (abs(width) * (depth / 8)) % 4;
    if (laizi == 4)
    {
        laizi = 0;
    }
    // printf("laizi = %d \n", laizi);
    // 实际的字节数 = 有效字节数 + 赖子
    line_size = abs(width) * (depth / 8) + laizi;
    // printf("line_size = %d \n", line_size);

    // 一口气把所有像素点数据全部读取出来
    unsigned char buf[abs(height) * line_size];
    lseek(fd_bmp, 0x36, SEEK_SET);
    read(fd_bmp, buf, abs(height) * line_size);

    int color;
    unsigned b, g, r, a;
    int i, j;
    int num = 0;

    for (j = 0; j < abs(height); j++)
    {
        for (i = 0; i < abs(width); i++)
        {
            // 合成颜色数据
            b = buf[num++];
            g = buf[num++];
            r = buf[num++];
            if (depth == 32)
            {
                a = buf[num++];
            }
            color = (a << 24) | (r << 16) | (g << 8) | b;
            // printf("color = %x \n", color);
            // 画点
            display_point(width > 0 ? i + x0: abs(width) - 1 - i + x0,
                          height > 0 ? abs(height) - 1 - j +y0 : j + y0,
                          color);
        }
        usleep(128);
        num = num + laizi; // 跳过无效的数据
    }

    // 关闭
    close(fd_bmp);
    return 0;
}
                                                             