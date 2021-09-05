#pragma once
#include "Bullet.h"
#include "SFML/Audio.hpp"
class Player
{
private:
	SoundBuffer buffer;
	Sound sound;

	Vector2f playerCenter;

	int shootTimer;
	int shootTimerMax;
	int damageTimer;
	int damageTimerMax;

	Texture* texture;

	Sprite sprite;
	RectangleShape hitBox;

	Texture* bulletTexture;
	vector<Bullet> bullets;

	int controls[5];
	Vector2f currentVelocity;
	float maxVelocity;
	float acceleration;
	Vector2f direction;
	float stabilizerForce;
	Vector2f normDir;
	Vector2f movementDirection;

	bool soundHeld = false;

	int level;
	int exp;
	int expNext;

	int hp;
	int hpMax;

	int damage;
	int damageMax;

	int score;

	int transform = 1;

	int imageCount;
	Vector2u currentImage;

	float totalTime;
	float switchTime;

public:
	Player(Texture* texture, Texture* bulletTexture, int imageCount, float switchTime,
		int UP = Keyboard::W,
		int DOWN = Keyboard::S,
		int LEFT = Keyboard::A,
		int RIGHT = Keyboard::D,
		int SHOOT = Keyboard::Space);
	virtual ~Player();

	//Accessors
	inline vector<Bullet>& getBullets() { return this->bullets; }
	inline const Vector2f& getPosition() { return this->sprite.getPosition(); }
	inline const String getHpAsString() const { return to_string(this->hp) + '/' + to_string(this->hpMax); }
	inline const int getDamage() const { return rand() % this->damageMax + this->damage; }
	inline FloatRect getGlobalBounds() const { return this->sprite.getGlobalBounds(); }
	inline const int& getHp() const { return this->hp; }
	inline const int& getHpMax() const { return this->hpMax; }
	void takeDamage(int damage);
	inline bool isAlive() const { return this->hp > 0; }
	inline const int& getLevel() const { return this->level; }
	inline const int& getExp() const { return this->exp; }
	inline const int& getExpNext() const { return this->expNext; }
	inline bool gainExp(int exp)
	{
		this->exp += exp;
		return this->UpdateLeveling();
	}
	inline const int checkTransform()
	{
		return this->transform;
	}
	inline void resetTransform() {
		this->transform = 1;
	}
	inline bool isDamageCooldown() { return this->damageTimer < this->damageTimerMax; };
	inline const int Damage() const { return this->damage; }
	//Function
	bool UpdateLeveling();
	void Combat();
	void Movement();
	void Update(Vector2u windowBounds, float deltaTime);
	void Draw(RenderTarget& target);

	//Statics
	static unsigned players;

	//Regular function
	float vectorLength(Vector2f v)
	{
		return sqrt(pow(v.x, 2) + pow(v.y, 2));
	}
	Vector2f normalize(Vector2f v, float length)
	{
		if (length == 0)
		{
			return Vector2f(0.f, 0.f);
		}
		else
		{
			return v / length;
		}

	}

public:
	IntRect uvRect;
};
