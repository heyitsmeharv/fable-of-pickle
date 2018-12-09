//Our stuff
#include "../Headers/Game.h" 
#include "../Headers/Bitmap.h"
#include "../Headers/Input.h"
#include "../Headers/Hero.h"
#include "../Headers/Arena.h"
#include "../Headers/SmartMonster.h"
#include "../Headers/Bomb.h"
#include "../Headers/Projectile.h"
#include "../Headers/Person.h"
#include "../Headers/Skeleton.h"
#include "../Headers/Bat.h"
#include "../Headers/HUD.h"
#include "../Headers/Boss.h"
#include "../Headers/Gold.h"


//windows stuff
#include <stdio.h>
#include <time.h>

//SDL stuff
#include "SDL.h"


const int FRAMES_PER_SECOND = 60;
const int MILLISECS_PER_FRAME = 1000 / FRAMES_PER_SECOND; //rounded down

Game::Game()
{	 
	m_window = nullptr;
	m_renderer = nullptr;

	//start up
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
	TTF_Init();

	//create the window
	m_window = SDL_CreateWindow(
		"The Fable of Pickle",	//title
		250,					//initial x pos
		50,						//initial y pos
		1024,					//width, in pixles 512
		1024,					//height, in pixles 512
		0						//window behaviour flags (ignore for now)
		); 

	if (!m_window)
	{
		printf("WINDOW initialisation failed: %s\n", SDL_GetError()); 
		printf("Press any key to continue\n"); 
		getchar();
		return;
	}

	//now create the renderer
	m_renderer = SDL_CreateRenderer(
		m_window,			//link the renderer to our newly created win
		-1,					//index rendering driver (ignore for now)
		0					//rendere behaviour flags (ignore for now)
		); 

	if (!m_renderer)
	{
		printf("RENDERER initialisation failed: %s\n", SDL_GetError());
		printf("Press any key to continue\n");
		getchar(); 

		return;
	}

	//seeding time
	srand(unsigned int(time(NULL)));
	
	// setting update loops to false
	m_updateLogic = false;
    m_renderFrame = false;

	// initializing
	m_input = new Input();
	m_arena = new Arena(m_renderer, 64, 64, 0, 0);
	m_HUD = new HUD(m_renderer); 

	// creating positions
	pos heroSpawn = {512, 512}; 
	pos PosSkele = {850, 620};
	pos PosBat = {790, 620};

	// creating a hero and calling the addframe();
	m_hero = new Hero(m_renderer, "Hero", heroSpawn, 3, 3, "assets/Hero.bmp", true, m_arena);
	m_hero->addFrame("assets/Hero2.bmp");
	m_hero->addFrame("assets/Hero3.bmp");
	m_hero->addFrame("assets/Hero4.bmp");
	m_hero->addFrame("assets/Hero5.bmp");

	// more initializing
	m_skeleton = new Skeleton(m_renderer, "skeleton", PosSkele, 1, "assets/Skeleton.bmp", true, m_arena, m_hero);
    m_bat = new Bat(m_renderer, "bat", PosBat, 1, "assets/bat.bmp", true, m_arena, m_hero);
	m_Bomb = new Bitmap(m_renderer, "assets/Bomb.bmp", 500, 620, true);
	m_key = new Bitmap(m_renderer, "assets/Key.bmp", 100, 100, true);
	m_lives = new Bitmap(m_renderer, "assets/Lives.bmp", 100, 100, true);

	// setting the custom font
	 m_pFont = TTF_OpenFont("assets/BACKTO1982.ttf", 80); 
	 m_pFont2 = TTF_OpenFont("assets/BACKTO1982.ttf", 20); 

	 SDL_TimerID m_gameTimerID = SDL_AddTimer(MILLISECS_PER_FRAME, &Game::TimerCallBack, this);

}

Game::~Game()
{

	if (m_hero)
	{
		delete m_hero;
		m_hero = nullptr;
	}

	if (m_input)
	{
		delete m_input;		
		m_input = nullptr;
	}

	if (m_renderer)
	{
		SDL_DestroyRenderer(m_renderer);
	}

	if (m_window)
	{
		SDL_DestroyWindow(m_window);
	}

}

