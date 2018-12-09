#include "../Headers/Skeleton.h"
#include "../Headers/Hero.h"


Skeleton::Skeleton(SDL_Renderer* renderer, string name, pos position, int lives, string filename, bool useTransparency, Arena* detection, Hero* hero) : SmartMonster(renderer, name,  position,  lives,  filename,  useTransparency,  detection, hero)
{

	m_hero = hero;

	setAlive(true);

	// calls relevent animation
	addFrame("assets/Skeleton2.bmp");
	addFrame("assets/Skeleton3.bmp");
	addFrame("assets/Skeleton4.bmp");
	addFrame("assets/Skeleton5.bmp");

}

// calls parents draw and update

void Skeleton::draw()
{

	SmartMonster::draw();

}

void Skeleton::update()
{

	SmartMonster::update(m_hero); 




}