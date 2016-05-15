// FuncTest.cpp : Defines the entry point for the console application.
//

#include "cached_function.hpp"
using namespace CachedFunction;

int fib(int n) {
	if (n < 2) return n;
	//return fib(n - 1) + fib(n - 2); // naieve recursive way, for reference
	return cached_function(fib, n - 1) + cached_function(fib, n - 2);
}

// same fibonacci function, but fully at compile time

template< size_t N >
struct compile_fib : std::integral_constant<size_t, compile_fib<N-1>::value + compile_fib<N-2>::value > {};

template<>
struct compile_fib<1> : std::integral_constant<size_t, 1> {};

template<>
struct compile_fib<2> : std::integral_constant<size_t, 1> {};

int main()
{
	printf("%i = %i\n", 44, compile_fib<44>::value);

	for (int i = 0; i < 45; ++i)
	{
		printf("%i = %i\n", i, fib(i));
	}
	system("PAUSE");
    return 0;
}

