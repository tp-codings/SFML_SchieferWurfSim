#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "pfeilAnimation.h"
#include "Ball.h"
using namespace sf;

class Engine
{
public:
	Engine();
	virtual ~Engine();

	void run();

	const bool running();

private:

	//window
	RenderWindow* window;
	VideoMode videomode;
	Event ev;

	//World
	Ball *ball;

	//Animations
	pfeilAnimation *animation;

	//GUI
	Font font;
	Text GUI;

	//Mouse positions
	Vector2i mousePosWindow;
	Vector2f mousePosView;
	bool mouseheld = false;

	//Game logic

	void update();
	void updateGUI();
	void updateMousePosition();
	void updateInput();
	void updateFlight();

	void render();
	void renderGUI(RenderTarget*);

	void initWindow();
	void initGUI();
	void initVariables();

	void initWorld();
	void pollEvent();

};




