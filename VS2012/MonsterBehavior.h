#ifndef __MONSTERBEHAVIOR_H__
#define __MONSTERBEHAVIOR_H__

#include "BaseBehavior.h"

namespace Engine
{
	
	// defines behavior of a monster.
	class MonsterBehavior : public BaseBehavior
	{
	protected:
		//regeneration returning point
		int _homeX;
		int _homeY;

		// build home-going-map
		// short[levX][levY]
		// TODO doors etc.

	public:
		MonsterBehavior(Game::Entity& entity);
		
		virtual void Tick(Game::DonManolo& game, Game::Level& level);

		virtual ~MonsterBehavior();

	};


}


#endif