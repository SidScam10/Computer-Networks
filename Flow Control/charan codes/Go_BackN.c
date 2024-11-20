#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#define WINDOW_SIZE 5
#define TIMEOUT 0.1

typedef struct {
    int sequence_number;
    char data[1024];
    bool ack_received;
} Frame;

void send_frame(Frame *frame) {
    printf("Sending Frame with Sequence Number: %d\n", frame->sequence_number);
    // Simulating transmission delay
    sleep(2);
}

void receive_ack(int *ack) {
    printf("Receiving ACK: %d\n", *ack);
}

void sliding_window_go_back_arq(Frame *frames, int frame_count) {
    int base = 0;
    int next_seq_num = 0;
    while (base < frame_count) {
        while (next_seq_num < base + WINDOW_SIZE && next_seq_num < frame_count) {
            if (!frames[next_seq_num].ack_received) {
                send_frame(&frames[next_seq_num]);
            }
            next_seq_num++;
        }
        // Set a timer to wait for ACK
        clock_t start_time = clock();
        double elapsed_time = 0;
        while (elapsed_time < TIMEOUT) {
            for (int i = base; i < next_seq_num; i++) {
                if (!frames[i].ack_received) {
                    receive_ack(&frames[i].sequence_number);
                    frames[i].ack_received = true;
                    base++;
                }
            }
            elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
        }

        // Timeout occurred, resending frames from the base
        if (base < next_seq_num) {
            printf("Timeout occurred. Resending frames from %d...\n", base);
            for (int i = base; i < next_seq_num; i++) {
                send_frame(&frames[i]);
            }
        }
    }
}

int main() {
    int frame_count;
    printf("Enter the number of frames: ");
    scanf("%d", &frame_count);
    Frame *frames = (Frame *)malloc(frame_count * sizeof(Frame));
    if (frames == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    srand(time(NULL)); // Initialize random seed
    for (int i = 0; i < frame_count; i++) {
        printf("Enter data for Frame %d: ", i);
        scanf("%s", frames[i].data);
        frames[i].sequence_number = i;
        frames[i].ack_received = false;
    }

    sliding_window_go_back_arq(frames, frame_count);
    free(frames);
    return 0;
}