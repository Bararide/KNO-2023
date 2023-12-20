#include "lib.hpp"

API int myFunction(int arg1) 
{
    std::cout << "Вызвана функция myFunction с аргументами: " << std::endl;
    return arg1;
};

API int factorial(int arg1) 
{
  int result = 1;
  for (int i = 1; i <= arg1; ++i) 
  {
    result *= i;
  }
  return result;
}

API int input() 
{
	int result;
	std::cout << "Введите число" << std::endl;
	std::cin >> result;
	return result;
}

API std::string instr()
{
  std::string result;
  std::cout << "Введите строку" << std::endl;
  std::cin >> result;
  return result;
}

API int fibonacci(int n) 
{
    if (n <= 1)
        return n;
    else
        return fibonacci(n - 1) + fibonacci(n - 2);
}
