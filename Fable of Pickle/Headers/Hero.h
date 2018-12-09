#pragma once

#include <string>
#include "Projectile.h"
#include "Person.h"


class Bomb;


const int numProjectiles = 1; // Can't assign inside class
const int numBombs = 1;

class Hero : public Person
{
private:

	int m_lives;
	int m_score;
	int m_bombs;
	bool m_key;

	int delay; 

	Projectile* projectile[numProjectiles];
	int projectileIndx;

	Bomb* bomb[numBombs];
	int bombIndx;
	//int livesLimit;
	//int bombLimit;
	

public:

	Hero(SDL_Renderer* renderer, string name, pos position, int lives, int bombs, string filename, bool useTransparency, Arena* detection);
	bool loadLevel();  
	void Fire();
	void draw(); 
	void LayBomb(); 
	void update(vector<Skeleton*> Skele_Vec, vector<Bat*> Bat_Vec, vector<Boss*> Boss_Vec);

	int getLives();
	void setLives(int lives);
	int getScore();
	void setScore(int score);
	bool getKey();
	void hasKey(bool key);
	int getBombs();
	void setBombs(int bombs);
	void pickUp();	

	int m_lastLoss;
	int m_imTime;

protected:
};