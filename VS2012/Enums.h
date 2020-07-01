#ifndef __ENUMS_H_
#define __ENUMS_H_

namespace Game
{
	// holds a hardcoded list of texture file names to load. (0 - 34)
	static char* textureList[] = {
		"res/background.bmp", "res/Mauer.bmp", "res/strongMauer.bmp", "res/bluePoint.bmp",				//0
		"res/redPoint.bmp", "res/Tsource.bmp", "res/Tdest.bmp", "res/boniSpeedUp.bmp",					//4
		"res/boniSpeedDown.bmp", "res/boniCPoint.bmp", "res/boniLeben.bmp", "res/boniMulti2.bmp",		//8
		"res/boniMulti3.bmp", "res/boniMulti4.bmp", "res/boniMulti8.bmp", "res/boniSchnecke.bmp",		//12
		"res/boniW.bmp", "res/boniPacFres.bmp" , "res/boniEnmWait.bmp" , "res/hscores.bmp",				//16
		"res/Player1.bmp", "res/Player2.bmp", "res/Player1an1.bmp", "res/Player2an1.bmp",				//20	(alpha starts at 20)
		"res/Player1an2.bmp", "res/Player2an2.bmp", "res/eLila.bmp", "res/eOrange.bmp",					//24
		"res/eBlau.bmp", "res/eRot.bmp", "res/eLilaG.bmp", "res/eOrangeG.bmp",							//28
		"res/eBlauG.bmp", "res/eRotG.bmp", "res/augeGrau.bmp",											//32
	};

	// this enum can be used to access textures by name.
	enum class ETexture : signed char {
		TEXTURE_NONE					=-1,
		TEXTURE_BACKGROUND				=0,
		TEXTURE_WALL					=1,
		TEXTURE_STRONG_WALL				=2,
		TEXTURE_BLUE_PILL				=3,
		TEXTURE_RED_PILL				=4,
		TEXTURE_TSOURCE					=5,
		TEXTURE_TDEST					=6,

		TEXTURE_BONI_SPEEDUP			=7,
		TEXTURE_BONI_SPEEDDOWN			=8,
		TEXTURE_BONI_COOKIE				=9,
		TEXTURE_BONI_EXTRALIFE			=10,
		TEXTURE_BONI_MPL2				=11,
		TEXTURE_BONI_MPL3				=12,
		TEXTURE_BONI_MPL4				=13,
		TEXTURE_BONI_MPL8				=14,
		TEXTURE_BONI_SNAIL				=15,
		TEXTURE_BONI_WARP				=16,

		TEXTURE_BONI_PACFRES			=17,
		TEXTURE_BONI_TIMESTOP			=18,
		TEXTURE_HISCORES				=19,

		TEXTURE_ALPHA_PLAYER1			=20,
		TEXTURE_ALPHA_PLAYER2			=21,
		TEXTURE_ALPHA_PLAYER1b			=22,
		TEXTURE_ALPHA_PLAYER2b			=23,
		TEXTURE_ALPHA_PLAYER1c			=24,
		TEXTURE_ALPHA_PLAYER2c			=25,

		TEXTURE_ALPHA_ENEMY_PURPLE		= 26,
		TEXTURE_ALPHA_ENEMY_ORANGE		= 27,
		TEXTURE_ALPHA_ENEMY_BLUE		= 28,
		TEXTURE_ALPHA_ENEMY_RED			= 29,

		TEXTURE_ALPHA_ENEMY_PURPLE_G	= 30,
		TEXTURE_ALPHA_ENEMY_ORANGE_G	= 31,
		TEXTURE_ALPHA_ENEMY_BLUE_G		= 32,
		TEXTURE_ALPHA_ENEMY_RED_G		= 33,

		TEXTURE_ALPHA_ENEMY_EYES        = 34,
	};

	// this enum can be used to access fonts by name.
	enum class EFont : signed char
	{
		FONT_BROAD_27 = 0,
	};

	// this enum assigns names to tile ids.
	enum class ETileId : signed char
	{
		TILEID_NONE = -1,
		TILEID_WALL = 0,
		TILEID_STRONG_WALL = 1,
		TILEID_BLUE_PILL = 2,
		TILEID_RED_PILL = 3,
		TILEID_TSOURCE = 4,   //?
		TILEID_TDEST = 5,     //?
		TILEID_EATABLE_WALL = 6,
	};

	// defines 4 orientations of the cartesian coordinate system.
	enum class EOrientation : unsigned char
	{
		ORIENTATION_0,
		ORIENTATION_90,
		ORIENTATION_180,
		ORIENTATION_270,
	};

	// identifies entities by ids.
	enum class EEntityId : unsigned char
	{
		ENTITYID_PLAYER1=0,
		ENTITYID_PLAYER2=1,
		ENTITYID_ENEMY1=2,
		ENTITYID_ENEMY2=3,
		ENTITYID_ENEMY3=4,
		ENTITYID_ENEMY4=5,
	};

	enum class EInputAction
	{
		INPUTACTION_UP=0,
		INPUTACTION_DOWN=1,
		INPUTACTION_LEFT=2,
		INPUTACTION_RIGHT=3,
		INPUTACTION_FIRE=4,
	};
}


#endif