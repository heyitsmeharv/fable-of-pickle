#include "../Headers/Boss Key.h"
#include "../Headers/Object.h"

BossKey::BossKey(SDL_Renderer* renderer, pos position, string name, string filename, bool  useTransparency, Arena* detection, Hero* hero) : Object(renderer, position, filename, useTransparency, detection)
{
	setAlive(false); // making sure it won't draw straight away



}


// calling parents update and draw functions 
 
void BossKey::update()
{

	Object::update();


}

void BossKey::draw()
{

	Object::draw();


}