#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#include "lcd.h"
#include "photo.h"
#include "touch.h"
#include "word.h"
#include "uart.h"
#include "control.h"
#include "desktop.h"

int main()
{

// 1. 显示图形
    // lcd_init();
    // //清屏
    // show_color(0xFFFFFF);
    // //显示矩形
    // show_Rectangle(0x0FFF00, 200, 100);
    // //显示圆形
    // show_Circle(0x000FFF, 100);
    // lcd_close();
    // return 0;


// 2. 显示图片
        // lcd_init();
        // while (1)
        // {
        //     // show_bmp(100,50, "./xiaoxin.bmp");
        //     // sleep(3);
        //     show_bmp(100,50, "./kobe.bmp");
        //     // sleep(3);
        //     // show_bmp(100,50, "./xiaoxin.bmp");
        //     // sleep(3);
        // }
        // show_bmp(0,0, "./smart_home.bmp");
        //     lcd_close();

// 3. 打字
    //  lcd_init();
    // // show_color(0xFFFFFF);
    // show_bmp(50,50, "./keai.bmp");
    // show_word(50, 50, 32, 33, li, 0xFF0000);
    // show_word(50, 100, 32, 33, jun, 0xFF0000);
    // show_word(50,150, 16 , 16 , hao , 0xFF0000 );
    // // count_down();
    // // lcd_close();
    

// 4. 触屏
    touch_init();
    lcd_init();
    show_color(0xFFFFFF);
    show_word(0, 50, 24, 48, san, 0xFF0000);
    show_word(450, 50, 48, 48, liu, 0xFF0000);
    show_word(450, 100, 48, 48, peng, 0xFF0000);
    show_word(450, 150, 48 , 48 , cheng , 0xFF0000 );
    while (1)
    {
        get_touch();
    }
    
    // int i = 0;
    // char* bmp[3] = {"./keai.bmp", "cxk.bmp", "xiaoxin.bmp"};
    // show_bmp(100, 50, bmp[i]);
    // // show_bmp(100,50, "./smart_home.bmp");
    // while (1)
    // {
    //     get_touch();
    //     if (get_direction() == 2) //向右
    //     {
    //         show_bmp(100,50, bmp[(i++)%3]);      
    //     }
    //     if(get_direction() == 3) //向左
    //     {
    //         show_bmp(100,50, bmp[(i--)%3]);
    //     }     
    // }
    // close(fd_touch);
    lcd_close();


// 5. 智能家居

    // 1)初始化
    // lcd_init();
    // touch_init();
    // // 桌面初始化
    // desktop_init();
    
    // // // 2)触摸和获取传感器数据创建两个线程工作

    // //创建获取传感器数据线程
    // pthread_t tid;
    // if (pthread_create( &tid, NULL, get_gy39, NULL) != 0)
    // {
    //     perror("pthread error:");
    //     exit(1);
    // }

    // pthread_t touch;
    // if( pthread_create( &touch, NULL, get_touch, NULL) !=0)
    // {
    //     perror("pthread error:");
    //     exit(1);
    // }
    
    // // 等待子线程完成
    // pthread_join(tid, NULL);
    // pthread_join(touch, NULL);

    // //关闭
    // lcd_close();
    // return 0;
}