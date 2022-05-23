// PowerPlay - 1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<random>

int getRandomUniformNumber(int min, int max);
int getRandomNormalNumber(int mean, int standardDeviation);

struct Object
{
    std::string name;
    int strength{ 0 };
    int health{ 0 };
};

int main()
{
    std::cout << getRandomNormalNumber(30,5) << std::endl;
    std::cout << getRandomUniformNumber(1,3);
}

int getRandomUniformNumber(int min, int max)
{
    std::random_device rdev; //seed
    std::default_random_engine e(rdev()); //engine
    std::uniform_int_distribution<int> uniformDistributionNumber(min, max);

    int result{ uniformDistributionNumber(e)};

    if (result < 1)
    {
        return 1;
    }
    else
    {
        return result;
    }

}

int getRandomNormalNumber(int mean, int standardDeviation)
{
    std::random_device rdev; //seed
    std::default_random_engine e(rdev()); //engine
    std::normal_distribution<double> normalDistributionNumber(mean, standardDeviation); //mean, standard deviation

    int result{ normalDistributionNumber(e) };

    if (result < 1)
    {
        return 1;
    }
    else
    {
        return result;
    }
}