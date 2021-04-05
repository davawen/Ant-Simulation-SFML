#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "Pheromone.h"

class Cell
{
	public:
	sf::RectangleShape shape;
	std::vector<Pheromone*> pheromones;

	Cell(sf::Vector2f pos, sf::Vector2f size);

	bool insert(Pheromone* pheromone);
};

