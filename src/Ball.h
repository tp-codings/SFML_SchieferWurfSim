#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "pfeilAnimation.h"

using namespace sf;

class Ball
{
public:
	Ball(RenderWindow *win);
	virtual ~Ball();

	void update();
	void render(RenderTarget* target);
	
	const Vector2f getPosition() const;
	const Vector2f getVelocity() const;

	void setVelocity(Vector2f vel);

private:

	CircleShape shape;
	Vector2f position;
	Vector2f velocity;
	RenderWindow* window;

	CircleShape oldBall;

	void initVariables(RenderWindow *win);
	void initShape();
	void updatePosition();
	void updateShape();
};

