#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <cstdlib>
#include <math.h>
using namespace std;
using namespace sf;
class TextTag
{
private:
	float dtMultiplier;
	Font* font;
	Text text;

	float speed;
	Vector2f direction;
	float timerMax;
	float timer;

public:
	TextTag(Font* font, string text, Color color,
		Vector2f position, unsigned int size, float timerMax);
	virtual ~TextTag();

	//Accessor
	inline const float& getTimer() const { return this->timer; }

	void Update(const float& dt);
	void Draw(RenderTarget& target);
};
