#include "../Headers/Hero.h"
#include "../Headers/Bat.h"
#include "../Headers/Skeleton.h"
#include "../Headers/Bomb.h"
#include "../Headers/Boss.h"
#include <ctime>

using namespace std;

Hero::Hero(SDL_Renderer* renderer, string name, pos position, int lives, int bombs, string filename, bool useTransparency, Arena* detection) : Person(renderer, position, name, filename, useTransparency, detection)
{
	//initializing vars
	m_lives = lives;
	m_bombs = bombs;
	m_key = false;
	m_alive = true; 
	projectileIndx = 0;
	bombIndx = 0; 
	m_score = 0;
	
	m_lastLoss = 0;
	m_imTime = 3;


	 // Creating the projectile.
	 for (int loop = 0; loop < numProjectiles; loop++) 
	 {

		projectile[loop] = new Projectile(renderer, position, "Projectile", "assets/Projectile.bmp", true, detection, this);


	 }


	 // Hacky way of trying to get bombs to work. They do not work the same as projectile.
	 pos BombPooos = {getX(), getY()};
	 
	 for (int loop = 0; loop < numBombs; loop++) 
	 {
		bomb[loop] = new Bomb(renderer, BombPooos, "bomb", "assets/Bomb.bmp", true, detection, this);
	 
	 }

}

bool Hero::loadLevel()
{
	// Is the player at the door?
	if(creatureCollision->isDoor(getX(), getY()) == true)
	{
		// does the player have a key?
		if (creatureCollision->getLevel() == creatureCollision->LevelSize() - 2 && getKey() == true)
			{
				// load in the lead level
				creatureCollision->LoadLevel(creatureCollision->LevelSize() - 1); 

			}


		else if (getKey() == true)
		{
			// load in boss level
			creatureCollision->LoadLevel(creatureCollision->LevelSize() - 2);

		}
		else
		{

			// if no key, load in random level that isn't the ones above
			creatureCollision->LoadLevel(rand() % (creatureCollision->LevelSize() - 2 ) + 1);

		}

		// loop through projectiles and stop drawing them 
		 for (int loop = 0; loop < numProjectiles; loop++) 
		{
			projectile[loop]->setAlive(false); 
		}

		 for (int loop = 0; loop < numBombs; loop++) 
		{
			bomb[loop]->setAlive(false); 
		}
			setX(62);
			setY(515);
		
			return true; 
	}
		return false;

}

void Hero::Fire()
{

	if (projectile[projectileIndx]->alive() == false) // so if you've not already been firing or a projectile exists
		{
			// you can fire
			projectile[projectileIndx]->setX(getX()); // Set the position and direction
			projectile[projectileIndx]->setY(getY());
			projectile[projectileIndx]->setAlive(true); // draw
			projectile[projectileIndx]->setDirection(m_direction);
			projectileIndx++; // increase the array

		}


	if (projectileIndx == numProjectiles)
	{
		// set the index to zero when number of proj are reached. Only want to fire one so it doesn't really matter
		projectileIndx = 0;
	}

	

}

void Hero::LayBomb()
{
	
	if (bomb[bombIndx]->alive() == false) // not being able to draw more than one bomb
	{
			bomb[bombIndx]->setX(getX()); // set positions
			bomb[bombIndx]->setY(getY());
			bomb[bombIndx]->setAlive(true); //draw
			bombIndx++;

	}
		
	if (bombIndx == numBombs)
	{

		bombIndx = 0; 

	}

	setBombs(-1); // minus one on the HUD counter
	
}

void Hero::update(vector<Skeleton*> Skele_Vec, vector<Bat*> Bat_Vec, vector<Boss*> Boss_Vec)
{


	Person::update(); 

	for (int loop = 0; loop < numProjectiles; loop++)
	{

		if (projectile[loop]->alive() == true) // if there is a projectile fired
		{

			projectile[loop]->update(Skele_Vec, Bat_Vec, Boss_Vec); // check to see if it's hit anything

		}


	}


	for (int loop = 0; loop < numBombs; loop++)
	{

		if (bomb[loop]->alive() == true)
		{

			bomb[loop]->update();

		}


	}
	
}

// calling parents update and draw functions 

void Hero::draw()
{

	Person::draw(); 

	for (int loop = 0; loop < numProjectiles; loop++)
	{

		if (projectile[loop]->alive() == true)
		{

			projectile[loop]->draw(); // if something is fired draw it!
			
		}

	}

	for (int loop = 0; loop < numBombs; loop++)
	{

		if (bomb[loop]->alive() == true)
		{

			bomb[loop]->draw();
			
		}

	}


}

// getters and setters!

int Hero::getLives()
{

	return m_lives;

}

void Hero::setLives(int lives)
{
	m_lives += lives;
}

int Hero::getScore()
{

	return m_score;

}

void Hero::setScore(int score)
{
	
	m_score += score; 

}

bool Hero::getKey()
{

	return m_key;

}

void Hero::hasKey(bool key)
{

	m_key = key;

}

int Hero::getBombs()
{
	return m_bombs; 
}

void Hero::setBombs(int bombs)
{
	
	 m_bombs += bombs;
	
}


