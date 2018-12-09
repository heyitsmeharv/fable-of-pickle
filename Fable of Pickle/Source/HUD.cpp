#include "../Headers/HUD.h"
#include <iostream>

using namespace std;

HUD::HUD(SDL_Renderer* renderer)
{
	
	// initializing what we want to see on our hud
	Lives = new Bitmap(renderer, "assets/Lives.bmp", 0, 0, true);
	BombCounter = new Bitmap(renderer, "assets/BombHUD.bmp", 0, 0, true); 
	Key = new Bitmap(renderer, "assets/Key.bmp", 0, 0, true); 
	m_renderer = renderer; 

}


HUD::~HUD(void)
{




}

void HUD::update(Hero* hero)
{

	// TODO: Fix the lives and bomb counter so they do not go over 3

	int LivesWidth = 0; 

	// check to see how many lives, then draws them
	for (int x = 0; x < hero->getLives(); x++) 
	{
			Lives->draw(LivesWidth + 150, 10); // draw each life their width apart so they are together in a row
			LivesWidth = LivesWidth + Lives->getWidth(); 
	}
	
	// same logic for bombs 
	int BombWidth = 0; 

	for (int y = 0; y < hero->getBombs(); y++)
	{

			BombCounter->draw(BombWidth + 415, 5);
			BombWidth = BombWidth + BombCounter->getWidth();
		
	}

	if (hero->getKey() == true)
	{

		Key->draw(900, 10); // make the key appear here if hero has it!

	}

	m_pHUDFont = TTF_OpenFont("assets/BACKTO1982.ttf", 30); // setting the font

	SDL_Color black = {0, 0, 0};

	UpdateText("Lives: ", 10, 10, m_pHUDFont, black);
	UpdateText("Bombs: ", 260, 10, m_pHUDFont, black); 
	UpdateText("Score: ", 530, 10, m_pHUDFont, black); 
	UpdateText(to_string(hero->getScore()), 690, 10, m_pHUDFont, black); 
	UpdateText("Key: ", 800, 10, m_pHUDFont, black); 
}

void HUD::UpdateText(string msg, int x, int y, TTF_Font* font, SDL_Color colour)
 {
	 SDL_Surface* surface = nullptr;
	 SDL_Texture* texture = nullptr;

	 int texW = 0;
	 int texH = 0;

	 //SDL_Color colour = {0,0,0};

	 //char msg[100];
	 //sprintf_s(msg, "Checks: %d". m_checkTally); 

	 surface = TTF_RenderText_Solid(font, msg.c_str(), colour); 
	 if (!surface)
	 {
		 //surface not loaded? Output the error
		 printf("SURFACE for font not loaded! \n");
		 printf("%s\n", SDL_GetError());
	 }
	 else
	 {
		texture = SDL_CreateTextureFromSurface(m_renderer, surface); 
		if (!texture)
		{
			//surface not loaded? Output the error
			printf("SURFACE for texture not loaded! \n"); 
			printf("%s\n", SDL_GetError());
		}
		else
		{
		SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
		SDL_Rect textRect = { x, y, texW, texH };

	SDL_RenderCopy(m_renderer, texture, NULL, &textRect); 
	 }

	 }
	if (texture)
		SDL_DestroyTexture(texture);

	if (surface)
		SDL_FreeSurface(surface);

 }