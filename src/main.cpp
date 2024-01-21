
// System directories
#include <iostream>
#include <chrono>
#include <cmath>

// Program directories
#include "primes.h"

// Global constants
constexpr unsigned short int N_EXTRA_THREADS { 7U };
const unsigned int MAX_RANGE { static_cast<unsigned int>(std::pow(10, 8)) };

int main()
{

	// Process execution start time
	auto start_time = std::chrono::high_resolution_clock::now();

	// Multithreaded object that stores all primes within a given range
	Primes prime_numbers(MAX_RANGE, N_EXTRA_THREADS);

	// Process execution time
	auto end_time = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

	// Get primes list and their sum
	std::vector<unsigned int>& found_primes_array_list = prime_numbers.getFoundPrimesArrayList();
	unsigned long long int sum_of_found_primes = prime_numbers.getSumOfFoundPrimes();

	// Prompt: <execution time> <total number of primes found> <sum of all primes found>
	std::cout << (static_cast<double>(duration.count()) / 1000) << "s " << found_primes_array_list.size() << " " << sum_of_found_primes << std::endl;

	// Prompt <top ten maximum primes, listed in order from lowest to highest>
	long int found_primes_array_list_size = found_primes_array_list.size();
	for (long int i = std::max(0L, found_primes_array_list_size - 10); i < found_primes_array_list_size; i++)
		std::cout << found_primes_array_list.at(i) << " ";

	// Exit
	std::cout << std::endl;
	return 0;

}
