#ifndef __DONMANOLO_H__
#define __DONMANOLO_H__

#include "Window.h"
#include "ResourceManager.h"
#include <map>
#include "Enums.h"

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

	

	protected:
		ResourceManager<SDL_Texture> _texture_manager;
		virtual void Initialize();
	public:
		
		DonManolo();
		virtual ~DonManolo();
		
		const ResourceManager<SDL_Texture>& GetTextureManager() const;
		Level& GetLevel() const;

		inline int GetNumPlayers() { return _numPlayers; }

		void StartNewGame(int players, bool shuffleMode);
		void EnterNextLevel();

		virtual void Tick();
	};
}



#endif