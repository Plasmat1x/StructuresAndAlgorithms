#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "Algorithms.h"

template<typename T>
void draw(T arr[], size_t size)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << i << " |";
    }
    std::cout << std::endl;
    for (int i = 0; i < size; i++)
    {
        std::cout << "--+";
    }
    std::cout << std::endl;
    for (int i = 0; i < size; i++)
    {
        std::cout << arr[i];
        if (arr[i] > 9)
        {
            std::cout << "|";
        }
        else
        {
            std::cout << " |";
        }
    }
    std::cout << std::endl;
}

template<typename T>
void generate(T arr[], size_t size, int range)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % range;
    }
}

int main()
{
    srand(time(NULL));
    
    const size_t size = 10;
    int* darr = new int[size];
    
    //---generate---
    generate(darr, size, 100);
    draw(darr, size);
    std::cout << std::endl;

    algo::sort::shell(darr, size, algo::add::ascending);

    //---draw---
    draw(darr, size);
    std::cout << std::endl;

    //---control---
    int search = 0;
    std::cin >> search;
    int resault = algo::search::binary(darr, size, search, algo::add::ascending);
    if (resault > -1)
    {
        std::cout << "searching index = " << resault << std::endl;
    }
    else
    {
        std::cout << "not found" << std::endl;
    }

    //---clear---
    delete[] darr;

    //---
    return 0;
}

