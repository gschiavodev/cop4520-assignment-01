
// System directories
#include <iostream>
#include <cmath>

// Program directories
#include "primes.h"

// Constants
constexpr unsigned short int N_EXTRA_THREADS { 7 };
const double RANGE_MAX { std::pow(10, 8) };

int main()
{

	// Multithreaded object that stores all primes within a given range
	Primes prime_numbers(RANGE_MAX, N_EXTRA_THREADS);

	#ifdef _DEBUG
		std::cout << prime_numbers.getFoundPrimesArrayList().size() << std::endl;
	#endif

	return 0;

}
