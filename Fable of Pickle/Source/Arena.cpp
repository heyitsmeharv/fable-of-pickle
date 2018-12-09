#include "../Headers/Arena.h"
#include "SDL.h"
#include <iostream>

// used in text documents
#include <fstream> 
#include <cstdlib>


Arena::Arena(SDL_Renderer* renderer, int width, int height, int posX, int posY)
{
	currentLevel = 0; // assigning current level to 0
	m_arenaRenderer = renderer;
	m_arenablockWidth = width;
	m_arenablockHeight = height;  

	// Loading in the text files
	Levels.push_back("assets/levels/level.txt"); 
	Levels.push_back("assets/levels/level2.txt");
	Levels.push_back("assets/levels/level3.txt");
	Levels.push_back("assets/levels/level4.txt");
	Levels.push_back("assets/levels/level5.txt");
	Levels.push_back("assets/levels/level6.txt");
	Levels.push_back("assets/levels/level7.txt");
	Levels.push_back("assets/levels/level8.txt");
	Levels.push_back("assets/levels/BossLead.txt"); 
	Levels.push_back("assets/levels/Boss.txt");
	LoadLevel(currentLevel); // Load in the first level of the array

	m_arenaSurface = SDL_CreateRGBSurface(0, m_arenablockWidth, m_arenablockHeight, 32, 0, 0, 0, 0); 
	Uint32 blockColour = SDL_MapRGB(m_arenaSurface->format, 89, 36, 37);
	SDL_FillRect(m_arenaSurface, NULL, blockColour);	
	
	m_arenaTexture = SDL_CreateTextureFromSurface(m_arenaRenderer, m_arenaSurface);
	SDL_FreeSurface(m_arenaSurface);
	

	// Creating Bitmaps that will be assigned later
	block = new Bitmap(renderer, "assets/Block.bmp", 0, 0, true);
	floor = new Bitmap(renderer, "assets/Floor.bmp", 0, 0, true); 
	door = new Bitmap(renderer, "assets/Door.bmp", 0, 0, true);
	lockedDoor = new Bitmap(renderer, "assets/LockedDoor.bmp", 0, 0, true); 
	HUD = new Bitmap(renderer, "assets/HUD.bmp", 0, 0, true); 
	bossdoor = new Bitmap(renderer, "assets/BossDoor.bmp", 0, 0, true); 

}

// A* Calc
aStarGridSquare* Arena::getSquareFromArenaBlockIndices(int x, int y)
{

	if (x >= 0 && x < getWidth() && y >= 0 && y < getHeight())
	{
		int index = y * getWidth() + x;
		return aStarSquares[index];
	}

	return nullptr; 


}

Arena::~Arena()
{

	my_gridLayout.clear(); 

	if (m_arenaRenderer)
		SDL_DestroyRenderer(m_arenaRenderer);

}


void Arena::Render()
{
	// Draw a basic floor for the entire game
	floor->draw(0,0); 

	xPos = 0;
	yPos = 0; 

	// Looping through the arena X
	for (int x = 0; x < getHeight(); x++)
	{
		// Looping throug the arena Y
		for (int y = 0; y < getWidth(); y++)
		{

			// Assigning Bitmaps to characters that the text doc can read in

			// Searching for the character 'W'
			if (my_gridLayout[x][y] == 'W')
			{
				// If found, draw block
				draw(block);

			}
			
			// Searching for the character 'D'
			if (my_gridLayout[x][y] == 'D')
			{
				// If found, draw door
				draw(door); 

			}
			
			// Searching for the character 'd'
			if (my_gridLayout[x][y] == 'd')
			{
				// If found, draw bossdoor
				draw(bossdoor); 

			}
			
			// Searching for the character 'L'
			if (my_gridLayout[x][y] == 'L')
			{
				// If found, draw lockedDoor
				draw(lockedDoor); 

			}
			
			// Searching for the character 'H'
			if (my_gridLayout[x][y] == 'H')
			{
				// If found, draw HUD
				draw(HUD); 

			}


			xPos += m_arenablockWidth;
		}

		yPos += m_arenablockHeight;

		xPos = 0; 

	}

}

int Arena::getHeight()
{

	return my_gridLayout.size(); // Returns the size of the arena


}

int Arena::getWidth()
{

	return my_gridLayout[0].length(); // Returns the length of the arena

}

