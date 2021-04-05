#include "Ant.h"

Ant::Ant(): Ant(sf::Vector2f(390, 390), 0.f) {}
Ant::Ant(sf::Vector2f pos) : Ant(pos, 0.f)   {}
Ant::Ant(sf::Vector2f pos, float a)
{
    this->angle = a;

    this->shape = sf::RectangleShape(sf::Vector2f(5.f, 3.f));
    this->shape.setPosition(pos);
    this->shape.setOrigin(2.5f, 1.5f);
}

void Ant::sense(std::vector<Pheromone *> &pheromones, float dt)
{
    float weigth[3] = { 0, 0, 0 };

    sf::Vector2f direction = fromAngle(this->angle, 1);


    for(auto &pheromone : pheromones)
    {
        sf::Vector2f pPos = pheromone->shape.getPosition();
        sf::Vector2f selfPos = this->shape.getPosition();

        sf::Vector2f relativePos(pPos.x - selfPos.x, pPos.y - selfPos.y);

        float sqDst = relativePos.x * relativePos.x + relativePos.y * relativePos.y;

        if(sqDst > 25.f * 25.f || sqDst < 5.f * 5.f) continue;

        float dot = direction.x * relativePos.x + direction.y * relativePos.y;
        if(dot < 0) continue; //Behind me, no need to normalize to test for this

        float dst = sqrt(sqDst);
        relativePos.x /= dst;
        relativePos.y /= dst;

        float cross = direction.x * -relativePos.y + direction.y * relativePos.x;

        if(cross > .2) weigth[0]++;
        else if(cross < -.2) weigth[2]++;
        else weigth[1]++;
    }

    if(weigth[1] > weigth[0] && weigth[1] > weigth[2]) //Continue forwards
    {
        //this->angle += 0;
    }
    else if(weigth[0] > weigth[2])
    {
        this->angle -= this->turnSpeed * this->randomSteerSpeed * dt;
    }
    else if(weigth[2] > weigth[0])
    {
        this->angle += this->turnSpeed * this->randomSteerSpeed * dt;
    }
    else if(weigth[1] <= weigth[0] && weigth[1] <= weigth[2])
    {
        this->angle += this->randomSteerAmount * this->randomSteerSpeed * .5f * dt;
    }
}

void Ant::trail(std::vector<Pheromone *> &pheromones, float dt)
{
    if(this->pheromoneTimer > 0)
    {
        this->pheromoneTimer -= dt;
        return;
    }
    else
    {
        Pheromone *p = NULL;

        p = new Pheromone(this->shape.getPosition());

        pheromones.push_back(p);

        this->pheromoneTimer = 1;
    }
}

void Ant::update(float dt)
{
    this->shape.move(fromAngle(this->angle, dt * this->speed));
    this->shape.setRotation(angle * toDegrees);

    sf::Vector2f selfPos = this->shape.getPosition();

    if(selfPos.x < 0) selfPos.x = screenWidth;
    else if(selfPos.x > screenWidth) selfPos.x = 0;

    if(selfPos.y < 0) selfPos.y = screenHeight;
    else if(selfPos.y > screenHeight) selfPos.y = 0;

    this->shape.setPosition(selfPos);

    this->randomSteerSpeed = randRange(.8f, 1.2f);
    this->randomSteerAmount += (randGaussian(1.f) * this->randomSteerSpeed * 6 - (this->randomSteerAmount * .01f)) * dt;



}