#ifndef __PLAYERBASEBEHAVIOR_H__
#define __PLAYERBASEBEHAVIOR_H__

#include "BaseBehavior.h"
#include "BaseTypes.h"
#include "Monster.h"
#include "Player.h"

namespace Engine
{
	class PlayerBaseBehavior : public BaseBehavior
	{
	protected:
		std::map<Game::EInputAction, int> _mapping;
	public:
		PlayerBaseBehavior(Game::Entity& entity, std::map<Game::EInputAction,int>& mapping) : BaseBehavior(entity)
		{
			_mapping = mapping;
		}

		virtual void Tick(Game::DonManolo& game, Game::Level& level){
			// TODO: move this code to smaller pieces
			// TODO: move 25 to a const all throughout the program.
			// TODO: change dir in-mid field (_offset != 0 ) (open, should i do that?)
			
			Game::EDirection lastDirection = _entity.GetDirection();
			const unsigned char* keyb = game.GetKeyboard()->GetState();

			_entity.BaseMovement(level.GetGameSpeed());
			// character out of border (x-axis)
			if( _entity.GetTilePosX() == -1 )
			{
				_entity.SetTilePos(level.GetWidth()-1, _entity.GetTilePosY());
			}
			if( _entity.GetTilePosX() == level.GetWidth())
			{
				_entity.SetTilePos(0, _entity.GetTilePosY());
			}


			// game mechanics
			Game::ETileId tile = level.GetTileId(_entity.GetTilePosX(),_entity.GetTilePosY());
			if(tile == Game::ETileId::TILEID_BLUE_PILL || tile == Game::ETileId::TILEID_RED_PILL || tile == Game::ETileId::TILEID_EATABLE_WALL)
			{
				Game::Player* p = dynamic_cast<Game::Player*>(&_entity);
				p->IncreaseScore(10);
				level.SetTileId(_entity.GetTilePosX(), _entity.GetTilePosY(), Game::ETileId::TILEID_NONE);
			}

			// mechanics for red pill.
			if (tile == Game::ETileId::TILEID_RED_PILL)
			{
				Game::EEntityId monsters[] = { Game::EEntityId::ENTITYID_ENEMY1 , Game::EEntityId::ENTITYID_ENEMY2 , Game::EEntityId::ENTITYID_ENEMY3 , Game::EEntityId::ENTITYID_ENEMY4 };
				// TODO repeat for all monsters
				for (int monsterIndex = 0; monsterIndex < 4; monsterIndex++)
				{
					Game::Monster* monster = dynamic_cast<Game::Monster*>(&level.GetEntity(monsters[monsterIndex]));
					if (monster != NULL)
					{
						monster->GetGhostedTickCounter().SetTarget(level.GetGhostedTime());
						monster->GetGhostedTickCounter().Reset();
					}
				}
			}


			// user input movement (only processed when standing on field)
			if( _entity.GetDirection() == Game::EDirection::EDIRECTION_NONE)
			{
				// tries to determine allowed directions.
				Game::EDirection horizontal = Game::EDirection::EDIRECTION_NONE;
				Game::EDirection vertical = Game::EDirection::EDIRECTION_NONE;
				Game::EDirection finalDir = Game::EDirection::EDIRECTION_NONE;
				// check keys and lastDirection to determine next direction / or stop.
				if( keyb[_mapping[Game::INPUTACTION_LEFT]] == 1 ) { horizontal = Game::EDirection::EDIRECTION_WEST; }
				else if( keyb[_mapping[Game::INPUTACTION_RIGHT]] == 1) { horizontal = Game::EDirection::EDIRECTION_EAST; }

				if( keyb[_mapping[Game::INPUTACTION_UP]] == 1 ) { vertical = Game::EDirection::EDIRECTION_NORTH;}
				else if( keyb[_mapping[Game::INPUTACTION_DOWN]] == 1) { vertical = Game::EDirection::EDIRECTION_SOUTH; }

				if( horizontal != Game::EDirection::EDIRECTION_NONE && vertical != Game::EDirection::EDIRECTION_NONE) 
				{
					//two directions pressed. abandon last moved direction then if possible.
					if( lastDirection == Game::EDirection::EDIRECTION_EAST || lastDirection == Game::EDirection::EDIRECTION_WEST  )
					{
						finalDir = vertical;
					}
					else // this also triggers if there was no last movement 
					{
						finalDir = horizontal;
					}
				}
				else
				{
					if( horizontal != Game::EDirection::EDIRECTION_NONE )
					{
						finalDir = horizontal;
					}
					else
					{
						finalDir = vertical;
					}
				}

				// collision checks and flip left/right. Turn to new direction if possible.
				if( level.DirectionWalkable(_entity, finalDir, true ) )
				{
					_entity.SetDirection( finalDir );
					if( finalDir == Game::EDirection::EDIRECTION_EAST ) 
					{
						_entity.SetHorizontalFlipped( false);
					}else if( finalDir == Game::EDirection::EDIRECTION_WEST )
					{
						_entity.SetHorizontalFlipped( true);
					}
				}
				else if( level.DirectionWalkable(_entity, lastDirection, false) )
				{
					// else walk old direction.
					_entity.SetDirection(lastDirection);
				}
			}
		}

		virtual ~PlayerBaseBehavior() {}
	};

}

#endif