#include "Window.h"

namespace Application
{
	void Window::Init(const char* name, int width, int height)
	{
		if( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0 )
		{
			// TODO: SDL_GetError()
			throw new ApplicationException("SDL Initialization failed.");
		}

		_keyboard = new Keyboard();

		// create window
		_window = SDL_CreateWindow(name,
						SDL_WINDOWPOS_CENTERED,
						SDL_WINDOWPOS_CENTERED,
						width, height,
						SDL_WINDOW_SHOWN);
		if( _window == NULL )
		{
			throw new ApplicationException("SDL_CreateWindow failed.");
		}
		_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
		
		if( _renderer == NULL )
		{
			//const char* msg = SDL_GetError();
	
			throw new ApplicationException("SDL_CreateRenderer failed.");
		}

	}

	Window::Window(const char* name, int width, int height)
	{
		Init(name, width, height);
	}

	Window::~Window()
	{
		delete _keyboard;
		SDL_DestroyRenderer(_renderer);
		SDL_DestroyWindow(_window);
		SDL_Quit();
	}

	void Window::Exit() const
	{
		(bool)quit = true;
	}



	void Window::Run()
	{
		SDL_Event event;
		bool minimized = false;

		quit = false;

		Initialize();

		while (!quit)
		{
			while(SDL_PollEvent(&event) )
			{
				switch(event.type)
				{
					case SDL_WINDOWEVENT:
						{
							switch (event.window.event)
							{
								case SDL_WINDOWEVENT_MINIMIZED:
									minimized = true;
									break;
								case SDL_WINDOWEVENT_RESTORED:
									minimized = false;
									break;
							}
						}
						break;
					case SDL_QUIT:
						quit = true;
						break;
					default:
						break;
				}
			}

			if( !minimized )
			{
				_keyboard->Refresh();
				Tick();
				SDL_RenderPresent(_renderer);
			} 
			else
			{
				SDL_Delay(30);
			}

		}
	}

}