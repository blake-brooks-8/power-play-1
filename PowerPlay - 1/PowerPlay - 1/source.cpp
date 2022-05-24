// PowerPlay - 1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<random>
#include <string>
#include <vector>


struct Creature
{
    std::string name;
    int strength{ 0 };
    int health{ 0 };
};

const int MEAN = 30;
const int STANDARD_DEVIATION = 5;
const int MIN = 1;
const int MAX = 3;

int getRandomUniformNumber(int min, int max);
int getRandomNormalNumber(int mean, int standardDeviation);
void spawnMonsters(std::vector<Creature> &monsterVector);
void monsterTurn(std::vector<Creature> monsters);
void playerTurn(std::vector<Creature>& monsters);
bool checkForHit();

int main()
{

    Creature Player{
        "Hrothgar",
        getRandomNormalNumber(MEAN, STANDARD_DEVIATION),
        getRandomNormalNumber(MEAN, STANDARD_DEVIATION)
    };

    std::vector<Creature> monsters;

    spawnMonsters(monsters);

    std::cout << checkForHit();
    
    while (false)
    {
        //display player name

        //display all monster's name and health'

        //prompt the user to heal or attack
    }

}

void playerTurn(std::vector<Creature> &monsters)
{

}

void monsterTurn(std::vector<Creature> monsters)
{
    for (Creature monster : monsters)
    {
        //attempt attack 
    }
}

void spawnMonsters(std::vector<Creature> &monsterVector)
{
    int numberOfMonsters{ getRandomUniformNumber(MIN, MAX)};

    for (int i = 0; i < numberOfMonsters; i++)
    {
        Creature Monster{
            "Monster" + (i + 1),
            getRandomNormalNumber(MEAN, STANDARD_DEVIATION),
            getRandomNormalNumber(MEAN, STANDARD_DEVIATION)
        };

        monsterVector.push_back(Monster);
    }

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

    int result{ (int)normalDistributionNumber(e) };

    if (result < 1)
    {
        return 1;
    }
    else
    {
        return result;
    }
}

bool checkForHit()
{
    std::random_device device;
    std::mt19937 generator(device());
    std::bernoulli_distribution distribution(0.75);
    bool outcome = distribution(generator);

    return outcome;
}