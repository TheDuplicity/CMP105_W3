#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	deltaTime = 0;
	xSpd = 500;
	ySpd = 500;

	// initialise game objects
	rectangle.setSize(sf::Vector2f(100, 100));
	rectangle.setPosition(500,500);
	rectangle.setFillColor(sf::Color::Red);
	
	
	circle.setRadius(50);
	circle.setPosition(sf::Vector2f(300, 300));
	circle.setFillColor(sf::Color::Blue);
	cDirection = 1;

	circleTwo.setRadius(75);
	circleTwo.setPosition(sf::Vector2f(250, 200));
	circleTwo.setFillColor(sf::Color::Green);
	ctwoxDirection = 1;
	ctwoyDirection = 1;

	aFont.loadFromFile("font/arial.ttf");

	speedText.setString("hello");
	speedText.setOrigin(0,0);
	speedText.setFillColor(sf::Color::Black);
	speedText.setCharacterSize(90);
	speedText.setFont(aFont);


}

Level::~Level()
{

}

// handle user input
void Level::handleInput(float dt)
{
	ryDirection = 0;
	rxDirection = 0;
	if (input->isKeyDown('W' - 65)) {
		ryDirection -= 1;
	}
	if (input->isKeyDown('S' - 65)) {
		ryDirection += 1;
	}
	if (input->isKeyDown('D' - 65)) {
		rxDirection += 1;
	}
	if (input->isKeyDown('A' - 65)) {
		rxDirection -= 1;
	}

	if (input->isKeyDown(sf::Keyboard::Add)) {
		xSpd++;
	}
	if (input->isKeyDown(sf::Keyboard::Subtract)) {
		xSpd--;
	}

}

// Update game objects
void Level::update(float dt)
{
	deltaTime += dt;
	//rectangle to be moved by the player
	rectangle.move(sf::Vector2f(rxDirection * 500 * dt, ryDirection * 500 * dt));
	// circle one for bouncing between left and righthand side of screen
	if ((circle.getPosition().x + (circle.getRadius() * 2)) > window->getSize().x) {
		circle.setPosition(window->getSize().x - circle.getRadius() * 2, circle.getPosition().y);
		cDirection *= -1;
	}
	else if (circle.getPosition().x < 0) {
		circle.setPosition(sf::Vector2f(0,circle.getPosition().y));
		cDirection *= -1;
	}
	circle.setPosition((circle.getPosition().x + (dt * 500 * cDirection)), circle.getPosition().y);


	//circle two for bouncing in all axis
	if ((circleTwo.getPosition().x + (circleTwo.getRadius() * 2)) > window->getSize().x) {
		circleTwo.setPosition(window->getSize().x - circleTwo.getRadius() * 2, circleTwo.getPosition().y);
		ctwoxDirection *= -1;
	}
	else if (circleTwo.getPosition().x < 0) {
		circleTwo.setPosition(sf::Vector2f(0, circleTwo.getPosition().y));
		ctwoxDirection *= -1;
	}
	if (circleTwo.getPosition().y < 0) {
		circleTwo.setPosition(sf::Vector2f(circleTwo.getPosition().x, 0));
		ctwoyDirection *= -1;
	}
	else if (circleTwo.getPosition().y + (circleTwo.getRadius() * 2) > window->getSize().y) {
		circleTwo.setPosition(sf::Vector2f(circleTwo.getPosition().x, window->getSize().y - (circleTwo.getRadius() * 2)));
		ctwoyDirection *= -1;
	}

	circleTwo.setPosition((circleTwo.getPosition().x + (dt * xSpd * ctwoxDirection)), (circleTwo.getPosition().y + (dt * ySpd * ctwoyDirection)));

	speedText.setString("Speed - " + std::to_string(sqrt(pow(xSpd, 2) + pow(xSpd, 2))));

}

// Render level
void Level::render()
{
	beginDraw();

	window->draw(circleTwo);
	window->draw(rectangle);
	window->draw(circle);
	window->draw(speedText);

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