#ifndef __BASEBEHAVIOR_H__
#define __BASEBEHAVIOR_H__

#include "Behavior.h"
#include "Entity.h"
#include "DonManolo.h"
#include "Level.h"

namespace Engine
{
	class BaseBehavior : public IBehavior
	{
	protected:
		Game::Entity& _entity;
	public:
		BaseBehavior(Game::Entity& entity) : _entity(entity)
		{

		}

		virtual void Tick(Game::DonManolo& game, Game::Level& level){
			_entity.SetPosX(_entity.GetFinalPosX());
			_entity.SetPosY(_entity.GetFinalPosY());
		}

		virtual ~BaseBehavior() {}

	};

}

#endif