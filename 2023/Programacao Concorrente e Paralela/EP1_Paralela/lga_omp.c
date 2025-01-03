#include "lga_base.h"
#include "lga_omp.h"
#include <omp.h>
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

static void update(byte *grid_in, byte *grid_out, int grid_size,int l, int h) {
    for (int i = l; i < h; i++) {
        for (int j = 0; j < grid_size; j++) {
            if (grid_in[ind2d(i,j)] == WALL)
                grid_out[ind2d(i,j)] = WALL;
            else
                grid_out[ind2d(i,j)] = get_next_cell(i, j, grid_in, grid_size);
        }
    }
}

static void updateomp(byte *grid_1, byte *grid_2, int grid_size, int num_threads) {
    int thread_chunk = grid_size / num_threads;
    int l, h;
    #pragma omp parallel for num_threads(num_threads)
    for (int i = 0; i < num_threads; i++) {
        l = i * thread_chunk;
        h = i * thread_chunk + thread_chunk;
        update(grid_1, grid_2, grid_size, l, h);
    }
}



void simulate_omp(byte *grid_1, byte *grid_2, int grid_size, int num_threads) {
    for (int i = 0; i < ITERATIONS/2; i++) {
        updateomp(grid_1, grid_2, grid_size,num_threads);
        updateomp(grid_2, grid_1, grid_size,num_threads);
    }
}