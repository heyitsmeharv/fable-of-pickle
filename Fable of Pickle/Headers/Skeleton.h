#pragma once

#include "SmartMonster.h"

class Hero;


class Skeleton : public SmartMonster
{

public:

	Skeleton(SDL_Renderer* renderer, string name, pos position, int lives, string filename, bool useTransparency, Arena* detection, Hero* hero);
	
	void draw();
	void update(); 

private:





protected:

	Hero* m_hero;







};