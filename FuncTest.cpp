// FuncTest.cpp : Defines the entry point for the console application.
//

#include "cached_function.hpp"
using namespace CachedFunction;

int fib(int n) {
	if (n < 2) return n;
	//return fib(n - 1) + fib(n - 2); // naieve recursive way, for reference
	return cached_function<decltype(&fib),fib>(n - 1) + cached_function<decltype(&fib),fib>(n - 2);
}

int main()
{
	for (int i = 0; i < 45; ++i)
	{
		printf("%i = %i\n", i, fib(i));
	}
  return 0;
}

