#include "Enemy.h"

enum eTypes
{
	MOVELEFT = 0,
	FOLLOW,
	MOVELEFTSHOOT,
	FOLLOWFAST,
	FOLLOWSHOOT,
	FOLLOWFASTSHOOT
};

enum bulletTypes
{
	REGULAR = 0,
	MISSILE
};

Enemy::Enemy(
	dArr < Texture>& textures,
	dArr < Texture>& bulletTextures,
	Vector2u windowBounds,
	Vector2f position,
	Vector2f moveDirection,
	int type,
	int scaler,
	int playerFollowNr)
{
	this->dtMultiplier = 62.5f;


	this->textures = &textures;
	this->bulletTextures = &bulletTextures;

	this->type = type;

	if (this->type >= (*this->textures).size())
		cout << "NO TEXTURE FOR THIS TYPE! ERROR!" << "\n";
	else
		this->sprite.setTexture((*this->textures)[this->type]);

	this->sprite.setOrigin
	(
		this->sprite.getGlobalBounds().width / 2,
		this->sprite.getGlobalBounds().height / 2
	);

	this->windowBounds = windowBounds;

	this->damageTimerMax = 4.f;
	this->damageTimer = 0;

	this->shootTimerMax = 50.f;
	this->shootTimer = this->shootTimerMax;

	this->moveDirection = moveDirection;

	switch (this->type)
	{
	case MOVELEFT:
		this->sprite.setScale(Vector2f(0.15, 0.15));
		this->hpMax = (rand() % 5 + 1) * scaler;
		this->hp = this->hpMax;
		this->damageMax = (rand() % 3 + 1) * scaler;
		this->damageMin = (rand() % 1 + 1) * scaler;
		this->maxVelocity = rand() % 20 + 5;
		break;
	case FOLLOW:
		this->sprite.setScale(Vector2f(0.1, 0.1));
		this->hpMax = (rand() % 3 + 1) * scaler;
		this->hp = this->hpMax;
		this->damageMax = (rand() % 2 + 1) * scaler;
		this->damageMin = (rand() % 1 + 1) * scaler;
		this->maxVelocity = 6 + 3;
		break;

	case MOVELEFTSHOOT:
		this->sprite.setScale(Vector2f(0.12, 0.12));
		this->hpMax = (rand() % 3 + 1) * scaler;
		this->hp = this->hpMax;
		this->damageMax = (rand() % 2 + 1) * scaler;
		this->damageMin = (rand() % 1 + 1) * scaler;
		this->maxVelocity = 10 + 3;
		this->shootTimerMax = 15.f;
		this->shootTimer = 0.f;
		break;

	default:
		this->hpMax = (rand() % 2 + 1) * scaler;
		this->hp = this->hpMax;
		this->damageMax = (rand() % 2 + 1) * scaler;
		this->damageMin = (rand() % 1 + 1) * scaler;
		this->maxVelocity = 15 + 5;
		break;
	}
	this->hpMax = hpMax;
	this->hp = this->hpMax;
	this->damageMax = damageMax;
	this->damageMin = damageMin;

	this->playerFollowNr = playerFollowNr;

	this->sprite.setPosition(this->windowBounds.x, (rand() % this->windowBounds.y) - this->sprite.getGlobalBounds().height);

}
Enemy::~Enemy()
{

}

void Enemy::collision()
{
	this->damageTimer = this->damageTimerMax;

}

void Enemy::takeDamage(int damage)
{
	this->hp -= damage;

	this->damageTimer = this->damageTimerMax;

	if (this->hp <= 0)
	{
		this->hp = 0;
	}
}
void Enemy::Update(const float& dt,Vector2f playerPosition)
{

	switch (this->type)
	{
	case MOVELEFT:
		this->sprite.move(
			this->moveDirection.x * this->maxVelocity * dt * this->dtMultiplier,
			this->moveDirection.y * this->maxVelocity * dt * this->dtMultiplier);
		
		this->normalizedMoveDIR = normalize(
			this->moveDirection, 
			vectorlength(this->moveDirection));

		break;
	case FOLLOW:

		if (this->sprite.getPosition().x > playerPosition.x)
		{
			this->moveDirection.x = playerPosition.x - this->sprite.getPosition().x;
			this->moveDirection.y = playerPosition.y - this->sprite.getPosition().y;
		}
		this->normalizedMoveDIR = normalize(
			this->moveDirection,
			vectorlength(this->moveDirection));

		if (this->normalizedMoveDIR.y > 0.3)
			this->normalizedMoveDIR.y = 0.3;
		else if (this->normalizedMoveDIR.y < -0.3)
			this->normalizedMoveDIR.y = -0.3;

		if (this->normalizedMoveDIR.x > -0.7)
			this->normalizedMoveDIR.x = -0.7;

		this->sprite.setRotation(atan2(
			this->normalizedMoveDIR.y,
			this->normalizedMoveDIR.x) * 100 / 3.14159265359 + 180);
		
		this->sprite.move(
			this->normalizedMoveDIR.x * this->maxVelocity * dt * dtMultiplier,
			this->normalizedMoveDIR.y * this->maxVelocity * dt * dtMultiplier);
		break;

	case MOVELEFTSHOOT:

		this->shootTimerMax = 50.f;

		if (shootTimer < this->shootTimerMax)
			this->shootTimerMax += 1.f * dt * this->dtMultiplier;

		this->lookDirection.x = playerPosition.x - this->sprite.getPosition().x;
		this->lookDirection.y = playerPosition.y - this->sprite.getPosition().y;
		
		this->normalizedlookDIR = normalize(this->lookDirection, vectorlength(this->lookDirection));
		
		this->sprite.setRotation(atan2(this->normalizedlookDIR.y, this->normalizedlookDIR.x) * 180 / 3.14159265359 + 180);

		this->sprite.move(
			this->moveDirection.x * this->maxVelocity * dt * this->dtMultiplier,
			this->moveDirection.y * this->maxVelocity * dt * this->dtMultiplier);

		this->normalizedMoveDIR = normalize(this->moveDirection, vectorlength(this->moveDirection));

		//Shoot
		if (this->shootTimer >= this->shootTimerMax)
		{
			this->bullets.add(
				Bullet(&(*this->bulletTextures)[REGULAR],
					this->sprite.getPosition(),
					Vector2f(0.2f, 0.2f),
					this->normalizedlookDIR,
					2.f,
					5,
					0.5f));

			this->shootTimer = 0.f;
		}


		break;

	default:
		break;
	}
	//Damaged
	if (this->damageTimer>0.f)
	{
		this->damageTimer -= 1.f * dt * dtMultiplier;

		this->sprite.setColor(Color::Red);
		this->sprite.move(
			10.f * -this->normalizedMoveDIR.x * this->damageTimer * dt * dtMultiplier,
			10.f * -this->normalizedMoveDIR.y * this->damageTimer * dt * dtMultiplier);
	}
	else
		this->sprite.setColor(Color::White);

}
void Enemy::Draw(RenderTarget& target)
{
	target.draw(this->sprite);

	for (int i = 0; i < this->bullets.size(); i++)
	{
		this->bullets[i].Draw(target);
	}
}