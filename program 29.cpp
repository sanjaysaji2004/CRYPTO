#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LANE_SIZE 64
#define NUM_LANES 16 

void initialize_state(unsigned long long state[NUM_LANES], int zero_lanes[NUM_LANES]) {
    for (int i = 0; i < NUM_LANES; i++) {
        state[i] = 0;
        zero_lanes[i] = 1; 
    }
}

void input_message(unsigned long long state[NUM_LANES]) {
    for (int i = 0; i < NUM_LANES; i++) {
        state[i] = rand() | (1ULL << (rand() % LANE_SIZE)); 
    }
}

int count_zero_lanes(unsigned long long state[NUM_LANES], int zero_lanes[NUM_LANES]) {
    int count = 0;
    for (int i = 0; i < NUM_LANES; i++) {
        if (zero_lanes[i] && state[i] == 0) {
            count++;
        }
    }
    return count;
}

void process_block(unsigned long long state[NUM_LANES]) {
    for (int i = 0; i < NUM_LANES; i++) {
        state[i] ^= rand(); 
    }
}

void update_zero_lanes(unsigned long long state[NUM_LANES], int zero_lanes[NUM_LANES]) {
    for (int i = 0; i < NUM_LANES; i++) {
        if (zero_lanes[i] && state[i] != 0) {
            zero_lanes[i] = 0;
        }
    }
}

int main() {
    srand(time(NULL));

    unsigned long long state[NUM_LANES];
    int zero_lanes[NUM_LANES];
    int iterations = 0;

    initialize_state(state, zero_lanes);

    input_message(state);

    int zero_lane_count = count_zero_lanes(state, zero_lanes);

    while (zero_lane_count > 0) {
        process_block(state);
        update_zero_lanes(state, zero_lanes);
        zero_lane_count = count_zero_lanes(state, zero_lanes);
        iterations++;
    }

    printf("Number of iterations until all initially zero lanes have at least one nonzero bit: %d\n", iterations);

    return 0;
}
