#pragma once

#include "Object.h"


class Bat;
class Skeleton; 
class Arena; 
class Boss;

class Projectile : public Object
{
public:

	Projectile(SDL_Renderer* renderer, pos position, string name, string filename, bool useTransparency, Arena* detection, Hero* hero);
	void update(vector<Skeleton*> Skele_Vec, vector<Bat*> Bat_Vec, vector<Boss*> Boss_Vec);
	void draw(); 

private:


protected:

	int speed;
    int lifetime;

	Hero* m_hero; 
	

};