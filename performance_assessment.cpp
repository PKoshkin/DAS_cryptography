#include <iostream>
#include <chrono>


const int OPERATIONS = 1000000000;
const int COMPUTERS = 1;


int main() {
    int x = 1;
    int y = 2;

    // record start time
    auto start = std::chrono::system_clock::now();

    // do some work
    for (int i = 0; i < OPERATIONS; ++i) {
        int z = x + y;
    }

    // record end time
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = end - start;
    double double_diff = diff.count();
    std::cout << 365 * 24 * 60 * 60 * COMPUTERS * (double(OPERATIONS) / double_diff) << " operations per year." << std::endl;
    return 0;
}
