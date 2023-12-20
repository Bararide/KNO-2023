#include <iostream>
#include <boost/config.hpp>

using namespace boost;

#define API extern "C" BOOST_SYMBOL_EXPORT

API int myFunction(int arg1);
API int factorial(int arg1);
API int input();
API std::string instr();
API int fibonacci(int n);