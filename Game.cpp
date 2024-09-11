#include "Game.h"
#include <iostream>
#include <fstream>
using namespace std;

enum texture
{
	player = 0,
	laser01,
	missile01,
	mainGun01
};

Game::Game(RenderWindow* window)
{
	this->window = window;
	this->window->setFramerateLimit(200);
	this->dtMultiplier = 62.5f;
	this->scoreMultiplier = 1;
	this->score = 0;
	this->multiplierAdderMax = 10;
	this->multiplierAdder = 0;
	this->multiplierTimerMax = 200.f;
	this->multiplierTimer = this->multiplierTimerMax;

	//Init Fonts
	this->font.loadFromFile("Fonts/Dosis-Light.ttf");

	//InitTextures 
	this->InitTextures();

	//Init player
	this->players.add(Player(this->textures,
		this->lWingTextures,this->rWingTextures,
		this->cPitTextures,this->auraTextures));

	//this->players.add(Player(this->textures,
	//	this->lWingTextures,this->rWingTextures,
	//	this->cPitTextures,this->auraTextures,
	//	Keyboard::Numpad8, Keyboard::Numpad5,
	//	Keyboard::Numpad4, Keyboard::Numpad6,
	//	Keyboard::Numpad0));

	this->playersAlive = this->players.size();

	this->enemySpawnTimerMax = 25.f;
	this->enemySpawnTimerMax = this->enemySpawnTimerMax;


	this->InitUI();
}
Game::~Game()
{

}

void Game::InitTextures()
{
	//Init Textures regular
	this->textures.push_back(Texture());
	this->textures[player].loadFromFile("Textures/ship.png");
	this->textures.push_back(Texture());
	this->textures[laser01].loadFromFile("Textures/Guns/rayTex01.png");
	this->textures.push_back(Texture());
	this->textures[missile01].loadFromFile("Textures/Guns/bullet.png");
	this->textures.push_back(Texture());
	this->textures[mainGun01].loadFromFile("Textures/Guns/gun01.png");
	
	Texture temp;
	temp.loadFromFile("Textures/enemyMoveLeft.png");
	this->enemyTextures.add(Texture(temp));
	temp.loadFromFile("Textures/enemyFollow.png");
	this->enemyTextures.add(Texture(temp));
	temp.loadFromFile("Textures/enemyMoveLeftShoot.png");
	this->enemyTextures.add(Texture(temp));

	temp.loadFromFile("Textures/enemyBullet.png");
	this->enemyBulletTextures.add(Texture(temp));

	//INIT accessory Textures
	ifstream in;
	in.open("Textures/Accessories/leftWings.txt");
	string fileName = "";
	if (in.is_open())
	{
		while (getline(in, fileName))
		{
			Texture temp;
			temp.loadFromFile(fileName);
			this->lWingTextures.add(Texture(temp));
		}
	}
	in.close();

	in.open("Textures/Accessories/rightWings.txt");
	fileName = "";
	if (in.is_open())
	{
		while (getline(in, fileName))
		{
			Texture temp;
			temp.loadFromFile(fileName);
			this->rWingTextures.add(Texture(temp));
		}
	}
	in.close();

	in.open("Textures/Accessories/cockpits.txt");
	fileName = "";
	if (in.is_open())
	{
		while (getline(in, fileName))
		{
			Texture temp;
			temp.loadFromFile(fileName);
			this->cPitTextures.add(Texture(temp));
		}
	}
	in.close();

	in.open("Textures/Accessories/auras.txt");
	fileName = "";
	if (in.is_open())
	{
		while (getline(in, fileName))
		{
			Texture temp;
			temp.loadFromFile(fileName);
			this->auraTextures.add(Texture(temp));
		}
	}
	in.close();

}

