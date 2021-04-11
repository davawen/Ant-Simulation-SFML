#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include <time.h>

#include "Constants.hpp"
#include "functions.hpp"

#include "Ant.hpp"
#include "Pheromone.hpp"
#include "Nest.hpp"

#include "Cell.hpp"
#include "Canvas.hpp"
#include "Food.hpp"

int main()
{
    srand(time(NULL));

    #pragma region Setup

    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "SFML", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
    sf::Clock deltaClock;

    sf::View view(sf::Vector2f(screenWidth / 2, screenHeight / 2), sf::Vector2f(screenWidth, screenHeight));

    float aspectRatio = screenWidth / screenHeight;

    window.setView(view);

    #pragma endregion

    #pragma region Border

    sf::VertexArray border(sf::LineStrip, 5);
    border[0].position = sf::Vector2f(0, 0);
    border[1].position = sf::Vector2f(screenWidth, 0);
    border[2].position = sf::Vector2f(screenWidth, screenHeight);
    border[3].position = sf::Vector2f(0, screenHeight);
    border[4].position = sf::Vector2f(0, 0);

    #pragma endregion

    #pragma region Cell division

    const int cellWidth = 50;
    const int cellHeight = 50;

    const int canvasWidth = floor(screenWidth / cellWidth)+1;
    const int canvasHeigth = floor(screenHeight / cellHeight)+1;
    const int canvasLength = canvasWidth * canvasHeigth;

    Canvas canvas(canvasWidth, canvasHeigth, cellWidth, cellHeight);

    #pragma endregion

    #pragma region Populate with food
    
    for(int i = 0; i < 6; i++)
    {
        int foodIndex = randRange(0, canvasLength-1);
        int foodAmount = randRange(5, 20);

        for(int j = 0; j < foodAmount; j++)
        {
            canvas[foodIndex]->food.push_back(
                new Food(canvas.getPosition(foodIndex, randRange(0.f, static_cast<float>(cellWidth)), randRange(0.f, static_cast<float>(cellHeight))))
            );
        }
    }

    #pragma endregion

    Nest nest(sf::Vector2f(screenWidth/2, screenHeight/2), 1000);

    //sf::Shader shader;
    //
    //if(!shader.loadFromFile("shader.frag", "shader.vert"))
    //{
    //    //Error...
    //}

    /*try
    {
        if(!shader.loadFromFile("shader.frag", "shader.vert")) throw "Unable to load shader";
    }
    catch(const std::exception e)
    {
        std::cout << e.what();
    }*/

    while(window.isOpen())
    {
        float dt = (deltaClock.restart()).asSeconds();

        sf::Vector2f mouseRoomPos = (view.getCenter() - view.getSize() / 2.f) +
                                    cWiseMultiplication(sf::Vector2f(sf::Mouse::getPosition(window)), cWiseDivision(view.getSize(), sf::Vector2f(screenWidth, screenHeight)));

        #pragma region Events
        
        sf::Event evnt;
        while(window.pollEvent(evnt))
        {
            switch(evnt.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                /*case sf::Event::MouseButtonPressed:
                    if(evnt.mouseButton.button == sf::Mouse::Middle)
                    {
                        mouseStart = mouseRoomPos;
                        viewPosStart = view.getCenter();
                    }
                    break;*/
                case sf::Event::MouseWheelMoved:
                {

                                    //_x + (_w - (_w*zoom))*ox, _y + (_h - (_h*zoom))*oy
                    sf::Vector2i __mousePosRelative = sf::Mouse::getPosition(window);
                    sf::Vector2f __origin(static_cast<float>(__mousePosRelative.x) / screenWidth - .5, static_cast<float>(__mousePosRelative.y) / screenHeight - .5);

                    float __zoomAmount = 1 - static_cast<float>(evnt.mouseWheel.delta) * .05f;

                    sf::Vector2f __viewSize = view.getSize();

                    view.move((__viewSize.x - __viewSize.x * __zoomAmount) * __origin.x, (__viewSize.y - __viewSize.y * __zoomAmount) * __origin.y);

                    view.zoom(__zoomAmount);

                    window.setView(view);
                }
                    break;
                case sf::Event::Resized:
                {
                    view.setSize(aspectRatio * evnt.size.height, evnt.size.height);

                    window.setView(view);
                }

                    break;
                    /*case sf::Event::TextEntered:
                        if(evnt.text.unicode < 128)
                        {
                            printf("%c", evnt.text.unicode);
                        }
                    
                        break;*/
            }
        }
        /*if(sf::Mouse::isButtonPressed(sf::Mouse::Middle))
        {
            view.setCenter(view.getCenter() - mouseRoomPos - mouseStart);

            window.setView(view);
        }*/

        #pragma endregion

        canvas.update(window, dt);
        nest.update(canvas, window, dt);

        window.draw(border);

        window.display();
        window.clear();

        printf("%f FPS\n", 1. / dt);
    }

    return 0;
}




