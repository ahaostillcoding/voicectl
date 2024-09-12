#ifndef _CAMERA_H_
#define _CAMERA_H_

int* camera_init(int argc, char const *argv[]);
void handle_signal(int signo);
void* camera_thread(void* arg) 
// int camera_init(int argc, char const *argv[]);

#endif
