#include "Game.h"
Game::Game(RenderWindow* window)
{
	//Sounds
	for (size_t i = 0; i < 9; i++)
	{
		if (!this->buffer[i].loadFromFile("Audio/" + to_string(i + 1) + ".wav"))
			cout << "Error load file" << endl;
		this->sound[i].setBuffer(this->buffer[i]);
	}
	this->sound[2].setVolume(100);
	this->sound[6].setVolume(100);
	this->sound[7].setVolume(100);

	this->window = window;
	this->window->setFramerateLimit(70);
	this->scoreMultiplier = 1;
	this->score = 0;
	this->multiplierAdderMax = 10;
	this->multiplierAdder = 0;
	this->multiplierTimerMax = 400.f;
	this->multiplierTimer = this->multiplierTimerMax;

	//Font
	this->font.loadFromFile("Fonts/Dosis-Light.ttf");

	//Init texture
	this->playerTexture.loadFromFile("Textures/Character/GokuSprite1.png");
	this->bulletTexture.loadFromFile("Textures/Character/beem/beem1.png");
	this->shenronTexture.loadFromFile("Textures/Items/shenron.png");
	this->enemy01Texture.loadFromFile("Textures/Enemy/saibaiman.png");

	this->BackgroundTexture[0].loadFromFile("Textures/Backgrounds/GamePlay/sky.jpg");
	this->BackgroundTexture[1].loadFromFile("Textures/Backgrounds/GamePlay/rock3.png");
	this->BackgroundTexture[2].loadFromFile("Textures/Backgrounds/GamePlay/rock2.png");
	this->BackgroundTexture[3].loadFromFile("Textures/Backgrounds/GamePlay/rock.png");

	this->backgrounds.push_back(Background(&this->BackgroundTexture[0], -60.f));
	this->backgrounds.push_back(Background(&this->BackgroundTexture[1], -120.f));
	this->backgrounds.push_back(Background(&this->BackgroundTexture[2], -180.f));
	this->backgrounds.push_back(Background(&this->BackgroundTexture[3], -380.f));

	float posY = 620.f;
	for (size_t i = 0; i < 2; i++)
	{
		this->menuOverTexture[i].loadFromFile("Textures/UI/menu/" + to_string(i) + ".png");
		this->menuOver[i].setTexture(&this->menuOverTexture[i]);
		this->menuOver[i].setSize(Vector2f(this->menuOverTexture[i].getSize()));
		this->menuOver[i].setOrigin(this->menuOverTexture[i].getSize().x / 2, this->menuOverTexture[i].getSize().y / 2);
		this->menuOver[i].setPosition(550.f, posY);
		this->menuOver[i].setScale(0.55f, 0.55f);
		posY += 190;
	}

	this->GameOverTexture.loadFromFile("Textures/Backgrounds/GameOver/background.jpg");
	this->GameOver.setTexture(&this->GameOverTexture);
	this->GameOver.setSize(Vector2f(this->window->getSize()));
	this->GameOver.setPosition(0.f, 0.f);

	//Items texture
	for (size_t i = 0; i < 7; i++)
		this->itemTexture[i].loadFromFile("Textures/Items/" + to_string(i + 1) + ".png");

	//UI Texture
	this->playerBar.loadFromFile("Textures/UI/player_bar.png");
	this->playerImage.loadFromFile("Textures/Character/profile/GokuProfile.png");
	this->playerImage2.loadFromFile("Textures/Character/profile/GokuProfile2.png");
	this->playerImage3.loadFromFile("Textures/Character/profile/GokuProfile3.png");
	this->playerImage4.loadFromFile("Textures/Character/profile/GokuProfile4.png");

	//UI button
	this->pause.loadFromFile("Textures/UI/menu/pause.png");
	this->menu.loadFromFile("Textures/UI/menu/main.png");
	this->resume.loadFromFile("Textures/UI/menu/resume.png");

	//UI Texture Setting Value
	this->playerUiBar.setTexture(&this->playerBar);
	this->playerUiBar.setPosition(0.f, 698.f);
	this->playerUiBar.setSize(Vector2f(this->playerBar.getSize()));

	this->playerProfile.setTexture(&this->playerImage);
	this->playerProfile.setPosition(28.f, 810.f);
	this->playerProfile.setSize(Vector2f(this->playerImage.getSize()));

	this->enemySpawnTimerMax = 35.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;

	//Init player
	this->players.push_back(Player(&playerTexture, &bulletTexture, 2, 0.3f));
	this->playerAlive = this->players.size();
	this->InitUI();
}

