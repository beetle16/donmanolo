#include "FontManager.h"

namespace Game
{
	FontManager::FontManager() 
	{
		
	}
	FontManager::~FontManager() 
	{
	
	}

	void FontManager::AddFont(char* filename, int ptSize)
	{
		_fonts.push_back(TTF_OpenFont(filename, ptSize));
	}
	
	TTF_Font* FontManager::GetFont(int index)  const
	{
		return _fonts[index];
	}

}