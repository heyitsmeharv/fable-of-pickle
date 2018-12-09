#pragma once

#include "Arena.h"
#include "Bitmap.h"
#include "SDL.h"
#include <string>
#include <vector>


enum Direction
{

	UP,
	DOWN,
	LEFT,
	RIGHT

};


class GameObj
{

public:
	GameObj(SDL_Renderer* renderer, pos position, string filename, bool useTransparency, Arena* detection);
	~GameObj(void);

	SDL_Renderer* m_renderer; 

	int   getX(void);
	int	  getY(void);
	void  setX(int x);
	void  setY(int y);
	void  addFrame(string filename);
	void  nextFrame(void);
	virtual void  update(void);
	virtual void  draw(void);
	void setDirection(Direction state);  
	bool alive(); 
	void setAlive(bool state);
	int BitmapWidth();
	int BitmapHeight();


private:




protected:

	int m_xpos;
	int m_ypos;
	string m_name;
	int m_current_frame; 
	Bitmap* creatureTexture;
	vector <Bitmap*> m_CreatureBitmaps;
	Arena*  creatureCollision;
	bool m_alive;
	Arena* arena;
	int m_speed;
	Direction m_direction; 

	

};

