#include "Level.h"
#include "Screen.h"
#include "Player.h"
#include <SDL.h>
#include <SDL_ttf.h>


//TODO
#define CURSOR_X 412
static const int CURSOR_Y[] = {316,364,419};



namespace Game
{

	ScreenBase::ScreenBase(DonManolo* parent)
	{
		_parent = parent;
	}

	ScreenBase::~ScreenBase()
	{
	}
	

	ScreenMenu::ScreenMenu(DonManolo* parent) : ScreenBase(parent)
	{
		_background_rect.x = 112;	//inner rectangle...
		_background_rect.y = 88;
		_background_rect.w = 800;
		_background_rect.h = 600;
			
		_cursor_pos_index = 0;

		_cursor_pos.x = CURSOR_X;
		_cursor_pos.y = CURSOR_Y[_cursor_pos_index];
		_cursor_pos.w = 25;
		_cursor_pos.h = 25;

	}

	ScreenMenu::~ScreenMenu()
	{
	}

	void ScreenMenu::Render()
	{
		SDL_RenderClear(_parent->GetRenderer());
		
		//TODO optimization
		SDL_RenderCopy(_parent->GetRenderer(), (SDL_Texture*) &_parent->GetTextureManager().GetResource((int)ETexture::TEXTURE_BACKGROUND), NULL, &_background_rect);

		_cursor_pos.y = CURSOR_Y[_cursor_pos_index];

		SDL_RenderCopy(_parent->GetRenderer(), (SDL_Texture*) &_parent->GetTextureManager().GetResource((int)ETexture::TEXTURE_ALPHA_PLAYER1), NULL, &_cursor_pos);
	}

	void ScreenMenu::Tick()
	{
		if(  _parent->GetKeyboard()->KeyPressed(SDL_SCANCODE_DOWN) )
		{
			_cursor_pos_index += 1;
			if( _cursor_pos_index > 2 ) _cursor_pos_index-=3;
		}
		if(  _parent->GetKeyboard()->KeyPressed(SDL_SCANCODE_UP) )
		{
			_cursor_pos_index -= 1;
			if( _cursor_pos_index < 0 ) _cursor_pos_index+=3;
		}

		if( _parent->GetKeyboard()->KeyPressed(SDL_SCANCODE_SPACE) )
		{
			//TODO distinguish options here..
			if( _cursor_pos_index == 0 || _cursor_pos_index == 1)
			{
				_parent->StartNewGame(_cursor_pos_index + 1,0);
			}
			else if( _cursor_pos_index == 2 )
			{
				_parent->Exit();
			}
		}
	}



	ScreenLevelBase::ScreenLevelBase(DonManolo* parent, Level* level) : ScreenBase(parent)
	{
		_level = level;
		_ready = false;
	}

	Level& ScreenLevelBase::GetLevel() const
	{
		return (*_level);
	}


	ScreenLevelBase::~ScreenLevelBase()
	{
		delete _level;
	}


