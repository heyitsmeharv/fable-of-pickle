#include "../Headers/Bat.h"
#include "../Headers/SmartMonster.h"



Bat::Bat(SDL_Renderer* renderer, string name, pos position, int lives, string filename, bool useTransparency, Arena* detection, Hero* hero) : SmartMonster(renderer, name, position,  lives,  filename,  useTransparency,  detection, hero)
{
	m_hero = hero; 

	// making sure it will render
	setAlive(true);

	// Call any animation
	addFrame("assets/Bat2.bmp");
	addFrame("assets/Bat3.bmp");
	addFrame("assets/Bat4.bmp");
	addFrame("assets/Bat5.bmp");


}

// calling parents update and draw functions 

void Bat::update()
{

	SmartMonster::update(m_hero);


}
void Bat::draw()
{

	SmartMonster::draw();


}
