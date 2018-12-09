#include "../Headers/SmartMonster.h"
#include "../Headers/Hero.h"
#include "../Headers/Bomb.h"
#include "../Headers/Gold.h" 
#include "../Headers/Boss Key.h"
#include "../Headers/Bitmap.h"
#include <ctime> 


SmartMonster::SmartMonster(SDL_Renderer* renderer, string name, pos position, int lives, string filename, bool useTransparency, Arena* detection, Hero* hero) : Person(renderer, position, name, filename, useTransparency, detection)
{
	arena = detection;

	// set positions
	 pos PosBomb = {getX(), getY()}; 
	 pos PosGold = {getX(), getY()}; 
	 pos PosKey = {getX(), getY()};  
	 pos PosLives = {getX(), getY()}; 

	m_bomb = new Bomb(renderer, PosBomb, "bomb" , "assets/Bomb.bmp", true, detection, hero);
	m_gold = new Gold(renderer, PosGold, "gold", "assets/Gold.bmp", true, detection, hero);
	m_key = new BossKey(renderer, PosKey, "boss key", "assets/Key.bmp", true, detection, hero);
	m_lives = new Gold(renderer, PosLives, "lives", "assets/Lives.bmp", true, detection, hero);


}

void SmartMonster::chase(Hero* hero)
{
	
	bool havePath = arena->aStar(m_xpos, m_ypos, hero->getX(), hero->getY(), &targetx, &targety);

	if (!havePath)
	{
		//no path. DO something sensible instead
		
		//patrol

	}
	else
	{
		//got a path. follow it.
		if (targetx > m_xpos) right(2);
		else if (targetx < m_xpos) left(2);
		if (targety > m_ypos) down(2);
		else if (targety < m_ypos) up(2);
	}


}

bool SmartMonster::isHero(Hero* hero)
{
	
	bool collision = false;

	//get the hero width and height same with monster aa bb check
	int HeroUp = hero->getY();
	int HeroDown = hero->getY() + hero->BitmapHeight() - 1;
	int HeroLeft = hero->getX();
	int HeroRight = hero->getX() + hero->BitmapWidth() - 1;

	int MonsterUp = m_ypos;
	int MonsterDown = m_ypos + BitmapHeight();
	int MonsterLeft = m_xpos;
	int MonsterRight = m_xpos + BitmapWidth();

	if ((HeroUp < MonsterDown) && (HeroDown > MonsterUp))
	{
		if ((HeroLeft < MonsterRight) && (HeroRight > MonsterLeft))
		{
	
			collision = true;

			// TODO: Fix the player when it takes damage. Give the hero a 3 second invulnrable period. 
			if(hero->m_lastLoss + hero->m_imTime <= time(0)) { 
				hero->m_lastLoss = time(0);
			// take a life away and set hero to the enterance of level
			hero->setLives(-1);
			hero->setX(80);
			hero->setY(515);

			}
		}


	}
	
	return collision; 

}

void SmartMonster::draw()
{
	Person::draw();

	if (m_bomb->alive() == true)
	{
		m_bomb->draw();
	}
	
	if (m_key->alive() == true)
	{
		m_key->draw();
	}
	
	if (m_gold->alive() == true)
	{
		m_gold->draw();
	}
	
	if (m_lives->alive() == true)
	{

		m_lives->draw(); 

	}
	
}

void SmartMonster::update(Hero* hero)
{

	Person::update(); 

	nextFrame(); 

	if (m_bomb->alive() == true)
	{
		m_bomb->update();

		if ((hero->getY() < m_bomb->getY() + m_bomb->BitmapHeight() - 1) && (hero->getY() + BitmapHeight() - 1 > m_bomb->getY()))
			{
				if ((hero->getX() < m_bomb->getX() + m_bomb->BitmapWidth() - 1) && (hero->getX() + BitmapWidth() - 1 > m_bomb->getX()))
				{

					// aa bb check with hero
					// if true stop draw and pick up!
					m_bomb->setAlive(false); 
					
					if(hero->getLives() < 3)
					{
						hero->setBombs(+1); 
					}
				}
			}

		}

	
	if (m_key->alive() == true)
	{
		m_key->update();

		if ((hero->getY() < m_key->getY() + m_key->BitmapHeight() - 1) && (hero->getY() + BitmapHeight() - 1 > m_key->getY()))
			{
				if ((hero->getX() < m_key->getX() + m_key->BitmapWidth() - 1) && (hero->getX() + BitmapWidth() - 1 > m_key->getX()))
				{

					// aa bb check with hero
					// if true stop draw and pick up!
					m_key->setAlive(false); 

					hero->hasKey(true);

				}
			}
		
		}

	
	if (m_gold->alive() == true)
	{
		m_gold->update();

		if ((hero->getY() < m_gold->getY() + m_gold->BitmapHeight() - 1) && (hero->getY() + BitmapHeight() - 1 > m_gold->getY()))
			{
				if ((hero->getX() < m_gold->getX() + m_gold->BitmapWidth() - 1) && (hero->getX() + BitmapWidth() - 1 > m_gold->getX()))
				{
					// aa bb check with hero
					// if true stop draw and pick up!
					m_gold->setAlive(false); 
					hero->setScore(10); 
 
				}
			}
	}



	if (m_lives->alive() == true)
	{

		m_lives->update(); 

		if ((hero->getY() < m_lives->getY() + m_lives->BitmapHeight() - 1) && (hero->getY() + BitmapHeight() - 1 > m_lives->getY()))
			{
				if ((hero->getX() < m_lives->getX() + m_lives->BitmapWidth() - 1) && (hero->getX() + BitmapWidth() - 1 > m_lives->getX()))
				{
					// aa bb check with hero
					// if true stop draw and pick up!
					m_lives->setAlive(false); 

					if(hero->getLives() < 3)
					{
						hero->setLives(+1); 
					}
				}



			}

	}
	

}

// function that assignes each item a random chance of dropping. 
// sets the item to drop on monsters position!

void SmartMonster::dropChance()
{

	int currentDrop = rand() % 20;

	if (currentDrop >= 10 && currentDrop <=20)
	{
		
		m_gold->setAlive(true);
		m_gold->setX(m_xpos);
		m_gold->setY(m_ypos); 


	}

	else if (currentDrop >= 6 && currentDrop <= 9)
	{

		m_bomb->setAlive(true);
		m_bomb->setX(m_xpos);
		m_bomb->setY(m_ypos); 

	}

	else if (currentDrop >= 2 && currentDrop <= 5)
	{

		m_lives->setAlive(true);
		m_lives->setX(m_xpos);
		m_lives->setY(m_ypos); 

	}
	
	else if (currentDrop == 1)
	{

		m_key->setAlive(true); 
		m_key->setX(m_xpos);
		m_key->setY(m_ypos); 

	}


}


