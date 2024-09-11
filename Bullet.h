#pragma once
#include"TextTag.h"
class Bullet
{
private:
	//Stabilizer
	float dtMultiplier;
	//Textures
	Texture* texture;
	Sprite sprite;
	//Velocity
	float maxVelocity;
	Vector2f currentvelocity;
	//Acceleration
	float acceleration;
	//moveDirection
	Vector2f direction;
	
	float initialVelocity;
public:
	Bullet(Texture* texture,
		Vector2f position, Vector2f scale,
		Vector2f moveDirection, float initialVelocity,
		float maxVelocity, float acceleration);

	virtual ~Bullet();

	//Accessors
	inline FloatRect getGlobalBounds()const
	{
		return this->sprite.getGlobalBounds();
	}
	inline const Vector2f& getPosition()const
	{
		return this->sprite.getPosition();
	}
	
	//Functions
	void Movement(const float& dt);
	void Update(const float& dt);
	void Draw(RenderTarget& target);


};

