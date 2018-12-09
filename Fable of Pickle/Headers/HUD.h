#pragma once

#include "Hero.h"
#include "Bitmap.h"
#include "SDL_ttf.h"

class HUD 
{
public:
	HUD(SDL_Renderer* renderer);
	~HUD(void);

	void update(Hero* hero);
	void UpdateText(string msg, int x, int y, TTF_Font* font, SDL_Color colour);

	SDL_Renderer* m_renderer;

	TTF_Font*		m_pHUDFont; 


private:





protected:

	Bitmap* Lives;
	Bitmap* BombCounter;
	Bitmap* Score;
	Bitmap* Key;


};

