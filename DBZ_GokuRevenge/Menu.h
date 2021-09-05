#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cstdlib>
#include <math.h>
#include <cctype>
using namespace std;
using namespace sf;
class MainMenu
{
	SoundBuffer buffer[2];
	Sound sound[2];

	bool soundLoop = false;

	RenderWindow* window;
	Font font;

	Event event;
	float deltaTime;

	float delayInput;
	float delayInputMax;

	enum STATE { MENU, PLAY, SCORE, QUIT, INPUT,QUESTION };
	STATE action = MENU;

	Texture howTexture;
	RectangleShape how;

	Texture questionTexture;
	RectangleShape question;

	Texture buttonTexture[3];
	RectangleShape button[3];

	Texture bgTexture;
	RectangleShape background;

	Texture InputTexture;
	RectangleShape Input;

	Texture buttonLetGoTexture;
	RectangleShape buttonLetGo;

	Texture buttonHomeTexture;
	RectangleShape buttonHome;

	string playerName;
	Text player;

public:
	MainMenu(RenderWindow* window);
	virtual ~MainMenu();

	inline int getAction() { return this->action; }
	inline string getPlayerName() { return this->playerName; }

	inline void setActionToZero() { this->action = MENU; };
	void UpdateMenuCheck(int action);

	void UpdateInput(Event& event, float deltaTime);
	void DrawPlay();
	void DrawHome();
	void Question();
	void How();

	void Update();
	void Draw();
	inline void ResetName() { this->playerName = ""; };
};
