#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "Entity.h"

namespace Game
{
		
	class Monster : public Entity
	{
	protected:
	public:
		Monster(ETexture texture);
		virtual ~Monster();

		//virtual void Tick(DonManolo& game, Level& level);
	};


}

#endif