	void ScreenLevelBase::Render()
	{
		SDL_RenderClear(_parent->GetRenderer());

		// when not ready, the "Get Ready , Level X" should be drawn, instead of the level.
		if (!_ready) {

			TTF_Font* font = _parent->GetFontManager().GetFont((int)EFont::FONT_BROAD_27);


			SDL_Color White = { 255, 255, 255 };  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
			SDL_Color Black = { 0,0,0 };

			int w;
			int h;
			SDL_GetWindowSize(_parent->GetWindow(), &w, &h);

			char msg[32];
			sprintf(msg, "Level %d", _parent->GetLevel().GetId());
			{
				SDL_Surface* surfaceMessage = TTF_RenderText_Shaded(font, "Get Ready!", White, Black); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
				SDL_Texture* Message = SDL_CreateTextureFromSurface(_parent->GetRenderer(), surfaceMessage); //now you can convert it into a texture
				SDL_Rect Message_rect; //create a rect
				Message_rect.x = (w - surfaceMessage->w) >> 1;  //controls the rect's x coordinate 
				Message_rect.y = ((h >> 1) - surfaceMessage->h); // controls the rect's y coordinte
				Message_rect.w = surfaceMessage->w; // controls the width of the rect
				Message_rect.h = surfaceMessage->h; // controls the height of the rect
				SDL_RenderCopy(_parent->GetRenderer(), Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
				SDL_FreeSurface(surfaceMessage);
				SDL_DestroyTexture(Message);
			}
			{
				SDL_Surface* surfaceMessage = TTF_RenderText_Shaded(font, msg, White, Black); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
				SDL_Texture* Message = SDL_CreateTextureFromSurface(_parent->GetRenderer(), surfaceMessage); //now you can convert it into a texture
				SDL_Rect Message_rect; //create a rect
				Message_rect.x = (w - surfaceMessage->w) >> 1;  //controls the rect's x coordinate 
				Message_rect.y = (h >> 1); // controls the rect's y coordinte
				Message_rect.w = surfaceMessage->w; // controls the width of the rect
				Message_rect.h = surfaceMessage->h; // controls the height of the rect
				SDL_RenderCopy(_parent->GetRenderer(), Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
				SDL_FreeSurface(surfaceMessage);
				SDL_DestroyTexture(Message);
			}

			return;
		}
		
		// render player score.
		TTF_Font* font = _parent->GetFontManager().GetFont((int)EFont::FONT_BROAD_27);

		//Game::Player a;
		

		SDL_Color White = { 255, 255, 255 };  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
		SDL_Color Black = { 0,0,0 };
		char msg[32];
		sprintf(msg, "%07d", ((Game::Player&)_parent->GetLevel().GetEntity(EEntityId::ENTITYID_PLAYER1)).GetScore());
		{ 
			SDL_Surface* surfaceMessage = TTF_RenderText_Shaded(font, msg, White, Black); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
			SDL_Texture* Message = SDL_CreateTextureFromSurface(_parent->GetRenderer(), surfaceMessage); //now you can convert it into a texture
			SDL_Rect Message_rect; //create a rect
			Message_rect.x = (400 - surfaceMessage->w);  //controls the rect's x coordinate 
			Message_rect.y = 50; // controls the rect's y coordinte
			Message_rect.w = surfaceMessage->w; // controls the width of the rect
			Message_rect.h = surfaceMessage->h; // controls the height of the rect
			SDL_RenderCopy(_parent->GetRenderer(), Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
			SDL_FreeSurface(surfaceMessage);
			SDL_DestroyTexture(Message);
		}



		//SDL_SetTextureColorMod((SDL_Texture*) &_parent->GetTextureManager().GetResource(TEXTURE_WALL), 255,200,75);
		//SDL_SetTextureColorMod((SDL_Texture*) &_parent->GetTextureManager().GetResource(TEXTURE_STRONG_WALL), 255,200,75);
		
		//draw field
		//for(int z=0;z<80;z++)
		for(int y=0;y<_level->GetHeight();y++)
		{
			for(int x=0;x<_level->GetWidth();x++)
			{
				ETileId t = _level->GetTileId(x,y);
				
		
				if( t != ETileId::TILEID_NONE )
				{
					//TODO optimize.
					SDL_Rect r = {
						112+x*25,88+y*25,25,25
					};

					SDL_Texture* current_texture;

					//TODO lookuptable?
					if( t != ETileId::TILEID_EATABLE_WALL )
					{
						current_texture = (SDL_Texture*) &_parent->GetTextureManager().GetResource((int)t+1);
					}
					else
					{
						current_texture = (SDL_Texture*) &_parent->GetTextureManager().GetResource((int)ETexture::TEXTURE_WALL);
					}
					
					//SDL_RenderCopy(_parent->GetRenderer(), current_texture, NULL, &r);
					SDL_RenderCopyEx(_parent->GetRenderer(), current_texture, NULL, &r,_level->GetTile(x,y).GetOrientation()*90.0,NULL, SDL_RendererFlip::SDL_FLIP_NONE);
				}
			}
		}

		//draw entities / sprites. This should be traverse a list of Sprite objects.
		for(int i=0;i<_level->GetEntityCount();i++)
		{
			//	inline void Render(SDL_Renderer& renderer, const ResourceManager<SDL_Texture>& resource_manager) const
			{
				const Entity& entity = _level->GetEntity((EEntityId)i);

				// leave second player if playing alone.
				if (i == (int)EEntityId::ENTITYID_PLAYER2 && _parent->GetNumPlayers() == 1) {
					continue;
				}


				//ETexture t = _level->GetEntity((EEntityId)i).GetTexture();
				if( entity.GetTexture() != ETexture::TEXTURE_NONE )
					{
						//TODO optimize.
						SDL_Rect r = {
							112+entity.Sprite::GetPosX(),88+entity.Sprite::GetPosY(),25,25
						};
						SDL_Texture* current_texture = (SDL_Texture*) &_parent->GetTextureManager().GetResource((int)entity.GetTexture());
						SDL_RenderCopyEx(_parent->GetRenderer(), current_texture, NULL, &r,0.0,NULL, 
							entity.IsHorizontalFlipped() ? SDL_RendererFlip::SDL_FLIP_HORIZONTAL : SDL_RendererFlip::SDL_FLIP_NONE);
					}
			}

			//_level->GetEntity((EEntityId)i).Render(*_parent->GetRenderer(), _parent->GetTextureManager());
		}
	}
	
	void ScreenLevelBase::Tick()
	{
		if (!_ready) {
			if (_parent->GetKeyboard()->KeyPressed(SDL_SCANCODE_SPACE)) {
				_ready = true;
				
			}
			return;
		}

		//controls

		//TODO handle number of players etc.
		int entityCount = _level->GetEntityCount();

		for (int index = 0; index < entityCount; index++)
		{
			// when single player, omit second player out.
			if (index == (int)EEntityId::ENTITYID_PLAYER2 && _parent->GetNumPlayers() == 1)
			{
				continue;
			}
			_level->GetEntity((EEntityId)index).Tick(*_parent, *_level);
			
		}

		if (_level->GetPillsLeft() == 0) {
			_parent->EnterNextLevel();
			return;
		}

		//_level->GetEntity(ENTITYID_PLAYER2).Tick(*_parent, *_level);
		//TODO debugcode
		if( _parent->GetKeyboard()->KeyPressed(SDL_SCANCODE_SPACE))
		{
			// warning - this function DELETES the screen (this) AND the level.
			_parent->EnterNextLevel();
			return;
		}

		

	}
}