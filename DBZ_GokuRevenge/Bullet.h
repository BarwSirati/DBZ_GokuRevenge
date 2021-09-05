#pragma once
#include "TextTag.h"
class Bullet
{
private:
	Texture* texture;
	Sprite sprite;

	Vector2f currentVelocity;
	float maxVelocity;
	float acceleration;
	Vector2f direction;

public:
	Bullet(Texture* texture, Vector2f position,
		Vector2f direction, float initialVelocity,
		float maxVelocity, float acceleration);
	virtual ~Bullet();
	//Accessor
	inline FloatRect getGlobalBounds() const
	{
		return this->sprite.getGlobalBounds();
	}
	inline const Vector2f& getPosition() const
	{
		return this->sprite.getPosition();
	}
	//Function
	void Movement();

	void Update();
	void Draw(RenderTarget& target);
};
