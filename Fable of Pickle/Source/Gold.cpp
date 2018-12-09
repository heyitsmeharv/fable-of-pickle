#include "../Headers/Gold.h"


Gold::Gold(SDL_Renderer* renderer, pos position , string name, string filename, bool useTransparency, Arena* detection, Hero* hero) : Object(renderer, position, filename,  useTransparency, detection)
{

	setAlive(false); // Won't draw unless told to 


}


// calling parents update and draw functions 

void Gold::update()
{

	Object::update();

}

void Gold::draw()
{


	Object::draw();


}