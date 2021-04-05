#include "Pheromone.h"

Pheromone::Pheromone(): Pheromone(sf::Vector2f(0, 0)) {}
Pheromone::Pheromone(sf::Vector2f pos)
{
    this->shape = sf::CircleShape(3.f);
    this->shape.setPosition(pos);
    this->shape.setFillColor(sf::Color::Blue);
    this->shape.setOrigin(1.5f, 1.5f);

    this->weigth = 10;
}

bool Pheromone::evaporate(float amount, float dt)
{
    this->weigth -= amount * dt;

    this->shape.setFillColor(sf::Color(0, 0, 255, (int)(this->weigth / 10 * 255)));

    return abs(this->weigth) <= amount;
}