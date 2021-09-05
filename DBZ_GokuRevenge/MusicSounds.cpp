#include "MusicSounds.h"

MusicSounds::MusicSounds()
{
	for (size_t i = 0; i < 2; i++)
	{
		if (!this->buffer[i].loadFromFile("Audio/b"+to_string(i+1)+".wav"))
		{
			cout << "Error load file" << endl;
		}
		this->sound[i].setBuffer(this->buffer[i]);
		this->sound[i].setLoop(true);
	}
	this->sound[1].setVolume(50);
}

MusicSounds::~MusicSounds()
{
}

void MusicSounds::Play(int index)
{
	if (!this->soundLoop[index])
	{
		this->sound[index].play();
		this->soundLoop[index] = 1;
	}
}