Game::~Game()
{


}
void Game::InitUI()
{
	this->hp.setFont(this->font);
	this->hp.setCharacterSize(14);
	this->hp.setFillColor(Color::Black);
	this->hp.setPosition(this->window->getSize().x - 1065.f, this->window->getSize().y - 150.f);

	this->exp.setFont(this->font);
	this->exp.setCharacterSize(12);
	this->exp.setFillColor(Color::Black);
	this->exp.setPosition(this->window->getSize().x - 1065.f, this->window->getSize().y - 120.f);

	this->level.setFont(this->font);
	this->level.setCharacterSize(20);
	this->level.setFillColor(Color::White);
	this->level.setPosition(this->window->getSize().x - 1280.f, this->window->getSize().y - 90.f);

	this->damage.setFont(this->font);
	this->damage.setCharacterSize(18);
	this->damage.setFillColor(Color::White);
	this->damage.setPosition(this->window->getSize().x - 1280.f, this->window->getSize().y - 60.f);

	this->playerExpBar.setSize(Vector2f(80.f, 5.f));
	this->playerExpBar.setFillColor(Color::Yellow);

	this->playerHpBarBack.setSize(Vector2f(100.f, 10.f));
	this->playerHpBarBack.setFillColor(Color::White);

	this->playerHpBarInside.setFillColor(Color::Green);

	this->enemyText.setFont(this->font);
	this->enemyText.setCharacterSize(14);
	this->enemyText.setFillColor(Color::White);

	this->scoreText.setFont(this->font);
	this->scoreText.setCharacterSize(40);
	this->scoreText.setFillColor(Color::White);
	this->scoreText.setPosition(this->window->getSize().x - 720.f, this->window->getSize().y - 170.f);

	this->scoreLasted.setFont(this->font);
	this->scoreLasted.setCharacterSize(65);
	this->scoreLasted.setFillColor(Color::White);
	this->scoreLasted.setPosition(350.f, 420.f);

	this->gameOverText.setFont(this->font);
	this->gameOverText.setFillColor(Color::Red);
	this->gameOverText.setCharacterSize(40);
	this->gameOverText.setString("GAME OVER!");
	this->gameOverText.setPosition(this->window->getSize().x / 2 - 100.f, this->window->getSize().y / 2);

	this->name.setFont(this->font);
	this->name.setCharacterSize(20);
	this->name.setFillColor(Color::White);
	this->name.setPosition(this->window->getSize().x - 1300.f, this->window->getSize().y - 250.f);

	this->form.setFont(this->font);
	this->form.setCharacterSize(20);
	this->form.setFillColor(Color::White);
	this->form.setPosition(this->window->getSize().x - 1300.f, this->window->getSize().y - 180.f);

	this->hpUiBack.setSize(Vector2f(450.f, 20.f));
	this->hpUiBack.setFillColor(Color::White);
	this->hpUiBack.setPosition(this->window->getSize().x - 1280.f, this->window->getSize().y - 150.f);

	this->hpUiInside.setFillColor(Color::Green);
	this->hpUiInside.setPosition(this->window->getSize().x - 1280.f, this->window->getSize().y - 150.f);

	this->expBack.setSize(Vector2f(450.f, 15.f));
	this->expBack.setFillColor(Color::White);
	this->expBack.setPosition(this->window->getSize().x - 1280.f, this->window->getSize().y - 120.f);

	this->expInside.setFillColor(Color::Yellow);
	this->expInside.setSize(Vector2f(450.f, 10.f));
	this->expInside.setPosition(this->window->getSize().x - 1280.f, this->window->getSize().y - 120.f);


	this->menuUI[0].setTexture(&this->pause);
	this->menuUI[0].setSize(Vector2f(this->pause.getSize()));
	this->menuUI[0].setPosition(this->window->getSize().x + 40, this->window->getSize().y - 80.f);
	this->menuUI[0].setOrigin(this->pause.getSize().x / 2, this->pause.getSize().y / 2);


	this->menuUI[1].setTexture(&this->menu);
	this->menuUI[1].setSize(Vector2f(this->menu.getSize()));
	this->menuUI[1].setPosition(this->window->getSize().x + 40, this->window->getSize().y + 20);
	this->menuUI[1].setOrigin(this->menu.getSize().x / 2, this->menu.getSize().y / 2);

	for (size_t i = 0; i < 2; i++)
	{
		this->menuUI[i].setSize(Vector2f(280.f, 80.f));
	}
}

