#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include <SDL.h>

//disable "unsafe function woaaah crap" warning.
#pragma warning(push)
#pragma warning(disable:4996)
#include <algorithm>
#pragma warning(pop)


namespace Application
{
	class Keyboard
	{
	protected:
		unsigned char* _oldState;
		unsigned char* _currentState;
		int numStates;

	public:
		Keyboard();

		~Keyboard();
		
		void Refresh();

		const unsigned char* GetState();

		bool KeyPressed(SDL_Scancode scancode);

	};
}


#endif