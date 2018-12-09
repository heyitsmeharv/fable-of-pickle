#pragma once; 

#include <string>
#include "SDL.h"

struct SDL_Surface;
struct SDL_Texture;
struct SDL_Renderer;


class Bitmap
{

protected:

	SDL_Surface*	m_pbitmapSurface;
	SDL_Texture*	m_pbitmapTexture;
	SDL_Renderer*	m_pRenderer;

	int				m_x, m_y;
	int				m_bitmapActualWidth;
	int				m_bitmapActualHeight;

	int				m_bitmapScaledWidth;
	int				m_bitmapScaledHeight;

public:

	Bitmap(SDL_Renderer* renderer, std::string fileName, int xpos, int ypos, bool useTransparency = false);
	~Bitmap();

	void draw(int x, int y); 
	int getBitX();
	int getBitY(); 
	int getWidth();
	int getHeight();
	
	int setDimension(int width, int height); 

};