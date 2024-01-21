
// System directories
#include <algorithm>

// Program directories
#include "primes.h"

// Determine primes within max range and append to prime array list
Primes::Primes(unsigned int max_range, unsigned short int n_extra_threads) : MAX_RANGE(max_range), sum_of_found_primes(0)
{
	

	// Check to append the only even prime
	if (max_range >= 2) foundPrimesArrayListAppend(2);

	// Spawn n extra threads to find primes
	for (size_t i = 0; i < n_extra_threads; i++)
	{

		// Create thread
		std::thread* thread = new std::thread(&Primes::findPrimes, this);

		// Store thread in thread pool
		threads.push_back(std::unique_ptr<std::thread>(thread));

	}
	
	findPrimes(); // Main thread!

	// Wait for all the extra threads to finish
	for (size_t i = 0; i < n_extra_threads; i++)
		if (threads.at(i)->joinable())
			threads.at(i)->join();
	
	// Theoretically already sorted, but sort the primes
	std::sort(found_primes_array_list.begin(), found_primes_array_list.end());

}

std::vector<unsigned int>& Primes::getFoundPrimesArrayList()
{

	return found_primes_array_list;

}

unsigned long long int Primes::getSumOfFoundPrimes()
{

	return sum_of_found_primes;

}

// Get  prime candidate packet of the form: 2k + 1
std::shared_ptr<unsigned int> Primes::getPrimeCandidateBatch()
{

	// Initialize return value
	std::shared_ptr<unsigned int> prime_candidate_batch = nullptr;

	prime_candidate_index_lock.lock();

	{

		try 
		{

			// Allocate batch to be returned
			prime_candidate_batch = std::shared_ptr<unsigned int>(new unsigned int[PRIME_CANDIDATE_BATCH_SIZE]);

			// Populate batch with prime candidates
			for (size_t i = 0; i < PRIME_CANDIDATE_BATCH_SIZE; i++)
			{

				unsigned int prime_candidate = (2 * prime_candidate_index) + 1;
				prime_candidate_batch.get()[i] = prime_candidate;
				prime_candidate_index++;

			}

		}
		catch (std::exception &e)
		{

		};

	}

	prime_candidate_index_lock.unlock();

	return prime_candidate_batch;

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
	unsigned int k = STARTING_ODD_NUMBER_INDEX;
	unsigned int odd_number = (2 * k) + 1;

	// Check all prime factors up to the square root of the prime candidate
	unsigned int prime_candidate_square_root = std::sqrt(prime_candidate);
	while (odd_number <= prime_candidate_square_root)
	{

		if ((prime_candidate % odd_number) == 0)
			return false;

		k++;
		odd_number = (2 * k) + 1;

	}

	// Its prime!
	return true;

}

// Called function for all threads
void Primes::findPrimes() 
{
	
	// Break condition
	bool max_range_exceeded = false;

	// Find primes!
	while (!max_range_exceeded)
	{

		// Get batch of prime candidates to test
		std::shared_ptr<unsigned int> prime_candidate_batch = getPrimeCandidateBatch();

		for (size_t i = 0; i < PRIME_CANDIDATE_BATCH_SIZE; i++)
		{

			// Get the ith prime candidate
			unsigned prime_candidate = prime_candidate_batch.get()[i];

			// Check if candidate exceeds search range
			if (prime_candidate > MAX_RANGE)
			{

				// Proceeding candidates also exceed..
				max_range_exceeded = true;
				break;

			}

			// The prime test!
			if (primalityTest(prime_candidate))
				foundPrimesArrayListAppend(prime_candidate);

		}

	}

}
