#include "Menu.h"
MainMenu::MainMenu(RenderWindow* window)
{
	
	if (!this->buffer[0].loadFromFile("Audio/button.wav"))
	{
		cout << "Error load file" << endl;
	}
	this->sound[0].setBuffer(this->buffer[0]);

	if (!this->buffer[1].loadFromFile("Audio/let.wav"))
	{
		cout << "Error load file" << endl;
	}
	this->sound[1].setBuffer(this->buffer[1]);

	this->window = window;
	float posY = 600;


	for (size_t i = 0; i < 3; i++)
	{
		this->buttonTexture[i].loadFromFile("Textures/MainMenu/button/" + to_string(i + 1) + ".png");
		this->button[i].setTexture(&this->buttonTexture[i]);
		this->button[i].setSize(Vector2f(this->buttonTexture[i].getSize()));
		this->button[i].setScale(0.8f, 0.8f);
		this->button[i].setPosition(this->window->getSize().x / 2, posY);
		this->button[i].setOrigin(this->buttonTexture[i].getSize().x / 2, this->buttonTexture[i].getSize().y / 2);
		posY += 150;
	}

	this->questionTexture.loadFromFile("Textures/MainMenu/button/question.png");
	this->question.setTexture(&this->questionTexture);
	this->question.setSize(Vector2f(this->questionTexture.getSize()));
	this->question.setPosition(1860.f, 1020.f);
	this->question.setScale(0.3f, 0.3f);
	this->question.setOrigin(this->questionTexture.getSize().x / 2, this->questionTexture.getSize().y / 2);

	this->bgTexture.loadFromFile("Textures/MainMenu/background.jpg");
	this->background.setTexture(&this->bgTexture);
	this->background.setSize(Vector2f(this->window->getSize()));


	this->InputTexture.loadFromFile("Textures/MainMenu/Input/bg.jpg");
	this->Input.setTexture(&this->InputTexture);
	this->Input.setSize(Vector2f(this->window->getSize()));


	this->howTexture.loadFromFile("Textures/MainMenu/how.jpg");
	this->how.setTexture(&this->howTexture);
	this->how.setSize(Vector2f(this->window->getSize()));

	this->font.loadFromFile("Fonts/Minecraft.ttf");
	this->player.setFont(this->font);
	this->player.setCharacterSize(100);
	this->player.setFillColor(Color::Black);
	this->player.setPosition(960.f, 525.f);
	this->player.setLetterSpacing(1.5);
	this->player.setOutlineThickness(3);
	this->player.setOutlineColor(Color::White);

	this->buttonLetGoTexture.loadFromFile("Textures/MainMenu/button/let.png");
	this->buttonLetGo.setTexture(&this->buttonLetGoTexture);
	this->buttonLetGo.setSize(Vector2f(this->buttonLetGoTexture.getSize()));
	this->buttonLetGo.setPosition(960.f, 720.f);
	this->buttonLetGo.setScale(0.6f, 0.6f);
	this->buttonLetGo.setOrigin(this->buttonLetGoTexture.getSize().x / 2, this->buttonLetGoTexture.getSize().y / 2);

	this->buttonHomeTexture.loadFromFile("Textures/MainMenu/button/menu.png");
	this->buttonHome.setTexture(&this->buttonHomeTexture);
	this->buttonHome.setSize(Vector2f(this->buttonHomeTexture.getSize()));
	this->buttonHome.setPosition(1850.f, 70.f);
	this->buttonHome.setScale(0.4f, 0.4f);
	this->buttonHome.setOrigin(this->buttonHomeTexture.getSize().x / 2, this->buttonHomeTexture.getSize().y / 2);

	this->player.setString("Enter Your Name");
	this->player.setOrigin(this->player.getLocalBounds().width / 2, this->player.getLocalBounds().height / 2);
}

MainMenu::~MainMenu()
{

}
void MainMenu::UpdateMenuCheck(int action)
{
	switch (action)
	{
	case 0:
		this->action = MENU;
		break;
	case 1:
		this->action = PLAY;
		break;
	case 2:
		this->action = SCORE;
		break;
	case 3:
		this->action = QUIT;
		break;
	case 4:
		this->action = INPUT;
		break;
	case 5:
		this->action = QUESTION;
		break;
	default:
		break;
	}
}
void MainMenu::Update()
{
	for (size_t i = 0; i < 3; i++)
	{
		if (this->button[i].getGlobalBounds().contains(Vector2f(Mouse::getPosition())))
		{
				
			this->button[i].setScale(0.9f, 0.9f);
		
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				switch (i)
				{
				case 0:
					UpdateMenuCheck(4);
					this->sound[0].play();
					break;
				case 1:
					UpdateMenuCheck(2);
					this->sound[0].play();
					break;
				case 2:
					UpdateMenuCheck(3);
					this->sound[0].play();
					break;
				default:
					break;
				}
			}
		}
		else
		{
			this->button[i].setScale(0.8f, 0.8f);
		}
	}
	Question();
}
void MainMenu::UpdateInput(vector<Event> events)
{
	this->window->clear();
	this->window->draw(Input);
	for (size_t i = 0; i < events.size(); i++)
	{
		if (events[i].text.unicode != 32 && !Keyboard::isKeyPressed(Keyboard::Enter) && events[i].text.unicode != 63)
		{
			if (events[i].text.unicode == 8 && playerName.length() > 0)
			{
				playerName.erase(playerName.length() - 1);
			}
			else if (events[i].text.unicode < 128 && playerName.length() < 10 && events[i].text.unicode != 8)
			{
				playerName += static_cast<char>(events[i].text.unicode);
			}
			player.setString(playerName);
			this->player.setOrigin(this->player.getLocalBounds().width / 2, this->player.getLocalBounds().height / 2);
		}
	}
	this->window->draw(player);
	DrawPlay();
	DrawHome();
	this->window->display();
}
void MainMenu::DrawPlay()
{
	if (this->buttonLetGo.getGlobalBounds().contains(Vector2f(Mouse::getPosition())) && this->playerName != "")
	{
		this->buttonLetGo.setScale(0.7f, 0.7f);
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			UpdateMenuCheck(1);
			this->sound[1].play();
		}
	}
	else
	{
		this->buttonLetGo.setScale(0.6f, 0.6f);
	}
	this->window->draw(buttonLetGo);
}
void MainMenu::DrawHome()
{
	if (this->buttonHome.getGlobalBounds().contains(Vector2f(Mouse::getPosition())))
	{
		this->buttonHome.setScale(0.5f, 0.5f);
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			UpdateMenuCheck(0);
			this->playerName.clear();
			this->sound[0].play();
		}
	}
	else
	{
		this->buttonHome.setScale(0.4f, 0.4f);
	}
	this->window->draw(buttonHome);
}
void MainMenu::Question()
{
	if (this->question.getGlobalBounds().contains(Vector2f(Mouse::getPosition())))
	{
		this->question.setScale(0.4f, 0.4f);
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			UpdateMenuCheck(5);
			this->sound[0].play();
		}
	}
	else
	{
		this->question.setScale(0.3f, 0.3f);
	}
	this->window->draw(this->question);
}
void MainMenu::How()
{
	this->window->clear();
	this->window->draw(this->how);
	DrawHome();
	this->window->display();
}
void MainMenu::Draw()
{
	this->window->clear();
	this->window->draw(background);
	for (size_t i = 0; i < 3; i++)
	{
		this->window->draw(this->button[i]);
	}
	Update();
	this->window->display();
}