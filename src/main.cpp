
// System directories
#include <iostream>
#include <chrono>
#include <cmath>

// Program directories
#include "primes.h"

// Constants
constexpr unsigned short int N_EXTRA_THREADS { 7U };
const unsigned int RANGE_MAX { static_cast<unsigned int>(std::pow(10, 8)) };

int main()
{

	// Process execution start time
	auto start_time = std::chrono::high_resolution_clock::now();

	// Multithreaded object that stores all primes within a given range
	Primes prime_numbers(RANGE_MAX, N_EXTRA_THREADS);

	// Process execution time
	auto end_time = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);

	// Get primes list and their sum
	std::vector<unsigned int>& found_primes_array_list = prime_numbers.getFoundPrimesArrayList();
	unsigned long long int sum_of_found_primes = prime_numbers.getSumOfFoundPrimes();

	// Prompt: <execution time> <total number of primes found> <sum of all primes found>
	std::cout << duration.count() << " " << found_primes_array_list.size() << " " << sum_of_found_primes << std::endl;

	// ..


	// Exit
	return 0;

}
