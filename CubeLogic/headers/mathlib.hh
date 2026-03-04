#include <iostream>
#include <vector>

/**
 * Returns the binomial coeficient 
 * Can be read as 'from' choose 'count'
 */ 
int choose(int from, int count);

/*
 * Returns the factorial of n
 */
int factorial(int n);

/**
 * Checks whether or not the target is somewhatre in the vector 'v'
 */
bool binarySearch(const std::vector<int>& v, int target);