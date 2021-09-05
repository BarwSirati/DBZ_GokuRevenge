#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <stdio.h>
#include <utility>
#include <algorithm>
#include <string.h>
#include <vector>
#include "Menu.h"
using namespace std;
using namespace sf;
class Score
{
private:
    SoundBuffer buffer;
    Sound sound;

    FILE* fp;
    Font font;

    RenderWindow* window;

    Text numUI[5];
    Text nameUI[5];
    Text scoreUI[5];

    char temp[255];
    unsigned int score[6];
    string name[6];
    vector<pair<int, string>> userScore;
    unsigned int getScore;
    string getName;
    Texture texture;
    RectangleShape background;

    Texture buttonHomeTexture;
    RectangleShape buttonHome;

    bool setActionToZero = false;
public:
    Score(RenderWindow* window);
    virtual ~Score();

    inline bool getCheckAction() { return this->setActionToZero; }
    inline void resetAction() { this->setActionToZero = false; }

    void scoreList();
    void UI();
    void Update();
    void readFile();
    void writeFile(string name, unsigned int score);
    void Draw();
};

