#pragma once
#include <iostream>

enum Direction
{
    LEFT = 0,
    CENTER = 1,
    RIGHT = 2
};

class DirectionSystem
{
public:
    static Direction PlayerShootDirection();
    static Direction PlayerDefenceDirection();
};