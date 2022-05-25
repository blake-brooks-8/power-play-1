#include <iostream>
#include "helper.h"

void Helper::validateUserInput(int& response, int numberOfOptions)
{
	while (!std::cin.good() || response < 1 || response > numberOfOptions)
	{
		std::cout << "Error, please select a number between " << 1 << " and " << numberOfOptions << ": ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> response;
	}
}


Helper::Helper()
{
}

Helper::~Helper()
{
}