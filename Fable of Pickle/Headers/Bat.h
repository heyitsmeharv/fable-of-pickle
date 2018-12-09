#pragma once

#include "SmartMonster.h"

class Hero; 

class Bat : public SmartMonster
{

public:

	Bat(SDL_Renderer* renderer, string name, pos position, int lives, string filename, bool useTransparency, Arena* detection, Hero* hero);

	void update();
	void draw(); 

private:

	



protected:


	Hero* m_hero;






};