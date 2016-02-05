#include "Keyboard.h"

namespace Application
{

	Keyboard::Keyboard() : _oldState(NULL), _currentState(NULL)
	{
		SDL_GetKeyboardState(&numStates);
		_oldState = new unsigned char[numStates];
		_currentState = new unsigned char[numStates];
	}

	Keyboard::~Keyboard()
	{
		delete[] _oldState;
		delete[] _currentState;
	}
		
	void Keyboard::Refresh()
	{
		const unsigned char* _state = SDL_GetKeyboardState(&numStates);	//get new state
		std::copy(_currentState, _currentState+numStates, _oldState);	//copy current state to old state
		std::copy(_state, _state+numStates, _currentState);				//copy new state to current state
	}

	const unsigned char* Keyboard::GetState()
	{
		return _currentState;
	}

	bool Keyboard::KeyPressed(SDL_Scancode scancode)
	{
		if( _currentState[scancode] == 1 && _oldState[scancode] == 0 )
		{
			return true;
		}
		return false;
	}

}
