#ifndef __LEVEL_H__
#define __LEVEL_H__
#include <vector>

#include "BaseTypes.h"
#include "Tile.h"
#include "Entity.h"

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

		int _pillsLeft;	// determines how many pills are left to win.

		Point<int> _startingPositions[6];	//default 6 entities ; 2 players + 4 monsters

		std::vector<Entity*> _entities;		//TODO (live data)
	public:
		Level(int width=1, int height=1, int id=0);
		~Level();

		inline int GetWidth() { return _width; }
		inline int GetHeight() { return _height; }
		inline int GetId() { return _id; }

		inline const Point<int>& GetStartingPosition(EEntityId entityId) { return _startingPositions[entityId]; }
		inline void SetStartingPosition(EEntityId entityId, const Point<int>& position)
		{
			_startingPositions[entityId]._X = position._X;
			_startingPositions[entityId]._Y = position._Y;

			_entities[entityId]->SetTilePos(position._X, position._Y);
		}

		inline Tile& GetTile(int x, int y) { return _map[y*_width+x]; }
		
		inline ETileId GetTileId(int x,int y) const { return _map[y*_width+x].GetTileId(); }

		inline void SetTileId(int x, int y, ETileId tileId, unsigned char orientation = 0)
		{
			ETileId oldTile = _map[y*_width + x].GetTileId();

			// when the tile to set is actually a eatable object, decrement eatable pills counter.
			if (oldTile == TILEID_BLUE_PILL || oldTile == TILEID_RED_PILL || oldTile == TILEID_EATABLE_WALL)
			{
				_pillsLeft--;
			}

			_map[y*_width + x].SetTileId(tileId, orientation);

			// if new tile is eatable object, increase eatable pills counter.
			if (tileId == TILEID_BLUE_PILL || tileId == TILEID_RED_PILL || tileId == TILEID_EATABLE_WALL)
			{
				_pillsLeft++;
			}
		}

		inline Entity& GetEntity(EEntityId entityId) const
		{
			return *_entities[entityId];
		}
		
		bool	DirectionWalkable(Entity& entity, EDirection direction, bool allowEatWall);

		inline int GetEntityCount() const 
		{
			return _entities.size();
		}

		inline int GetPillsLeft() const {
			return _pillsLeft;
		}
	};



	
}
#endif