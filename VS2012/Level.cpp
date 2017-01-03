
#include "Level.h"
#include "Player.h"
#include "Monster.h"
#include "SimpleAnimationController.h"

namespace Game
{
	Level::Level(int width, int height, int id)
	{
		this->_width = width;
		this->_height = height;
		this->_id = id;

		this->_pillsLeft = 0;
		this->_gameSpeed = 3;
		this->_enemySpeed = 3;
		this->_ghostedTime = 600;

		_map = new Tile[width*height]();

		// TODO move this out of level. This is game specific (app specific).
		// pregenerate entites with its default textures.
		ETexture textures[] = {TEXTURE_ALPHA_PLAYER1, TEXTURE_ALPHA_PLAYER2, 
			TEXTURE_ALPHA_ENEMY_PURPLE, TEXTURE_ALPHA_ENEMY_ORANGE, TEXTURE_ALPHA_ENEMY_BLUE, TEXTURE_ALPHA_ENEMY_RED,
			TEXTURE_ALPHA_ENEMY_PURPLE_G, TEXTURE_ALPHA_ENEMY_ORANGE_G, TEXTURE_ALPHA_ENEMY_BLUE_G, TEXTURE_ALPHA_ENEMY_RED_G};

		ETexture player[2][4] ={ {TEXTURE_ALPHA_PLAYER1, TEXTURE_ALPHA_PLAYER1b, TEXTURE_ALPHA_PLAYER1c, TEXTURE_ALPHA_PLAYER1b},
						{TEXTURE_ALPHA_PLAYER2, TEXTURE_ALPHA_PLAYER2b, TEXTURE_ALPHA_PLAYER2c, TEXTURE_ALPHA_PLAYER2b} };
		
		for(int i=0;i<6;i++)
		{
			if( i < 2 )
			{
				Player* e = new Player(textures[i]);

				Engine::SimpleAnimationController* controller1 = new Engine::SimpleAnimationController(*e, 4);
				controller1->AddTexture(player[i][0]);
				controller1->AddTexture(player[i][1]);
				controller1->AddTexture(player[i][2]);
				controller1->AddTexture(player[i][3]);
				e->SetAnimationController(controller1);

				_entities.push_back(e);
			}
			else
			{
				Monster* e = new Monster(textures[i], textures[i+4]);
				_entities.push_back(e);
			}
		}
	}

	Level::~Level()
	{
		delete[] _map;

		for(unsigned int i=0;i<_entities.size();i++)
		{
			delete _entities[i];
		}
		_entities.clear();
	}

	bool Level::DirectionWalkable(Entity& entity, EDirection direction, bool allowEatWall)
	{
		if( direction == EDIRECTION_NONE ) 
		{
			return false;
		}

		int targetX = entity.GetTilePosX() + dirX[direction];
		int targetY = entity.GetTilePosY() + dirY[direction];
		if( targetX >= -1 && targetX <= GetWidth() && targetY >= 0 && targetY < GetHeight())
		{
			if( targetX >= 0 && targetX < GetWidth())
			{
				//fully in-bounds
				ETileId targetFieldId = GetTile(targetX, targetY).GetTileId();
				if( targetFieldId != TILEID_STRONG_WALL && targetFieldId != TILEID_WALL )
				{
					if( targetFieldId == TILEID_EATABLE_WALL )
					{
						return allowEatWall;
					}else
					{
						return true;
					}
				}
			}else
			{
				// x-axis border
				return true;
			}
		}
		return false;
	}
}