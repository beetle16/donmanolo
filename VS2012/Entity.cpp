#include "Entity.h"
#include "BaseTypes.h"


namespace Game
{
	Entity::Entity(ETexture texture) : _direction(EDIRECTION_NONE)
	{
		_texture = texture;
		_horizontalFlip = false;
		_posX = 0;
		_posY = 0;
		_offsetX = 0;
		_offsetY = 0;
	}

	Entity::~Entity()
	{
		if( _animationController != NULL )
		{
			delete _animationController;
			_animationController = NULL;
		}

		for(unsigned int index = 0; index < _behaviors.size(); index++)
		{
			delete _behaviors[index];
		}
		_behaviors.clear();
	}

	void Entity::BaseMovement(int speed)
	{
					// auto move if direction is set.
			if( _direction != Game::EDIRECTION_NONE )
			{
				_offsetX += Game::dirX[_direction] * speed;
				_offsetY += Game::dirY[_direction] * speed;
				if( _animationController != NULL )
				{
					_animationController->AnimationStep();
				}
			}

			// fixate on next field if animation (offset) reached it.
			if( abs(_offsetX) >= 25 )
			{
				_offsetX = 0;
				_tilePosX +=  dirX[_direction];
				_direction = EDIRECTION_NONE;
			
			}
			if( abs(_offsetY) >= 25 )
			{
				_offsetY = 0;
				_tilePosY +=  dirY[_direction];
				_direction = EDIRECTION_NONE;
			}

		
	}

	void Entity::Tick(Game::DonManolo& game, Game::Level& level)
	{
		for (unsigned int index = 0; index < _behaviors.size(); index++)
		{
			_behaviors[index]->Tick(game, level);
		}
	}
}