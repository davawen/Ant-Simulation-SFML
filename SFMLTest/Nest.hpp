#pragma once

#include "Ant.fwd.hpp"
#include "Nest.fwd.hpp"

#include <vector>
#include <string>

#include "Ant.hpp"
#include "Canvas.hpp"

class Nest
{
    private:
    std::vector<Ant> ants;

    sf::Text text;
    sf::Font font;

    public:
    sf::CircleShape shape;
    int foodAmount = 0;

    Nest(sf::Vector2f pos, int numAnts);

    void update(Canvas &canvas, sf::RenderWindow &window, float dt);
};