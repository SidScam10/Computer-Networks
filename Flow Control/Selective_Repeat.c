#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define WINDOW_SIZE 4

typedef struct {
    int sequence_number;
    char data[1024];
    bool ack_received;
} Frame;

void send_frame(Frame *frame) {
    printf("Sending Frame %d\n", frame->sequence_number);
    sleep(1);
}

void selective_repeat_arq(Frame *frames, int frame_count) {
    int base = 0, next_seq_num = 0;
    while (base < frame_count) {
        for (int i = base; i < base + WINDOW_SIZE && i < frame_count; i++)
            if (!frames[i].ack_received) send_frame(&frames[i]);
        for (int i = base; i < base + WINDOW_SIZE && i < frame_count; i++) {
            if (rand() % 10 < 7) {
                printf("ACK %d received\n", frames[i].sequence_number);
                frames[i].ack_received = true;
            }
        }
        while (base < frame_count && frames[base].ack_received) base++;
    }
}

int main() {
    int frame_count;
    printf("Enter the number of frames: ");
    scanf("%d", &frame_count);
    Frame *frames = (Frame *)malloc(frame_count * sizeof(Frame));
    srand(time(NULL));
    for (int i = 0; i < frame_count; i++) {
        printf("Enter data for Frame %d: ", i);
        scanf("%s", frames[i].data);
        frames[i].sequence_number = i;
        frames[i].ack_received = false;
    }
    selective_repeat_arq(frames, frame_count);
    free(frames);
    return 0;
}
