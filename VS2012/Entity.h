#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <SDL.h>

#include "Enums.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Behavior.h"
#include "BaseTypes.h"

namespace Game
{
	class DonManolo;
	class Level;

	class Entity : public Engine::Sprite
	{
	protected:
		int _tilePosX;
		int _tilePosY;
		int _offsetX;
		int _offsetY;
		EDirection _direction;

		std::vector<Engine::IBehavior*> _behaviors;

		Entity(ETexture texture);


	public:
		       void BaseMovement(int speed);
		
		virtual ~Entity();

		inline void SetTilePos(int posX, int posY) {_tilePosX = posX; _tilePosY = posY;}
		inline void SetDirection(EDirection direction) { _direction = direction;}
		inline void SetOffset(int offsetX, int offsetY) { _offsetX = offsetX; _offsetY = offsetY; }

		inline int GetTilePosX() { return _tilePosX; }
		inline int GetTilePosY() { return _tilePosY; }

		inline int GetFinalPosX() const{ return _tilePosX*25+_offsetX; }
		inline int GetFinalPosY() const{ return _tilePosY*25+_offsetY; }
		
		inline EDirection GetDirection() const { return _direction;}

		inline void AddBehavior(Engine::IBehavior* behavior) { _behaviors.push_back(behavior); }


		virtual void Tick(Game::DonManolo& game, Game::Level& level);

	};

}

#endif