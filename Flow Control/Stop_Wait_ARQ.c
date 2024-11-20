#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define TIMEOUT 2

typedef struct {
    int sequence_number;
    char data[1024];
} Frame;

void send_frame(Frame *frame) {
    printf("Sending Frame %d\n", frame->sequence_number);
    sleep(1);
}

void stop_and_wait_arq(Frame *frame) {
    bool ack_received = false;
    while (!ack_received) {
        send_frame(frame);
        if (rand() % 10 < 7) {
            printf("ACK %d received\n", frame->sequence_number);
            ack_received = true;
        } else {
            printf("ACK not received. Resending frame...\n");
        }
    }
}

int main() {
    Frame frame;
    int sequence_number = 0;
    srand(time(NULL));
    while (1) {
        printf("Enter data to send ('exit' to quit): ");
        scanf("%s", frame.data);
        if (!strcmp(frame.data, "exit")) break;
        frame.sequence_number = sequence_number;
        stop_and_wait_arq(&frame);
        sequence_number = 1 - sequence_number;
    }
    return 0;
}
