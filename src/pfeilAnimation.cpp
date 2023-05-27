#define _USE_MATH_DEFINES
#include "pfeilAnimation.h"
#include <iostream>
#include <math.h>

pfeilAnimation::pfeilAnimation(RenderWindow *win)
{
	this->initVariables(win);
	this->initShapes();
}

pfeilAnimation::~pfeilAnimation()
{
}

void pfeilAnimation::update(Vector2f mousePos)
{
	this->mousePosition = mousePos;
	//std::cout << this->mouseDirection.x << " " << this->mouseDirection.y << "\n";
	this->updateRotation();
	this->updateMouseDirection();
	this->updateDistance();
}

void pfeilAnimation::render(RenderTarget* target)
{
	if (this->mouseheld)
	{
		target->draw(this->body);
		target->draw(this->tip);
	}
	target->draw(*this->tower);
	target->draw(this->ball);
}

const float pfeilAnimation::getValue() const
{
	return this->value;
}

const bool pfeilAnimation::getRelease() const
{
	return this->release;
}

const CircleShape pfeilAnimation::getBall() const
{
	return this->ball;
}

void pfeilAnimation::initShapes()
{

	this->tower = new RectangleShape(Vector2f(30, 100));
	this->tower->setFillColor(Color(154, 205, 186));
	this->tower->setPosition(Vector2f(150, this->window->getSize().y - this->tower->getGlobalBounds().height));
	
	this->ball.setRadius(30);
	this->ball.setOrigin(Vector2f(this->ball.getGlobalBounds().width * 0.5, -this->ball.getGlobalBounds().height * 0.5));
	this->ball.setPosition(Vector2f(this->tower->getPosition().x + this->tower->getGlobalBounds().width * 0.5, this->tower->getPosition().y - 3* this->ball.getRadius()));
	this->ball.setFillColor(Color::White);

	this->body.setFillColor(Color::Black);
	this->body.setSize(this->sizeBody);
	this->body.setOrigin(Vector2f(this->sizeBody.x * 0.5, 0));
	this->body.setPosition(Vector2f(this->ball.getPosition().x,this->ball.getPosition().y + this->body.getGlobalBounds().height));
	

	this->tip.setPosition(Vector2f(this->body.getPosition().x, this->body.getPosition().y));
	this->tip.setOrigin(Vector2f(this->body.getGlobalBounds().width + 0.25 * this->tip.getGlobalBounds().width, 1 * this->body.getGlobalBounds().height + this->tip.getGlobalBounds().height));
	this->tip.setFillColor(Color::Black);
	this->tip.setRadius(this->sizeTip);
}

void pfeilAnimation::initVariables(RenderWindow *win)
{
	this->value = 0.f;
	this->mousePosition = Vector2f(0, 0);
	this->direction = Vector2f(1, 1);
	this->posBody = Vector2f(300, 300);
	this->sizeBody = Vector2f(5, 50);
	this->sizeTip = 2 * this->sizeBody.x;
	this->posTip = Vector2f(this->posBody.x, this->posBody.y);
	this->window = win;
	this->mouseheld = false;
	this->mouseDirection = Vector2f(0, 0);
	this->distance = 0.f;
}

void pfeilAnimation::updateMouseDirection()
{
	this->mouseDirection = Vector2f(
		-(this->ball.getPosition().x - this->mousePosition.x),
		this->ball.getPosition().y - this->mousePosition.y +2*this->ball.getRadius()
	);
}

void pfeilAnimation::updateRotation()
{
	/*static int i = 0;
	static int fak = 1;
	this->body.setRotation(i);
	this->tip.setRotation(this->body.getRotation()+180);
	this->body.setScale(Vector2f(fak, fak*1.15));
	this->tip.setScale(Vector2f(fak, fak*1.15));

	this->direction = Vector2f(sin(this->body.getRotation()), cos(this->body.getRotation()));
	i++;
	*/
	if (!Mouse::isButtonPressed(Mouse::Left) && this->value != 0)
	{
		this->release = true;
	}

	if (!Mouse::isButtonPressed(Mouse::Left))
	{
		this->mouseheld = false;
		this->value = 0.f;
	}
	if (this->ball.getGlobalBounds().contains(this->mousePosition) || this->mouseheld)
	{
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			//std::cout << "pressed ";
			this->mouseheld = true;
		}
	}
	if (this->mouseheld && this->mousePosition.x < this->ball.getPosition().x)
	{
		
		float winkel = 0;
		winkel = atan(this->mouseDirection.y/this->mouseDirection.x)*360/(2*M_PI);
		//std::cout <<  winkel <<"\n ";
		this->body.setRotation(-winkel-90);
		this->tip.setRotation(this->body.getRotation() + 180);
		std::cout << this->distance << "\n";
		this->body.setScale(Vector2f(this->distance/50, this->distance/50 * 1.15));
		this->tip.setScale(Vector2f(this->distance/50, this->distance/50 * 1.15));
		this->value = this->distance / 50;
	}


	
}

void pfeilAnimation::updateDistance()
{
	this->distance = sqrt(this->mouseDirection.x * this->mouseDirection.x + this->mouseDirection.y * this->mouseDirection.y);
}
