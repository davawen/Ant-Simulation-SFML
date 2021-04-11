#include "Cell.hpp"

Cell::Cell() : Cell(sf::Vector2f(0.f, 0.f), sf::Vector2f(10.f, 10.f)) {}

Cell::Cell(sf::Vector2f pos, sf::Vector2f size)
{
	this->shape = sf::RectangleShape(size);
	this->shape.setPosition(pos);
	this->shape.setFillColor(sf::Color::Transparent);
	this->shape.setOutlineColor(sf::Color::White);
	this->shape.setOutlineThickness(1.f);
}

void Cell::draw(sf::RenderWindow& window, float dt)
{
    if(!this->pheromones.empty())
    {
        std::vector<int> deletePheromones;

        auto it = this->pheromones.begin();

        while(it != this->pheromones.end())
        {
            if((*it)->evaporate(dt))
            {
                delete *it;

                it = this->pheromones.erase(it);
            }
            else
            {
                window.draw((*it)->shape);
                ++it;
            }
        }

        /*int __it = 0;
        int __size = this->pheromones.size();
        for(auto& pheromone : this->pheromones)
        {
            if(pheromone->evaporate(dt))
            {
                deletePheromones.push_back(__size - __it);
            }
            else
            {
                window.draw(pheromone->shape);
            }

            __it++;
        }

        for(auto& p : deletePheromones)
        {
            this->pheromones.erase(this->pheromones.end() - p);
        }*/
    }

	for(auto& food : this->food)
	{
		window.draw(food->shape);
	}
}