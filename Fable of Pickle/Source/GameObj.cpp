#include "../Headers/GameObj.h"



GameObj::GameObj(SDL_Renderer* renderer, pos position, string filename, bool useTransparency, Arena* detection)
{
	//Initialising objects
	
	m_xpos = position.x;
	m_ypos = position.y;
	m_current_frame = 0;

	m_renderer = renderer; 
	
	creatureTexture = new Bitmap(renderer, filename, position.x, position.y, useTransparency);
	creatureCollision = detection;

	m_CreatureBitmaps.push_back(creatureTexture);

	
	m_direction = UP; 

}


GameObj::~GameObj(void)
{
}


//Setting the Co-ordinates
void GameObj::setX(int x)
{
	m_xpos = x;
}

void GameObj::setY(int y)
{
	m_ypos = y;
}

//Getting the Co-ordinates
int GameObj::getX(void)
{
	return m_xpos;
}

int GameObj::getY(void)
{
	return m_ypos;
}

void GameObj::draw(void)
{
	if (alive())
	{
		m_CreatureBitmaps[m_current_frame]->draw(m_xpos, m_ypos);
	}

}

void GameObj::update()
{

	//nextFrame();


}

void GameObj::addFrame(string filename)
{
	
	Bitmap* newBitmap = new Bitmap(m_renderer, filename, m_xpos, m_ypos, true);
	m_CreatureBitmaps.push_back(newBitmap);

}

void GameObj::nextFrame()
{

	m_current_frame++;

	if (m_current_frame >= m_CreatureBitmaps.size())
	{

		m_current_frame = 0;
		// reset to the first frame

	}


}

bool GameObj::alive()
{

	return m_alive;

}

void GameObj::setAlive(bool state)
{

	m_alive = state; 

}

void GameObj::setDirection(Direction state)
{

	m_direction = state; 


}

int GameObj::BitmapWidth()
{

	return m_CreatureBitmaps[m_current_frame]->getWidth();

}

int GameObj::BitmapHeight()
{

	return m_CreatureBitmaps[m_current_frame]->getHeight();


}