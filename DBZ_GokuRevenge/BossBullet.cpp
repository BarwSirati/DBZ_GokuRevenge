#include "BossBullet.h"

BossBullet::BossBullet(Texture *texture,Vector2f position, Vector2f size, Vector2f direction, float speed)
{
	this->texture = texture;
	this->position = position;
	this->size = size;
	this->direction = direction;
	this->speed = speed;
	this->sprite.setTexture(*this->texture);
	this->sprite.setPosition(this->position);
	this->sprite.setScale(this->size);
}

void BossBullet::Update(float deltaTime)
{
	this->sprite.move(normalize(this->direction) * this->speed * deltaTime);
}

void BossBullet::Draw(RenderTarget& target)
{
	target.draw(this->sprite);
}
