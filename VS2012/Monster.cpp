#include "Monster.h"

namespace Game
{
	Monster::Monster(ETexture baseTexture, ETexture ghostedTexture) : Entity(baseTexture)
	{
		_baseTexture = baseTexture;
		_ghostedTexture = ghostedTexture;
	}

	Monster::~Monster()
	{
	}

	//void Monster::Tick(DonManolo& game, Level& level)
	//{
	//}
}