#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

class Pheromone
{
    public:
        sf::CircleShape shape;
        float weigth;

        Pheromone();
        Pheromone(sf::Vector2f pos);

        bool evaporate(float amount, float dt);
};