bool Arena::isWall(int x, int y)
{

	// Defining the boundaries

	// Loop through the arena
	int xCheck = x / m_arenablockWidth; 
	int yCheck = y / m_arenablockHeight;
	
	if (my_gridLayout[yCheck][xCheck] == 'W' || my_gridLayout[yCheck][xCheck] == 'L' || my_gridLayout[yCheck][xCheck] == 'H')
	{

		// If any of the characters are found, it classes as a wall/impassible object
		return true;

	}

	else
	{
		return false;
	
	}
	

}

bool Arena::isDoor(int x, int y)
{
	
	// Defining the doors

	// Loop through the arena
	int xCheck = x / m_arenablockWidth;
	int yCheck = y / m_arenablockHeight;
	
	if (my_gridLayout[yCheck][xCheck] == 'D' || my_gridLayout[yCheck][xCheck] == 'd') // Door and Boss Door
	{

		//
		return true;

	}

	else
	{
		return false;
	
	}



}

void Arena::draw(Bitmap* bitmap)
{
	// Draw function that passes through an xpos and ypos
	bitmap->draw(xPos,yPos);

}

int Arena::getLevel()
{
	
	// Returns the current level through an integer
	return currentLevel;


}

int Arena::LevelSize()
{
	// Returns the size of the level
	return Levels.size();

}


void Arena::LoadLevel(int level)
{
	
	// Clears previous level
	my_gridLayout.clear();

	// Assigning the current level to the passed through variable
	currentLevel = level;

	ifstream levelFile;
	levelFile.open(Levels[level]); // Opening the text doc. 

	// Fail safe
	if(levelFile.fail())
	{
		printf("Unable to open file\n");
		exit(1);
	}

	// storing the line in the file
	string item;
	int count = 0; // counts number of lines
	while(!levelFile.eof())
	{
		levelFile >> item; // get a line in the file
		my_gridLayout.push_back(item); // stores in the gridlayout
		count++; // Increment count
	}
	
	findEnemies(); // When loading a enemy find enemys
	BuildAI(); // When loading a new level re-build AI
	
}


// A star!! Dans Tutorials
bool Arena::aStar(int sx, int sy, int tx, int ty, int* nx, int* ny)
{

	struct adjacentOffsets{ int x;  int y; };
	int g = 1;

	aStarGridSquare* currentGridSquare, *startGridSquare;
	aStarGridSquare* targetGridSquare, *adjacentGridSquare;

	aStarOpenList.clear();
	aStarClosedList.clear(); 

	for (int i = 0; i < aStarSquares.size(); i++)
	{
		aStarSquares.at(i)->clear();
	}

	int targetblockx = tx / m_arenablockWidth;
	int targetblocky = ty / m_arenablockHeight;
	targetGridSquare = getSquareFromArenaBlockIndices(targetblockx, targetblocky);

	int startblockx = sx / m_arenablockWidth;
	int startblocky = sy / m_arenablockHeight;
	startGridSquare = getSquareFromArenaBlockIndices(startblockx, startblocky);

	if (startGridSquare == targetGridSquare) // in same grid
	{
		*nx = tx;
		*ny = ty; // return target xy 
		return true;
	}

	startGridSquare->CostFromStart = 0; 
	currentGridSquare = startGridSquare;
	aStarClosedList.push_back(currentGridSquare);

	do 
	{
		//K.I.S.S. - only check N/S/E/W squares for now.
		adjacentOffsets offsets[4] = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } };
		for (int i = 0; i < 4; i++)
		{
			adjacentGridSquare = getSquareFromArenaBlockIndices(
				currentGridSquare->blockx + offsets[i].x,
				currentGridSquare->blocky + offsets[i].y);

			//make sure square is not in closed list
			if (adjacentGridSquare != NULL &&
				std::find(aStarClosedList.begin(),
				aStarClosedList.end(),
				adjacentGridSquare) == aStarClosedList.end())
			{
				//not in the list, so not a closed square
				if (!adjacentGridSquare->passable)
				{
					aStarClosedList.push_back(adjacentGridSquare);
				}
				else
				{
					//Calc G-Score
					int CostFromStart = currentGridSquare->CostFromStart + g;
					bool updateSquare = false;

					if (std::find(aStarOpenList.begin(), aStarOpenList.end(),
						adjacentGridSquare) != aStarOpenList.end())
					{
						//in list
						if (CostFromStart < adjacentGridSquare->CostFromStart)
							updateSquare = true; 
					}
					else
					{
						//not in list. Flag for update and add to open list.
						updateSquare = true;
						aStarOpenList.push_back(adjacentGridSquare);
					}

					if (updateSquare == true)
					{
						int CostToEndEstimate = (abs(adjacentGridSquare->blockx - targetblockx) + abs(adjacentGridSquare->blocky - targetblocky));
						adjacentGridSquare->CostFromStart = CostFromStart;
						adjacentGridSquare->CostToEndEstimate = CostToEndEstimate; 
						adjacentGridSquare->TotalCostEstimate = CostFromStart + CostToEndEstimate;
						adjacentGridSquare->parent = currentGridSquare;
					}
				}

			}
		}

		int lowestFscore = -1;
		int foundSquareIndex = -1;

		for (int i = 0; i < aStarOpenList.size(); i++)
		{
			aStarGridSquare* openSquare = aStarOpenList[i];
			if (lowestFscore < 0 || lowestFscore > openSquare->TotalCostEstimate)
			{
				currentGridSquare = openSquare;
				lowestFscore = openSquare->TotalCostEstimate;
				foundSquareIndex = i;
			}
		}

		if (foundSquareIndex >= 0)
		{
			aStarOpenList.erase(aStarOpenList.begin() + foundSquareIndex);
			aStarClosedList.push_back(currentGridSquare);
		}

	} while ((currentGridSquare != targetGridSquare) && (aStarOpenList.size() > 0));

	if (currentGridSquare != targetGridSquare)
	{
		//path not found, return false
		*nx = -1;
		*ny = -1; 
		return false;
	}

	//got here? There's a path from start to finish, so find it...
	aStarGridSquare* squareToMoveTo = targetGridSquare;
	while (squareToMoveTo->parent != startGridSquare)
		squareToMoveTo = squareToMoveTo->parent;

	//and return the coords of the square to move to.
	*nx = squareToMoveTo->blockx * m_arenablockWidth;
	*ny = squareToMoveTo->blocky * m_arenablockHeight;

	return true;

};

