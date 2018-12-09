#include <string>
#include "../Headers/Bitmap.h"

#include "SDL.h"
#include "SDL_render.h"

using namespace std; 

Bitmap::Bitmap(SDL_Renderer* renderer, string fileName, int xpos, int ypos, bool useTransparency)
{
	//store the renderer
	m_pRenderer = renderer;
	
	//create the bitmap surface
	m_pbitmapSurface = SDL_LoadBMP(fileName.c_str());
	if (!m_pbitmapSurface)
	{
		//bitmap not loaded? Output the error
		printf("SURFACE for bitmap '%s' not loaded! \n", fileName.c_str());
		printf("%s\n", SDL_GetError()); 
	}
	else
	{
		//if we are to use the transparency, going to assume 
		//the colour key is magenta (r=255, g=0, b=225)
		if(useTransparency)
		{
			Uint32 colourKey = SDL_MapRGB(m_pbitmapSurface->format, 255, 0, 255);
			SDL_SetColorKey(m_pbitmapSurface, SDL_TRUE, colourKey);
		}

		//create the texture
		m_pbitmapTexture = SDL_CreateTextureFromSurface(m_pRenderer, m_pbitmapSurface);
		if (!m_pbitmapTexture)
		{
			//texture not loaded? Output error
			printf("TEXTURE for bitmap '%s' not loaded! \n", fileName.c_str());
			printf("%s\n", SDL_GetError());
		}
	}

	
	m_x = xpos;
	m_y = ypos; 
 
	m_bitmapActualWidth = m_pbitmapSurface->w; // getting width
	m_bitmapActualHeight = m_pbitmapSurface->h; // getting height of bitmap

	
	//scale our bitmaps to 32pix by 32 pix
	//m_bitmapScaledWidth = 64;
	//m_bitmapScaledHeight = 64;
	

}

Bitmap::~Bitmap()
{
	if (m_pbitmapTexture)
		SDL_DestroyTexture(m_pbitmapTexture);

	if (m_pbitmapSurface)
		SDL_FreeSurface(m_pbitmapSurface); 

}

void Bitmap::draw(int x, int y)
{

	//render the bitmap at the x/y coords
	if (m_pbitmapTexture)
	{
		SDL_Rect destRect = { x, y, m_bitmapActualWidth, m_bitmapActualHeight };
		SDL_RenderCopy(m_pRenderer, m_pbitmapTexture, NULL, &destRect);
	}
}

int Bitmap::getBitX()
{
	
	return m_x;

}

int Bitmap::getBitY()
{

	return m_y; 

}

int Bitmap::getWidth()
{

	return m_bitmapActualWidth;

}

int Bitmap::getHeight()
{

	return m_bitmapActualHeight;


}
