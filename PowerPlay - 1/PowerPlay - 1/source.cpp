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
void monsterTurn(Creature& player, std::vector<Creature> &monsters);
void playerTurn(Creature &player, std::vector<Creature>& monsters);
bool canHit();
void displayCreatureDetails(Creature creature);
void attack(Creature& attacker, Creature& defender);
void playerAttack(Creature &player, std::vector<Creature> &monsters);
void validateUserInput(int &response, int numberOfOptions);
void heal(Creature& player);
void gameOver(std::string name);
bool checkForWinner(std::vector<Creature> monsters);

int main()
{

    Creature player{
        "Hrothgar",
        getRandomNormalNumber(MEAN, STANDARD_DEVIATION),
        getRandomNormalNumber(MEAN, STANDARD_DEVIATION)
    };

    std::vector<Creature> monsters;

    spawnMonsters(monsters);
    
    while (true)
    {
        playerTurn(player, monsters);

        monsterTurn(player, monsters);

    }

}

void playerTurn(Creature &player, std::vector<Creature> &monsters)
{
    displayCreatureDetails(player);

    std::cout << "Would you like to: \n";
    std::cout << "1. Attack\n";
    std::cout << "2. Heal\n";

    int response{ 0 };
    std::cin >> response;

    validateUserInput(response, 2);

    switch (response)
    {
    case 1:
        playerAttack(player, monsters);
        break;
    case 2:
        heal(player);
        break;
    default:
        break;
    }
}

void heal(Creature& player)
{
    player.health += (player.strength * 2);
}

void playerAttack(Creature &player, std::vector<Creature> &monsters)
{
    std::cout << "Which monster would you like to attack: \n";
    int size = monsters.size();
    for (int i = 0; i < size; i++)
    {
        if (monsters[i].health < 1)
        {
            std::cout << i + 1 << ". " << monsters[i].name << ", " << "<DEAD>";
        }
        else
        {
            std::cout << i + 1 << ". " << monsters[i].name << ", " << "Health: " << monsters[i].health << '\n';

        }
    }

    int response{ 0 };
    std::cin >> response;

    validateUserInput(response, monsters.size());
    
    Creature currentMonster = monsters[response - 1];
    
    if (currentMonster.health > 1)
    {
        attack(player, monsters[response - 1]);
        if (checkForWinner(monsters))
        {
            gameOver(player.name);
        }
    }
    else
    {
        std::cout << "That monster is dead. Try again. ";
        playerAttack(player, monsters);
    }
}

bool checkForWinner(std::vector<Creature> monsters)
{
    for (Creature monster : monsters)
    {
        if (monster.health > 1)
        {
            return false;
        }
    }

    return true;
}

void gameOver(std::string name)
{
    if (name != "Hrothgar")
    {
        std::cout << "You lose!";
    }
    else
    {
        std::cout << "You win!";
    }

    exit(0);
}

void displayCreatureDetails(Creature creature)
{
    std::cout << "Name: " << creature.name << '\n';
    if (creature.health < 1)
    {
        std::cout << "<DEAD>\n";
    }
    else
    {
        std::cout << "Health: " << creature.health << '\n';
    }
}

void attack(Creature &attacker, Creature &defender)
{
    defender.health -= attacker.strength;
}

void monsterTurn(Creature &player, std::vector<Creature> &monsters)
{
    for (Creature monster : monsters)
    {
        if (monster.health < 1)
        {
            continue;
        }
        if (canHit())
        {
            attack(monster, player);
        }
        if (player.health < 1)
        {
            gameOver("Monsters");
            return;
        }
    }
}

void spawnMonsters(std::vector<Creature> &monsterVector)
{
    int numberOfMonsters{ getRandomUniformNumber(MIN, MAX)};
    std::string monsterString{ "Monster" };

    for (int i = 0; i < numberOfMonsters; i++)
    {
        int currentNumber{ i + 1 };
        Creature Monster{
            monsterString + std::to_string(currentNumber),
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

void validateUserInput(int& response, int numberOfOptions)
{
    while (!std::cin.good() || response < 1 || response > numberOfOptions)
    {
        std::cout << "Error, please select a number between " << 1 << " and " << numberOfOptions << ": ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> response;
    }
}