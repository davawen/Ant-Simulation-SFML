#include "functions.h"

sf::Vector2f fromAngle(float angle, float magnitude)
{
    return sf::Vector2f(cos(angle) * magnitude, sin(angle) * magnitude);
}

int sqr(int value)
{
    return value * value;
}

float sqr(float value)
{
    return value * value;
}

#pragma region Random Functions

int randRange(int min, int max)
{
    int diff = max - min;

    return rand() % diff + min;
}

float randRange(float min, float max)
{
    float diff = (max - min);

    return (float)rand() / (float)RAND_MAX * diff + min;
}

float randGaussian(float stretch)
{
    float _r = randRange(-1.f, 1.f);

    return (1.f - _r * _r * _r - 1.f) * stretch;
}

#pragma endregion