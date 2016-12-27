#include "MonsterBehavior.h"
#include "CMWC.h"

namespace Engine
{



	MonsterBehavior::MonsterBehavior(Game::Entity& entity) : BaseBehavior(entity), _waitCounter(130)
	{
		_homeX = _entity.GetTilePosX();
		_homeY = _entity.GetTilePosY();
		_behaviorState = MONSTERBEHAVIORSTATE_WAITING;

	}

	void MonsterBehavior::Tick(Game::DonManolo& game, Game::Level& level) 
	{
		if (_behaviorState == MONSTERBEHAVIORSTATE_WAITING) {
			_waitCounter.Tick();

			if (_waitCounter.TargetReached()) {
				_behaviorState = MONSTERBEHAVIORSTATE_NORMAL;
			}

			return;
		}

		// TODO: move this code to smaller pieces
		// TODO: move 25 to a const all throughout the program.
		// TODO: change dir in-mid field (_offset != 0 ) (open, should i do that?)

		Game::EDirection lastDirection = _entity.GetDirection();

		_entity.BaseMovement(level.GetEnemySpeed());

		// character out of border (x-axis)
		if (_entity.GetTilePosX() == -1)
		{
			_entity.SetTilePos(level.GetWidth() - 1, _entity.GetTilePosY());
		}
		if (_entity.GetTilePosX() == level.GetWidth())
		{
			_entity.SetTilePos(0, _entity.GetTilePosY());
		}



		// user input movement (only processed when standing on field)
		if (_entity.GetDirection() == Game::EDirection::EDIRECTION_NONE)
		{
			Game::EDirection backDir = (Game::EDirection) ((lastDirection + 2) % 4);
			Game::EDirection finalDir = (Game::EDirection) (CMWC() % 4);

			
			
			// algorithm is:
			// go to random direction, but not back, if possible.
			//while (!level.DirectionWalkable(_entity, finalDir, true)) {
			
			bool accept = false;
			
			for (int count = 0; count < 4; count++)
			{
				if (finalDir != backDir && level.DirectionWalkable(_entity, finalDir, true))
				{
					accept = true;
				}
				else 
				{
					// NOT accept
					finalDir = (Game::EDirection) ((finalDir+1)%4);
				}



			}
			
			if (!accept) {
				finalDir = backDir;
			}
			
			// collision checks and flip left/right. Turn to new direction if possible.
			//if (level.DirectionWalkable(_entity, finalDir, true))
			{
				_entity.SetDirection(finalDir);
				if (finalDir == Game::EDirection::EDIRECTION_EAST)
				{
					_entity.SetHorizontalFlipped(false);
				}
				else if (finalDir == Game::EDirection::EDIRECTION_WEST)
				{
					_entity.SetHorizontalFlipped(true);
				}
			}
		}
	}

	MonsterBehavior::~MonsterBehavior() {

	}




}