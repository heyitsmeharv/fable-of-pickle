#pragma once


#include "GameObj.h" 
#include <string>
#include <vector>

using namespace std;


class Hero;

class Object : public GameObj
{
public:

	Object(SDL_Renderer* renderer, pos position, string filename, bool useTransparency, Arena* detection);
	
	void  update(void);
	void  draw( void);


private:





protected:

	

};