void Game::InitUI()
{
	Text tempText;

	//Follow text Init

	this->followPlayerText.setFont(font);
	this->followPlayerText.setCharacterSize(18);
	this->followPlayerText.setFillColor(Color::White);
	this->followPlayerText.setFillColor(Color::Cyan);


	// static text Init

	this->staticPlayerText.setFont(font);
	this->staticPlayerText.setCharacterSize(18);
	this->staticPlayerText.setFillColor(Color::White);
	this->staticPlayerText.setFillColor(Color::Magenta);

	this->playerExpBar.setSize(Vector2f(90.f, 10.f));
	this->playerExpBar.setFillColor(Color(0.f, 90.f, 200.f, 200.f));


	//Enemy Hp Fonts
	this->enemyText.setFont(this->font);
	this->enemyText.setCharacterSize(18);
	this->enemyText.setFillColor(Color::White);
	this->enemyText.setFillColor(Color::Yellow);

	this->gameOverText.setFont(this->font);
	this->gameOverText.setFillColor(Color::Red);
	this->gameOverText.setCharacterSize(50);
	this->gameOverText.setString("GAME OVER!");
	// Set the position to the center of the screen
	this->gameOverText.setPosition(
		(this->window->getSize().x - this->gameOverText.getLocalBounds().width) / 2.f,
		(this->window->getSize().y - this->gameOverText.getLocalBounds().height) / 2.f);

	this->scoreText.setFont(this->font);
	this->scoreText.setFillColor(Color(200,200,200,150));
	this->scoreText.setCharacterSize(25);
	this->scoreText.setString("Score: 0 ");
	// Set the position to the center of the screen
	this->scoreText.setPosition(10.f,10.f);
		
}

void Game::UpdateUIPlayer(int index)
{
	if (index >= this->players.size())
		cout << "OUT OF BOUNDS! (UPDATEUI)";
	else      //Follow Text
	{
		this->followPlayerText.setPosition(
			this->players[index].getPosition().x - 25.f,
			this->players[index].getPosition().y - 40.f
		);

		this->followPlayerText.setString(
			to_string(
				this->players[index].getPlayerNr())
			+ "				    	 "
			+ this->players[index].getHPAsString()
			+ "\n\n\n\n\n\n\n"
			+ to_string(this->players[index].getLevel())
		);

		//BARS
		this->playerExpBar.setPosition(
			this->players[index].getPosition().x + 20.f,
			this->players[index].getPosition().y + 89.f
		);

		this->playerExpBar.setScale(
		(static_cast<float>(this->players[index].getExp())/ this->players[index].getExpNext()),
			1.f);

		//STATIC TEXT
	}
}

void Game::UpdateUIEnemy(int index)
{
	this->enemyText.setPosition(
		this->enemies[index].getPosition().x,
		this->enemies[index].getPosition().y - this->enemies[index].getGloabalBounds().height
	);
	this->enemyText.setString(
		to_string(this->enemies[index].getHP()) + "/" +
		to_string(this->enemies[index].getHPMax()));

}

