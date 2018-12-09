/*

	Adam Harvey Games Programming
	File Name - Creature.cpp
	Project - Tutorial 01 Exercise 01

*/

#include "../Headers/Person.h"
#include <iostream>
#include <conio.h>
#include "SDL.h"
#include "../Headers/Bitmap.h"
#include "../Headers/GameObj.h"

using namespace std; 

const int maxPixels = 5;

Person::Person(SDL_Renderer* renderer, pos position, string name, string filename, bool useTransparency, Arena* detection) : GameObj(renderer, position,filename,useTransparency,detection)
{
	
	Pixels = 0;
	int m_speed = 1;

}

	//Adjusts co-ordinates left
void Person::left(int speed)
{	

	m_direction = LEFT; // enum used to determine direction

	int creatureWidth = creatureTexture->getWidth() - 1; // minusing the one pixel for accurate collision
	int creatureHeight = creatureTexture->getHeight() - 1;

	if (creatureCollision->isWall(getX() - speed, getY()) == false) // check to see if there is a wall
	{

		if (creatureCollision->isWall(getX() - speed, getY() + creatureHeight) == false)
		{
			m_xpos = m_xpos - speed; // if no wall movement available
			Pixels++;
			if (Pixels >= maxPixels)
			{
				nextFrame();
				Pixels = 0; 
			}
			 
		}
	}
}
	//Adjusts co-ordinates right
void Person::right(int speed)
{
	
	m_direction = RIGHT; 

	int creatureWidth = creatureTexture->getWidth() - 1;
	int creatureHeight = creatureTexture->getHeight() - 1; 

	if (creatureCollision->isWall(getX() + creatureWidth + speed, getY()) == false)
	{
		if (creatureCollision->isWall(getX() + creatureWidth + speed, getY() + creatureHeight) == false)
		{
			m_xpos = m_xpos + speed;
			Pixels++;
			if (Pixels >= maxPixels)
			{
				nextFrame();
				Pixels = 0;
			}
		}
	}

	bool hitwall = true;

}
	//Adjusts co-ordinates up
void Person::up(int speed)
{

	m_direction = UP; 

	int creatureWidth = creatureTexture->getWidth() - 1;
	int creatureHeight = creatureTexture->getHeight() - 1;

	if (creatureCollision->isWall(getX(), getY() - speed) == false)  
	{
		if (creatureCollision->isWall(getX() + creatureWidth, getY() - speed) == false)
		{
			m_ypos = m_ypos - speed;
			Pixels++;
			if (Pixels >= maxPixels)
			{
				nextFrame();
				Pixels = 0;
			}
		}
	}
}
	//Adjusts co-ordinates down
void Person::down(int speed)
{

	m_direction = DOWN; 

	int creatureWidth = creatureTexture->getWidth() - 1;
	int creatureHeight = creatureTexture->getHeight() - 1;

	if (creatureCollision->isWall(getX(), getY() + creatureHeight + speed) == false) 
	{
		if (creatureCollision->isWall(getX() + creatureWidth, getY() + creatureHeight + speed) == false)
		{
			m_ypos = m_ypos + speed;
			Pixels++;
			if (Pixels >= maxPixels)
			{
				nextFrame();
				Pixels = 0;
			}
		}
	}
	
}

// calling parents update and draw

void Person::draw(void)
{

	GameObj::draw();


}
void Person::update(void)
{


	GameObj::update(); 

}

