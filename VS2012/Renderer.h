#ifndef __RENDERER_H__
#define __RENDERER_H__

// design of further development
#include <vector>
#include "Enums.h"
#include "SimpleAnimationController.h"

namespace Engine
{
	class SimpleAnimationController;

	class IRendererObject
	{
	};

	class Sprite : public IRendererObject
	{
	protected:
		Game::ETexture _texture;
		bool _horizontalFlip;
		int _posX;
		int _posY;
		SimpleAnimationController* _animationController;
	public:
		Sprite();

		inline Game::ETexture GetTexture() const { return _texture; }
		inline bool IsHorizontalFlipped() const { return _horizontalFlip; }
		inline int GetPosX() const {return _posX;}
		inline int GetPosY() const {return _posY;}
		inline SimpleAnimationController* GetAnimationController() { return _animationController;}

		inline void SetTexture(Game::ETexture texture) { _texture = texture; }
		inline void SetHorizontalFlipped(bool flip) { _horizontalFlip = flip; }
		inline void SetPosX(int value) { _posX = value;}
		inline void SetPosY(int value) { _posY = value;}
		inline void SetAnimationController(SimpleAnimationController* animationController) { _animationController = animationController; }
	};

	//class TileMap : public IRendererObject
	//{
	//};

}

#endif