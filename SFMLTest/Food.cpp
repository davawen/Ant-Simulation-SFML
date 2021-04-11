#include "Food.hpp"

Food::Food() : Food(sf::Vector2f(0.f, 0.f)) {}
Food::Food(sf::Vector2f pos)
{
	this->shape = sf::CircleShape(5.f);
	this->shape.setPosition(pos);
	this->shape.setOrigin(5.f, 5.f);
	this->shape.setFillColor(sf::Color::Green);
}

void Food::remove(std::vector<Food *> &food, float amount)
{
	this->amount -= amount;
	this->shape.setRadius(this->amount);

	if(this->amount <= 0)
	{
		for(auto it = food.begin(); it < food.end(); it++)
		{
			if((*it) == this)
			{
				food.erase(it);

				break;
			}
		}
	}
}