void Game::Update(const float& dt)
{

	if (this->playersAlive > 0)
	{

		//Update Timers
		if (this->enemySpawnTimer < this->enemySpawnTimerMax)
			this->enemySpawnTimer += 1.f * dt * this->dtMultiplier;

		//Score Timers and Multipliers
		if (this->multiplierTimer > 0)
		{
			this->multiplierTimer -= 1.f * dt * this->dtMultiplier;
			
			if (this->multiplierTimer <= 0.f)
			{
				this->multiplierTimer = 0.f;
				this->multiplierAdder = 0;
				this->scoreMultiplier = 1;
			}
		}
	
		if (this->multiplierAdder >= this->multiplierAdderMax)
		{
			this->multiplierAdder = 0;
			this->scoreMultiplier++;
		}

		//Spawn Enemies
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			this->enemies.add(Enemy(
				this->enemyTextures,
				this->enemyBulletTextures,
				this->window->getSize(),
				Vector2f(0.f, 0.f),
				Vector2f(-1.f, 0.f),
				rand() % 3,
				this->players[(rand() % playersAlive)].getLevel(),
				rand() % this->playersAlive));

			this->enemySpawnTimer = 0;   //Reset Timer
		}

		//Update players,bullets and combat
		for (int i = 0; i < this->players.size(); i++)
		{

			//UPDATE PLAYERS
			this->players[i].Update(this->window->getSize(), dt);

			//Bullets update
			for (int k = 0; k < this->players[i].getBulletsSize()/*&&!bulletRemoved*/; k++)
			{
				this->players[i].getBullet(k).Update(dt);

				//Enemy collision check
				for (int j = 0; j < enemies.size(); j++)
				{

					if (this->players[i].getBullet(k).getGlobalBounds().intersects(this->enemies[j].getGloabalBounds()))
					{
						this->players[i].removeBullet(k);
						//Enemy Take Damage
						int damage = this->players[i].getDamage();
						if (this->enemies[j].getHP() > 0)
						{
							this->enemies[j].takeDamage(damage);

							//Create Text tag
							this->textTags.add(
								TextTag(&this->font,
								"-" + to_string(damage),
									Color::Green,
									Vector2f(this->enemies[j].getPosition().x + 20.f,
										this->enemies[j].getPosition().y - 20.f),
									Vector2f(1.f,0.f),
									28, 30.f,true)
							);
						}
						//Enemy Dead
						if (this->enemies[j].getHP() <= 0)
						{
							//GAIN SCORE & RESET MULTIPLIER TIMER
							this->multiplierTimer = this->multiplierTimerMax;
							int score = this->enemies[j].getHPMax() * this->scoreMultiplier;
							this->multiplierAdder++;
							this->players[i].gainScore(score);

							//GAIN EXP
							int exp = this->enemies[j].getHPMax()
								+ (rand() % this->enemies[j].getHPMax() + 1)
								+ this->scoreMultiplier;

							//SCORE TEXT TAG
							this->textTags.add(
								TextTag(&this->font,
									"+" + to_string(this->score) + "   ( x" + to_string(this->scoreMultiplier) + ")",
									Color::White,
									Vector2f(100.f, 10.f),
									Vector2f(1.f, 0.f),
									30, 40.f, true)
							);

							//LEVEL UP TAG
							if (players[i].gainExp(exp))
							{
								//Create Texttag
								this->textTags.add(
									TextTag(&this->font,
										"LEVEL UP!",
										Color::Cyan,
										Vector2f(this->players[i].getPosition().x + 20.f,
											this->players[i].getPosition().y - 20.f),
										Vector2f(0.f, 1.f),
										32, 40.f, true)
								);
							}

							//GAIN EXP TAG
							//Create Texttag
							this->textTags.add(
								TextTag(&this->font,
									"+" +
									to_string(exp) +
									" ( x"+
									to_string(this->scoreMultiplier)+
									" ) "+
									" EXP",
									Color::Cyan,
									Vector2f(this->enemies[j].getPosition().x + 20.f,
										this->players[i].getPosition().y - 20.f),
									Vector2f(0.f, 1.f),
									24, 40.f,true)
							);
							this->enemies.remove(j);
						}
						return;

					}

				}
				//window bounds check
				if (this->players[i].getBullet(k).getPosition().x > this->window->getSize().x)
				{
					this->players[i].removeBullet(k);
					return;
				}
			}
			//UPDATE SCORE
			this->score = 0;
			this->score += players[i].getScore();
			this->scoreText.setString(
				"Score :" + to_string(this->score) +
				"\nMultiplier :" + to_string(this->scoreMultiplier) + "x" +
				"\nMultiplier Timer :" + to_string((int)this->multiplierTimer) +
				"\nNew Multiplier :" + to_string(this->multiplierAdder) +
				" / " + to_string(this->multiplierAdderMax)
			);
			//WRITING THE SCORES TO THE BINARY FILE
			ofstream binaryFile1("score_data.dat", std::ios::binary | std::ios::trunc);
			if (binaryFile1.is_open())
			{
				// Write the data to the binary file
				binaryFile1.write(reinterpret_cast<const char*>(&this->score), sizeof(this->score));
				binaryFile1.write(reinterpret_cast<const char*>(&this->scoreMultiplier), sizeof(this->scoreMultiplier));
				binaryFile1.write(reinterpret_cast<const char*>(&this->multiplierTimer), sizeof(this->multiplierTimer));
				binaryFile1.write(reinterpret_cast<const char*>(&this->multiplierAdder), sizeof(this->multiplierAdder));
				binaryFile1.write(reinterpret_cast<const char*>(&this->multiplierAdderMax), sizeof(this->multiplierAdderMax));

				// Check for errors during writing
				if (!binaryFile1)
				{
					std::cerr << "Error writing to binary file!" << std::endl;
				}

				// Close the binary file
				binaryFile1.close();
			}
			else
			{
				// Handle file opening error
				std::cerr << "Error opening binary file!" << std::endl;
			}

			//READING FROM THE BINARY FILE
			//std::ifstream binaryFile("score_data.dat", std::ios::binary);

			//if (binaryFile.is_open()) {
			//	// Read the data from the binary file
			//	binaryFile.read(reinterpret_cast<char*>(&score), sizeof(score));
			//	binaryFile.read(reinterpret_cast<char*>(&scoreMultiplier), sizeof(scoreMultiplier));
			//	binaryFile.read(reinterpret_cast<char*>(&multiplierTimer), sizeof(multiplierTimer));
			//	binaryFile.read(reinterpret_cast<char*>(&multiplierAdder), sizeof(multiplierAdder));
			//	binaryFile.read(reinterpret_cast<char*>(&multiplierAdderMax), sizeof(multiplierAdderMax));

			//	// Output the read values
			//	std::cout << "Score: " << score << std::endl;
			//	std::cout << "Score Multiplier: " << scoreMultiplier << std::endl;
			//	std::cout << "Multiplier Timer: " << multiplierTimer << std::endl;
			//	std::cout << "Multiplier Adder: " << multiplierAdder << std::endl;
			//	std::cout << "Multiplier Adder Max: " << multiplierAdderMax << std::endl;

			//	// Close the binary file
			//	binaryFile.close();
			//}
			//else {
			//	std::cerr << "Error opening binary file!" << std::endl;
			//}
		
		}

		//Update Enemies
		for (int i = 0; i < this->enemies.size(); i++)
		{
			this->enemies[i].Update(dt,this->players[this->enemies[i].getPlayerFollowNr()].getPosition());
			
			//Enemy bullet Update
			for (int k = 0; k < this->enemies[i].getBullets().size(); k++)
			{
				this->enemies[i].getBullets()[k].Update(dt);
			}
			
			
			//Enemy player collision
			for (int k = 0; k < this->players.size(); k++)
			{
				if (this->players[k].isAlive())
				{
					if (this->players[k].getGlobalBounds().intersects(this->enemies[i].getGloabalBounds())
						&& !this->players[k].isDamageCoolDown())
					{
						int damage = this->enemies[i].getDamage();

						this->players[k].takeDamage(damage);

						this->enemies[i].collision();
						
						//Create Text tag
						this->textTags.add(
							TextTag(&this->font,
								"-" + to_string(damage),
								Color::Magenta,
								Vector2f(this->players[k].getPosition().x + 20.f,
									this->players[k].getPosition().y - 20.f),
								Vector2f(-1.f, 0.f),
								30,30.f,true)
						);
					

						//Player Death
						if (!this->players[k].isAlive())
							this->playersAlive--;

						
						return;   //RETURN
					}
				}
			}
			//Enemeies out of bounds
			if (this->enemies[i].getPosition().x < 0 - this->enemies[i].getGloabalBounds().width)
			{
				this->enemies.remove(i);
				return;    //RETURN
			}
		}
		//Update TextTags
		for (int i = 0; i < this->textTags.size(); i++)
		{
			this->textTags[i].Update(dt);

			if (this->textTags[i].getTimer() <= 0.f)
			{
				this->textTags.remove(i);
				break;
			}
		}
	}
}

void Game::DrawUI()
{
	//Draw Textags
	for (int i = 0; i < this->textTags.size(); i++)
	{
		this->textTags[i].Draw(*this->window);
	}
	//GAME OVER TEXT
	if (this->playersAlive <= 0)
	{
		this->window->draw(this->gameOverText);
	}
	//Score Text
	this->window->draw(this->scoreText);
}

void Game::Draw()
{
	this->window->clear();

	//Draw Player
	for (int i = 0; i < this->players.size(); i++)
	{

		if (this->players[i].isAlive())
		{
			this->players[i].Draw(*this->window);
			//UI
			this->UpdateUIPlayer(i);
			this->window->draw(this->followPlayerText);
			this->window->draw(this->playerExpBar);
		}
	}

	//Draw Enemies
	for (int i = 0; i < this->enemies.size(); i++)
	{
		this->enemies[i].Draw(*this->window);
		//UI
		this->UpdateUIEnemy(i);
		this->window->draw(this->enemyText);
	}
	this->DrawUI();

	this->window->display();
}
