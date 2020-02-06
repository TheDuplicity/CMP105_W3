#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	deltaTime = 0;

	// initialise game objects
	rectangle.setSize(sf::Vector2f(100, 100));
	rectangle.setPosition(500,500);
	rectangle.setFillColor(sf::Color::Red);
	rDirection = 1;
	
	circle.setRadius(50);
	circle.setPosition(sf::Vector2f(300, 300));
	circle.setFillColor(sf::Color::Blue);
	cDirection = 1;
}

Level::~Level()
{

}

// handle user input
void Level::handleInput(float dt)
{
}

// Update game objects
void Level::update(float dt)
{
	deltaTime += dt;
	if ((circle.getPosition().x + (circle.getRadius() * 2)) > window->getSize().x) {
		circle.setPosition(window->getSize().x - circle.getRadius() * 2, circle.getPosition().y);
		cDirection *= -1;
	}
	else if (circle.getPosition().x < 0) {
		circle.setPosition(sf::Vector2f(0,circle.getPosition().y));
		cDirection *= -1;
	}
	circle.setPosition((circle.getPosition().x + (dt * 500 * cDirection)), circle.getPosition().y);

}

// Render level
void Level::render()
{
	beginDraw();

	window->draw(rectangle);
	window->draw(circle);

	endDraw();
}

// clear back buffer
void Level::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}