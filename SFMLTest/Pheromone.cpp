#include "Pheromone.hpp"

float Pheromone::evaporateAmount = 0.2f;

Pheromone::Pheromone(): Pheromone(sf::Vector2f(0, 0), 0, 0) {}
Pheromone::Pheromone(sf::Vector2f pos, int type, float weigth)
{
    //this->shape = sf::CircleShape(3.f);
    //this->shape.setPosition(pos);
    //this->shape.setOrigin(1.5f, 1.5f);

    //this->vShape.

    this->pos = pos;

    this->shape = sf::VertexArray(sf::PrimitiveType::TriangleStrip, 4);

    this->shape[0].position = sf::Vector2f( pos.x-1.5f, pos.y-1.5f );
    this->shape[1].position = sf::Vector2f( pos.x-1.5f, pos.y+1.5f );
    this->shape[2].position = sf::Vector2f( pos.x+1.5f, pos.y-1.5f );
    this->shape[3].position = sf::Vector2f( pos.x+1.5f, pos.y+1.5f );

    //this->shape.setFillColor(sf::Color(this->red, this->green, this->blue, 255));

    this->weigth = weigth;

    this->type = type;

    this->red = type == 1 ? 255 : 0;
    this->green = 0;
    this->blue = type == 0 ? 255 : 0;

}

bool Pheromone::evaporate(float dt)
{
    this->weigth -= this->evaporateAmount * dt;

    for(int i = 0; i < 4; i++) { this->shape[i].color = sf::Color(this->red, this->green, this->blue, (int)(this->weigth / 10 * 255)); }

    //this->shape.setFillColor(sf::Color(this->red, this->green, this->blue, (int)(this->weigth / 10 * 255)));

    return abs(this->weigth) <= this->evaporateAmount;
}