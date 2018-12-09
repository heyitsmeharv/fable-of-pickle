#include "../Headers/Item.h"

Item::Item(SDL_Renderer* renderer, pos position, string name, string filename, bool useTransparency, Arena* detection, Hero* hero) : Object(renderer, position, filename, useTransparency, detection)
{




}

void Item::draw()
{

	Object::draw();


}

void Item::update()
{

	Object::update(); 

}