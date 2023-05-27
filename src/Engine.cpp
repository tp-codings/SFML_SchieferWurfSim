#include "Engine.h"
#include <iostream>
#include <math.h>
#include <cmath>
#include <sstream>
#include <iomanip>

Engine::Engine()
{
	this->initWindow();
	this->initGUI();
	this->initVariables();
	this->initWorld();
}

Engine::~Engine()
{
	delete this->window;
}

void Engine::run()
{
	while (this->running())
	{
		this->update();
		this->render();
	}
}

const bool Engine::running()
{
	return this->window->isOpen();
}

void Engine::update()
{
	this->updateGUI();
	this->updateMousePosition();
	this->updateInput();
	this->pollEvent();
	this->ball->update();
	this->updateFlight();
	this->animation->update(this->mousePosView);
	

}

void Engine::updateGUI()
{
	std::stringstream ss;
	ss << this->animation->getValue();
	this->GUI.setString(ss.str());
}

void Engine::updateMousePosition()
{
	this->mousePosWindow = Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Engine::updateInput()
{
}

void Engine::updateFlight()
{
	if (this->animation->getRelease())
	{
		std::cout << "zium ";
		this->ball->setVelocity(Vector2f(this->animation->getValue(), this->animation->getValue()));
	}
}

void Engine::render()
{
	this->window->clear(Color::White);
	this->renderGUI(this->window);
	this->animation->render(this->window);
	this->ball->render(this->window);
	this->window->display();
}

void Engine::renderGUI(RenderTarget* target)
{
	target->draw(this->GUI);
}

void Engine::initWindow()
{
	this->videomode.height = 700;
	this->videomode.width = 1500;
	this->window = new RenderWindow(this->videomode, "Life", Style::Titlebar | Style::Close);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);
}

void Engine::initGUI()
{
	if (!this->font.loadFromFile("Fonts/Silkscreen-Bold.ttf")) std::cout << "fuck it";
	this->GUI.setFont(this->font);
	this->GUI.setCharacterSize(20);
	this->GUI.setString("NONE");
	this->GUI.setFillColor(Color::Black);
	this->GUI.setPosition(0.5 * this->window->getSize().x - 0.5 * this->GUI.getGlobalBounds().width, 0.24 * this->window->getSize().y);
}

void Engine::initVariables()
{
	this->animation = new pfeilAnimation(this->window);
	this->ball = new Ball(this->window);
}

void Engine::initWorld()
{
	
}

void Engine::pollEvent()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case Event::Closed:
			this->window->close();
			break;
		case Event::KeyPressed:
			if (this->ev.key.code == Keyboard::F) this->window->close();
			break;
		}
	}
}
