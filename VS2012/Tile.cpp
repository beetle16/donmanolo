#include "Enums.h"
#include "Tile.h"

namespace Game
{
	Tile::Tile(ETileId tileId) : _tileId(tileId), _orientation(0)
	{
	}

	

	void Tile::SetTileId(ETileId tileId, unsigned char orientation)
	{
		_tileId = tileId;
		_orientation = orientation;
	}
}