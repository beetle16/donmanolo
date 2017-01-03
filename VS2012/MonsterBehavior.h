#ifndef __MONSTERBEHAVIOR_H__
#define __MONSTERBEHAVIOR_H__

#include "BaseBehavior.h"
#include "Monster.h"
#include "TickCounter.h"

namespace Engine
{
	
	enum EMonsterBehaviorState : char 
	{
		MONSTERBEHAVIORSTATE_WAITING,
		MONSTERBEHAVIORSTATE_NORMAL,
		MONSTERBEHAVIORSTATE_RETURNING,
	};

	// defines behavior of a monster.
	class MonsterBehavior : public BaseBehavior
	{
	protected:
		// casted entity
		Game::Monster& _monster;

		//regeneration returning point
		int _homeX;
		int _homeY;

		EMonsterBehaviorState _behaviorState;
		TickCounter _waitCounter;
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