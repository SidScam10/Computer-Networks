#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#define WINDOW_SIZE 4
#define TIMEOUT 2

typedef struct {
    int sequence_number;
    char data[1024];
    bool ack_received;
} Frame;

void send_frame(Frame *frame) {
    printf("Sending Frame with Sequence Number: %d\n", frame->sequence_number);
    // Simulating transmission delay
    sleep(1);
}

void receive_ack(int *ack) {
    printf("Receiving ACK: %d\n", *ack);
}

void sliding_window_selective_repeat(Frame *frames, int frame_count) {
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
                    // Simulating random loss of ACK
                    if (rand() % 10 < 7) {
                        // ACK received
                        receive_ack(&frames[i].sequence_number);
                        frames[i].ack_received = true;
                    } else {
                        printf("ACK %d not received. Resending frame %d...\n", frames[i].sequence_number,frames[i].sequence_number);
                        send_frame(&frames[i]);
                    }
                }
            }
            elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
        }
        // Slide the window
        while (base < frame_count && frames[base].ack_received) {
            base++;
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
    sliding_window_selective_repeat(frames, frame_count);
    free(frames);
    return 0;
}