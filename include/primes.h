#pragma once

// System directories
#include <mutex>

// Constants
#define FIRST_PRIME 2

class Primes
{

	// Max value to look for prime numbers
	long long int max_range;
	
	// Shared counter variable for primality testing
	long long int prime_candidate;
	std::mutex lock;

	// Constructors
	Primes(long long int);

};

