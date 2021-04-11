#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

class Pheromone
{
    private:
    int red;
    int green;
    int blue;

    static float evaporateAmount;

    public:
        sf::VertexArray shape;
        sf::Vector2f pos;

        //sf::VertexArray vShape;

        float weigth;
        int type;

        Pheromone();
        Pheromone(sf::Vector2f pos, int type, float weigth);

        bool evaporate(float dt);
};