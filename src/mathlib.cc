#include "../headers/mathlib.hh"

int factorial(int n) {
    if (n < 0) {
        std::cerr << "can't compute negative factorials!!";
        return -1;
    }

    int res = 1;
    for (int i = 1; i <= n; ++i) {
        res *= i;
    }
}

int choose(int from, int count) {
    if (from < count or count < 0 or from < 0) {
        std::cerr << "can't calculate " << from << " choose " << count << "!\n";
        return -1;
    }   
    return factorial(from)/(factorial(count)*factorial(from-count));
}