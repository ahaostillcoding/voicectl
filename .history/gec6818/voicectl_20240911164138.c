﻿#include "common.h"
#include "lcd.h"
#include "photo.h"
#include "control.h"

//#define REC_CMD  "./arecord -d4 -c1 -r16000 -traw -fS16_LE cmd.pcm"
#define REC_CMD  "arecord -d3 -c1 -r16000 -traw -fS16_LE cmd.pcm"
#define PCM_FILE "./cmd.pcm"
/* -d：录音时长（duration）
-c：音轨（channels）
-r：采样频率（rate）
-t：封装格式（type）
-f：量化位数（format） */

char *bmp[3] = {"./xiaoxin.bmp", "./keai.bmp", "./c.bmp"};
int i = 0;
int flag1, flag2, flag3, flag4, flag5 = -1; // 开关标志位

void catch (int sig)
{
	if (sig == SIGPIPE)
	{
		printf("killed by SIGPIPE\n");
		exit(0);
	}
}

int main(int argc, char const* argv[])
{
	if (argc != 2)
	{
		printf("Usage: %s <ubuntu-IP>\n", argv[0]);
		exit(0);
	}
	signal(SIGPIPE, catch);
	// 初始化TCP客户端套接字，用于连接到语音识别服务器(即ubuntu)
	int sockfd_tcp = init_tcp_socket(argv[1]);
	// 初始化本地UDP套接字
	int sockfd_udp = init_udp_socket();

	int id_num = -1; // 识别后的指令id

	lcd_init();
	show_bmp(0, 0, "./background2.bmp");
	
	while (1)
	{
		// 1，调用arecord来录一段音频
		printf("please to start REC in 3s...\n");

		// 在程序中执行一条命令  “录音的命令”
		system(REC_CMD);

		// 2，将录制好的PCM音频发送给语音识别引擎
		send_pcm(sockfd_tcp, PCM_FILE);

		// 3，等待对方回送识别结果（字符串ID）
		xmlChar* id = wait4id(sockfd_tcp);
		if (id == NULL)
		{
			continue;
		}
		id_num = atoi((char*)id);
		if (id_num == 999)
		{
			printf("bye-bye!\n");
			// exit(1);
		}
		if (id_num == 1)
		{
			// 图片
			show_color(0xFFFFFF);
			show_bmp(200, 50, bmp[0]);
			flag1 = 1;
		}
		if (id_num == 11 && flag1 == 1)
		{
			// 上一张
			show_color(0xFFFFFF);
			// show_bmp(0, 0, "./photo.bmp");
			i = (i + 1) % 3;
			show_bmp(200, 50, bmp[i]);
		}
		if (id_num == 12 && flag1 == 1)
		{
			// 下一张
			show_color(0xFFFFFF);
			i = (i + 2) % 3;
			show_bmp(200, 50, bmp[i]);
		}

		if (id_num == 2)
		{
			printf("2!\n");
		}
		if (id_num == 3)
		{
			// 开灯
			led_beep_ctrl(LED7, 1);
		}
		if (id_num == 4)
		{
			// 关灯
			led_beep_ctrl(LED7, 0);
		}
		if (id_num == 5)
		{
			// 蜂鸣器
			led_beep_ctrl(beep, 1);
		}
		if (id_num == 6)
		{
			// 关蜂鸣器
			led_beep_ctrl(beep, 0);
		}
		printf("recv id: %d \n", id_num);
		// udp发送数据给接收端, 接收端收到数据id后，再决定执行什么功能
		send_id(sockfd_udp, id_num);
		
	}

	return 0;
}
