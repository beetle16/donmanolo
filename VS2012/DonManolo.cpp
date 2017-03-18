#include "DonManolo.h"
#include "LevelLoader.h"
#include "Screen.h"
#include "Exception.h"
#include "CMWC.h"
#include "Enums.h"
#include "Level.h"
#include "BaseBehavior.h"
#include "PlayerBaseBehavior.h"
#include "PlayerFactory.h"
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
		for (int i = 0; i < _players.size(); i++)
		{
			delete _players[i];
		}
		_players.clear();

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

		_numPlayers = players;

		// initialize players;
		// delete old players
		for (int i = 0; i < _players.size(); i++)
		{
			delete _players[i];
		}
		_players.clear();

		_players.push_back(PlayerFactory::Create(ENTITYID_PLAYER1));
		_players.push_back(PlayerFactory::Create(ENTITYID_PLAYER2));

		_players[0]->AddBehavior(new Engine::BaseBehavior(*_players[0]));
		_players[1]->AddBehavior(new Engine::BaseBehavior(*_players[1]));

		std::map<EInputAction, int> p1map;
		p1map[INPUTACTION_DOWN] = SDL_SCANCODE_DOWN;
		p1map[INPUTACTION_UP] = SDL_SCANCODE_UP;
		p1map[INPUTACTION_LEFT] = SDL_SCANCODE_LEFT;
		p1map[INPUTACTION_RIGHT] = SDL_SCANCODE_RIGHT;
		p1map[INPUTACTION_FIRE] = SDL_SCANCODE_RCTRL;

		std::map<EInputAction, int> p2map;
		p2map[INPUTACTION_DOWN] = SDL_SCANCODE_S;
		p2map[INPUTACTION_UP] = SDL_SCANCODE_W;
		p2map[INPUTACTION_LEFT] = SDL_SCANCODE_A;
		p2map[INPUTACTION_RIGHT] = SDL_SCANCODE_D;
		p2map[INPUTACTION_FIRE] = SDL_SCANCODE_LCTRL;

		_players[0]->AddBehavior(new Engine::PlayerBaseBehavior(*_players[0], p1map));
		_players[1]->AddBehavior(new Engine::PlayerBaseBehavior(*_players[1], p2map));

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
		_players[0]->SetOffset(0, 0);
		_players[0]->SetDirection(EDIRECTION_NONE);
		_players[1]->SetOffset(0, 0);
		_players[1]->SetDirection(EDIRECTION_NONE);
		ScreenLevelBase* screenLevelBase = new ScreenLevelBase(this, LevelLoader::Create(_players, buf, _currentLevelId));

		_currentScreen = screenLevelBase;
	}

	void DonManolo::Tick()
	{
		_currentScreen->Tick();
		_currentScreen->Render();
	}
}