void Game::UpdateUIPlayer(int index)
{
	//EXP BARS
	this->playerExpBar.setPosition(
		this->players[index].getPosition().x + 10.f,
		this->players[index].getPosition().y - 25.f);
	this->playerExpBar.setScale(
		(static_cast<float>(this->players[index].getExp()) / this->players[index].getExpNext()),
		1.f);
	//HP BARS
	this->playerHpBarInside.setSize(Vector2f((this->players[index].getHp() * 100.0f) / this->players[index].getHpMax(), this->playerHpBarBack.getSize().y));
	this->playerHpBarInside.setPosition(
		this->players[index].getPosition().x + 10.f,
		this->players[index].getPosition().y - 35.f);
	this->playerHpBarBack.setPosition(
		this->players[index].getPosition().x + 10.f,
		this->players[index].getPosition().y - 35.f);

	//Ui Text

	this->form.setString("Form : Goku " + this->textForm[this->players[index].checkTransform() - 1]);
	this->hpUiInside.setSize(Vector2f((this->players[index].getHp() * 450.f) / this->players[index].getHpMax(), this->hpUiBack.getSize().y));
	this->hp.setString(this->players[index].getHpAsString());
	this->expInside.setScale((static_cast<float>(this->players[index].getExp()) / this->players[index].getExpNext()), 1.5f);
	this->exp.setString(to_string(this->players[index].getExp()) + " / " + to_string(this->players[index].getExpNext()));
	this->damage.setString("Damage Min : " + to_string(this->players[index].Damage()));
	this->level.setString("Level : " + to_string(this->players[index].getLevel()));

	//Ui dragonBall In Player Bar 
	float dragonBallPos = 800;
	for (int i = 0; i < 7; i++)
	{
		this->dragonBall[i].setTexture(&itemTexture[i]);
		this->dragonBall[i].setSize(Vector2f(itemTexture[i].getSize()));
		this->dragonBall[i].setScale(0.04f, 0.04f);
		if (itemsKeep[i] == 0)
			this->dragonBall[i].setFillColor(Color(99, 99, 99));
		else
			this->dragonBall[i].setFillColor(Color::White);
		this->dragonBall[i].setPosition(dragonBallPos, 999.f);
		dragonBallPos += 40;
	}
	this->name.setString("Player Name : " + this->playerName);
}

void Game::UpdateUIEnemy(int index)
{
	this->enemyText.setPosition(
		this->enemies[index].getPosition().x, this->enemies[index].getPosition().y - 15.f
	);

	this->enemyText.setString(
		to_string(this->enemies[index].getHP()) + "/" +
		to_string(this->enemies[index].getHPMax()));
}

