#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>

#include "functions.h"
#include "Ant.h"
#include "Pheromone.h"

#include "Constants.h"

int main()
{
    #pragma region Setup

    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "SFML", sf::Style::Close | sf::Style::Titlebar);
    sf::Clock deltaClock;

    sf::View view(sf::Vector2f(screenWidth / 2, screenHeight / 2), sf::Vector2f(screenWidth, screenHeight));

    window.setView(view);

    #pragma endregion
    #pragma region Ant Stuff

    std::vector<Ant> ants(300);
    std::vector<Pheromone *> pheromones;

    float evaporateAmount = .8f;

    for(auto &ant : ants)
    {
        ant = Ant(sf::Vector2f(randRange(0.f, screenWidth), randRange(0.f, screenHeight)), randRange(0.f, 2 * PI));

        ant.shape.setFillColor(sf::Color::White);
    }

    #pragma endregion

    float mouseXStart = 0;
    float mouseYStart = 0;

    #pragma region Border

    sf::VertexArray border(sf::LineStrip, 5);
    border[0].position = sf::Vector2f(0, 0);
    border[1].position = sf::Vector2f(screenWidth, 0);
    border[2].position = sf::Vector2f(screenWidth, screenHeight);
    border[3].position = sf::Vector2f(0, screenHeight);
    border[4].position = sf::Vector2f(0, 0);

    #pragma endregion

    #pragma region Cell division

    const int canvasWidth = floor(screenWidth / 20);
    const int canvasHeigth = floor(screenHeight / 20);

    std::vector<std::vector<Pheromone>> canvas;

    #pragma endregion


    sf::Shader shader;

    //if(!shader.loadFromFile())

    while(window.isOpen())
    {
        float dt = (deltaClock.restart()).asSeconds();

        #pragma region Events
        
        sf::Event evnt;
        while(window.pollEvent(evnt))
        {
            switch(evnt.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    if(evnt.mouseButton.button == sf::Mouse::Middle)
                    {
                        sf::Vector2f __viewPos = view.getCenter();

                        mouseXStart = evnt.mouseButton.x + __viewPos.x;
                        mouseYStart = evnt.mouseButton.y + __viewPos.y;
                    }
                    break;
                case sf::Event::MouseWheelMoved:
                    //_x + (_w - (_w*zoom))*ox, _y + (_h - (_h*zoom))*oy
                    sf::Vector2i __mousePosRelative = sf::Mouse::getPosition(window);
                    sf::Vector2f __origin((float)__mousePosRelative.x / screenWidth - .5, (float)__mousePosRelative.y / screenHeight - .5);

                    float __zoomAmount = 1 - (float)evnt.mouseWheel.delta * .05f;

                    sf::Vector2f __viewSize = view.getSize();

                    view.move((__viewSize.x - __viewSize.x * __zoomAmount) * __origin.x, (__viewSize.y - __viewSize.y * __zoomAmount) * __origin.y);

                    view.zoom(__zoomAmount);

                    window.setView(view);
                    break;
                    /*case sf::Event::TextEntered:
                        if(evnt.text.unicode < 128)
                        {
                            printf("%c", evnt.text.unicode);
                        }

                        break;*/
            }
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Middle))
        {
            sf::Vector2i __mousePos = sf::Mouse::getPosition(window);

            view.setCenter(sf::Vector2f(mouseXStart - (float)__mousePos.x, mouseYStart - (float)__mousePos.y));

            window.setView(view);
        }

        #pragma endregion

        if(!pheromones.empty())
        {
            std::vector<int> deletePheromones;

            int __it = 0;
            for(auto &pheromone : pheromones)
            {
                if(pheromone->evaporate(evaporateAmount, dt))
                {
                    deletePheromones.push_back(__it);
                }
                else
                {
                    window.draw(pheromone->shape);
                }

                __it++;
            }

            for(auto &p : deletePheromones)
            {
                pheromones.erase(pheromones.begin() + p);
            }
        }

        for(auto &ant : ants)
        {
            ant.update(dt);
            ant.sense(pheromones, dt);
            ant.trail(pheromones, dt);

            window.draw(ant.shape);
        }

        window.draw(border);

        window.display();
        window.clear();

        printf("%f\n", 1. / dt);
    }

    return 0;
}




