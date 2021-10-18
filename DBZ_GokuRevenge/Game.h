#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "Menu.h"
#include "Background.h"
#include "Shenron.h"
#include "Score.h"
#include "MusicSounds.h"
#include "SFML/Audio.hpp"
class Game
{
private:
	SoundBuffer buffer[9];
	Sound sound[9];

	RenderWindow* window;

	int randTexture;
	int randBoss;
	float deltaTime;

	float spawntimerMax;
	float spawntimer;

	//Score
	unsigned int score;
	unsigned scoreMultiplier;
	float multiplierTimerMax;
	float multiplierTimer;
	int multiplierAdder;
	int multiplierAdderMax;

	bool setActionToZero = false;

	//UI
	RectangleShape playerUiBar;
	RectangleShape playerProfile;
	RectangleShape menuUI[2];
	RectangleShape dragonBall[7];

	bool pauseEvent = false;
	bool resumeButton = false;
	bool resumeHeld = false;
	bool held = true;
	bool shenRon = false;

	//Text
	Font font;

	Text enemyText;

	Text gameOverText;
	Text scoreLasted;

	Text form;
	Text scoreText;
	Text name;
	Text hp;
	Text exp;
	Text level;
	Text damage;

	//Bars
	RectangleShape playerExpBar;
	RectangleShape playerHpBarBack;
	RectangleShape playerHpBarInside;

	RectangleShape hpUiInside;
	RectangleShape hpUiBack;
	RectangleShape expInside;
	RectangleShape expBack;

	//Text tags
	vector<TextTag> textTags;

	//PLayer
	vector<Player> players;
	int playerAlive;
	int state = 0;
	//Items
	vector<Item> items;

	vector<Shenron> shenrons;

	//Enemies
	vector<Enemy> enemies;
	vector<Enemy> enemiesSaved;
	float enemySpawnTimer;
	float enemySpawnTimerMax;

	//Background
	vector<Background> backgrounds;

	//Texture

	Texture playerTexture;
	Texture bulletTexture;
	Texture shenronTexture;

	Texture itemTexture[7];

	Texture enemy01Texture;
	Texture enemy02Texture;
	Texture playerBar;

	Texture playerImage;
	Texture playerImage2;
	Texture playerImage3;
	Texture playerImage4;

	Texture pause;
	Texture menu;
	Texture resume;

	Texture BackgroundTexture[4];

	Texture GameOverTexture;
	RectangleShape GameOver;

	Texture menuOverTexture[2];
	RectangleShape menuOver[2];

	Texture timeStopIconTexture;
	Sprite timeStopIconSprite;

	Text coolTimeText;
	float coolTime;

	bool canStopTime = false;
	bool useTimeStop = false;
	bool usingTime = false;

	Texture beamIconTexture;
	Sprite beamIconSprite;
	RectangleShape beam;
	Texture beamTexture;
	Text coolBeamText;
	float coolBeam;
	bool useBeam = false;
	bool usingBeam = false;

	string textForm[4] = { "","( Super Saiya )","( Super Saiya God )","( Super Saiya Blue )" };
	int itemsKeep[7] = { 0,0,0,0,0,0,0 };
	string playerName;
	
	int transform[3] = { 0,0,0};

	

public:
	Game(RenderWindow* window);
	virtual ~Game();
	//Accessors
	inline RenderWindow& getWindow()
	{
		return *this->window;
	}
	inline bool getPause() { return this->resumeButton; }
	inline bool getCheckAction() { return this->setActionToZero; }
	inline void resetAction() { this->setActionToZero = false; }

	inline void getPlayerName(string playerName) { this->playerName = playerName; }

	//Function
	void InitUI();
	void UpdateUIPlayer(int index);
	void UpdateUIEnemy(int index);
	void Update(float deltaTime);
	void GameOverMenu();
	void Pause();
	void Menu();
	void Draw();
	void gameReset();
};
