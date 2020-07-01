#ifndef __BASETYPES_H__
#define __BASETYPES_H__

namespace Game
{
	// defines a 2 dimensional point.
	template<class T>
	struct Point
	{
	public:
		T _X;
		T _Y;
	};

	// defines the directions N,E,S,W.
	static const int dirX[4] = { 0, 1,0,-1};
	static const int dirY[4] = {-1, 0,1, 0};

	enum class EDirection : signed char
	{
		EDIRECTION_NONE = -1,
		EDIRECTION_NORTH = 0,
		EDIRECTION_EAST = 1,
		EDIRECTION_SOUTH = 2,
		EDIRECTION_WEST = 3
	};

}


#endif