void Arena::BuildAI(void)
{
	aStarSquares.clear();

	aStarGridSquare* pathSquare;
	for(int loopY = 0; loopY < getHeight(); loopY++)
	{
		for(int loopX = 0; loopX < getWidth(); loopX++)
		{
			bool passable = false;
			// All the things we want the hero to be able to pass through
			if((my_gridLayout[loopY][loopX] == '.') || (my_gridLayout[loopY][loopX] == 'S') ||
				(my_gridLayout[loopY][loopX] == 'B') || (my_gridLayout[loopY][loopX] == 'b')) 
				passable = true;

			pathSquare = new aStarGridSquare(loopX, loopY, passable);
			aStarSquares.push_back(pathSquare);
		}
	}
	
}

void Arena::findEnemies(void)
{
	skeletonCounter = 0; // Set to 0
	sMonsterPosition.clear(); // Clears Skeleton

	batCounter = 0;
	bMonsterPosition.clear(); // Clears Bat

	bossCounter = 0;
	BBossPosition.clear(); // Clears Boss

	for(int loop = 0; loop < getHeight(); loop++) // Areas of arena (height)
	{
		for(int loop2 = 0; loop2 < getWidth(); loop2++) // Width
		{
			if(my_gridLayout[loop][loop2] == 'S') // checking for skeletons
			{
				m_coords.x = loop2 * m_arenablockWidth; 
				m_coords.y = loop * m_arenablockHeight;
				skeletonCounter++;
				sMonsterPosition.push_back(m_coords);
				// Increase the Skeleton count if 'S' is found in the arena
			}

			if(my_gridLayout[loop][loop2] == 'B')
			{
				m_coords.x = loop2 * m_arenablockWidth;
				m_coords.y = loop * m_arenablockHeight;
				batCounter++;
				bMonsterPosition.push_back(m_coords);
				// Increase the Bat count if 'B' is found in the arena
			}
			if(my_gridLayout[loop][loop2] == 'b')
			{
				m_coords.x = loop2 * m_arenablockWidth;
				m_coords.y = loop * m_arenablockHeight;
				bossCounter++;
				BBossPosition.push_back(m_coords);
				// Increase the Boss count if 'b' is found in the arena
			}
		}
	}
}

// Getters and Setters!

pos Arena::getSkeleton(int position)
{

	return sMonsterPosition[position];

}

pos Arena::getBat(int position)
{

	return bMonsterPosition[position];

}

pos Arena::getBoss(int position)
{

	return BBossPosition[position];

}


int Arena::getSkeletonCounter()
{

	return skeletonCounter;

}

int Arena::getBatCounter()
{

	return batCounter;

}

int Arena::getBossCounter()
{

	return bossCounter;

}