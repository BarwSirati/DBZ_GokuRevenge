#include "Enemy.h"

enum eTypes
{
	MOVELEFT,
	FOLLOW,
};

Enemy::Enemy(Texture* texture, Vector2u windowBounds,
	Vector2f direction,
	Vector2f scale, int type,
	int hpMax, int damageMax, int damageMin,
	int playerFollowNr)
{

	this->texture = texture;
	this->sprite.setTexture(*this->texture);
	this->sprite.setScale(scale);
	this->windowBounds = windowBounds;
	this->direction = direction;
	this->max = (rand() % 500 + 40);
	this->sprite.setPosition(windowBounds.x, this->max);
	this->type = type;

	this->hpMax = hpMax;
	this->hp = this->hpMax;

	this->damageMax = damageMax;
	this->damageMin = damageMin;
	this->damageTimerMax = 4.f;
	this->damageTimer = 0;

	this->shootTimerMax = 15.f;
	this->shootTimer = this->shootTimerMax;

	this->playerFollowNr = playerFollowNr;
}

Enemy::~Enemy()
{
}

void Enemy::takeDamage(int damage)
{
	this->hp -= damage;
	this->damageTimer = this->damageTimerMax;
	if (this->hp <= 0)
		this->hp = 0;
}

void Enemy::Update(Vector2f playerPostion)
{
	Vector2f normalizedDir;

	switch (this->type)
	{
	case MOVELEFT:
		this->sprite.move(this->direction.x * 10.f, this->direction.y * 10.f);
		this->normalizedDir = normalize(this->direction, vectorLength(this->direction));
		break;
	case FOLLOW:
		if (this->sprite.getPosition().x > playerPostion.x)
		{
			direction.x = playerPostion.x - this->sprite.getPosition().x;
			direction.y = playerPostion.y - this->sprite.getPosition().y;
		}
		this->normalizedDir = normalize(this->direction, vectorLength(this->direction));

		if (this->normalizedDir.y > 0.3)
			this->normalizedDir.y = 0.3;
		else if (this->normalizedDir.y < -0.3)
			this->normalizedDir.y = -0.3;

		if (this->normalizedDir.x > -0.7)
			this->normalizedDir.x = -0.7;

		this->sprite.setRotation(atan2(this->normalizedDir.y, this->normalizedDir.x) * 180 / 3.14159265359 + 180);

		this->sprite.move(this->normalizedDir.x * 3.f, this->normalizedDir.y * 3.f);
		break;
	default:
		break;
	}
	if (this->damageTimer > 0.f)
	{
		this->damageTimer -= 1.f;
		this->sprite.setColor(Color::Red);
		this->sprite.move(-10.f * this->normalizedDir.x * this->damageTimer, 0.f);
	}
	else
	{
		this->sprite.setColor(Color::White);
	}

}

void Enemy::Draw(RenderTarget& target)
{
	target.draw(this->sprite);

	for (size_t i = 0; i < this->bullets.size(); i++)
	{
		this->bullets[i].Draw(target);
	}
}
