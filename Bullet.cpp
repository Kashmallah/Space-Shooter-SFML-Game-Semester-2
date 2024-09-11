#include "Bullet.h"

Bullet::Bullet(
	Texture* texture, Vector2f position, Vector2f scale,
	Vector2f moveDirection, float initialVelocity,
	float maxVelocity, float acceleration)
{
	this->dtMultiplier = 62.5f;

	this->texture = texture;
	this->sprite.setTexture(*this->texture);
	this->initialVelocity=initialVelocity;
	this->maxVelocity = maxVelocity;
	this->acceleration = acceleration;
	this->direction = moveDirection;
	this->currentvelocity = Vector2f(
		initialVelocity * this->direction.x,
		initialVelocity * this->direction.y);

	this->sprite.setOrigin(
		this->sprite.getGlobalBounds().width / 2,
		this->sprite.getGlobalBounds().height / 2);

	this->sprite.setScale(scale);
	this->sprite.setPosition(position);

	this->sprite.setRotation(atan2(this->direction.y, this->direction.x) * 180 / 3.14159265359 + 180);
}

Bullet::~Bullet()
{

}

void Bullet::Movement(const float& dt)
{
	if (this->acceleration > 0.f)
	{
		if (this->currentvelocity.x < this->maxVelocity)
			this->currentvelocity.x += this->acceleration
			* this->direction.x
			* dt * this->dtMultiplier;
		if (this->currentvelocity.y < this->maxVelocity)
			this->currentvelocity.y += this->acceleration
			* this->direction.y
			* dt * this->dtMultiplier;
	}
	else
	{
		this->currentvelocity = Vector2f(
			this->maxVelocity * this->direction.x,
			this->maxVelocity * this->direction.y);
	}
	this->sprite.move(this->currentvelocity * dt * this->dtMultiplier);

}

void Bullet::Update(const float& dt)
{
	this->Movement(dt);
}

void Bullet::Draw(RenderTarget& target)
{
	target.draw(this->sprite);

}
