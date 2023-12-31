#include "GameEngine.h"

void GameEngine::input(sf::Event& e, sf::RenderWindow& window)
{
	std::for_each(
		this->sliders.begin(),
		this->sliders.end(),
		[&](std::pair<std::string, Slider*> keyValue) {
			keyValue.second->logic(window);
			if (keyValue.first == "population")
				populationSize = keyValue.second->getValue();
			else if (keyValue.first == "mutation")
				mutationRate = keyValue.second->getValue();
			else if (keyValue.first == "selection")
				selectionSize = keyValue.second->getValue();
			else if (keyValue.first == "step")
				pixelsPerStep = keyValue.second->getValue();
		}
	);
	while (window.pollEvent(e))
	{
		switch (e.type) {
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::MouseEntered:
			this->inBounds = true;
			break;
		case sf::Event::MouseLeft:
			this->inBounds = false;
			break;
		case sf::Event::MouseButtonPressed:
			if (sf::Mouse::getPosition(window).y > SCREEN_HEIGHT - 50.0f)
			{
				std::for_each(
					this->buttons.begin(),
					this->buttons.end(),
					[&](std::pair<std::string, Button*> keyValue)
					{
						if (keyValue.second->getDrawable().getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
						{
							if (keyValue.first == "play" &&
								this->buttons["play"]->isEnabled())
							{
								this->simulating = !this->simulating;
							}
							else if (keyValue.first == "reset" &&
								this->buttons["reset"]->isEnabled())
							{
								this->population.clear();
							}
							else if (keyValue.first == "eraser" &&
								this->buttons["eraser"]->isEnabled())
							{
								this->penColour = sf::Color::White;
								this->buttons["eraser"]->enable(false);
								this->buttons["start"]->enable(true);
								this->buttons["finish"]->enable(true);
								this->buttons["wall"]->enable(true);
							}
							else if (keyValue.first == "start" &&
								this->buttons["start"]->isEnabled())
							{
								this->penColour = sf::Color::Green;
								this->buttons["eraser"]->enable(true);
								this->buttons["start"]->enable(false);
								this->buttons["finish"]->enable(true);
								this->buttons["wall"]->enable(true);
							}
							else if (keyValue.first == "finish" &&
								this->buttons["finish"]->isEnabled())
							{
								this->penColour = sf::Color::Red;
								this->buttons["eraser"]->enable(true);
								this->buttons["start"]->enable(true);
								this->buttons["finish"]->enable(false);
								this->buttons["wall"]->enable(true);
							}
							else if (keyValue.first == "wall" &&
								this->buttons["wall"]->isEnabled())
							{
								this->penColour = sf::Color::Blue;
								this->buttons["eraser"]->enable(true);
								this->buttons["start"]->enable(true);
								this->buttons["finish"]->enable(true);
								this->buttons["wall"]->enable(false);
							}
						}
					});
			}
			else
			{
				this->drawing = true;
			}
			break;
		case sf::Event::MouseButtonReleased:
			this->drawing = false;
			break;
		case sf::Event::MouseWheelMoved:
			if (e.mouseWheel.delta == 1 && this->brushSize != 40) this->brushSize++;
			else if (e.mouseWheel.delta == -1 && this->brushSize != 1) this->brushSize--;
			break;
		case sf::Event::Resized:
		{
			sf::FloatRect visibleArea(sf::Vector2f(0, 0), sf::Vector2f(e.size.width, e.size.height));
			window.setView(sf::View(visibleArea));
			SCREEN_HEIGHT = e.size.height;
			SCREEN_WIDTH = e.size.width;
		}
		break;
		case sf::Event::KeyPressed:
			switch (e.key.code)
			{
			case sf::Keyboard::Space:
				//
				break;
			}
			break;
		}

		if (this->inBounds && this->drawing && sf::Mouse::getPosition(window).y < SCREEN_HEIGHT - 50.0f)
		{
			if (this->penColour == sf::Color::White)
			{
				this->walls.erase(std::remove_if(
					this->walls.begin(),
					this->walls.end(),
					[&window](sf::CircleShape* wall)
					{
						int r = wall->getRadius();
						if (GameEngine::distance(wall->getPosition() + sf::Vector2f(r, r), sf::Vector2f(sf::Mouse::getPosition(window))) < r) {
							return true;
						}
						return false;
					}), this->walls.end());
				//remove start and finish
				if (this->start != nullptr && GameEngine::distance(sf::Vector2f(sf::Mouse::getPosition(window)), (*this->start) + sf::Vector2f(10, 10)) < 10)
					this->start = nullptr;
				if (this->finish != nullptr && GameEngine::distance(sf::Vector2f(sf::Mouse::getPosition(window)), *this->finish + sf::Vector2f(10, 10)) < 10)
					this->finish = nullptr;
			}
			else if (this->penColour == sf::Color::Green)
			{
				this->start = new sf::Vector2f(sf::Vector2f(sf::Mouse::getPosition(window)) + sf::Vector2f(-this->brushSize, -this->brushSize));
			}
			else if (this->penColour == sf::Color::Red)
			{
				this->finish = new sf::Vector2f(sf::Vector2f(sf::Mouse::getPosition(window)) + sf::Vector2f(-this->brushSize, -this->brushSize));
			}
			else
			{
				if ((this->penColour == sf::Color::Green && this->start != nullptr) ||
					(this->penColour == sf::Color::Red && this->finish != nullptr))
					break;
				sf::CircleShape* brush = new sf::CircleShape(this->brushSize);
				brush->setFillColor(this->penColour);
				brush->setPosition(sf::Vector2f(sf::Mouse::getPosition(window)) + sf::Vector2f(-this->brushSize, -this->brushSize));
				if (this->penColour == sf::Color::Green)
				{
					sf::Vector2f v = brush->getPosition();
					this->start = &v;
				}
				else if (this->penColour == sf::Color::Red)
				{
					sf::Vector2f v = brush->getPosition();
					this->finish = &v;
				}
				else
				{
					this->walls.push_back(brush);
					dotIndex++;
				}

			}

		}

	}
}