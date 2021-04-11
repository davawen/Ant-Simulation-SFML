#pragma once

#include <SFML/Graphics.hpp>

sf::Vector2f fromAngle(float angle, float magnitude);

sf::Vector2f cWiseMultiplication(sf::Vector2f v1, sf::Vector2f v2);
sf::Vector2f cWiseDivision(sf::Vector2f v1, sf::Vector2f v2);

int sqr(int value);
float sqr(float value);

template <typename T> int sign(T val);

float signedMin(float value, float minimum);

int randRange(int min, int max);
float randRange(float min, float max);
float randGaussian(float stretch);