#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <iostream>
#include <cstring>
#include <random>

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
	unsigned int seed = 1;
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-s") == 0 && i + 1 < argc) {
				seed = atoi(argv[i + 1]);
				i++;
		}
	}

	uint8_t data[N];
	uint8_t target = 17;
	std::mt19937_64 rng(seed);
	std::uniform_int_distribution<uint8_t> dist(0, UINT8_MAX);
	for (int i = 0; i < N; i++) {
			data[i] = dist(rng);
	}
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
