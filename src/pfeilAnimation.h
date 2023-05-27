#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace sf;

class pfeilAnimation
{
public:
	pfeilAnimation(RenderWindow *win);
	virtual ~pfeilAnimation();

	void update(Vector2f mousePos);
	void render(RenderTarget* target);

	const float getValue() const;
	const bool getRelease() const;
	const CircleShape getBall() const;

private:

	RectangleShape body = RectangleShape(Vector2f(5, 50));
	RectangleShape* tower;
	CircleShape tip = CircleShape(10, 3);
	CircleShape ball;

	Vector2f mousePosition;
	Vector2f posBody;
	Vector2f posTip;
	Vector2f sizeBody;
	float sizeTip;
	Vector2f direction;
	float distance;

	RenderWindow* window;

	float value;
	bool mouseheld;
	bool release;
	Vector2f mouseDirection;

	void initShapes();
	void initVariables(RenderWindow *win);
	void updateMouseDirection();
	void updateRotation();
	void updateDistance();
};

