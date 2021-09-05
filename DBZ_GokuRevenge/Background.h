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
class Background
{
private:
	RectangleShape body[2];
	Vector2f position;
	Vector2f size;

	float speed;
public:
	Background(Texture* texture, float speed);

	void Update(float deltaTime);
	void Draw(RenderWindow& window);
};

