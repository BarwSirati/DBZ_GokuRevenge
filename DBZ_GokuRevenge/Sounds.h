#pragma once
#include <iostream>
#include "SFML/Audio.hpp"
using namespace std;
using namespace sf;
class Sounds
{
private:
	SoundBuffer mainMenu;
public:
	Sounds();
	virtual ~Sounds();

	inline void MainMenu() 
	{ 
		if (!mainMenu.loadFromFile("Audio/mainmenu.wav"))
			cout << "Sounds Not Found" << endl;
		Sound sound;
		sound.setBuffer(mainMenu);
	}
};

