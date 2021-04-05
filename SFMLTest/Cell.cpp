#include "Cell.h"

Cell::Cell(sf::Vector2f pos, sf::Vector2f size)
{
	this->shape = sf::RectangleShape(size);
	this->shape.setPosition(pos);
}

bool Cell::insert(Pheromone* pheromone)
{
	return false;
}