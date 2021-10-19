#pragma once
#define PI 3.14159265
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
using namespace std;
using namespace sf;
class BossBullet
{
private:
	Sprite sprite;
	Texture* texture;
	
	Vector2f direction;
	Vector2f position;
	Vector2f size;
	float speed;
public:
	BossBullet(Texture *texture,Vector2f position, Vector2f size, Vector2f direction, float speed);
	void Update(float deltaTime);
	void Draw(RenderTarget& target);
	inline FloatRect getGlobalBounds() const
	{
		return this->sprite.getGlobalBounds();
	}
	inline const Vector2f& getPosition() const
	{
		return this->sprite.getPosition();
	}
	inline float lenght(Vector2f vec)
	{
		return sqrt(vec.x * vec.x + vec.y * vec.y);
	}

	inline Vector2f normalize(Vector2f vec)
	{
		float len = lenght(vec);
		if (len != 0)
			return vec / len;
		return vec;
	}

	Vector2f rotateVector(Vector2f dir, float angle)
	{
		if (dir == Vector2f(0, 0))
			return Vector2f(0, 0);
		float nx = dir.x * cos((angle)*PI / 180) - dir.y * sin((angle)*PI / 180);
		float ny = dir.x * sin((angle)*PI / 180) + dir.y * cos((angle)*PI / 180);
		return Vector2f(nx, ny);
	}
};

