#include "functions.hpp"

sf::Vector2f fromAngle(float angle, float magnitude)
{
    return sf::Vector2f(cos(angle) * magnitude, sin(angle) * magnitude);
}

sf::Vector2f cWiseMultiplication(sf::Vector2f v1, sf::Vector2f v2)
{
    return sf::Vector2f(v1.x * v2.x, v1.y * v2.y);
}

sf::Vector2f cWiseDivision(sf::Vector2f v1, sf::Vector2f v2)
{
    return sf::Vector2f(v1.x / v2.x, v1.y / v2.y);
}

int sqr(int value)
{
    return value * value;
}

float sqr(float value)
{
    return value * value;
}

template <typename T> int sign(T val)
{
    return (T(0) < val) - (val < T(0));
}

float signedMin(float value, float minimum)
{
    return fmin(value, abs(minimum))*sign<float>(minimum);
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