
# Programming Assignment 1

Since distributing an equal number of primes to each thread does not work efficiently due to larger numbers requiring more computations, I went for a batching approach. Each thread would access a shared index for the odd numbers given by (2k - 1), where k is the shared index. Given the batch size I chose, 1000 odd numbers would be given to a respective thread to all be tested for primality and added to a shared list. Dispatching a single prime number at a time created a bottleneck on the mutexes. This approach works because primes can only be odd except for two, which is hardcoded to be added if the range is greater than or equal to two. The program was experimentally tested with different batch sizes up to the maximum range of 10^8. Given the compilations options and build environment, the program consistently completed the maximum range within 11-16 seconds. 

## Authors

- [@gschiavodev](https://github.com/gschiavodev)

## Run Locally

To compile and run the program locally, either execute the makefile, open the visual studio project and compile in release mode, or manually compile the current state of the project with the commands below:

```bash
$ mkdir -p int
$ mkdir -p bin

$ g++ -I include -std=c++11 -static -O3 -c -o int/main.o src/main.cpp
$ g++ -I include -std=c++11 -static -O3 -c -o int/primes.o src/primes.cpp
$ g++ -I include -std=c++11 -static -static-libgcc -static-libstdc++ -O3 -o bin/primes int/main.o int/primes.o
```