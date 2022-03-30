
#include <algorithm>
#include <chrono>
#include <cmath>
#include <iterator>
#include <random>
#include <iostream>

template <typename TimeUnit, typename F>
typename TimeUnit::rep measure(F &&func)
{
	auto start = std::chrono::steady_clock::now();

	func();

	auto duration = std::chrono::duration_cast<TimeUnit>(std::chrono::steady_clock::now() - start);
	return duration.count();
}

struct XXX {
    alignas(64) uint64_t data[ITER];
};

int main()
{
    XXX *xxx = new XXX[NUM];

    for (size_t i = 0; i < NUM; i++) {
        for (size_t j = 0; j < ITER; j++) {
            xxx[i].data[j] = (i + 1) * (j + 23);
        }
    }

    size_t cnt = 0;
    std::cout << measure<std::chrono::nanoseconds>([&]{
        for (size_t i = 0; i < NUM; i++) {
            for (size_t j = 0; j < ITER; j++) {
                cnt += (xxx[i].data[j] == 11111);
            }
        }
    });

    free(xxx);
}
