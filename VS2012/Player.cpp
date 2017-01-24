#include "Player.h"
#include "Level.h"
#include "DonManolo.h"

namespace Game
{


	Player::Player(ETexture texture) : Entity(texture)
	{
		_score = 0;
	}

	Player::~Player()
	{
	}

	int Player::GetScore() 
	{
		return _score;
	}
	void Player::IncreaseScore(int amount) {
		_score += amount;
	}


	int Player::GetLives()
	{
		return _lives;
	}

	//void Player::Tick(DonManolo& game, Level& level)
	//{
	//	// TODO: move this code to smaller pieces
	//	// TODO: move speed out to donManolo or a base rule object.
	//	// TODO: move 25 to a const all throughout the program.
	//	// TODO: change dir in-mid field (_offset != 0 ) (open, should i do that?)

	//	const int SPEED = 3;
	//	EDirection lastDirection = _direction;
	//	const unsigned char* keyb = game.GetKeyboard()->GetState();

	//	// auto move if direction is set.
	//	if( _direction != EDIRECTION_NONE )
	//	{
	//		_offsetX += dirX[_direction] * SPEED;
	//		_offsetY += dirY[_direction] * SPEED;
	//		if( _animationController != NULL )
	//		{
	//			_animationController->AnimationStep();
	//		}
	//	}

	//	// fixate on next field if animation (offset) reached it.
	//	if( abs(_offsetX) >= 25 )
	//	{
	//		_offsetX = 0;
	//		_tilePosX +=  dirX[_direction];
	//		_direction = EDIRECTION_NONE;
	//		
	//	}
	//	if( abs(_offsetY) >= 25 )
	//	{
	//		_offsetY = 0;
	//		_tilePosY +=  dirY[_direction];
	//		_direction = EDIRECTION_NONE;
	//	}

	//	// this updates the final pos out of tilePos and offset.
	//	Entity::Tick(game, level);

	//	// game mechanics
	//	ETileId tile = game.GetLevel().GetTileId(_tilePosX,_tilePosY);
	//	if(tile == ETileId::TILEID_BLUE_PILL || tile == ETileId::TILEID_RED_PILL || tile == ETileId::TILEID_EATABLE_WALL)
	//	{
	//		game.GetLevel().SetTileId(_tilePosX, _tilePosY, TILEID_NONE);
	//	}


	//	if( _direction == EDIRECTION_NONE)
	//	{
	//		// tries to determine allowed directions.
	//		EDirection horizontal = EDIRECTION_NONE;
	//		EDirection vertical = EDIRECTION_NONE;
	//		EDirection finalDir = EDIRECTION_NONE;
	//		// check keys and lastDirection to determine next direction / or stop.
	//		if( keyb[SDL_SCANCODE_LEFT] == 1 ) { horizontal = EDIRECTION_WEST; }
	//		else if( keyb[SDL_SCANCODE_RIGHT] == 1) { horizontal = EDIRECTION_EAST; }

	//		if( keyb[SDL_SCANCODE_UP] == 1 ) { vertical = EDIRECTION_NORTH;}
	//		else if( keyb[SDL_SCANCODE_DOWN] == 1) { vertical = EDIRECTION_SOUTH; }

	//		if( horizontal != EDIRECTION_NONE && vertical != EDIRECTION_NONE) 
	//		{
	//			//two directions pressed. abandon last moved direction then if possible.
	//			if( lastDirection == EDIRECTION_EAST || lastDirection == EDIRECTION_WEST  )
	//			{
	//				finalDir = vertical;
	//			}
	//			else // this also triggers if there was no last movement 
	//			{
	//				finalDir = horizontal;
	//			}
	//		}
	//		else
	//		{
	//			if( horizontal != EDIRECTION_NONE )
	//			{
	//				finalDir = horizontal;
	//			}
	//			else
	//			{
	//				finalDir = vertical;
	//			}
	//		}

	//		// collision checks and flip left/right. Turn to new direction if possible.
	//		if( level.DirectionWalkable(*this, finalDir, true ) )
	//		{
	//			_direction = finalDir;
	//			if( finalDir == EDIRECTION_EAST ) 
	//			{
	//				_horizontalFlip = false;
	//			}else if( finalDir == EDIRECTION_WEST )
	//			{
	//				_horizontalFlip = true;
	//			}
	//		}
	//		else if( level.DirectionWalkable(*this, lastDirection, false) )
	//		{
	//			// else walk old direction.
	//			_direction = lastDirection;
	//		}
	//	}
	//}
}

