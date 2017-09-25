#include <iostream>
#include <vector>
#include <numeric>
#include <chrono>


const int OPERATIONS = 1000000000;


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
    std::chrono::duration<double> diff = end-start;
    std::cout << OPERATIONS << " operations take " << diff.count() << " seconds." << std::endl;
    return 0;
}
