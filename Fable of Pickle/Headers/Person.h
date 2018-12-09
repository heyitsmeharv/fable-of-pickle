/*

	Adam Harvey Games Programming 
	File Name - Person.h
	Project - AE2

*/

#pragma once

#include <string>
#include "SDL.h"
#include "GameObj.h"

using namespace std;


class Person : public GameObj
{
	//Protected Variables
protected:
	
	int Pixels;

	//Public Variables
public:
	
	//Private Methods
private:
	
	
	


	//Public Methods
public:
	Person(SDL_Renderer* renderer, pos position, string name, string filename, bool useTransparency, Arena* detection);
	void left(int speed);
	void right(int speed);
	void up(int speed);
	void down(int speed);
	
	void draw(void); 
	
	int m_speed;
	
	void update(void);

};