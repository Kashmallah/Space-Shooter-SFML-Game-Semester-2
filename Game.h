#pragma once
#include"Player.h"
#include"Enemy.h"

using namespace sf;
using namespace std;
class Game
{
private:
	//Game
	RenderWindow* window;
	float dtMultiplier;

	//Score
	unsigned  score;
	unsigned scoreMultiplier;
	float multiplierTimerMax;
	float multiplierTimer;
	int multiplierAdder;
	int multiplierAdderMax;

	//UI
	//Fonts
	Font font;
	Text followPlayerText;
	Text staticPlayerText;
	Text enemyText;
	Text gameOverText;
	Text scoreText;

	//Bars
	RectangleShape playerExpBar;

	//Players
	dArr<Player>players;
	int playersAlive;

	//Textags
	dArr<TextTag>textTags;

	//Enemies
	dArr<Enemy>enemies;
	vector<Enemy>enemiesSaved;
	float enemySpawnTimer;
	float enemySpawnTimerMax;

	//Textures
	vector<Texture>textures;
	dArr<Texture>enemyTextures;
	dArr<Texture>lWingTextures;
	dArr<Texture>rWingTextures;
	dArr<Texture>cPitTextures;
	dArr<Texture>auraTextures;
	dArr<Texture>enemyBulletTextures;
public:
	//Parameterized Constructor
	Game(RenderWindow* window);
	//Destructor
	virtual~Game();

	//Accessors
	inline RenderWindow& getWindow()
	{
		return *this->window;
	}

	//Setters

	//Functions
	void InitTextures();
	void InitUI();
	void UpdateUIPlayer(int index);
	void UpdateUIEnemy(int index);
	void Update(const float& dt);
	void DrawUI();
	void Draw();
};

