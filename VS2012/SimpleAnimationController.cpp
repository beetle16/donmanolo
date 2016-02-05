#include "SimpleAnimationController.h"

namespace Engine
{
		SimpleAnimationController::SimpleAnimationController(Sprite& target, int frames) : _frame(0), _frameSpeed(frames), _currentTexture(0), _target(target)
		{
		}

		void SimpleAnimationController::AddTexture(Game::ETexture texture)
		{
			_textures.push_back(texture);
		}

		void SimpleAnimationController::AnimationStep()
		{
			_frame++;
			if( (_frame % _frameSpeed) == 0 )
			{
				_currentTexture++;
				if( _currentTexture >= _textures.size() ) 
				{
					_currentTexture = 0;
				}
				_target.SetTexture(_textures[_currentTexture]);
			}
		}

}