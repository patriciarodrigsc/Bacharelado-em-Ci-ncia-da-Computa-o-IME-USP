#include "lga_base.h"
#include "lga_pth.h"
#include <pthread.h>
#include "pthread_barrier.h"

typedef struct {
    int start;
    int end;
    int grid_size;
    byte *grid_in;  
    byte *grid_out;  
} threadArguments;

pthread_barrier_t barrier;

static byte get_next_cell(int i, int j, byte *grid_in, int grid_size) {
    byte next_cell = EMPTY;

    for (int dir = 0; dir < NUM_DIRECTIONS; dir++) {
        int rev_dir = (dir + NUM_DIRECTIONS/2) % NUM_DIRECTIONS;
        byte rev_dir_mask = 0x01 << rev_dir;

        int di = directions[i%2][dir][0];
        int dj = directions[i%2][dir][1];
        int n_i = i + di;
        int n_j = j + dj;

        if (inbounds(n_i, n_j, grid_size)) {
            if (grid_in[ind2d(n_i,n_j)] == WALL) {
                next_cell |= from_wall_collision(i, j, grid_in, grid_size, dir);
            }
            else if (grid_in[ind2d(n_i, n_j)] & rev_dir_mask) {
                next_cell |= rev_dir_mask;
            }
        }
    }

    return check_particles_collision(next_cell);
}

static void update(byte *grid_in, byte *grid_out, int grid_size, int start, int end) {
    for (int i = start; i < end; i++) {
        for (int j = 0; j < grid_size; j++) {
            if (grid_in[ind2d(i,j)] == WALL)
                grid_out[ind2d(i,j)] = WALL;
            else
                grid_out[ind2d(i,j)] = get_next_cell(i, j, grid_in, grid_size);
        }
    }
    pthread_barrier_wait(&barrier);
}

static void *update_pth(void * argument){
    threadArguments *threadArgs = (threadArguments *)argument;
    update(threadArgs->grid_in, threadArgs->grid_out, threadArgs->grid_size, threadArgs->start, threadArgs->end);
    pthread_exit(NULL);
}

void simulate_pth(byte *grid_in, byte *grid_out, int grid_size, int num_threads) {
    pthread_barrier_init(&barrier, NULL, num_threads);
    pthread_t threads[num_threads];
    threadArguments args[num_threads];
    
    int chunk_size = grid_size / num_threads;

    for (int j = 0; j < ITERATIONS; j++) {
        for(int i = 0; i < num_threads; i++) {
            args[i].grid_in = (j % 2 == 0) ? grid_in : grid_out;
            args[i].grid_out = (j % 2 == 0) ? grid_out : grid_in;
            args[i].grid_size = grid_size;
            args[i].start = i * chunk_size;
            args[i].end = (i + 1) * chunk_size;
            pthread_create(&threads[i], NULL, update_pth, (void*)&args[i]);
        }

        for (int i = 0; i < num_threads; i++) {
            pthread_join(threads[i], NULL);
        }
    }

    pthread_barrier_destroy(&barrier);
}