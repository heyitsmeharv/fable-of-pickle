#include "../Headers/Object.h"



Object::Object(SDL_Renderer* renderer, pos position, string filename, bool useTransparency, Arena* detection) : GameObj(renderer, position, filename, useTransparency, detection)
{


}


// calling parents update and draw

void Object::update(void)
{
	
	GameObj::update();

}

void Object::draw()
{

	GameObj::draw();

}

