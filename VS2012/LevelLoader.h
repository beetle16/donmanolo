#ifndef __LEVELLOADER_H__
#define __LEVELLOADER_H__

#include <stdio.h>
#include "BaseTypes.h"
#include "PlayerBaseBehavior.h"

namespace Game
{
	class Level;

	class LevelLoader
	{
	private:
		static void ReadMap(Level* target, FILE* fp);
	protected:
		static Point<int> ReadPosition(FILE* fp); 
	public:

		static Level* Create(std::vector<Player*>& players, char* filename, int id);
	};
}

#endif