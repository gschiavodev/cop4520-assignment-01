#pragma once

// System directories
#include <mutex>
#include <vector>

// Constants
constexpr unsigned short int FIRST_PRIME_CANDIDATE_INDEX { 1 };

class Primes
{

	// Thread pool
	std::vector<std::thread> threads;

	// Max value to look for prime numbers
	// 10^8 is equal to 2^26.575 (32 bits will suffice)
	unsigned int max_range;
	
	// Shared index variable for primality testing
	// All possible prime numbers are of the form: 6k - 1
	unsigned int prime_candidate_index = FIRST_PRIME_CANDIDATE_INDEX;
	std::mutex prime_candidate_index_lock;

	// Shared array list for found primes
	std::vector<unsigned int> found_primes_array_list;
	std::mutex found_primes_array_list_lock;

	// Helper functions
	unsigned int nextPrimeCandidate();
	void foundPrimesArrayListAppend(unsigned int);
	bool primalityTest(unsigned int);
	void findPrimes();

	public:

		// Constructor
		Primes(double , unsigned short int);

		// Getter/Setter functions
		std::vector<unsigned int>& getFoundPrimesArrayList();

};
