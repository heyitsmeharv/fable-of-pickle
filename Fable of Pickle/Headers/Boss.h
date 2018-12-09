#pragma once

#include "SmartMonster.h"

class Hero; 

class Boss : public SmartMonster
{
public:
	
	Boss(SDL_Renderer* renderer, string name, pos position, int lives, string filename, bool useTransparency, Arena* detection, Hero* hero);
	~Boss(void);
	void draw();
	void update();
	
	void takeDamage(); 

private:



protected:

	Hero* m_hero;

	int m_lives;

};

