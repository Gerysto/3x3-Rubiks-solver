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
    return res;
}

int choose(int from, int count) {
    if (from < count or count < 0 or from < 0) {
        std::cerr << "can't calculate " << from << " choose " << count << "!\n";
        return -1;
    }   
    return factorial(from)/(factorial(count)*factorial(from-count));
}

bool binarySearch(const std::vector<int>& v, int target) {
    int left = 0;
    int right = v.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;  // avoid overflow
        if (v[mid] == target) {
            return true; // found
        } else if (v[mid] < target) {
            left = mid + 1; // search right half
        } else {
            right = mid - 1; // search left half
        }
    }
    return false; // not found
}