// FuncTest.cpp : Defines the entry point for the console application.
//

#include <map>
#include <tuple>

// http://stackoverflow.com/questions/28509273/get-types-of-function-parameters
//#include <boost/function_types/function_type.hpp>
//#include <boost/function_types/parameter_types.hpp>
#include <boost/function_types/result_type.hpp>

template <typename FuncType>
using ResultType = typename boost::function_types::result_type<FuncType>::type;

// based on http://madebyevan.com/obscure-cpp-features/ but extended to not hardcode the return and parameter types

template <class FuncType, FuncType functionPointer, class ... ArgTypes>
ResultType<FuncType> memoize(ArgTypes ... arguments) {
	// a tuple type to map all our function's parameters to the return type
	using ArgumentTupleType = std::tuple<ArgTypes...>;
	ArgumentTupleType parameters = std::make_tuple(arguments...);
	static std::map< ArgumentTupleType, ResultType<FuncType> > cache;
	auto cacheIterator = cache.find(parameters);
	if (cacheIterator != cache.end()) return cacheIterator->second;
	return cache[parameters] = functionPointer(arguments...);
}

int fib(int n) {
	if (n < 2) return n;
	return memoize<decltype(&fib), fib>(n - 1) + memoize<decltype(&fib), fib>(n - 2);
}

int main()
{
	for (int i = 0; i < 45; ++i)
	{
		printf("%i = %i\n", i, fib(i));
	}
	system("PAUSE");
    return 0;
}