void Game::Update(float deltaTime)
{
	if (this->playerAlive > 0 && !this->pauseEvent)
	{
		for (Background& background : backgrounds)
			background.Update(deltaTime);

		//Update timers
		if (this->enemySpawnTimer < this->enemySpawnTimerMax)
			this->enemySpawnTimer++;
		if (this->multiplierTimer > 0.f)
		{
			this->multiplierTimer--;
			if (this->multiplierTimer <= 0.f)
			{
				this->multiplierTimer = 0.f;
				this->multiplierAdder = 0;
				this->scoreMultiplier = 1;
			}
		}

		this->scoreMultiplier = this->multiplierAdder / this->multiplierAdderMax + 1;

		//Spawn enemies
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax && !this->shenRon)
		{
			randTexture = rand() % 20 + 1;
			if (randTexture == 1)
			{
				randBoss = rand() % (20 * this->players[0].getLevel()) + 1;
				if (randBoss < 20 && this->players[0].getLevel() > 15)
				{
					this->enemy02Texture.loadFromFile("Textures/Enemy/freezer.png");
					this->enemies.push_back(Enemy(
						&enemy02Texture, this->window->getSize(),
						Vector2f(-1.f, 0.f),
						Vector2f(0.5f, 0.5f),
						0,
						this->players[0].getHpMax() * 2.15,
						this->players[0].getDamageMin() * 4.15,
						this->players[0].getDamageMin() * 2.15,
						rand() % this->playerAlive));
				}
				else
				{
					this->enemy02Texture.loadFromFile("Textures/Enemy/freezer.png");
					this->enemies.push_back(Enemy(
						&enemy02Texture, this->window->getSize(),
						Vector2f(-1.f, 0.f),
						Vector2f(0.2f, 0.2f),
						rand() % 2,
						this->players[0].getHpMax() * 1.15,
						this->players[0].getDamageMin() * 3,
						this->players[0].getDamageMin() * 2,
						rand() % this->playerAlive));
				}
			}
			else
			{
				this->enemies.push_back(Enemy(
					&enemy01Texture, this->window->getSize(),
					Vector2f(-1.f, 0.f), Vector2f(0.2f, 0.2f),
					rand() % 2,
					rand() % 3 + this->players[0].getHpMax() * 0.15,
					this->players[0].getDamageMin() * 2,
					this->players[0].getDamageMin() * 1.1,
					rand() % this->playerAlive));
			}

			this->enemySpawnTimer = 0;
		}
		for (size_t i = 0; i < this->players.size(); i++)
		{
			if (this->players[i].isAlive())
			{
				//Update Players
				this->players[i].Update(this->window->getSize(), deltaTime);
				if (this->players[i].checkTransform() == 2 && !this->transform[0])
				{
					this->sound[2].play();
					this->playerTexture.loadFromFile("Textures/Character/GokuSprite2.png");
					this->bulletTexture.loadFromFile("Textures/Character/beem/beem2.png");
					this->playerProfile.setTexture(&this->playerImage2);
					this->transform[0] = 1;
				}
				else if (this->players[i].checkTransform() == 3 && !this->transform[1])
				{
					this->sound[2].play();
					this->playerTexture.loadFromFile("Textures/Character/GokuSprite3.png");
					this->bulletTexture.loadFromFile("Textures/Character/beem/beem3.png");
					this->playerProfile.setTexture(&this->playerImage3);
					this->transform[1] = 1;
				}
				else if (this->players[i].checkTransform() == 4 && !this->transform[2])
				{
					this->sound[2].play();
					this->playerTexture.loadFromFile("Textures/Character/GokuSprite4.png");
					this->bulletTexture.loadFromFile("Textures/Character/beem/beem4.png");
					this->playerProfile.setTexture(&this->playerImage4);
					this->transform[2] = 1;
				}
				//Bullets update
				for (size_t k = 0; k < this->players[i].getBullets().size(); k++)
				{
					this->players[i].getBullets()[k].Update();
					//Enemy collision check
					for (size_t j = 0; j < this->enemies.size(); j++)
					{
						if (this->players[i].getBullets()[k].getGlobalBounds().intersects(this->enemies[j].getGlobalBounds()))
						{

							this->players[i].getBullets().erase(this->players[i].getBullets().begin() + k);
							//Sound
							this->sound[8].play();
							//Enemy take damage
							int damage = this->players[i].getDamage();
							if (this->enemies[j].getHP() > 0)
							{
								this->enemies[j].takeDamage(damage);

								//Create TextTag
								this->textTags.push_back(
									TextTag(
										&this->font,
										"-" + to_string(damage),
										Color(252, 94, 3),
										Vector2f(this->enemies[j].getPosition().x + 20.f,
											this->enemies[j].getPosition().y - 20.f),
										28, 20.f));
							}
							//Enemy dead
							if (this->enemies[j].getHP() <= 0)
							{
								//Random Items
								int randItems = (rand() % 100) + 1;

								if (randItems < 20)
								{
									int randItemTexture = (rand() % 7) + 1;
									this->items.push_back(Item(&itemTexture[randItemTexture - 1], this->enemies[j].getPosition(), randItemTexture));
								}

								//Gain Exp
								int exp = this->enemies[j].getHPMax() + (rand() % this->enemies[j].getHPMax() + 1);

								//Gain Score
								this->multiplierTimer = this->multiplierTimerMax;
								this->multiplierAdder++;

								//Update Score
								this->score += this->enemies[j].getHPMax() * this->scoreMultiplier;

								if (this->players[i].gainExp(exp))
								{
									this->sound[0].play();
									//Create TextTag
									this->textTags.push_back(
										TextTag(
											&this->font,
											"LEVEL UP",
											Color::Green,
											Vector2f(this->players[i].getPosition().x + 20.f,
												this->players[i].getPosition().y + 150.f),
											32, 30.f));
									if (this->enemySpawnTimerMax > 20)
									{
										this->enemySpawnTimerMax -= 0.3;
										this->enemySpawnTimer = this->enemySpawnTimerMax;
									}

								}
								//Create TextTag
								this->textTags.push_back(
									TextTag(
										&this->font,
										"+" + to_string(exp) + " exp",
										Color::Cyan,
										Vector2f(this->players[i].getPosition().x + 20.f,
											this->players[i].getPosition().y - 20.f),
										24, 25.f));
								this->enemies.erase(this->enemies.begin() + j);
							}
							return;
						}
					}
					//Window bounds check
					if (this->players[i].getBullets()[k].getPosition().x > this->window->getSize().x || this->players[i].getBullets()[k].getPosition().y < 0 || this->players[i].getBullets()[k].getPosition().y > this->window->getSize().y)
					{
						this->players[i].getBullets().erase(this->players[i].getBullets().begin() + k);
						return;
					}
				}
			}
			this->scoreText.setString("Score :    " + to_string(this->score));
			this->scoreLasted.setString("Score :    " + to_string(this->score));
		}
		//Dragon LevelUP
		if (this->itemsKeep[0] && this->itemsKeep[1]
			&& this->itemsKeep[2] && this->itemsKeep[3]
			&& this->itemsKeep[4] && this->itemsKeep[5]
			&& this->itemsKeep[6])
		{
			this->shenRon = true;
			this->sound[4].play();
			this->shenrons.push_back(Shenron(&shenronTexture));
			for (size_t i = 0; i < shenrons.size(); i++)
			{
				this->shenrons[i].setSpawn();
				this->textTags.push_back(
					TextTag(
						&this->font,
						"CLEAR ENEMIES",
						Color::Red,
						Vector2f(700, 540), 80, 100.f));
			}
			this->enemies.clear();
			for (size_t i = 0; i < players.size(); i++)
			{
				int exp = this->players[i].getExpNext();
				if (this->players[i].gainExp(exp))
				{
					this->sound[0].play();
					//Create TextTag
					this->textTags.push_back(
						TextTag(
							&this->font,
							"LEVEL UP",
							Color::Green,
							Vector2f(this->players[i].getPosition().x + 20.f,
								this->players[i].getPosition().y + 150.f),
							32, 30.f));
					if (this->enemySpawnTimerMax > 20)
					{
						this->enemySpawnTimerMax -= 0.3;
						this->enemySpawnTimer = this->enemySpawnTimerMax;
					}
				}
			}

			for (int i = 0; i < 7; i++)
			{
				this->itemsKeep[i] = 0;
				this->dragonBall[i].setFillColor(Color(99, 99, 99));
			}

		}
		//Update Items
		for (size_t i = 0; i < this->items.size(); i++)
		{
			//Items Player collision
			for (size_t k = 0; k < this->players.size(); k++)
			{
				if (this->players[k].getGlobalBounds().intersects(this->items[i].getGlobalBounds()))
				{

					this->sound[1].play();
					this->itemsKeep[this->items[i].getStar() - 1] = 1;
					//Create textTag
					this->textTags.push_back(
						TextTag(
							&this->font,
							to_string(this->items[i].getStar()) + " Star",
							Color::White,
							Vector2f(this->players[k].getPosition().x + 20.f, this->players[k].getPosition().y + 120.f),
							30, 15.f));
					this->items.erase(this->items.begin() + i);
					return;
				}
			}
			if (this->items[i].getPosition().x < 0 - this->items[i].getGlobalBounds().width)
			{
				this->items.erase(this->items.begin() + i);
				break;
			}
		}
		//Update Enemy
		for (size_t i = 0; i < this->enemies.size(); i++)
		{
			this->enemies[i].Update(this->players[this->enemies[i].getPlayerFollowNr()].getPosition());
			//Enemy Player collision
			for (size_t k = 0; k < this->players.size(); k++)
			{
				if (this->players[k].isAlive())
				{
					if (this->players[k].getGlobalBounds().intersects(this->enemies[i].getGlobalBounds())
						&& !this->players[k].isDamageCooldown())
					{
						this->sound[5].play();
						int damage = this->enemies[i].getDamage();

						this->players[k].takeDamage(damage);

						//Create textTag
						this->textTags.push_back(
							TextTag(
								&this->font,
								to_string(damage),
								Color::Red,
								Vector2f(this->players[k].getPosition().x + 20.f, this->players[k].getPosition().y - 20.f),
								30, 15.f));


						this->enemies.erase(this->enemies.begin() + i);
						//Player death
						if (!this->players[k].isAlive()) {
							this->sound[6].play();
							this->playerAlive = 0;
						}
						return;
					}
				}
			}
			if (this->enemies[i].getPosition().x < 0 - this->enemies[i].getGlobalBounds().width)
			{
				this->enemies.erase(this->enemies.begin() + i);
				break;
			}
		}
		//Update Texttags
		for (size_t i = 0; i < this->textTags.size(); i++)
		{
			this->textTags[i].Update(deltaTime);

			if (this->textTags[i].getTimer() <= 0.f)
			{
				this->textTags.erase(this->textTags.begin() + i);
				break;
			}
		}

		//Update Shenrons
		for (size_t i = 0; i < this->shenrons.size(); i++)
		{
			this->shenrons[i].Update(deltaTime);
			if (this->shenrons[i].getTimer() <= 0.f)
			{
				this->shenRon = false;
				this->shenrons[i].setSpawn();
				this->shenrons.erase(this->shenrons.begin() + i);
				break;
			}
		}

	}
}
void Game::GameOverMenu()
{
	for (size_t i = 0; i < 2; i++)
	{
		if (menuOver[i].getGlobalBounds().contains(Vector2f(Mouse::getPosition())))
		{
			this->menuOver[i].setScale(0.6f, 0.6f);
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				switch (i)
				{
				case 0:
					gameReset();
					break;
				case 1:
					this->setActionToZero = true;
					this->sound[7].play();
					break;
				default:
					break;
				}
			}
		}
		else
		{
			this->menuOver[i].setScale(0.55f, 0.55f);
		}
		this->window->draw(this->menuOver[i]);
	}
}
void Game::Pause()
{
	if ((this->menuUI[0].getGlobalBounds().contains(Vector2f(Mouse::getPosition())) && Mouse::isButtonPressed(Mouse::Left)) || Keyboard::isKeyPressed(Keyboard::P))
	{
		if (!this->resumeHeld)
		{
			this->resumeHeld = true;
			if (!this->resumeButton)
			{
				this->pauseEvent = true;
				this->resumeButton = true;
				this->menuUI[0].setTexture(&this->resume);
			}
			else
			{
				this->pauseEvent = false;
				this->resumeButton = false;
				this->menuUI[0].setTexture(&this->pause);
			}
		}
	}
	else
	{
		this->resumeHeld = false;
	}
}
void Game::Menu()
{
	if (this->menuUI[1].getGlobalBounds().contains(Mouse::getPosition().x, Mouse::getPosition().y) && Mouse::isButtonPressed(Mouse::Left) || Keyboard::isKeyPressed(Keyboard::M))
	{
		this->sound[7].play();
		Score(this->window).writeFile(this->playerName, this->score);
		this->setActionToZero = true;
	}
}
void Game::Draw()
{
	this->window->clear();
	for (Background& background : backgrounds)
		background.Draw(*this->window);
	Pause();
	Menu();
	for (size_t i = 0; i < shenrons.size(); i++)
	{
		this->shenrons[i].Draw(*this->window);
	}
	for (size_t i = 0; i < this->enemies.size(); i++)
	{
		this->enemies[i].Draw(*this->window);
		//UI
		this->UpdateUIEnemy(i);
		this->window->draw(this->enemyText);
	}
	for (size_t i = 0; i < this->items.size(); i++)
	{
		if (!this->pauseEvent)
		{
			this->items[i].Update();
		}
		this->items[i].Draw(*this->window);
	}
	for (size_t i = 0; i < this->players.size(); i++)
	{
		if (this->players[i].isAlive())
		{
			this->players[i].Draw(*this->window);
			//UI
			this->UpdateUIPlayer(i);
			this->window->draw(this->playerUiBar);
			this->window->draw(this->playerProfile);
			this->window->draw(this->name);
			this->window->draw(this->form);
			this->window->draw(this->playerExpBar);
			this->window->draw(this->playerHpBarBack);
			this->window->draw(this->playerHpBarInside);
			this->window->draw(this->scoreText);
			this->window->draw(this->hpUiBack);
			this->window->draw(this->hpUiInside);
			this->window->draw(this->hp);
			this->window->draw(this->expBack);
			this->window->draw(this->expInside);
			this->window->draw(this->exp);
			this->window->draw(this->damage);
			this->window->draw(this->level);
			for (size_t j = 0; j < 2; j++)
			{
				this->window->draw(this->menuUI[j]);
			}
			for (size_t j = 0; j < 7; j++)
			{
				this->window->draw(this->dragonBall[j]);
			}
		}
	}
	for (size_t i = 0; i < this->textTags.size(); i++)
	{
		this->textTags[i].Draw(*this->window);
	}
	//Game Over Text
	if (this->playerAlive <= 0)
	{
		if (this->held)
		{
			Score(this->window).writeFile(this->playerName, this->score);
			this->held = false;
		}
		this->window->clear();
		this->window->draw(this->GameOver);
		GameOverMenu();
		this->window->draw(this->scoreLasted);
	}
	this->window->display();
}
void Game::gameReset()
{
	for (size_t i = 0; i < players.size(); i++)
	{
		this->players[i].getBullets().clear();
		this->players[i].resetTransform();
	}
	this->held = true;
	this->playerAlive = 1;
	this->players.clear();
	this->enemies.clear();
	this->backgrounds.clear();
	this->items.clear();
	this->scoreMultiplier = 1;
	this->score = 0;
	this->multiplierAdderMax = 10;
	this->multiplierAdder = 0;
	this->multiplierTimerMax = 400.f;
	this->multiplierTimer = this->multiplierTimerMax;
	for (size_t i = 0; i < 7; i++)
	{
		this->itemsKeep[i] = 0;
	}
	if (this->pauseEvent)
	{
		this->pauseEvent = false;
		this->resumeButton = true;
		this->menuUI[0].setTexture(&this->pause);
		this->score = 0;
	}
	for (size_t i = 0; i < 3; i++)
	{
		transform[i] = 0;
	}
	this->playerTexture.loadFromFile("Textures/Character/GokuSprite1.png");
	this->bulletTexture.loadFromFile("Textures/Character/beem/beem1.png");
	this->playerProfile.setTexture(&this->playerImage);
	this->players.push_back(Player(&playerTexture, &bulletTexture, 2, 0.3f));
	this->backgrounds.push_back(Background(&this->BackgroundTexture[0], -60.f));
	this->backgrounds.push_back(Background(&this->BackgroundTexture[1], -120.f));
	this->backgrounds.push_back(Background(&this->BackgroundTexture[2], -180.f));
	this->backgrounds.push_back(Background(&this->BackgroundTexture[3], -380.f));
}
