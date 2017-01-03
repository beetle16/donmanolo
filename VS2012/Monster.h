#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "Entity.h"
#include "GhostedTickCounter.h"

namespace Game
{
		
	class Monster : public Entity
	{
	protected:
		Engine::GhostedTickCounter _ghostedTickCounter;

		// texture controller
		Game::ETexture _baseTexture;
		Game::ETexture _ghostedTexture;

	public:
		Monster(ETexture baseTexture, ETexture ghostedTexture);
		virtual ~Monster();

		inline Game::ETexture GetBaseTexture() { return _baseTexture; }
		inline Game::ETexture GetGhostedTexture() { return _ghostedTexture; }

		inline Engine::GhostedTickCounter& GetGhostedTickCounter() { return _ghostedTickCounter; }
		//virtual void Tick(DonManolo& game, Level& level);
	};


}

#endif