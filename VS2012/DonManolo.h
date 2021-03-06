#ifndef __DONMANOLO_H__
#define __DONMANOLO_H__

#include "Window.h"
#include "ResourceManager.h"
#include "FontManager.h"
#include "Player.h"
#include <map>
#include "Enums.h"
#include <vector>

namespace Game
{
	class Level;
	class ScreenBase;

	class DonManolo : public Application::Window
	{
	private:
		ScreenBase* _currentScreen;

		int _currentLevelId;
		int _numPlayers;

		std::vector<Player*> _players;

	protected:
		ResourceManager<SDL_Texture> _texture_manager;
		FontManager _font_manager;
		virtual void Initialize();
	public:
		
		DonManolo();
		virtual ~DonManolo();
		
		const ResourceManager<SDL_Texture>& GetTextureManager() const;
		const FontManager& GetFontManager() const;
		Level& GetLevel() const;

		inline int GetNumPlayers() { return _numPlayers; }

		void StartNewGame(int players, bool shuffleMode);
		void EnterNextLevel();

		virtual void Tick();
	};
}



#endif