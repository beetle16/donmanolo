#include "MonsterBehavior.h"

namespace Engine
{



	MonsterBehavior::MonsterBehavior(Game::Entity& entity) : BaseBehavior(entity)
	{
		_homeX = _entity.GetTilePosX();
		_homeY = _entity.GetTilePosY();
	}

	void MonsterBehavior::Tick(Game::DonManolo& game, Game::Level& level) {
		

	}

	MonsterBehavior::~MonsterBehavior() {

	}




}