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
	protected:
		static Point<int> ReadPosition(FILE* fp); 
	public:

		static Level* Create(char* filename);
	};
}

#endif