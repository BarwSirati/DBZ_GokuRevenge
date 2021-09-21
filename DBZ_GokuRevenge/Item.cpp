#include "Item.h"

Item::Item(Texture* texture, Vector2f position, int star)
{
	this->texture = texture;
	this->position = position;
	this->sprite.setTexture(*this->texture);
	if (position.x > 1920)
		this->sprite.setPosition(1900, position.y);
	else
		this->sprite.setPosition(position);
	this->sprite.setScale(0.05f, 0.05f);
	this->star = star;
}

Item::~Item()
{
}

void Item::Update()
{
	this->sprite.move(-3.f, 0.8f);
}

void Item::Draw(RenderTarget& target)
{
	target.draw(this->sprite);
}
