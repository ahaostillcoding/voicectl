#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include "video.h"

int main()
{
    pthread_t tid;
    if (pthread_create( &tid, NULL, play_video, NULL) != 0)
    {
        perror("pthread error:");
        exit(1);
    }
    pthread_join(tid, NULL);
    return 0;
}