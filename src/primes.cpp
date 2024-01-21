
// System directories
#include <thread>
#include <cmath>

// Program directories
#include "primes.h"

// Determine primes within max range and append to prime array list
Primes::Primes(unsigned int max_range, unsigned short int n_extra_threads) : max_range(max_range), sum_of_found_primes(0)
{
	
	// Check to append the only even prime
	if (max_range >= 2) foundPrimesArrayListAppend(2);

	// Spawn n extra threads to find primes
	for (size_t i = 0; i < n_extra_threads; i++)
		threads.push_back(std::thread(&Primes::findPrimes, this));
	
	findPrimes(); // Main thread!

	// Wait for all the extra threads to finish
	for (size_t i = 0; i < n_extra_threads; i++)
		if (threads.at(i).joinable())
			threads.at(i).join();

}

std::vector<unsigned int>& Primes::getFoundPrimesArrayList()
{

	return found_primes_array_list;

}

unsigned long long int Primes::getSumOfFoundPrimes()
{

	return sum_of_found_primes;

}

// Get next prime candidate of the form: 2k + 1
unsigned int Primes::getNextPrimeCandidate()
{

	// Initialize with an error value
	unsigned int next_prime_candidate = 0;

	prime_candidate_index_lock.lock();

	{

		try 
		{

			next_prime_candidate = (2 * prime_candidate_index) + 1;
			prime_candidate_index++;

		}
		catch (std::exception &e)
		{

		};

	}

	prime_candidate_index_lock.unlock();

	return next_prime_candidate;

}

// A thread safe append for the primes list
void Primes::foundPrimesArrayListAppend(unsigned int prime)
{

	found_primes_array_list_lock.lock();
	sum_of_found_primes_lock.lock();

	{

		try {
			
			found_primes_array_list.push_back(prime);
			sum_of_found_primes += prime;

		}
		catch (std::exception &e)
		{

		};

	}

	found_primes_array_list_lock.unlock();
	sum_of_found_primes_lock.unlock();

}

// Test if a given integer is prime
bool Primes::primalityTest(unsigned int prime_candidate)
{

	// Initial prime factor
	unsigned int k = FIRST_PRIME_CANDIDATE_INDEX;
	unsigned int prime_factor = (2 * k) + 1;

	// Test if candidate is divisable by 2
	if ((prime_candidate % 2) == 0) return false;

	// Check all prime factors up to the square root of the prime candidate
	unsigned int prime_candidate_square_root = std::sqrt(prime_candidate);
	while (prime_factor <= prime_candidate_square_root)
	{

		if ((prime_candidate % prime_factor) == 0)
			return false;

		k++;
		prime_factor = (2 * k) + 1;

	}

	// Its prime!
	return true;

}

// Called function for all threads
void Primes::findPrimes() 
{
	
	// Candidate to be tested
	unsigned int prime_candidate;

	// Find primes until max range is reached
	while ((prime_candidate = getNextPrimeCandidate()) <= max_range)
	{

		// The prime test!
		if (primalityTest(prime_candidate)) 
			foundPrimesArrayListAppend(prime_candidate);

	}

}
