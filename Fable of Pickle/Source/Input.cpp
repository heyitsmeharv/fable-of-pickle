#include "../Headers/Input.h" 
#include "../Headers/Game.h"

Input::Input()
{
	
	for(int i=0; i<SIZE_OF_KEYS_PRESSED_ENUM;i++)
	{
		m_keysPressed[i] = false;
	}

};


Input::~Input()
{


};

void Input::Update(SDL_Event& Event)
{
	m_event = Event;

	//loop through all the events in the event list
	//while (SDL_PollEvent(&m_event) != NULL)
	{
		//got an event. let's process it. 

		//check for keydown
		if (m_event.type == SDL_KEYDOWN)
		{
			//cache the code of key we pressed for easier debugging
			SDL_Keycode KeyPressed = m_event.key.keysym.sym;

			//update keys
			switch(KeyPressed)
			{
				case SDLK_ESCAPE:
					m_keysPressed[KEY_ESCAPE] = true;
					break;
				
				case SDLK_SPACE:
					m_keysPressed[KEY_SPACE] = true;
					break;

				case SDLK_r:
					m_keysPressed[KEY_R] = true;
					break;

				case SDLK_g:
					m_keysPressed[KEY_G] = true;
					break;

				case SDLK_b:
					m_keysPressed[KEY_B] = true;
					break;
				
				case SDLK_w:
					m_keysPressed[KEY_W] = true;
					break;

				case SDLK_a:
					m_keysPressed[KEY_A] = true;
					break;

				case SDLK_s:
					m_keysPressed[KEY_S] = true;
					break;

				case SDLK_d:
					m_keysPressed[KEY_D] = true;
					break;
			}
		}
		//check for key up
		else if (m_event.type  == SDL_KEYUP)
		{
			SDL_Keycode KeyPressed = m_event.key.keysym.sym;

			//update keys
			switch(KeyPressed)
			{
				case SDLK_SPACE:
					m_keysPressed[KEY_SPACE] = false;
					break;

				case SDLK_r:
					m_keysPressed[KEY_R] = false;
					break;

				case SDLK_g:
					m_keysPressed[KEY_G] = false;
					break;

				case SDLK_b:
					m_keysPressed[KEY_B] = false;
					break;
					
				case SDLK_w:
					m_keysPressed[KEY_W] = false;
					break;

				case SDLK_a:
					m_keysPressed[KEY_A] = false;
					break;

				case SDLK_s:
					m_keysPressed[KEY_S] = false;
					break;

				case SDLK_d:
					m_keysPressed[KEY_D] = false;
					break;
			}
		}
	}

}

bool Input::KeyIsPressed(KEYS_PRESSED_LIST key)
{

	return m_keysPressed[key];

}