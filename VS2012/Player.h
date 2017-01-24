#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"

#include "BaseTypes.h"


namespace Game
{
	// TODO: current problem: player objects are currently created/destroyed along with level.
	// Scores and other information in here will be lost after each level change.

	class Player : public Entity
	{
	protected:
		int _score;
		int _lives;
		
	public:
		Player(ETexture texture);
		virtual ~Player();


		int GetScore();
		void IncreaseScore(int amount);

		int GetLives();
	};
}

#endif