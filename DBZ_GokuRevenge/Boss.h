#pragma once
#define PI 3.14159265
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "BossBullet.h"
using namespace std;
using namespace sf;
class Boss
{
private:
	Sprite sprite;
	Texture* texture;
	Texture* bulletTexture;
	Vector2f bulletDir;
	vector<BossBullet> bullets;
	int hp;
	int hpMax;
	int damage;
	int damageMax;
	float damageTimer;
	float damageTimerMax;
	float angle;
	float sweepSpeed;
	float shootTimerMax;
	float shootTimer;
public:
	Boss(Texture* texture, Texture* bulletTexture, Vector2f position, int hp, int hpMax, int damage, int damageMax);
	void Update(float deltaTime);
	void Draw(RenderTarget& target);
	inline vector<BossBullet>& getBullets() { return this->bullets; }
	inline void takeDamage(int damage)
	{
		hp -= damage;
		this->damageTimer = this->damageTimerMax;
	}
	inline const bool isDead() const { return this->hp <= 0; }
	inline FloatRect getGlobalBounds() const { return this->sprite.getGlobalBounds(); }
	inline Vector2f getPosition() const { return this->sprite.getPosition(); }
	inline int getHpMax() { return this->hpMax; }
	inline int getHp() { return this->hp; }
	inline int getDamage() { return this->damage; }
	inline float lenght(Vector2f vec) { return sqrt(vec.x * vec.x + vec.y * vec.y); }
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

