#include "Player.h"

unsigned Player::players = 0;

enum controls
{
	UP = 0,
	DOWN,
	LEFT,
	RIGHT,
};
Player::Player(Texture* texture, Texture* bulletTexture, int imageCount, float switchTime,
	int UP, int DOWN, int LEFT, int RIGHT, int SHOOT)
	: level(15), exp(0),
	hp(300), hpMax(300),
	damage(25), damageMax(50),
	score(0)
{

	if (!this->buffer.loadFromFile("Audio/shoot.wav"))
	{
		cout << "Error load file" << endl;
	}
	//Stats
	this->expNext = 20 + static_cast<int>(
		(50 / 3) * ((pow(level, 3) - 6 * pow(level, 2)) + 17 * level - 12));
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	currentImage.x = 0;

	uvRect.width = texture->getSize().x / imageCount;
	uvRect.height = texture->getSize().y;

	this->texture = texture;
	this->bulletTexture = bulletTexture;
	this->sprite.setTexture(*this->texture);
	this->sprite.setScale(0.7f, 0.7f);

	this->shootTimerMax = 30.f;
	this->shootTimer = this->shootTimerMax;
	this->damageTimerMax = 10.f;
	this->damageTimer = this->damageTimerMax;

	this->controls[controls::UP] = UP;
	this->controls[controls::DOWN] = DOWN;
	this->controls[controls::LEFT] = LEFT;
	this->controls[controls::RIGHT] = RIGHT;

	this->maxVelocity = 25.f;
	this->acceleration = 0.8f;
	this->stabilizerForce = 0.4f;
}

