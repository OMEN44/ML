#include "GameEngine.h"

void GameEngine::input(sf::Event& e, sf::RenderWindow& window)
{
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
			if (this->showControllPanel)
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
				this->showControllPanel = !this->showControllPanel;
				break;
			}
			break;
		}



		if (this->inBounds && this->drawing && !this->showControllPanel)
		{
			if (this->penColour == sf::Color::White)
			{
				std::vector<std::string> forRemoval;
				std::for_each(
					this->entities.begin(),
					this->entities.end(),
					[&](std::pair<std::string, sf::Drawable*> keyValue) {
						if (auto circleShape = dynamic_cast<sf::CircleShape*>(this->getEntity(keyValue.first))) {
							int r = circleShape->getRadius();
							if (GameEngine::distance(circleShape->getPosition() + sf::Vector2f(r, r), sf::Vector2f(sf::Mouse::getPosition(window))) < r) {
								forRemoval.push_back(keyValue.first);
							}
						}
					}
				);
				for (std::string s : forRemoval)
				{
					if (s == "start")
						this->start = nullptr;
					if (s == "finish")
						this->finish = nullptr;
					this->deleteEntity(s);
				}
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
					this->addEntity("start", brush);
					this->start = brush;
				}
				else if (this->penColour == sf::Color::Red)
				{
					this->addEntity("finish", brush);
					this->finish = brush;
				}
				else
				{
					this->addEntity(std::to_string(dotIndex), brush);
					dotIndex++;
				}

			}

		}

	}
}