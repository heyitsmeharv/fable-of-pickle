#include "../Headers/Projectile.h"
#include "../Headers/Arena.h"
#include "../Headers/Bat.h"
#include "../Headers/Skeleton.h"
#include "../Headers/Hero.h"
#include "../Headers/Boss.h"

const int time = 20; // when i want it to refresh
const int Projspeed = 10; // speed of projectile


Projectile::Projectile(SDL_Renderer* renderer, pos position, string name, string filename, bool useTransparency, Arena* detection, Hero* hero) : Object(renderer, position, filename, useTransparency, detection)
{

	m_alive = false;  // don't draw!
	speed = Projspeed;
	lifetime = time; 
	m_hero = hero;

}

void Projectile::update(vector<Skeleton*> Skele_Vec, vector<Bat*> Bat_Vec, vector<Boss*> Boss_Vec)
{

	Object::update();
	
	bool collision = false; // collision is false until...

	int creatureWidth = creatureTexture->getWidth() - 1;
	int creatureHeight = creatureTexture->getHeight() - 1;

	// Switch statement with an enum to determine direction

	switch(m_direction){

		
	case UP: 

		if ((creatureCollision->isWall(getX(), getY()) == false)
		 && (creatureCollision->isWall(getX() + creatureWidth, getY() - speed) == false))
			{

				m_ypos = m_ypos - speed; // unless proj hits a wall go increment on y axis

			}
		
		else
		{
			setAlive(false); // stop draw

		}


		break;


	case DOWN:

		if ((creatureCollision->isWall(getX(), getY()) == false)
		 && (creatureCollision->isWall(getX() + creatureWidth, getY() + creatureHeight + speed) == false))
			{
				m_ypos = m_ypos + speed; // unless proj hits a wall go decrease on y axis

				 
			}
		
		else
		{
			setAlive(false); // stop draw

		}

		break;


	case LEFT:


		if ((creatureCollision->isWall(getX() - speed, getY()) == false)
		 &&(creatureCollision->isWall(getX() - speed, getY() + creatureHeight) == false))
		{
				m_xpos = m_xpos - speed; // unless proj hits a wall go increment on x axis	  
				
		}
		
		else
		{
			setAlive(false); // stop draw

		}
	
		break;


	case RIGHT:
		if ((creatureCollision->isWall(getX(), getY()) == false)
		&&(creatureCollision->isWall(getX() + creatureWidth + speed, getY() + creatureHeight) == false))
			{
				m_xpos = m_xpos + speed; // unless proj hits a wall go decrease on x axis

				
			}
		else
		{
			setAlive(false); // stop draw!

		}

		break;

	}

	// lifetime of the projectile

	if (lifetime < 0)
	{

		setAlive(false); // if time runs out don't draw
		lifetime = time;

	}


	// collision

	// loop through each enemy vector

	// if it's alive do aa bb collision check

	// if collided...do something. stop draw alive

	for (int loop = 0; loop < Skele_Vec.size(); loop++)
	{
		if (Skele_Vec[loop]->alive() == true)
		{

			if ((getY() < Skele_Vec[loop]->getY() + Skele_Vec[loop]->BitmapHeight() - 1) && (getY() + BitmapHeight() - 1 > Skele_Vec[loop]->getY()))
			{
				if ((getX() < Skele_Vec[loop]->getX() + Skele_Vec[loop]->BitmapWidth() - 1) && (getX() + BitmapWidth() - 1 > Skele_Vec[loop]->getX()))
				{

					collision = true; 

					m_hero->setScore(+10); // increment score
					
					Skele_Vec[loop]->setAlive(false); // stop draw 

					Skele_Vec[loop]->dropChance(); // drops items 
		
	
				}
			}
		
		}

	}
	
	for (int loop = 0; loop < Bat_Vec.size(); loop++)
	{

		if (Bat_Vec[loop]->alive() == true)
		{

		if ((getY() < Bat_Vec[loop]->getY() + Bat_Vec[loop]->BitmapHeight() - 1) && (getY() + BitmapHeight() - 1 > Bat_Vec[loop]->getY()))
			{
				if ((getX() < Bat_Vec[loop]->getX() + Bat_Vec[loop]->BitmapWidth() - 1) && (getX() + BitmapWidth() - 1 > Bat_Vec[loop]->getX()))
				{
					
					collision = true;
					
					m_hero->setScore(+5); 

					Bat_Vec[loop]->setAlive(false);
					
					Bat_Vec[loop]->dropChance();
			

				}
			}
		
		
		}
	}

	for (int loop = 0; loop < Boss_Vec.size(); loop++)
	{
		if (Boss_Vec[loop]->alive() == true)
		{

			if ((getY() < Boss_Vec[loop]->getY() + Boss_Vec[loop]->BitmapHeight() - 1) && (getY() + BitmapHeight() - 1 > Boss_Vec[loop]->getY()))
			{
				if ((getX() < Boss_Vec[loop]->getX() + Boss_Vec[loop]->BitmapWidth() - 1) && (getX() + BitmapWidth() - 1 > Boss_Vec[loop]->getX()))
				{

					collision = true;

					Boss_Vec[loop]->takeDamage();

					setAlive(false);

	
				}
			}
		
		}

	}


	lifetime--; // make timer go down

}

void Projectile::draw()
{


	Object::draw(); 

}
