#pragma once
#include "Bullet.h"
class Item
{
private:
	Texture* texture;
	Sprite sprite;
	Vector2f position;
	int star;
public:
	Item(Texture* texture, Vector2f position, int star);
	virtual ~Item();
	inline FloatRect getGlobalBounds() const { return this->sprite.getGlobalBounds(); }
	inline int getStar() { return this->star; };
	inline Vector2f getPosition() const { return this->sprite.getPosition(); }
	void Update();
	void Draw(RenderTarget& target);
};

