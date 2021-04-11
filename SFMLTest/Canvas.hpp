#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "Cell.hpp"

class Canvas
{
	private:
	std::vector<Cell> cells;

	public:
	int canvasWidth;
	int canvasHeight;
	int canvasLength;
	int cellWidth;
	int cellHeight;

	/// <summary>
	/// Creates a grid of cells
	/// </summary>
	/// <param name="canvasWidth">Number of columns</param>
	/// <param name="canvasHeight">Number of rows</param>
	/// <param name="cellWidth">Width in pixels of a cell</param>
	/// <param name="cellHeight">Height in pixels of a cell</param>
	Canvas(int canvasWidth, int canvasHeight, int cellWidth, int cellHeight);

	/// <summary>
	/// Updates and draw all cells
	/// </summary>
	/// <param name="window">The render window to draw to</param>
	/// <param name="dt">Deltatime</param>
	void update(sf::RenderWindow &window, float dt);

	/// <summary>
	/// Get the cell at this index
	/// </summary>
	/// <param name="index"></param>
	/// <returns>Pointer to the cell at that index</returns>
	Cell *operator[](int index);

	/// <summary>
	/// Get the index from a position based on cellWidth/cellHeight
	/// </summary>
	/// <param name="pos">Position in the room</param>
	/// <returns>Index of the cell at that position</returns>
	int getIndex(sf::Vector2f pos);

	/// <summary>
	/// Gets a room position from a cell index, and offset it by the given variables
	/// </summary>
	/// <param name="index">Index of the cell</param>
	/// <param name="offsetX">Pixels to offset in the X axis</param>
	/// <param name="offsetY">Pixels to offset in the Y axis</param>
	/// <returns></returns>
	sf::Vector2f getPosition(int index, float offsetX = 0.f, float offsetY = 0.f);
};