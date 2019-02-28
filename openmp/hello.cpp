#include <iostream>
#include <string>

int main()
{
#pragma omp parallel
	{
	std::cout << "Hello, World!\n";
	}
	system("pause"); // <----------------------------------
	return 0;
}