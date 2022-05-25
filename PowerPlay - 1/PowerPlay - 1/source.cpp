// PowerPlay - 1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<random>
#include <string>
#include <vector>
#include "helper.h"


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
void monsterTurn(Creature& player, std::vector<Creature> monsters);
void playerTurn(Creature &player, std::vector<Creature>& monsters);
bool canHit();
void displayCreatureName(Creature creature);
void attack(Creature& attacker, Creature& defender);
void playerAttack(Creature &player, std::vector<Creature> &monsters);

int main()
{

    Creature player{
        "Hrothgar",
        getRandomNormalNumber(MEAN, STANDARD_DEVIATION),
        getRandomNormalNumber(MEAN, STANDARD_DEVIATION)
    };

    std::vector<Creature> monsters;

    spawnMonsters(monsters);
    
    while (false)
    {
        playerTurn(player, monsters);

        monsterTurn(player, monsters);

        //display all monster's name and health'

        //prompt the user to heal or attack
    }

}

void playerTurn(Creature &player, std::vector<Creature> &monsters)
{
    displayCreatureName(player);

    std::cout << "Would you like to: \n";
    std::cout << "1. Attack\n";
    std::cout << "2. Heal\n";

    int response{ 0 };
    std::cin >> response;

    Helper::validateUserInput(response, 2);

    switch (response)
    {
    case 1:
        playerAttack(player, monsters);
        break;
    case 2:
        //heal();
        break;
    default:
        break;
    }
}

void playerAttack(Creature &player, std::vector<Creature> &monsters)
{

}

void displayCreatureName(Creature creature)
{
    std::cout << creature.name;
}

void attack(Creature &attacker, Creature &defender)
{
    defender.health -= attacker.strength;
}

void monsterTurn(Creature &player, std::vector<Creature> monsters)
{
    for (Creature monster : monsters)
    {
        if (canHit())
        {
            attack(monster, player);
        }
        if (player.health < 1)
        {
            //gameOver();
            return;
        }
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

bool canHit()
{
    std::random_device device;
    std::mt19937 generator(device());
    std::bernoulli_distribution distribution(0.75);
    bool outcome = distribution(generator);

    return outcome;
}