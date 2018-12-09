#include "../Headers/Bomb.h"



Bomb::Bomb(SDL_Renderer* renderer, pos position, string name, string filename, bool  useTransparency, Arena* detection, Hero* hero) : Object(renderer, position, filename,  useTransparency, detection)
{
	setAlive(false); // making sure it won't draw straight away.

	m_pHero = hero;

}


// calling parents update and draw functions 

void Bomb::update()
{

	Object::update(); 
	


}

void Bomb::draw()
{

	Object::draw(); 

}

