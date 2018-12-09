#include "../Headers/Boss.h"
#include "../Headers/Hero.h"

Boss::Boss(SDL_Renderer* renderer, string name, pos position, int lives, string filename, bool useTransparency, Arena* detection, Hero* hero) : SmartMonster(renderer, name,  position,  lives,  filename,  useTransparency,  detection, hero)
{
	setAlive(true); // will be able to draw 

	m_hero = hero;

	m_lives = lives;

}


Boss::~Boss(void)
{
}


// calling parents update and draw functions 

void Boss::draw()
{

	SmartMonster::draw();


}

void Boss::update()
{

	SmartMonster::update(m_hero); 

}

// taking damge function used for boss only 

void Boss::takeDamage()
{

	m_hero->setScore(50); // adding score each hit. 

  	m_lives = m_lives - 1; // take away a life each hit. 

	if (m_lives == 0)
	{

		setAlive(false); // stop drawing it

	}


}