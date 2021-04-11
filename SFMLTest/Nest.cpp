#include "Nest.hpp"

Nest::Nest(sf::Vector2f pos, int numAnts)
{
    this->shape = sf::CircleShape(30.f);
    this->shape.setOrigin(30.f, 30.f);
    this->shape.setPosition(pos);
    this->shape.setFillColor(sf::Color(165, 42, 42, 255));
    this->shape.setOutlineColor(sf::Color::White);
    this->shape.setOutlineThickness(3.f);

    this->ants.resize(numAnts);

    for(auto &ant : this->ants)
    {
        float _dir = randRange(0.f, 2 * PI);

        ant = Ant(sf::Vector2f(screenWidth / 2, screenHeight / 2) + fromAngle(_dir, 33.f), _dir);

        ant.shape.setFillColor(sf::Color::White);
    }

    this->font.loadFromFile("./arial.ttf");

    this->text.setFont(this->font);
    this->text.setCharacterSize(24);
    this->text.setFillColor(sf::Color::White);
    this->text.setString("0");
}

void Nest::update(Canvas &canvas, sf::RenderWindow &window, float dt)
{
    for(auto &ant : this->ants)
    {
        ant.update(canvas, this, dt);

        ant.draw(window);
    }

    this->text.setString(std::to_string(this->foodAmount));

    window.draw(this->shape);
    window.draw(this->text);
}
