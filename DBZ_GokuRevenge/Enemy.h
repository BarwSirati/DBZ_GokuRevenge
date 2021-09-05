#pragma once
#include "Bullet.h"
class Enemy
{
private:
	Texture* texture;
	Sprite sprite;
	Vector2u windowBounds;
	Vector2f direction;
	Vector2f normalizedDir;

	vector<Bullet> bullets;

	float maxVelocity;
	float max;

	int type;
	int hp;
	int hpMax;

	int damageMin;
	int damageMax;

	int damageTimer;
	int damageTimerMax;

	float shootTimerMax;
	float shootTimer;

	int playerFollowNr;

public:
	Enemy(Texture* texture, Vector2u windowBounds,
		Vector2f direction,
		Vector2f scale, int type,
		int hpMax, int damageMax, int damageMin,
		int playerFollowNr);
	virtual ~Enemy();
	inline const int getDamage() const { return (rand() % this->damageMax + this->damageMin); }
	inline const int getHP() const { return this->hp; }
	inline const int getHPMax() const { return this->hpMax; }
	inline const bool isDead() const { return this->hp <= 0; }
	inline FloatRect getGlobalBounds() const { return this->sprite.getGlobalBounds(); }
	inline Vector2f getPosition() const { return this->sprite.getPosition(); }
	inline const int& getPlayerFollowNr() const { return this->playerFollowNr; }

	//Function
	void takeDamage(int damage);
	void Update(Vector2f playerPostion);
	void Draw(RenderTarget& target);

	float vectorLength(Vector2f v)
	{
		return sqrt(pow(v.x, 2) + pow(v.y, 2));
	}
	Vector2f normalize(Vector2f v, float length)
	{
		return v / length;
	}
};