#pragma once

#include <SFML/Graphics.hpp>

sf::Vector2f fromAngle(float angle, float magnitude);

int sqr(int value);
float sqr(float value);

int randRange(int min, int max);
float randRange(float min, float max);
float randGaussian(float stretch);