#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <iostream>

#define N (1<<30)
#define TRIALS 5

long count_bytes(uint8_t *data, long n, uint8_t target) {
  long count = 0;

  for (long i = 0; i < n; i++) {
    if (data[i] == target) {
      count += 1;
    }
  }

  return count;
}

int main(int argc, char *argv[]) {
	uint8_t data[N];
	uint8_t target = 13;

	auto start_time = std::chrono::steady_clock::now();
	long count;

	for(size_t trial = 0; trial < TRIALS; trial++) {
		count = count_bytes(data, N, target);
	}

	auto end_time = std::chrono::steady_clock::now();

  std::chrono::duration<double> diff = end_time - start_time;
	double seconds = diff.count() / TRIALS;

	std::cout << "Time per trial: " << seconds << " seconds, got " << count << " as the count.\n";
}
