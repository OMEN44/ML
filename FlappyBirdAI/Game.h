#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class RenderObject
{
public:
	//============== CONSTRUCTERS AND DESTRUCTERS ==============
	RenderObject(sf::Vector2f position, std::vector<sf::Shape*> body)
		: position(position), body(body) {}
	RenderObject(sf::Vector2f position)
		: position(position) {}
	~RenderObject();

	//============== PUBLIC API ==============
	virtual void onCreate() {}
	virtual void onUpdate(sf::Time deltaTime) {}
	virtual void onRender(sf::RenderWindow &window)
	{
		std::for_each(
			this->body.begin(),
			this->body.end(),
			[&window](sf::Shape* bodyMember) {
				window.draw(*bodyMember);
			}
		);
	}
	
	//============== GETTERS AND SETTERS ==============
	void move(sf::Vector2f distance);
	void setPosition(sf::Vector2f position);
	sf::Vector2f getPosition();
	void addBodyMember(sf::Shape* member);
	std::vector<sf::Shape*>& getBody();

private:
	sf::Vector2f position;
	std::vector<sf::Shape*> body;
};

extern float screenHeight;
extern float screenWidth;

class Game
{
private:
	std::map<std::string, RenderObject*> uniqueObjects;
	std::vector<RenderObject*> genericObjects;
	sf::Time deltaTime;
	bool paused = false;
protected:
	sf::RenderWindow window;
public:

	/// <summary>
	///	Creates an instance of the game. 
	/// Should handle all rendering and intputs through overriding the appropriate methods.
	/// </summary>
	/// <param name="title">Title of the window</param>
	/// <param name="frameRateLimit">Max frame rate, set to -1 for unlimited</param>
	Game(std::string title, int frameRateLimit);
	~Game();

	/// <summary>
	/// When this function is called the game starts to run untill the end() function is called or the window is closed.
	/// </summary>
	void run();
	void end();
	void pause();

	void addObject(std::string name, RenderObject* object);
	void addObject(RenderObject* object);
	void delObject(std::string name);
	void delObject(int index);
	void clearGenericObjects();
	RenderObject* getObject(std::string name);
	RenderObject* getObject(int index);
	std::vector<RenderObject*> getGenericObjects();
	bool objectCollision(RenderObject& object1, RenderObject& object2);
	bool objectCollision(const std::string& objectName1, const std::string& objectName2);
	bool objectCollisionWithGeneric(const std::string& objectName);

	virtual void start();
	virtual void beforeUpdate();
	virtual void onUpdate();
	virtual void beforeRender();
	virtual void onRender();
	virtual void onInput(sf::Event& e);
	virtual void onKeyPress(sf::Event& e);
	virtual void onKeyRelease(sf::Event &e);

	virtual void onPause();
	virtual void pauseInput();
	virtual void pauseRender();
	virtual void pauseUpdate();
};