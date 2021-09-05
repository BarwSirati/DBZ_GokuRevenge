#pragma once
#include <iostream>
#include "SFML/Audio.hpp"
using namespace std;
using namespace sf;
class MusicSounds
{
private:
	SoundBuffer buffer[2];
	Sound sound[2];
	bool soundLoop[2] = { 0,0};
public:
	MusicSounds();
	virtual ~MusicSounds();
	inline void StopSounds(int index) 
	{
		soundLoop[index] = false;
		sound[index].stop();
	}
	void Play(int index);
};

