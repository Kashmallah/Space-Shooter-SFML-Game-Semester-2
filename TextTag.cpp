#include "TextTag.h"
using namespace std;
TextTag::TextTag(Font* font, string text,
	const Color color,
	Vector2f position, Vector2f moveDirection,
	unsigned int size,
	float timerMax, bool accelarate)
{
	this->dtMultiplier = 62.5f;

	this->text.setFont(*font);
	this->text.setCharacterSize(size);
	this->text.setPosition(position);
	this->text.setString(text);
	this->text.setFillColor(color);

	this->speed = 0.6f;
	this->moveDirection.x = moveDirection.x;
	this->moveDirection.y = moveDirection.y;
	this->timerMax = timerMax;
	this->timer = this->timerMax;
	this->accelarate = accelarate;
}
TextTag::~TextTag()
{

}

void TextTag::Update(const float& dt)
{
	//Update Timer
	if (this->timer > 0.f)
	{
		this->timer += 1.f * dt * dtMultiplier;
		if (this->accelarate)
		{
			if (this->timer > this->timerMax / 2)
			{
				this->text.move(this->moveDirection.x * (this->speed*10.f) * dt * this->dtMultiplier,
					this->moveDirection.y * (this->speed * 10.f) * dt * this->dtMultiplier );

			}
			else
			{
				this->text.move(this->moveDirection.x * this->speed * dt * this->dtMultiplier,
					this->moveDirection.y * this->speed * dt * this->dtMultiplier);

			}

		}
		else
		{
			this->text.move(this->moveDirection.x * this->speed * dt * this->dtMultiplier,
				this->moveDirection.y * this->speed * dt * this->dtMultiplier);

		}
	}
	else
	{
		this->text.setFillColor(Color(0, 0, 0, 0));
	}
}
void TextTag::Draw(RenderTarget &target)
{
	target.draw(this->text);
}