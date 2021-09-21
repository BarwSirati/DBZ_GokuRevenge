#include "Game.h"
int main()
{
	srand(time(NULL));
	RenderWindow window(VideoMode(1920, 1080), "DragonBallZ GokuRevenge", Style::Fullscreen | Style::Titlebar);
	float deltaTime = 0.0f;
	Clock clock;

	Game game(&window);
	MainMenu menu(&window);
	Score scores(&window);
	MusicSounds musicSound;
	
	bool Focus = true;

	vector<Event> textEntered;
	
	Image icon;
	icon.loadFromFile("Icon/icon.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	while (window.isOpen())
	{
		textEntered.clear();
		deltaTime = clock.restart().asSeconds();
		Event event;
		
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;
			case Event::KeyPressed:
				if (Keyboard::isKeyPressed(Keyboard::Escape))
				{
					window.close();
				}
				break;
			case Event::TextEntered:
				textEntered.push_back(event);
				break;
			case Event::GainedFocus:
				Focus = true;
				break;
			case Event::LostFocus:
				Focus = false;
				break;
			}
		}
		if (Focus)
		{
			int action = menu.getAction();
			if (action == 0)
			{	
				
				musicSound.Play(0);
				menu.Draw();
				game.resetAction();
			}
			if (action == 1)
			{
				musicSound.StopSounds(0);
				musicSound.Play(1);
				game.getPlayerName(menu.getPlayerName());
				game.Update(deltaTime);
				game.Draw();

				if (game.getCheckAction())
				{
					menu.setActionToZero();
					menu.ResetName();
					game.gameReset();
					musicSound.StopSounds(1);
				}
			}
			if (action == 2)
			{
				scores.Draw();
				if (scores.getCheckAction())
				{
					menu.setActionToZero();
					scores.resetAction();
				}
			}
			if (action == 3)
				window.close();
			if (action == 4)
				menu.UpdateInput(textEntered);
			if (action == 5)
				menu.How();
		}
	}
	return 0;
}