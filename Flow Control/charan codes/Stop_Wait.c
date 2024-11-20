#include <stdio.h>
#include <stdlib.h>  // for rand()
#include <time.h>    // for time()
#include <unistd.h>  // for sleep()

#define TIMEOUT 1 // Timeout set to 1 second

// Structure to represent a frame
struct Frame {
    int sequence_number; // The sequence number of the frame
    char data[1024];     // The data of the frame (max size 1024)
};

// Function to simulate sending a frame
void send_frame(struct Frame *frame) {
    printf("Sending frame %d\n", frame->sequence_number);
}

// Function to simulate receiving an acknowledgment
int receive_ack(int sequence_number) {
    if (rand() % 10 < 5) { // Simulate a 50% chance of acknowledgment
        printf("Acknowledgment for frame %d\n", sequence_number);
        return 1; // Acknowledgment received
    }
    return 0; // No acknowledgment received
}

// Stop-and-Wait ARQ Protocol function
void stop_and_wait_arq(int frame_count) {
    struct Frame frame;
    for (int i = 0; i < frame_count; ++i) {
        frame.sequence_number = i;
        int ack_received = 0; // ACK flag

        while (!ack_received) {
            send_frame(&frame);
            sleep(TIMEOUT); // Wait for timeout
            if (receive_ack(frame.sequence_number)) {
                ack_received = 1; // If ACK received, move to the next frame
            } else {
                printf("Waiting...\n");
                printf("Resending frame %d\n", frame.sequence_number);
            }
        }
    }
}

int main() {
    int frame_count;
    printf("Enter the number of frames: ");
    scanf("%d", &frame_count);

    srand(time(0)); // Seed the random number generator
    stop_and_wait_arq(frame_count);

    printf("End of Stop and Wait protocol\n");
    return 0;
}
