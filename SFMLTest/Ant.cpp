#include "Ant.hpp"

float Ant::speed = 25.f;
float Ant::turnSpeed = PI * .75f;
float Ant::pheromoneStrength = 4.f;
float Ant::pheromoneReplenish = 200.f;

Ant::Ant() : Ant(sf::Vector2f(390, 390), 0.f) {}
Ant::Ant(sf::Vector2f pos) : Ant(pos, 0.f) {}
Ant::Ant(sf::Vector2f pos, float a)
{
    this->angle = a;
    this->pheromoneAmount = pheromoneReplenish;

    this->shape = sf::RectangleShape(sf::Vector2f(5.f, 3.f));
    this->shape.setPosition(pos);
    this->shape.setOrigin(2.5f, 1.5f);

    this->foodShape = sf::CircleShape(1.f);
    this->foodShape.setOrigin(1.f, 1.f);
    this->foodShape.setFillColor(sf::Color::Green);
}

int Ant::directionTo(sf::Vector2f &relativePos)
{
    float cross = this->direction.x * -relativePos.y + this->direction.y * relativePos.x;

    return -(cross > .2f) + (cross < -.2f);

    /* Branchless for :
    if(cross > .2      ) return -1;
    else if(cross < -.2) return  1;
    else                 return  0;
    */
}

void Ant::senseFood(std::vector<Food *> &food, float dt)
{
    if(sensedFood != nullptr)
    {
        sf::Vector2f relativePos = sensedFood->shape.getPosition() - this->shape.getPosition();

        float sqDst = relativePos.x * relativePos.x + relativePos.y * relativePos.y;

        if(sqDst < sqr(this->sensedFood->shape.getRadius()))
        {
            this->state = 1;
            this->pheromoneAmount = pheromoneReplenish;

            this->sensedFood->remove(food, 0.5f);

            this->sensedFood = nullptr;
            this->followPheromone = true;
        }
        else
        {
            sf::Vector2f direction = fromAngle(this->angle, 1);

            relativePos /= sqrt(sqDst);

            this->angle += directionTo(relativePos) * turnSpeed * dt * this->randomSteerSpeed * this->pheromoneStrength;
        }
    }
    else if(state == 0)
    {
        sf::Vector2f myPos = this->shape.getPosition();

        //food[0]->shape.setFillColor(sf::Color::Magenta);
        if(food.empty()) return;

        std::sort(food.begin(), food.end(),
            [myPos](Food *f1, Food *f2)
            {
                sf::Vector2f pos1 = f1->shape.getPosition();
                sf::Vector2f pos2 = f2->shape.getPosition();

                return (sqr(pos1.x - myPos.x) + sqr(pos1.y - myPos.y)) < (sqr(pos2.x - myPos.x) + sqr(pos2.y - myPos.y));
            }
        );

        this->sensedFood = food[0];
        this->followPheromone = false;
    }
}

void Ant::sense(std::vector<Pheromone *> &pheromones, float dt)
{
    if(!this->followPheromone) return;

    float weigth[3] = { 0, 0, 0 };

    for(auto &pheromone : pheromones)
    {
        if(pheromone->type == this->state) continue;

        sf::Vector2f relativePos = pheromone->pos - this->shape.getPosition();

        float sqDst = relativePos.x * relativePos.x + relativePos.y * relativePos.y;

        if(sqDst > 25.f * 25.f || sqDst < 5.f * 5.f) continue;

        float dot = this->direction.x * relativePos.x + this->direction.y * relativePos.y;
        if(dot < 0) continue; //Behind me, no need to normalize to test for this

        //float dst = sqrt(sqDst);

        //relativePos = { relativePos * this->pheromoneStrength * (1/sqDst) };
        relativePos *= this->pheromoneStrength * (1 / sqDst);
        //relativePos.x *= this->pheromoneStrength * (1/sqDst);
        //relativePos.y *= this->pheromoneStrength * (1/sqDst);

        weigth[directionTo(relativePos)+1] += pheromone->weigth;
    }

    if(weigth[1] > weigth[0] && weigth[1] > weigth[2]) //Continue forwards
    {
        //this->angle += 0;
    }
    else if(weigth[0] > weigth[2])
    {
        this->angle -= this->pheromoneStrength * this->turnSpeed * this->randomSteerSpeed * dt;
    }
    else if(weigth[2] > weigth[0])
    {
        this->angle += this->pheromoneStrength * this->turnSpeed * this->randomSteerSpeed * dt;
    }
    else if(weigth[1] <= weigth[0] && weigth[1] <= weigth[2])
    {
        this->angle += this->randomSteerAmount * this->randomSteerSpeed * dt;
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
        float weigth = fmin(this->pheromoneAmount / 10.f, 5.f);

        pheromones.push_back(new Pheromone(this->shape.getPosition(), this->state, weigth));

        this->pheromoneAmount -= weigth;

        this->pheromoneTimer = 1;
    }
}

void Ant::update(Canvas &canvas, Nest *nest, float dt)
{
    int index = canvas.getIndex(this->shape.getPosition());

    this->senseFood(canvas[index]->food, dt);

    this->sense(canvas[index]->pheromones, dt);
    this->trail(canvas[index]->pheromones, dt);

    this->shape.move(fromAngle(this->angle, dt * this->speed));
    this->shape.setRotation(angle * toDegrees);

    this->direction = fromAngle(this->angle, 1);

#pragma region Interact with nest

    sf::Vector2f distToNest = this->shape.getPosition() - nest->shape.getPosition();

    float dst = sqrtf(sqr(distToNest.x) + sqr(distToNest.y));

    distToNest /= dst;

    if(dst <= nest->shape.getRadius() + 3.f + 150.f)
    {
        //Go towards nest if you have food
        if(this->state == 1)
        {
            this->angle -= directionTo(distToNest) * turnSpeed * dt * this->randomSteerSpeed * this->pheromoneStrength;

            this->followPheromone = false;
        }

        if(dst <= nest->shape.getRadius() + 3.f)
        {
            state = 0;

            nest->foodAmount += state == 1; //Add food to nest if you have some
            this->pheromoneAmount = pheromoneReplenish;

            this->angle += PI;

            this->followPheromone = true;
        }
    }

#pragma endregion


    this->foodShape.setPosition(this->shape.getPosition() + fromAngle(this->angle, 1.5f));



#pragma region "Collision" Detection


    sf::Vector2f selfPos = this->shape.getPosition();

    if(selfPos.x < 0) selfPos.x = screenWidth;
    else if(selfPos.x > screenWidth) selfPos.x = 0;

    if(selfPos.y < 0) selfPos.y = screenHeight;
    else if(selfPos.y > screenHeight) selfPos.y = 0;

    this->shape.setPosition(selfPos);
#pragma endregion

    this->randomSteerSpeed = randRange(.8f, 1.2f);
    this->randomSteerAmount += (randGaussian(1.f) * this->randomSteerSpeed * 2.f - (this->randomSteerAmount * .01f)) * dt;
}

void Ant::draw(sf::RenderWindow &window)
{
    window.draw(this->shape);

    if(state == 1)
    {
        window.draw(this->foodShape);
    }
}