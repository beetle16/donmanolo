#ifndef __PLAYERFACTORY_H__
#define __PLAYERFACTORY_H__

#include "Player.h"
#include "Enums.h"

namespace Game
{
	class PlayerFactory
	{
	protected:

	public:
		static Player* Create(EEntityId id);

	};

}

#endif