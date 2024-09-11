#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<vector>
#include<cstdlib>
#include<math.h>
#include<fstream>
#include"dArr.h"
using namespace sf;
using namespace std;
class TextTag
{
private:
	//stabilizer
	float dtMultiplier;
	//fonts
	Font* font;
	Text text;
	//speed
	float speed;
	Vector2f moveDirection;
	//timer
	float timerMax;
	float timer;
	bool accelarate;

public:
	TextTag(Font* font, string text,
		const Color color,
		Vector2f position,Vector2f moveDirection,
		unsigned int size,
		float timerMax,bool accelarate);
	virtual ~TextTag();

	//Accessors
	inline const float& getTimer()const
	{
		return this->timer;
	}
	void Update(const float& dt);
	void Draw(RenderTarget &target);


};

