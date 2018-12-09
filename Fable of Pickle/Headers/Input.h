//SDL Stuff
#include "SDL.h"

//Global vars
enum KEYS_PRESSED_LIST
{
	KEY_ESCAPE, KEY_SPACE, KEY_R, KEY_G, KEY_B, KEY_W, KEY_A, KEY_S, KEY_D, SIZE_OF_KEYS_PRESSED_ENUM
};

class Input
{
public :
	void Update(SDL_Event& Event); 
	bool KeyIsPressed(KEYS_PRESSED_LIST key); 

	Input();
	~Input();

private:
	SDL_Event m_event; 
	bool m_keysPressed[SIZE_OF_KEYS_PRESSED_ENUM];
};