#pragma once

#include "Arena.h"
#include "Hero.h"
#include "Object.h"

class Gold : public Object
{
public:

	Gold(SDL_Renderer* renderer, pos position, string name, string filename, bool  useTransparency, Arena* detection, Hero* hero);
	void update();
	void draw();

private:





protected:




};