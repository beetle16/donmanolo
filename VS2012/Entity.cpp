#include "Entity.h"
#include "BaseTypes.h"


namespace Game
{
	Entity::Entity(ETexture texture) : _direction(EDirection::EDIRECTION_NONE)
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
			if( _direction != Game::EDirection::EDIRECTION_NONE )
			{
				_offsetX += Game::dirX[(int)_direction] * speed;
				_offsetY += Game::dirY[(int)_direction] * speed;
				if( _animationController != NULL )
				{
					_animationController->AnimationStep();
				}
			}

			// fixate on next field if animation (offset) reached it.
			if( abs(_offsetX) >= 25 )
			{
				_offsetX = 0;
				_tilePosX +=  dirX[(int)_direction];
				_direction = EDirection::EDIRECTION_NONE;
			
			}
			if( abs(_offsetY) >= 25 )
			{
				_offsetY = 0;
				_tilePosY +=  dirY[(int)_direction];
				_direction = EDirection::EDIRECTION_NONE;
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