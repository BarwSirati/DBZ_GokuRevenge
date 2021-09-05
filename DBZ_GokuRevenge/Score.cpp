#define _CRT_SECURE_NO_WARNINGS
#include "Score.h"


Score::Score(RenderWindow* window)
{
    if (!this->buffer.loadFromFile("Audio/button.wav"))
    {
        cout << "Error load file" << endl;
    }
    this->sound.setBuffer(this->buffer);
    this->window = window;
    this->texture.loadFromFile("Textures/MainMenu/score.jpg");
    this->background.setTexture(&this->texture);
    this->background.setSize(Vector2f(this->window->getSize()));
    this->background.setPosition(0.f, 0.f);
    this->font.loadFromFile("Fonts/Minecraft.ttf");
    UI();
}

Score::~Score()
{
}

void Score::scoreList()
{
    readFile();
    fclose(this->fp);
    for (int i = 0; i < 5; i++)
    {
        if (name[i] != "?")
        {
            this->numUI[i].setFont(this->font);
            this->nameUI[i].setFont(this->font);
            this->scoreUI[i].setFont(this->font);

            this->numUI[i].setCharacterSize(60);
            this->nameUI[i].setCharacterSize(60);
            this->scoreUI[i].setCharacterSize(60);

            this->numUI[i].setFillColor(Color::Black);
            this->nameUI[i].setFillColor(Color::Black);
            this->scoreUI[i].setFillColor(Color::Black);

            this->numUI[i].setPosition(200.f, 430.f + (i * 100));
            this->nameUI[i].setPosition(250.f, 430.f + (i * 100));
            this->scoreUI[i].setPosition(1700.f, 430.f + (i * 100));


            this->numUI[i].setOrigin(0, this->numUI[i].getLocalBounds().height);;
            this->nameUI[i].setOrigin(0, this->nameUI[i].getLocalBounds().height);;
            this->scoreUI[i].setOrigin(this->scoreUI[i].getLocalBounds().width, this->scoreUI[i].getLocalBounds().height);

            this->numUI[i].setString(to_string(i + 1) + ". ");
            this->nameUI[i].setString(name[i]);
            this->scoreUI[i].setString(to_string(score[i]) + " P");

            this->window->draw(numUI[i]);
            this->window->draw(nameUI[i]);
            this->window->draw(scoreUI[i]);
        }
    }
}

void Score::UI()
{
    this->buttonHomeTexture.loadFromFile("Textures/MainMenu/button/menu.png");
    this->buttonHome.setTexture(&this->buttonHomeTexture);
    this->buttonHome.setSize(Vector2f(this->buttonHomeTexture.getSize()));
    this->buttonHome.setPosition(1850.f, 70.f);
    this->buttonHome.setScale(0.4f, 0.4f);
    this->buttonHome.setOrigin(this->buttonHomeTexture.getSize().x / 2, this->buttonHomeTexture.getSize().y / 2);
}


void Score::readFile()
{
    this->fp = fopen("./System/score.txt", "r");
    for (int i = 0; i < 5; i++)
    {
        fscanf(fp, "%s", &temp);
        name[i] = temp;
        fscanf(fp, "%d", &score[i]);
        this->userScore.push_back(make_pair(this->score[i], this->name[i]));
    }
}

void Score::writeFile(string name, unsigned int score)
{
    readFile();
    this->name[5] = name;
    this->score[5] = score;
    this->userScore.push_back(make_pair(this->score[5], this->name[5]));
    sort(this->userScore.begin(), this->userScore.end());
    fclose(this->fp);

    fopen("./System/score.txt", "w");
    for (int i = 5; i >= 1; i--)
    {
        strcpy(temp, userScore[i].second.c_str());
        fprintf(fp, "%s %d\n", temp, userScore[i].first);
    }
    fclose(this->fp);
}

void Score::Update()
{
    if (this->buttonHome.getGlobalBounds().contains(Vector2f(Mouse::getPosition())))
    {
        this->buttonHome.setScale(0.5f, 0.5f);
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            this->sound.play();
            this->setActionToZero = true;
            
        }
    }
    else
    {
        this->buttonHome.setScale(0.4f, 0.4f);
    }
    this->window->draw(buttonHome);
}

void Score::Draw()
{
    this->window->clear();
    this->window->draw(background);
    Update();
    scoreList();
    this->window->display();

}
