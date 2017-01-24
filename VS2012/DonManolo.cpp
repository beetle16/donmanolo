#include "DonManolo.h"
#include "LevelLoader.h"
#include "Screen.h"
#include "Exception.h"
#include "CMWC.h"
#include "Enums.h"
#include "Level.h"
#include "BaseBehavior.h"
#include "PlayerBaseBehavior.h"
#include <SDL_ttf.h>

namespace Game
{
	//LevelLoader::Create("res/lvl/lev17.txt")
	DonManolo::DonManolo() : Application::Window("DonManolo", 1024, 768)
	{
		CMWC_init();
		
		
		
	}

	void DonManolo::Initialize()
	{
		if (TTF_Init() != 0) {
			// error
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "TTF", TTF_GetError(), this->GetWindow());
			
			throw "SDL_TTF could not be initialized!";
		}

		//TODO hardcoded number of textures...
		for(int i=0;i<35;i++)
		{
			_texture_manager.AddResource(*(new TextureResourceItem(textureList[i], GetRenderer())));		
		}

		_font_manager.AddFont("res/broadway.ttf", 27);


		_numPlayers = 0;
		_currentScreen = new ScreenMenu(this);
		_currentLevelId = 0;
	

	}

	DonManolo::~DonManolo()
	{

		delete _currentScreen;

		TTF_CloseFont(_font_manager.GetFont(FONT_BROAD_27));
		

		TTF_Quit();
	}


	const ResourceManager<SDL_Texture>& DonManolo::GetTextureManager() const
	{
		return _texture_manager;
	}

	const FontManager& DonManolo::GetFontManager() const
	{
		return _font_manager;
	}


	Level& DonManolo::GetLevel() const
	{
		// TODO optimization needed?
		ScreenLevelBase* level = dynamic_cast<ScreenLevelBase*>(_currentScreen);
		if( level != NULL )
		{
			

			return level->GetLevel();
		}
		else
		{
			throw new Exception::ApplicationException("Game is not in Level state.");
		}
	}

	//WARNING: See EnterNextLevel(), which is called here.
	void DonManolo::StartNewGame(int players, bool shuffleMode)
	{
		// TODO parameter handling

		// TODO  --  get ready screen
		//       --  gaming screen

		_numPlayers = players;
		_currentLevelId = 0;
		EnterNextLevel();
	}

	//WARNING: This function deletes the current screen. Do not use any members after that; don't do anything after calling that function.
	void DonManolo::EnterNextLevel()
	{
		//TODO level (name) generator...
		
		_currentLevelId +=1;


		char buf[256];
		sprintf(buf, "res/lvl/lev%d.txt", ((_currentLevelId-1) % 62)+1);
		
		if( _currentScreen != NULL )
		{
			delete _currentScreen;
		}
		ScreenLevelBase* screenLevelBase = new ScreenLevelBase(this, LevelLoader::Create(buf, _currentLevelId));

		_currentScreen = screenLevelBase;
	}

	void DonManolo::Tick()
	{
		_currentScreen->Tick();
		_currentScreen->Render();
	}
}

