//Jacob Boney
//COP 3503
//Project 03

#pragma once
#include <random>

class Random {
    static std::mt19937 random;

public:
    static int Int(int min, int max);
    static float Float(float min, float max);
};



