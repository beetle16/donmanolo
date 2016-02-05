#ifndef __SIMPLEANIMATIONCONTROLLER_H__
#define __SIMPLEANIMATIONCONTROLLER_H__

#include <vector>
#include "Renderer.h"
#include "Enums.h"

namespace Engine
{
	class Sprite;
// TODO move this out , don't preset textuers.
	// move animation to entity
	// can let animation null or defaultAnimationController.
	class SimpleAnimationController
	{
	protected:
		int _frame;
		int _frameSpeed;
		unsigned int _currentTexture;
		std::vector<Game::ETexture> _textures;
		Sprite& _target;
	public:

		SimpleAnimationController(Sprite& target, int frames) ;

		void AddTexture(Game::ETexture texture);

		void AnimationStep();
	};
}

#endif