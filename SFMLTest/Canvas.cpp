#include "Canvas.hpp"

Canvas::Canvas(int canvasWidth, int canvasHeight, int cellWidth, int cellHeight)
{
    this->canvasWidth = canvasWidth;
    this->canvasHeight = canvasHeight;
    this->canvasLength = canvasWidth * canvasHeight;
    this->cellWidth = cellWidth;
    this->cellHeight = cellHeight;

    this->cells.resize(canvasLength);

    for(int i = 0; i < canvasLength; i++)
    {
        this->cells[i] = Cell(this->getPosition(i), sf::Vector2f(cellWidth, cellHeight));
    }
}

void Canvas::update(sf::RenderWindow &window, float dt)
{
    for(int i = 0; i < this->canvasLength; i++)
    {
        this->cells[i].draw(window, dt);
    }
}

Cell *Canvas::operator[](int index)
{
    if(index < 0 || index >= this->canvasLength) return nullptr;

    return &this->cells[index];
}

int Canvas::getIndex(sf::Vector2f pos)
{
    return floor(pos.x / this->cellWidth) + floor(pos.y / this->cellHeight) * this->canvasWidth;
}

sf::Vector2f Canvas::getPosition(int index, float offsetX, float offsetY)
{
    return sf::Vector2f((index % this->canvasWidth) * this->cellWidth + offsetX, floor(index / this->canvasWidth) * this->cellHeight + offsetY);
}