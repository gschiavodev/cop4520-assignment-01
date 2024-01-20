
// System directories
#include <thread>

// Program directories
#include "primes.h"

// Determine primes within max range and append to prime array list
Primes::Primes(double max_range, unsigned short int n_extra_threads) : max_range(max_range)
{
	
	// Append primes less than 5 if necessary
	if (max_range >= 3) foundPrimesArrayListAppend(3);
	if (max_range >= 2) foundPrimesArrayListAppend(2);

	// Spawn n extra threads to find primes
	for (size_t i = 0; i < n_extra_threads; i++)
		threads.push_back(std::thread(&Primes::findPrimes, this));
	
	findPrimes(); // Main thread!

	// Wait for all the extra threads to finish
	for (size_t i = 0; i < n_extra_threads; i++)
		threads.at(i).join();

}

std::vector<unsigned int>& Primes::getFoundPrimesArrayList()
{

	return found_primes_array_list;

}

// Get next prime candidate of the form: 6k - 1
unsigned int Primes::nextPrimeCandidate()
{

	// Initialize with an error value
	unsigned int next_prime_candidate = 0;

	prime_candidate_index_lock.lock();

	{

		try {

			next_prime_candidate = (6 * prime_candidate_index) - 1;
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

	{

		try {
			
			found_primes_array_list.push_back(prime);

		}
		catch (std::exception &e)
		{

		};

	}

	found_primes_array_list_lock.unlock();

}

// Test if a given integer is prime
bool Primes::primalityTest(unsigned int prime_candidate)
{

	// Initial prime factor
	unsigned int k = 1;
	unsigned int prime_factor = (6 * k) - 1;

	// Test with primes less than 5
	if ((prime_candidate % 2) == 0) return false;
	if ((prime_candidate % 3) == 0) return false;

	// Test if candidate is not prime
	while (prime_factor < prime_candidate)
	{

		if ((prime_candidate % prime_factor) == 0) return false;

		k++;
		prime_factor = (6 * k) - 1;

	}
	
	// Its prime!
	return true;

}

// TODO!
void Primes::findPrimes() 
{
	
	

}
