#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <SDL.h>
#include "Keyboard.h"
#include "Exception.h"

namespace Application
{
	using namespace Exception;

	class Window
	{
	private:
		SDL_Window* _window;
		SDL_Renderer* _renderer;
		Keyboard* _keyboard;
		void Init(const char* name, int width, int height);

		bool quit;

	public:
		Window(const char* name, int width, int height);
		~Window();

		void Exit() const;

		inline SDL_Window* const  GetWindow() const
		{
			return _window;
		}

		inline SDL_Renderer* const GetRenderer() const
		{
			return _renderer;
		}

		inline Keyboard* const GetKeyboard() const
		{
			return _keyboard;
		}

		void Run();

		virtual void Initialize() = 0;
		virtual void Tick() = 0;
	};
}

#endif