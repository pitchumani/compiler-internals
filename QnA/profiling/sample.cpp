#include <iostream>
#include <vector>
#include <algorithm>

void expensive_calculation_1() {
    std::vector<int> data(1000000);
    std::generate(data.begin(), data.end(), [](){ return rand() % 1000; });
    std::sort(data.begin(), data.end());
}

void expensive_calculation_2() {
    double sum = 0.0;
    for (int i = 0; i < 50000000; ++i) {
        sum += std::sqrt(i);
    }
}

int main() {
    std::cout << "Starting profiling example...\n";
    expensive_calculation_1();
    expensive_calculation_2();
    expensive_calculation_1(); // Call it again to see its cumulative effect
    std::cout << "Profiling example finished.\n";
    return 0;
}

