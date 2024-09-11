#pragma once
#include"Bullet.h"
class Enemy
{
private:
	//stabilizer
	float dtMultiplier;

	//Textures
	dArr<Texture>* textures;
	Sprite sprite;

	//Bounds
	Vector2u windowBounds;
	Vector2f moveDirection;
	Vector2f normalizedMoveDIR;
	Vector2f lookDirection;
	Vector2f normalizedlookDIR;
	float maxVelocity;

	dArr<Texture> *bulletTextures;
	dArr<Bullet>bullets;
	
	float damageTimerMax;
	float damageTimer;

	float shootTimerMax;
	float shootTimer;

	//Damages and healths
	int type;
	int hp;
	int hpMax;
	int damageMin;
	int damageMax;

	int playerFollowNr;
public:
	Enemy(
		dArr < Texture>& textures,
		dArr < Texture>& bulletTextures,
		Vector2u windowBounds,
		Vector2f position,
		Vector2f moveDirection,
		int type,
		int scaler,
		int playerFollowNr);

	virtual ~Enemy();

	//Accessors
	inline const int getDamage()const
	{
		return rand() % this->damageMax + this->damageMin;
	}
	inline const int getHP()const
	{
		return this->hp;
	}
	inline const int getHPMax()const
	{
		return this->hpMax;
	}
	inline const bool isDead()const
	{
		return this->hp <= 0;
	}
	inline FloatRect getGloabalBounds()const
	{
		return this->sprite.getGlobalBounds();
	}
	inline Vector2f getPosition()const
	{
		return this->sprite.getPosition();
	}
	inline const int& getPlayerFollowNr()const
	{
		return this->playerFollowNr;
	}
	inline dArr<Bullet>& getBullets()
	{
		return this->bullets;
	}


	//Functions
	void collision();
	void takeDamage(int damage);
	void Update(const float& dt, Vector2f playerPosition);
	void Draw(RenderTarget& target);
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

