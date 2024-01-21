#pragma once

// System directories
#include <thread>
#include <mutex>
#include <vector>
#include <memory>

// Global constants
constexpr unsigned int STARTING_ODD_NUMBER_INDEX { 1U };
constexpr unsigned int PRIME_CANDIDATE_BATCH_SIZE { 1000U };

class Primes
{

	// Max value to look for prime numbers
	// 10^8 is equal to 2^26.575 (32 bits will suffice)
	const unsigned int MAX_RANGE;

	// Thread pool
	std::vector<std::unique_ptr<std::thread>> threads;

	// Shared index variable for primality testing
	// All possible prime numbers are of the form: 2k + 1
	unsigned int prime_candidate_index = STARTING_ODD_NUMBER_INDEX;
	std::mutex prime_candidate_index_lock;

	// Shared array list for found primes
	std::vector<unsigned int> found_primes_array_list;
	std::mutex found_primes_array_list_lock;

	// Shared total for sum of primes primes
	unsigned long long int sum_of_found_primes;
	std::mutex sum_of_found_primes_lock;

	// Helper functions
	std::shared_ptr<unsigned int> getPrimeCandidateBatch();
	void foundPrimesArrayListAppend(unsigned int);
	bool primalityTest(unsigned int);
	void findPrimes();

	public:

		// Constructor
		Primes(unsigned int, unsigned short int);

		// Getter/Setter functions
		std::vector<unsigned int>& getFoundPrimesArrayList();
		unsigned long long int getSumOfFoundPrimes();

};
