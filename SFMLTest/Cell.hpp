#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "Pheromone.hpp"
#include "Food.hpp"

class Cell
{
	public:
	sf::RectangleShape shape;
	std::vector<Pheromone*> pheromones;
	std::vector<Food*> food;

	Cell();
	Cell(sf::Vector2f pos, sf::Vector2f size);

	void draw(sf::RenderWindow& window, float dt);
};