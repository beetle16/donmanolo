#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"

#include "BaseTypes.h"


namespace Game
{
	class Player : public Entity
	{
	protected:
		int _score;
		int _lives;
		
	public:
		Player(ETexture texture);
		virtual ~Player();
	};
}

#endif