#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cstdlib>
#include <math.h>
using namespace std;
using namespace sf;
class Shenron
{
private:
	RenderWindow* window;
	RectangleShape sprite;
	Texture* texture;
	bool switchSpawn = false;

	float timerMax;
	float timer;
	float dtMultiplier;

public:
	Shenron(Texture* texture);
	virtual ~Shenron();
	inline const Vector2f& getPosition() { return this->sprite.getPosition(); }
	inline const float& getTimer() const { return this->timer; }
	inline bool getSpawn() { return this->switchSpawn; }
	inline void setSpawn() { this->switchSpawn = !this->switchSpawn; }
	void Update(float deltaTime);
	void Draw(RenderTarget& target);
};

