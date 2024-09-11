#pragma once
#include"Bullet.h"
using namespace std;

class Player
{
private:
	//Timers
	float dtMultiplier;
	float keyTimerMax;
	float keyTime;

	unsigned playerNr;    //unsigned numbers are to store non-negative numbers only i-e,+ive nums and 0
	
	float shootTimer;
	float shootTimerMax;
	float damageTimer;
	float damageTimerMax;


	Vector2f playerCenter;
	Sprite sprite;
	RectangleShape hitBox;

	//Accessories
	Sprite mainGunSprite;
	dArr<Bullet>bullets;
	Texture* laserTexture;
	Texture* missile01Texture;
	Texture* missile02Texture;

	dArr<Texture>* lWingTextures;
	dArr<Texture>* rWingTextures;
	dArr<Texture>* cPitTextures;
	dArr<Texture>* auraTextures;
	Sprite lWing;
	Sprite rWing;
	Sprite cPit;
	Sprite aura;

	int lWingSelect;
	int rWingSelect;
	int cPitSelect;
	int auraSelect;


	int controls[5];
	Vector2f currentVelocity;
	float maxVelocity;
	float accelaration;
	Vector2f moveDirection;
	float stabilizerForce;
	Vector2f normDir;

	//Leveling
	int level;
	//Experience Points
	int exp;
	int expNext;
	int statPoints;

	//Additionals
	int cooling;//endurance
	int plating;//vigor
	int power;//strength
	int wiring;//agility

	//Health
	int hp;
	int hpMax;

	//Damage
	int damage;
	int damageMax;

	//Score
	int score;

	//Loaded Weapon
	int currentWeapon;

	//Upgrades
	int mainGunLevel;
	bool dualMissiles01;
	bool dualMissiles02;

public:

	Player(vector<Texture> &textures,
		dArr<Texture> &lWingTextures,
		dArr<Texture> &rWingTextures,
		dArr<Texture> &cPitTextures,
		dArr<Texture> &auraTextures,
		int UP = 22, int DOWN = 18,
		int LEFT = 0, int RIGHT = 3,
		int SHOOT = 57
		);

	virtual ~Player();

	//Accessors
	Bullet& getBullet(unsigned index);
	void removeBullet(unsigned index);
	inline const int getBulletsSize()const
	{
		return this->bullets.size();
	}
	inline const Vector2f& getPosition()const
	{
		return this->sprite.getPosition();
	}
	inline const String getHPAsString() const
	{
		return to_string(this->hp) + "/" + to_string(this->hpMax);
	}
	int getDamage()const;
	inline FloatRect getGlobalBounds()const
	{
		return this->sprite.getGlobalBounds();
	}
	inline const int& getHp()const
	{
		return this->hp;
	}
	inline const int& getHpMax()const
	{
		return this->hpMax;
	}
	void takeDamage(int damage);
	inline bool isAlive()const
	{
		return this->hp > 0;
	}
	inline const int& getPlayerNr()const
	{
		return this->playerNr;
	}
	inline const int& getLevel()const
	{
		return this->level;
	}
	inline const int& getExp()const
	{
		return this->exp;
	}
	inline const int& getExpNext()const
	{
		return this->expNext;
	}
	inline bool gainExp(int exp)
	{
		this->exp += exp;
		return this->UpdateLeveling();
	}
	inline void gainScore(int score)
	{
		this->score += score;
	}
	inline const int getScore()const
	{
		return this->score;
	}
	inline bool isDamageCoolDown()
	{
		return this->damageTimer < this->damageTimerMax;
	}
	//Functions
	bool UpdateLeveling();
	void ChangeAccessories();
	void UpdateAccessories(const float& dt);
	void Combat(const float& dt);
	void Movement(Vector2u windowBounds,const float& dt);
	void Update(Vector2u windowBounds, const float& dt);
	void Draw(RenderTarget& target);

	//Statics
	static unsigned players;

	//Regular Functions
	float vectorlength(Vector2f v)
	{
		return sqrt(pow(v.x, 2) + pow(v.y, 2));
	}
	Vector2f normalize(Vector2f v, float length)
	{
		if (length == 0)
			return Vector2f(0.f, 0.f);
		else
			return v / length;
	}
};

