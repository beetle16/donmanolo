#ifndef __FONT_MANAGER__
#define __FONT_MANAGER__

#include <vector>
#include <SDL_TTF.h>

namespace Game
{
	class FontManager
	{
	protected:
		//TTF_Font* font = TTF_OpenFont("res/broadway.ttf", 27);
		std::vector<TTF_Font*> _fonts;
	public:
		FontManager();
		~FontManager();

		void AddFont(char* filename, int ptSize);
		TTF_Font* GetFont(int index) const;



	};

}

#endif