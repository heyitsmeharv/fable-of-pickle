#pragma once

#include "Arena.h"
#include "Hero.h"
#include "Bitmap.h"
#include "Object.h"


class Bomb : public Object
{
public:

	Bomb(SDL_Renderer* renderer, pos position, string name, string filename, bool useTransparency, Arena* detection, Hero* hero);
	void collision(Hero* m_pHero);
	void update();
	void draw();
	void explosionRadius();
	bool pickedUp;
	bool placedDown;
	int m_bombCounter;
	int m_bombTimer;
	bool bombExplode;

private:





protected:

	

	Hero* m_pHero;

};