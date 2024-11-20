#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>

#define WINDOW_SIZE 4

typedef struct {
    int seq_num;
    char data[1024];
    bool ack_rec;
} Frame;

void send_frame(Frame *frame)
{
    printf("Sending Frame: %d\n",frame->seq_num);
    sleep(1);
}

void selective_repeat(Frame *frames, int frame_size)
{
    int base=0;
    while(base<frame_size)
    {
        for(int i=0;i<WINDOW_SIZE && i<frame_size;i++)
            if(!frames[i].ack_rec) send_frame(&frames[i]);
        for(int i=0;i<WINDOW_SIZE && i<frame_size;i++)
        {
            if(rand()%10<7)
            {
                printf("ACK %d Received\n",frames[i].seq_num);
                frames[i].ack_rec=true;
            }
        }
        while(base<frame_size && frames[base].ack_rec) base++;
    }
}

int main()
{
    int frame_size;
    printf("Enter Frame Size: ");
    scanf("%d",&frame_size);
    Frame *frames=(Frame *)malloc(frame_size*sizeof(Frame));
    srand(time(NULL));
    for(int i=0;i<frame_size;i++)
    {
        printf("Enter Data for Frame %d: ",i+1);
        scanf("%s",&frames[i].data);
        frames[i].seq_num=i;
        frames[i].ack_rec=false;
    }
    selective_repeat(frames,frame_size);
    free(frames);
    return 0;
}