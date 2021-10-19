#include "Boss.h"

Boss::Boss(Texture* texture,Texture *bulletTexture, Vector2f position, int hp, int hpMax, int damage, int damageMax)
{
	this->texture = texture;
	this->bulletTexture = bulletTexture;
	this->sprite.setTexture(*this->texture);
	this->hpMax = hpMax;
	this->damageMax = damageMax;
	this->hp = this->hpMax;
	this->damage = this->damageMax;
	this->sprite.setScale(0.5f, 0.5f);
	this->sprite.setPosition(position);
	this->damageTimerMax = 4.f;
	this->damageTimer = 0;
	this->shootTimerMax = 0.15f;
	this->shootTimer = shootTimerMax;
	this->angle = 0;
	this->sweepSpeed = 80;
	this->bulletDir = normalize(Vector2f(-1, 1));
}

void Boss::Update(float deltaTime)
{
	this->sprite.move(-80.f * deltaTime, 0);
	this->angle += deltaTime * this->sweepSpeed;
	if (this->shootTimer >= this->shootTimerMax)
	{
		this->bullets.push_back(BossBullet(this->bulletTexture,this->sprite.getPosition(), Vector2f(0.1f, 0.1f), rotateVector(this->bulletDir, this->angle), 500.f));
		this->shootTimer = 0;
	}
	else
	{
		this->shootTimer += deltaTime;
	}
	if (this->damageTimer > 0.f)
	{
		this->damageTimer -= 1.f;
		this->sprite.setColor(Color::Red);
		
	}
	else
	{
		this->sprite.setColor(Color::White);
	}
}

void Boss::Draw(RenderTarget& target)
{
	target.draw(this->sprite);
	for (size_t i = 0; i < bullets.size(); i++)
	{
		this->bullets[i].Draw(target);
	}
}
