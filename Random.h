//
// Created by jacob on 7/24/2021.
//

#pragma once
#include <random>

class Random {
    static std::mt19937 random;

public:
    static int Int(int min, int max);
    static float Float(float min, float max);
};