Player::~Player()
{
}
void Player::takeDamage(int damage)
{
	this->hp -= damage;
	this->damageTimer = 0;
	this->sprite.move(-10.f, 0.f);
	this->currentVelocity.x += -this->normDir.x * 10.f;
	this->currentVelocity.y += -this->normDir.y * 10.f;
}
bool Player::UpdateLeveling()
{
	if (this->exp >= this->expNext)
	{
		this->level++;
		if (this->level == 5)
		{
			transform = 2;
			this->hpMax *= 1.5;
			this->damageMax += 5;
			this->damage += 3;
		}
		else if (this->level == 10)
		{
			transform = 3;
			this->hpMax *= 1.8;
			this->damageMax += 10;
			this->damage += 6;
		}
		else if (this->level == 15)
		{
			transform = 4;
			this->hpMax *= 3;
			this->damageMax *= 3;
			this->damage *= 1.5;
		}
		else if (this->level > 15)
		{
			if (this->shootTimerMax > 15)
			{
				this->shootTimerMax -= 0.1f;
				this->shootTimer = this->shootTimerMax;
			}
			this->hpMax *= 1.1;
			this->damageMax += 4;
			this->damage += 2;

		}
		else
		{
			this->hpMax += 5;
			this->damageMax += 1;
			this->damage++;
		}

		this->hp = hpMax;
		this->exp -= this->expNext;
		this->expNext = static_cast<int>(
			(50 / 3) * ((pow(level, 3) - 6 * pow(level, 2)) + 17 * level - 12));
		return true;
	}
	return false;
}
void Player::Movement()
{
	//Update normalized direction
	this->normDir = normalize(this->currentVelocity, vectorLength(this->currentVelocity));
	//UP
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::UP])))
	{
		this->direction.x = 0.f;
		this->direction.y = -1.f;

		if (this->currentVelocity.y > -this->maxVelocity && this->direction.y < 0)
			this->currentVelocity.y += this->direction.y * this->acceleration;
	}
	//DOWN
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::DOWN])))
	{
		this->direction.x = 0.f;
		this->direction.y = 1.f;

		if (this->currentVelocity.x < this->maxVelocity && this->direction.x> 0)
			this->currentVelocity.x += this->direction.x * this->acceleration;

		if (this->currentVelocity.y < this->maxVelocity && this->direction.y> 0)
			this->currentVelocity.y += this->direction.y * this->acceleration;
	}
	//LEFT
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::LEFT])))
	{
		this->direction.x = -1.f;
		this->direction.y = 0.f;

		if (this->currentVelocity.x > -this->maxVelocity && this->direction.x < 0)
			this->currentVelocity.x += this->direction.x * this->acceleration;
	}
	//RIGHT
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::RIGHT])))
	{
		this->direction.x = 1.f;
		this->direction.y = 0.f;

		if (this->currentVelocity.x < this->maxVelocity && this->direction.x> 0)
			this->currentVelocity.x += this->direction.x * this->acceleration;
	}
	//Drag force
	if (this->currentVelocity.x > 0)
	{
		this->currentVelocity.x -= this->stabilizerForce;
		if (this->currentVelocity.x < 0)
		{
			this->currentVelocity.x = 0;
		}
	}
	else if (this->currentVelocity.x < 0)
	{
		this->currentVelocity.x += this->stabilizerForce;
		if (this->currentVelocity.x > 0)
		{
			this->currentVelocity.x = 0;
		}
	}
	if (this->currentVelocity.y > 0)
	{
		this->currentVelocity.y -= this->stabilizerForce;
		if (this->currentVelocity.y < 0)
		{
			this->currentVelocity.y = 0;
		}
	}
	else if (this->currentVelocity.y < 0)
	{
		this->currentVelocity.y += this->stabilizerForce;
		if (this->currentVelocity.y > 0)
		{
			this->currentVelocity.y = 0;
		}
	}

	//Final move
	this->sprite.move(this->currentVelocity.x, this->currentVelocity.y);

	if (this->getPosition().y < 40.4f)
		this->sprite.setPosition(this->getPosition().x, 40.4f);
	if (this->getPosition().x < 12.0f)
		this->sprite.setPosition(12.0f, this->getPosition().y);
	if (this->getPosition().x > 1790.0f)
		this->sprite.setPosition(1790.0f, this->getPosition().y);
	if (this->getPosition().y > 542.0f)
		this->sprite.setPosition(this->getPosition().x, 542.0f);
}
void Player::Combat(RenderWindow& target)
{
	if (Mouse::isButtonPressed(Mouse::Left) && this->shootTimer >= this->shootTimerMax)
	{
		this->sound.setBuffer(this->buffer);
		this->sound.play();

		this->PlayerPos = this->sprite.getPosition();
		this->MousePos = Vector2f(Mouse::getPosition(target));

		this->aimDir = this->MousePos - this->PlayerPos;

		this->aimDirNorm = this->aimDir / sqrt((this->aimDir.x * this->aimDir.x + this->aimDir.y * this->aimDir.y));
		this->bullets.push_back(
			Bullet(bulletTexture,
				this->playerCenter,
				this->aimDirNorm, 2.f,
				50.f, 1.5f));
		this->shootTimer = 0; //Reset Timer
	}
	//DAMAGE
	if (this->isDamageCooldown())
	{
		if ((int)this->damageTimer % 2 == 0)
		{
			this->sprite.setColor(Color::Red);
		}
		else
		{
			this->sprite.setColor(Color::White);
		}
	}
	else
	{
		this->sprite.setColor(Color::White);
	}
}

void Player::Update(Vector2u windowBounds, float deltaTime)
{
	totalTime += deltaTime;

	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImage.x++;

		if (currentImage.x >= imageCount)
		{
			currentImage.x = 0;
		}
	}

	uvRect.left = currentImage.x * uvRect.width;
	sprite.setTextureRect(uvRect);

	//Update Timers
	if (this->shootTimer < this->shootTimerMax)
	{
		this->shootTimer++;
	}
	if (this->damageTimer < this->damageTimerMax)
	{
		this->damageTimer++;
	}
	//Update positions
	this->playerCenter.x = this->sprite.getPosition().x +
		this->sprite.getGlobalBounds().width / 2;
	this->playerCenter.y = this->sprite.getPosition().y +
		this->sprite.getGlobalBounds().height / 2;

	this->Movement();

}

void Player::Draw(RenderWindow& target)
{
	target.draw(this->sprite);
	for (size_t i = 0; i < this->bullets.size(); i++)
	{
		this->bullets[i].Draw(target);
	}
	this->Combat(target);
}
