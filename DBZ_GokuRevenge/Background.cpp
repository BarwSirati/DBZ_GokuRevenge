#include "Background.h"

Background::Background(Texture* texture, float speed)
{
	this->speed = speed;
	this->size = Vector2f(1920.0f, 1080.0f);


	for (size_t i = 0; i < 2; i++)
	{
		this->body[i].setSize(size);
		this->body[i].setTexture(texture);
	}
	if (speed < 0)
	{
		this->body[1].setPosition(size.x - 2.0f, 0.0f);
	}
	else
	{
		this->body[1].setPosition(-size.x + 4.0f, 0.0f);
	}
}

void Background::Update(float deltaTime)
{
	for (size_t i = 0; i < 2; i++)
	{
		this->position = body[i].getPosition();
		this->body[i].move(this->speed * deltaTime, 0);

		if (this->position.x <= -size.x && this->speed < 0)
		{
			this->body[i].setPosition(size.x - 4.0f, this->position.y);
		}
		else if (this->position.x >= this->size.x && this->speed > 0)
		{
			this->body[i].setPosition(-size.x + 4.0f, this->position.y);
		}
	}
}

void Background::Draw(RenderWindow& window)
{
	window.draw(body[1]);
	window.draw(body[0]);
}
