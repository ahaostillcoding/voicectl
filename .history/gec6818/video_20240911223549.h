#ifndef _MUSIC_H_
#define _MUSIC_H_

// int play_video();
void *play_video(void *arg);
int* video_init(int argc, char const *argv[]);
void handle_signal(int signo);
extern int video_stop;
// int play_video();
// void stop_video();
// void quit_video();

#endif

