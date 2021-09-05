#include "Shenron.h"

Shenron::Shenron(Texture* texture)
{
	this->dtMultiplier = 62.5f;
	this->window = window;
	this->texture = texture;
	this->sprite.setTexture(this->texture);
	this->sprite.setSize(Vector2f(this->texture->getSize()));
	this->sprite.setScale(1.f, 1.f);
	this->sprite.setPosition(0.f, 0.f);

	this->timerMax = 400.f;
	this->timer = this->timerMax;
}

Shenron::~Shenron()
{

}

void Shenron::Update(float deltaTime)
{
	if (this->timer > 0.f)
	{
		this->timer -= 1.f * deltaTime * this->dtMultiplier;
	}
}

void Shenron::Draw(RenderTarget& target)
{
	if (switchSpawn)
	{
		target.draw(this->sprite);
	}
}
