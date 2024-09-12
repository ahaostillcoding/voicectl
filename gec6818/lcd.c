#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include "lcd.h"

int fd_lcd = -1;
int *plcd = NULL;
int mmap_return;

void display_point( int x, int y, int color );
int lcd_init();
void lcd_close();


int lcd_init()
{
    // 打开帧缓冲区
    fd_lcd = open("/dev/fb0", O_RDWR);
    if (fd_lcd == -1)
    {
        perror("open error:");
        return -1;
    }
    printf("fd_lcd = %d \n", fd_lcd);

    // 内存映射帧缓冲区
    plcd =(int *) mmap(NULL, 800 * 480 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, fd_lcd, 0);
    if (plcd == MAP_FAILED)
    {
        perror("mmap error:");
        close(fd_lcd);
        return -1;
    }
    printf("mmap address %p\n", plcd);
    return 0;
    // // 保存映射的地址，以便之后可以取消映射
    // mmap_return = (int)mmapped_addr;

    // // 关联 plcd 指针到映射的内存
    // plcd = (int *)mmapped_addr;

    // return mmap_return;
}


void lcd_close()
{
    // 关闭帧缓冲区
    close(fd_lcd);

    // 取消内存映射
    int munmap_return = munmap(plcd, 800 * 480 * 4);
    if (munmap_return == -1)
    {
        perror("munmap error:");
    }
}


//清屏
void display_point( int x, int y, int color )
{
    if( x>=0 && x<800 && y>=0 && y<480 )
    {
        *( plcd + y*800 + x ) = color;
    }
}


void show_color(int c)
{
    int x,y;
    for (y= 0; y < 480; y++)
    {
        for (x = 0; x < 800; x++)
        {
            display_point(x, y, c);
        }
        
    }
}

//画矩形
void display_Rectangle(int x, int y, int w, int h, int color, int offset)
{
    if( x>=0 && x<800 && y>=0 && y<480 )
    {
        if(x < offset + w && y < offset + h)
        {
            *( plcd + y*800 + x ) = color;
        }
    }
}

void show_Rectangle(int w, int h, int c, int offset)
{
    int x,y;
    for (y = 0; y < 480; y++)
    {
        for (x = 0; x < 800; x++)
        {
            // display_point(x + offset, y, c);
            display_Rectangle(x, y, w, h, c, offset);
        }
        
    }
}


//画圆
void display_Circle(int x, int y, int r, int c, int offset)
{
    if( x>=0 && x<800 && y>=0 && y<480 )
    {
        if( ((x-(offset+r))*(x-(offset+r)) + (y-(offset+r))*(y-(offset+r))) <= r*r)
        {
            *( plcd + y*800 + x ) = c;
        }
    }
}


void show_Circle(int c, int r)
{
    int x,y;
    int offset = 200;
    for (y = 0; y < 480; y++)
    {
        for (x = 0; x < 800; x++)
        {
            display_Circle(x + offset, y + offset, r, c, offset);
        }
        
    }  
}

//画三角
void display_Triangle(int x1, int y1, int x2, int y2, int x3, int y3, int c, int offset)
{
    if (x1 >= 0 && x1 < 800 && y1 >= 0 && y1 < 480)
    {
        if (x1 < offset + 10 && y1 < offset + 10)
        {
            *(plcd + y1 * 800 + x1) = c;
        }
    }
}

void show_Triangle(int c, int offset)
{
    int x, y;
    for (y = 0; y < 480; y++)
    {
        for (x = 0; x < 800; x++)
        {
            display_Triangle(x + offset, y + offset, x + offset + 10, y + offset + 10, x + offset + 5, y + offset + 10, c, offset);
        }
    }
}
