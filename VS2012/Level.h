#ifndef __LEVEL_H__
#define __LEVEL_H__
#include <vector>

#include "BaseTypes.h"
#include "Tile.h"
#include "Entity.h"
#include "Player.h"

namespace Game
{
		// represents a level
	class Level
	{
	protected:
		Tile* _map;		// level design
		int _width;		// level width
		int _height;	// level height

		int _id; // level id

		// determines how many pills are left to win.
		int _pillsLeft;	

		// main speed of the player.
		int _gameSpeed;

		// main speed of the enemies.
		int _enemySpeed;

		// time while the red pill lasts. (in frames at 60 fps, so 16.67 ms per unit).
		int _ghostedTime;

		Point<int> _startingPositions[6];	//default 6 entities ; 2 players + 4 monsters

		std::vector<Entity*> _entities;		//TODO (live data)
	public:
		Level(std::vector<Player*>& players, int width=1, int height=1, int id=0);
		~Level();

		inline int GetWidth() { return _width; }
		inline int GetHeight() { return _height; }
		inline int GetId() { return _id; }

		inline const Point<int>& GetStartingPosition(EEntityId entityId) { return _startingPositions[(int)entityId]; }
		inline void SetStartingPosition(EEntityId entityId, const Point<int>& position)
		{
			_startingPositions[(int)entityId]._X = position._X;
			_startingPositions[(int)entityId]._Y = position._Y;

			_entities[(int)entityId]->SetTilePos(position._X, position._Y);
		}

		inline Tile& GetTile(int x, int y) { return _map[y*_width+x]; }
		
		inline ETileId GetTileId(int x,int y) const { return _map[y*_width+x].GetTileId(); }

		inline void SetTileId(int x, int y, ETileId tileId, unsigned char orientation = 0)
		{
			ETileId oldTile = _map[y*_width + x].GetTileId();

			// when the tile to set is actually a eatable object, decrement eatable pills counter.
			if (oldTile == ETileId::TILEID_BLUE_PILL || oldTile == ETileId::TILEID_RED_PILL || oldTile == ETileId::TILEID_EATABLE_WALL)
			{
				_pillsLeft--;
			}

			_map[y*_width + x].SetTileId(tileId, orientation);

			// if new tile is eatable object, increase eatable pills counter.
			if (tileId == ETileId::TILEID_BLUE_PILL || tileId == ETileId::TILEID_RED_PILL || tileId == ETileId::TILEID_EATABLE_WALL)
			{
				_pillsLeft++;
			}
		}

		inline Entity& GetEntity(EEntityId entityId) const
		{
			return *_entities[(int)entityId];
		}
		
		bool	DirectionWalkable(Entity& entity, EDirection direction, bool allowEatWall);

		inline int GetEntityCount() const 
		{
			return _entities.size();
		}

		inline int GetPillsLeft() const {
			return _pillsLeft;
		}

		inline int GetGameSpeed() const { return _gameSpeed; }
		inline void SetGameSpeed(int speed) { _gameSpeed = speed; }

		inline int GetEnemySpeed() const { return _enemySpeed; }
		inline void SetEnemySpeed(int speed) { _enemySpeed = speed; }

		inline int GetGhostedTime() const { return _ghostedTime; }
		inline void SetGhostedTime(int time) { _ghostedTime = time; }
	};



	
}
#endif