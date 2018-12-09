#pragma once
#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_ttf.h"
#include <string>
#include <vector>

using namespace std; 

//forward declare any SDL stuff we need
struct SDL_Window;
struct SDL_Renderer;
class Bitmap;
class Input;
class Hero;
class Monster; 
class Arena;
class SmartMonster;
class Bomb;
class Projectile;
class Person;
class Bat;
class Skeleton;
class HUD;
class Boss; 
class Gold;

class Game
{

private:

	//SDL stuff
	SDL_Window*		m_window;
	SDL_Renderer*	m_renderer; 
	SDL_Event		m_event;

	bool m_running; 

	//bitmaps
	Hero*			m_hero;
	Skeleton*		m_skeleton;
	Bat*			m_bat; 
	Arena*			m_arena;
	Bitmap*			m_Bomb;
	Projectile*		m_Projectile;
	HUD*			m_HUD;
	Bitmap*			m_key;
	Bitmap*			m_lives;
	Gold*			m_gold; 


	TTF_Font*		m_pFont; 
	TTF_Font*		m_pFont2;


	// Enemies vectors!
	vector<Skeleton*> skeleton_vector;
	vector<Bat*> bat_vector;
	vector<Boss*> boss_vector; 

	//Input
	Input*			m_input;

public:

	Game();
	~Game();
	void Update(); 
	void CheckEvents();
	bool GameRunning(); 
	void SpawnMonsters(); 
	void UpdateText(string msg, int x, int y, TTF_Font* font, SDL_Color colour);

	int delay; 

	bool			m_updateLogic;
	bool			m_renderFrame;
	int				timer; 			
	int				m_consecutiveLogicUpdates;

	SDL_TimerID		m_gameTimerID;

	static Uint32 TimerCallBack(Uint32 interval, void* gameObjectIn);

	void			CreateTimerEvent(); 

	enum GameEvent {GE_TIMER, NUM_GAME_EVENTS};
	
};

