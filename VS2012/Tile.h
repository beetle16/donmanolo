#ifndef __TILE_H__
#define __TILE_H__

#include "Enums.h"

namespace Game
{
	// basic tile; no special functions
	// TODO events; special properties (timer etc)
	class Tile
	{
	protected:
		ETileId _tileId;
		unsigned char _orientation;
	public:
		Tile(ETileId tileId = TILEID_NONE);

		inline ETileId GetTileId()
		{
			return _tileId;
		}

		inline unsigned char GetOrientation()
		{
			return _orientation;
		}

		void SetTileId(ETileId tileId, unsigned char orientation = 0);
	};
}

#endif