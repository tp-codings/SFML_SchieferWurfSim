#include "Ball.h"

Ball::Ball(RenderWindow *win)
{
    this->initVariables(win);
    this->initShape();
}

Ball::~Ball()
{
}

void Ball::update()
{
    this->updatePosition();
    this->updateShape();
}

void Ball::render(RenderTarget* target)
{
    target->draw(this->shape);
}

const Vector2f Ball::getPosition() const
{
    return this->position;
}

const Vector2f Ball::getVelocity() const
{
    return this->velocity;
}

void Ball::setVelocity(Vector2f vel)
{
    this->velocity = vel;
}

void Ball::initVariables(RenderWindow *win)
{
    this->position = Vector2f(0, 0);
    this->velocity = Vector2f(0, 0);
    this->window = win;
    pfeilAnimation animation = pfeilAnimation(window);
    animation = pfeilAnimation(win);
    this->oldBall = animation.getBall();
}

void Ball::initShape()
{
    this->shape = this->oldBall;
    this->shape.setFillColor(Color::Black);
}

void Ball::updatePosition()
{
    this->position.x += this->velocity.x;
    this->position.y += this->velocity.y;
}

void Ball::updateShape()
{
    this->shape.setPosition(this->position);
}
