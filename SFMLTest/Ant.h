#pragma once

#include "Pheromone.h"
#include "functions.h"
#include "Constants.h"

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

class Ant
{
    private:
    float pheromoneTimer = randRange(.0f, 1.f);
    float turnSpeed = PI / 2;
    float speed = 15;

    float randomSteerSpeed = 1.f;
    float randomSteerAmount = 0.f;

    public:
    sf::RectangleShape shape;
    float angle;

    Ant();
    Ant(sf::Vector2f pos);
    Ant(sf::Vector2f pos, float a);

    void sense(std::vector<Pheromone *> &pheromones, float dt);

    void trail(std::vector<Pheromone *> &pheromones, float dt);

    void update(float dt);
};