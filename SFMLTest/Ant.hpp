#pragma once

#include "Ant.fwd.hpp"
#include "Nest.fwd.hpp"

#include "Pheromone.hpp"
#include "functions.hpp"
#include "Constants.hpp"
#include "Food.hpp"
#include "Cell.hpp"
#include "Canvas.hpp"
#include "Nest.hpp"

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

class Ant
{
    private:
    float pheromoneTimer = randRange(.0f, 1.f);
    float pheromoneAmount; //Amount of pheromone it has on it
    bool followPheromone = true;

    float randomSteerSpeed = 1.f;
    float randomSteerAmount = 0.f;
    sf::Vector2f direction;
    
    int state = 0;

    Food *sensedFood = nullptr;
    sf::CircleShape foodShape;

    static float turnSpeed;
    static float speed;
    static float pheromoneStrength;
    static float pheromoneReplenish;

    public:
    sf::RectangleShape shape;
    float angle;

    Ant();
    Ant(sf::Vector2f pos);
    Ant(sf::Vector2f pos, float a);

    int directionTo(sf::Vector2f &relativePos);

    void senseFood(std::vector<Food *> &food, float dt);

    void sense(std::vector<Pheromone *> &pheromones, float dt);

    void trail(std::vector<Pheromone *> &pheromones, float dt);

    void update(Canvas &canvas, Nest *nest, float dt);

    void draw(sf::RenderWindow &window);
};