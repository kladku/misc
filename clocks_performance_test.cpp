#include <chrono>
#include <iostream>
#include <time.h>
using namespace std;

constexpr int iters = 10000000;
typedef chrono::duration<double> dsecs;

int main()
{
    auto start = chrono::steady_clock::now();
    for (int i = 0; i < iters; i++)
        chrono::steady_clock::now();
    auto end = chrono::steady_clock::now();

    std::cout << "steady_clock::now(): " << 1e6 * chrono::duration_cast<dsecs>(end-start).count() / iters << "µs per iteration\n";

    start = chrono::steady_clock::now();
    for (int i = 0; i < iters; i++)
        chrono::high_resolution_clock::now();
    end = chrono::steady_clock::now();

    std::cout << "high_resolution_clock: " << 1e6 * chrono::duration_cast<dsecs>(end-start).count() / iters << "µs per iteration\n";

    start = chrono::steady_clock::now();
    timespec ts;
    for (int i = 0; i < iters; i++)
        clock_gettime(CLOCK_MONOTONIC, &ts);
    end = chrono::steady_clock::now();

    std::cout << "clock_gettime: " << 1e6 * chrono::duration_cast<dsecs>(end-start).count() / iters << "µs per iteration\n";
}
