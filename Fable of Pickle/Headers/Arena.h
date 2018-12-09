/*
	//////////////////////////////////////////////
	//
	//  Computer Games Programming - AE2 
	//	Adam Harvey 
	//	Arena.h
	//	
	//	Notes:
	//
	
*/


#pragma once //--Compile Once!--//


//////////////////////////////////////////////////////
//                    INCLUDES					    
#include "SDL.h"
#include <vector>
#include <string> 
#include "Bitmap.h" 
#include "UTILS.h"


//////////////////////////////////////////////////////
//					NAMESPACES					    
using namespace std; 


//////////////////////////////////////////////////////
//				 A * PATH FINDING				    
struct aStarGridSquare
{
	float TotalCostEstimate, CostFromStart, CostToEndEstimate; // f = g + h
	int blockx, blocky;
	bool passable;

	aStarGridSquare* parent;

	aStarGridSquare(int x, int y, bool isPassable)
	{
		blockx = x; blocky = y;
		passable = isPassable;

		clear();
	}

	void clear()
	{
		parent = NULL;
		TotalCostEstimate = 0.0f; CostFromStart = 0.0f; CostToEndEstimate = 0.0f;
	}
};


class Arena
{
		//-----------------------PUBLIC-----------------------//
public:
	//----Methods----//
	Arena	(SDL_Renderer* renderer, int width, int height, int posX, int posY);
	~Arena	(void);

	aStarGridSquare*	getSquareFromArenaBlockIndices(int x, int y);

	pos		getSkeleton(int position);
	pos		getBat(int position);
	pos		getBoss(int position); 
	
	void	Render(void); 
	void	draw(Bitmap* bitmap);
	void	LoadLevel(int level);
	void	findEnemies(void); 
	void	BuildAI(void);

	bool	aStar(int sx, int sy, int tx, int ty, int* nx, int* ny);
	bool	isDoor(int x, int y);
	bool	isWall(int x, int y);
	bool	getBossKey(void);

	int		getSkeletonCounter(void);
	int		getBatCounter(void);
	int		getBossCounter(void); 
	int		getLevel(void); 
	int		LevelSize(void);

	//----Variables----//
	vector<aStarGridSquare*> aStarSquares;
	vector<aStarGridSquare*> aStarOpenList;
	vector<aStarGridSquare*> aStarClosedList;
	vector<aStarGridSquare*> aStarGridSquareList;
	vector<string> Levels;


	int		m_arenablockWidth;
	int		m_arenablockHeight;
	int		currentLevel;

		//-----------------------PRIVATE------------------------//	
private:
	//----Methods----//
	

	//----Variables----//
	SDL_Surface*		m_arenaSurface;
	SDL_Texture*		m_arenaTexture;
	SDL_Renderer*		m_arenaRenderer;
	
	pos		m_coords;

	Bitmap*		block;
	Bitmap*		floor; 
	Bitmap*		door;
	Bitmap*		lockedDoor;
	Bitmap*		HUD;
	Bitmap*		m_Boss;
	Bitmap*		bossdoor;

	vector<string>		my_gridLayout;
	vector<pos>			sMonsterPosition;
	vector<pos>			bMonsterPosition;
	vector<pos>			BBossPosition; 
	
	int		xPos;
	int		yPos;
	int		skeletonCounter;
	int		batCounter;
	int		bossCounter; 
	int		getHeight();
	int		getWidth();


		//-----------------------PROTECTED-----------------------//	
protected:
	//----Methods----//


	//----Variables----//
};
