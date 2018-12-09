#pragma once

#include "Arena.h"
#include "Hero.h"
#include "Object.h"


class Item : public Object 
{
public:

	Item(SDL_Renderer* renderer, pos position, string name, string filename, bool useTransparency, Arena* detection, Hero* hero);
	void pickUp(void);
	void update(void); 
	void draw();

private:





protected:

	bool m_itemPickedUp;



};