void Game::UpdateText(string msg, int x, int y, TTF_Font* font, SDL_Color colour)
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

	

 void Game::Update(void)
 {  

	 CheckEvents(); // call checkevents before every update loop

	 // LOGIC!!

	 if (m_updateLogic)
	 {

		 m_updateLogic = false; 

		 // checking to see any keys that are pressed

		 if (m_input->KeyIsPressed(KEY_W))
		 {

			 // passing in an integer represents speed. 
			 m_hero->up(4);
			
		 }

		 if (m_input->KeyIsPressed(KEY_A))
		 {
			  // passing in an integer represents speed. 
			 m_hero->left(4);

		 }

		 if (m_input->KeyIsPressed(KEY_S))
		 {

			  // passing in an integer represents speed. 
			 m_hero->down(4);
			 

		 }

		 if (m_input->KeyIsPressed(KEY_D))
		 {

			 // passing in an integer represents speed. 
		     m_hero->right(4);
			 
		 }

		 if (m_input->KeyIsPressed(KEY_R))
		 {
			 
			// calling the function that will lay the bomb when the user presses R
			m_hero->LayBomb();
			//m_hero->hasKey(true); //dubug use

		 }

		 if (m_input->KeyIsPressed(KEY_SPACE))
		 {
			// calling the function that will fire a projectile when the user presses SPACE
			m_hero->Fire();
	
		 }

		 m_hero->update(skeleton_vector, bat_vector, boss_vector); // calling hero's update
		 
	
		// Looping through enemy's vector
		 for (int loop = 0; loop < boss_vector.size(); loop++)
		 {
			boss_vector[loop]->update(); // automatically call it's update

			if (boss_vector[loop]->alive()) // do things only when it's alive
			{
				boss_vector[loop]->chase(m_hero); // passing through the hero

				if (boss_vector[loop]->isHero(m_hero))
				{
					if (m_hero->getLives() == 0)
						{ 
							m_running = false; // exits the game when it kills the hero
						}
				}
				
			}
		 }
		 


		 for (int loop = 0; loop < skeleton_vector.size(); loop++)
		 {
			 skeleton_vector[loop]->update();

			if (skeleton_vector[loop]->alive())
			{
				skeleton_vector[loop]->chase(m_hero);

				if (skeleton_vector[loop]->isHero(m_hero))
				{
					if (m_hero->getLives() == 0)
						{ 
							m_running = false;
						}
				}
				
			}
		 }
		 
		 for (int loop = 0; loop < bat_vector.size(); loop++)
		 {
			 bat_vector[loop]->update();

			 if (bat_vector[loop]->alive())
				{
					 bat_vector[loop]->chase(m_hero);

					 if (bat_vector[loop]->isHero(m_hero))
					 {
							if (m_hero->getLives() == 0)
							{
								m_running = false;
							}
					}
				}
		 }
		
		
		
		 if(m_hero->loadLevel() == true)
		{
			
			SpawnMonsters(); // calling spawnmonsters function that will read through what to render.

		}


	
	 }

	 // DRAWING!!

	 if (m_renderFrame)
	 {

		 m_renderFrame = false;

		SDL_RenderClear(m_renderer);

		m_arena->Render(); // calling the arena render()
		m_HUD->update(m_hero);  // update any changes to hud picked up bombs/gold score

		if (m_arena->currentLevel == 0) // anything I want to show only in the first level!
		{

		SDL_Color white = {255, 255, 255};
		SDL_Color gold = {255, 215, 0};
		SDL_Color red = {255, 0, 0}; 

		 UpdateText("The Fable", 80, 80, m_pFont, white);
		 UpdateText("Of Pickle...", 200, 180, m_pFont, white);
		
		 // Break from streaming
		 //UpdateText("BRB...", 500, 380, m_pFont, gold); 

		 UpdateText("Controls : ", 80, 360, m_pFont2, white); 
		 UpdateText("UP : 'W' ", 80, 420, m_pFont2, white);
		 UpdateText("DOWN : 'S' ", 80, 460, m_pFont2, white);
		 UpdateText("LEFT : 'A' ", 80, 500, m_pFont2, white);
		 UpdateText("RIGHT : 'D' ", 80, 540, m_pFont2, white);
		 UpdateText("BOMB : 'R' ", 80, 580, m_pFont2, white);
		 UpdateText("FIRE : 'SPACE' ", 80, 620, m_pFont2, white);
		
		 m_skeleton->draw();
		 m_bat->draw(); 
		 m_Bomb->draw(720, 830);
		 m_key->draw(690, 850); 
		 m_lives->draw(650, 850);

		}
		
		if (m_hero->alive() == true)
		{

			m_hero->draw(); 

		}

		// drawing the enemies to the screen by looping through each vector

		for (int y = 0; y < skeleton_vector.size(); y++)
		{
			
			skeleton_vector[y]->draw();

		}

		for (int x = 0; x < bat_vector.size(); x++)
		{
			
			bat_vector[x]->draw();

		}

		for (int z = 0; z < boss_vector.size(); z++)
		{
			
			boss_vector[z]->draw();

		}


		SDL_RenderPresent(m_renderer); 

	 }

 }

 void Game::CheckEvents()
 {

	 const int m_maxConsecutiveLogicUpdates = 10; 

	 while (SDL_PollEvent(&m_event))
	 {

		 switch (m_event.type)
		 {
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				m_input->Update(m_event); 

			 case SDL_USEREVENT:
			 {
				 if (m_event.user.code == GE_TIMER)
						 {
							//we have a ping!

								   if (++m_consecutiveLogicUpdates < m_maxConsecutiveLogicUpdates)
								   {
									   m_updateLogic = true;
								   }

								   if (SDL_PeepEvents(NULL, 1, SDL_PEEKEVENT, SDL_USEREVENT, SDL_USEREVENT) == 0)
								   {
									   m_renderFrame = true;
									   m_consecutiveLogicUpdates = 0;
								   }

						 }
		 }  break;
		 }
	 }

 		
 }

 bool Game::GameRunning()
 {


	 if (m_input->KeyIsPressed(KEY_ESCAPE) || !m_running)  // Quit game is press ESCAPE
	 {

		 return false;
	 }
	 
	 else 
	 {
		 return true;
	 }


 }

 Uint32 Game::TimerCallBack(Uint32 interval, void* gameObjectIn)
 {
	 if (gameObjectIn)
	 {
		 Game* gameObject = static_cast<Game*>(gameObjectIn);
		 gameObject->CreateTimerEvent(); 

	 }

	 return interval;


 }

 void Game::CreateTimerEvent()
 {

	 SDL_Event event;
	 SDL_UserEvent userEvent;

	 //set up userEvent with default data
	 userEvent.type = SDL_USEREVENT;
	 userEvent.data1 = NULL;
	 userEvent.data2 = NULL;

	 //this is the timer event
	 userEvent.code = GE_TIMER;

	 //create the event
	 event.type = SDL_USEREVENT;
	 event.user = userEvent;

	 //push the event
	 SDL_PushEvent(&event);


 }

 void Game::SpawnMonsters()
 {

	 // Each new level want to clear what enemies were previously there
	 skeleton_vector.clear();
	 bat_vector.clear();
	 boss_vector.clear();


   	 // Creating enemies and storing them in their own vectors
	for (int loop = 0; loop < m_arena->getSkeletonCounter(); loop++)
	{
		
		Skeleton* skeleton = new Skeleton(m_renderer, "Skeleton", m_arena->getSkeleton(loop), 1, "assets/Skeleton.bmp", true, m_arena, m_hero); 
		skeleton_vector.push_back(skeleton);

	}

	for (int loop = 0; loop < m_arena->getBatCounter(); loop++)
	{
		
		Bat* bat = new Bat(m_renderer, "Bat", m_arena->getBat(loop), 1, "assets/Bat.bmp", true, m_arena, m_hero); 
		bat_vector.push_back(bat);

	}

	for (int loop = 0; loop < m_arena->getBossCounter(); loop++)
	{
		
		Boss* boss = new Boss(m_renderer, "Boss", m_arena->getBoss(loop), 20, "assets/Boss.bmp", true, m_arena, m_hero); 
		boss_vector.push_back(boss);

 }

 }