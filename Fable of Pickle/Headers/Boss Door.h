#pragma once

#include "Hero.h"
#include "Arena.h"


class BossDoor
{
public:

	BossDoor(SDL_Renderer* renderer, int x, int y, string name, string filename, bool useTransparency, Arena* detection, Hero* hero);
	void keyCheck(); 


private:





protected:

	bool hasKey;



};