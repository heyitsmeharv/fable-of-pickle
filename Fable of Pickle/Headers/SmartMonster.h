#pragma once

#include "string.h"
#include "Person.h"
#include "HUD.h"


class Hero;
class Gold;
class BossKey;
class Hero;

class SmartMonster : public Person
{
private: 
	int targetx, targety;

	Arena* arena;
	HUD* hud;
	Bomb* m_bomb;
	Gold* m_gold;
	BossKey* m_key;
	Gold* m_lives;

public:
	SmartMonster(SDL_Renderer* renderer, string name, pos position, int lives, string filename, bool useTransparency, Arena* detection, Hero* hero);

	void chase(Hero* hero);
	bool isHero(Hero* hero);

	void draw();
	void update(Hero* hero); 

	void dropChance();

};