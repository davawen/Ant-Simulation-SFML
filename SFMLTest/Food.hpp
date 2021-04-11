#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

class Food
{
	public:
	float amount = 5.f;

	sf::CircleShape shape;

	Food();
	Food(sf::Vector2f pos);

	void remove(std::vector<Food *> &food, float amount);
};

