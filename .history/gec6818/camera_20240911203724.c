#include "v4l2.h"
#include "convert.h"
#include <signal.h>
#include <stdio.h>
#include "lcd2.h"
#include "camera.h"

// #include "myjpeg.h"

int stop = 0;
//信号处理函数：当ctrl+c时，退出
void handle_signal(int signo)
{
	if (signo == SIGINT)
	{
		stop = 1;
	}
}


int *camera_init(int argc, char const *argv[])
// int camera_init(int argc, char const *argv[])
{
	//初始化
	signal(SIGINT, handle_signal);
	v4l2_init();
	lcd2_init();

	//读取一帧-格式转换-显示到本地LCD-入队
	while (stop == 0)
	{
		struct Frame frame = v4l2_get_frame();
		char rgb888[frame.width * frame.height * 3];
		// yuv直接转rgb
		YUV422toRGB888(frame.width, frame.height, frame.addr, rgb888);
		printf("fw: %d, fh: %d\n", frame.width, frame.height);

		// -------测试yuv转jpg, jpg转rgb--------
		// unsigned char *jpgbuffer = NULL;
		// unsigned long jpgsize = 0;
		// YUYV_JPEG_MEMORY(frame.addr, frame.width, frame.height, &jpgbuffer, &jpgsize);
		// // printf("jpgbuffer: %p, jpgsize: %d\n", jpgbuffer, jpgsize);
		// JPEG_RGB_MEMORY(jpgbuffer, jpgsize, rgb888);
		// // -------------------------------------------

		// 显示rgb图像到lcd2屏幕
		lcd2_draw_rgb888(rgb888, frame.width, frame.height, 0, 0);
		// 把帧缓冲区加入采集队列
		v4l2_enqueue(frame.index);
	}

	//释放资源
	v4l2_uninit();
	lcd2_uninit();
	return 0;
}
