#include"Game.h"
using namespace std;
using namespace sf;

int main()
{
	RenderWindow window(VideoMode(1920, 1080), "WingMan Game", Style::Default);
	
	Clock clock;
	float dt = 0.f;

	Game game(&window);

	Music music;
	if (!music.openFromFile("Textures/game1.mp3"))
	{
		cout << "ERROR" << endl;
	}
	music.setVolume(1000.f);
	music.getLoop();
	music.play();


	//Game Loop
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
				window.close();
		}

		dt = clock.restart().asSeconds();

		game.Update(dt);
		game.Draw();

	}

	return 0;
}


