#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <unistd.h>

#define N 5  // Number of philosophers

omp_lock_t forks[N];  // Locks for forks

void philosopher(int id) {
    int left = id;              // Left fork
    int right = (id + 1) % N;   // Right fork

    // Deadlock prevention: Last philosopher picks right fork first
    if (id == N - 1) {
        int temp = left;
        left = right;
        right = temp;
    }

    for (int i = 0; i < 3; i++) {  // Each philosopher eats 3 times
        printf("Philosopher %d is thinking...\n", id);
        sleep(1);

        // Pick up left fork
        omp_set_lock(&forks[left]);
        printf("Philosopher %d picked up left fork (%d)\n", id, left);

        // Pick up right fork
        omp_set_lock(&forks[right]);
        printf("Philosopher %d picked up right fork (%d) and is eating\n", id, right);
        
        sleep(2);  // Eating time

        // Put down right fork
        omp_unset_lock(&forks[right]);
        printf("Philosopher %d put down right fork (%d)\n", id, right);

        // Put down left fork
        omp_unset_lock(&forks[left]);
        printf("Philosopher %d put down left fork (%d) and is thinking again\n", id, left);
    }
}

int main() {
    // Initialize locks (forks)
    for (int i = 0; i < N; i++) {
        omp_init_lock(&forks[i]);
    }

    // Run philosophers in parallel
    #pragma omp parallel num_threads(N)
    {
        int id = omp_get_thread_num();
        philosopher(id);
    }

    // Destroy locks
    for (int i = 0; i < N; i++) {
        omp_destroy_lock(&forks[i]);
    }

    return 0;
}

