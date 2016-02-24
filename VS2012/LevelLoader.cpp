#include "LevelLoader.h"
#include "Level.h"
#include "BaseTypes.h"
#include "CMWC.h"
#include "PlayerBaseBehavior.h"
#include "MonsterBehavior.h"

namespace Game
{
	Point<int> LevelLoader::ReadPosition(FILE* fp)
	{
		Point<int> result;
		fscanf(fp, "%d,%d",&result._X, &result._Y);

		return result;
	}

	Level* LevelLoader::Create(char* filename)
	{
		Level* result = new Level(32,24);
		FILE* f = fopen(filename, "r");

		// load level map
		for(int y=0;y<result->GetHeight();y++)
		{
			for(int x=0;x<result->GetWidth();x++)
			{
				int m;
				if( fscanf(f, "%d", &m) == 1)
				{
					if ( m >= 0)
					{
						if( (ETileId)(m) == TILEID_WALL || (ETileId)(m) == TILEID_STRONG_WALL || (ETileId)(m) == TILEID_EATABLE_WALL )
						{
							result->SetTileId(x,y,(ETileId)(m), CMWC()%4);
						}
						else
						{
							result->SetTileId(x,y,(ETileId)(m));
						}
					}
				}
				// read delimiter, omit at end of line
				if( x != 31)
				{
					fscanf(f, ",");
				}
			}
			fscanf(f, " ");	//newlines, whitespaces
		}

		//read entity starting positions.
		for(int i=0;i<6;i++)
		{
			result->SetStartingPosition((EEntityId) i, ReadPosition(f));

			// adds the basic behavior (move on a field until reached) to entity
			Entity& entity = result->GetEntity((EEntityId)i);
			entity.AddBehavior(new Engine::BaseBehavior(entity));
		}

		// TODO: keymappings are hardcoded here...
		// add special behaviors to entities.
		Entity& p1 = result->GetEntity(EEntityId::ENTITYID_PLAYER1);
		Entity& p2 = result->GetEntity(EEntityId::ENTITYID_PLAYER2);

		Entity& m1 = result->GetEntity(EEntityId::ENTITYID_ENEMY1);
		Entity& m2 = result->GetEntity(EEntityId::ENTITYID_ENEMY2);
		Entity& m3 = result->GetEntity(EEntityId::ENTITYID_ENEMY3);
		Entity& m4 = result->GetEntity(EEntityId::ENTITYID_ENEMY4);

		std::map<EInputAction , int> p1map;
		p1map[INPUTACTION_DOWN] = SDL_SCANCODE_DOWN;
		p1map[INPUTACTION_UP] = SDL_SCANCODE_UP;
		p1map[INPUTACTION_LEFT] = SDL_SCANCODE_LEFT;
		p1map[INPUTACTION_RIGHT] = SDL_SCANCODE_RIGHT;
		p1map[INPUTACTION_FIRE] = SDL_SCANCODE_RCTRL;

		std::map<EInputAction , int> p2map;
		p2map[INPUTACTION_DOWN] = SDL_SCANCODE_S;
		p2map[INPUTACTION_UP] = SDL_SCANCODE_W;
		p2map[INPUTACTION_LEFT] = SDL_SCANCODE_A;
		p2map[INPUTACTION_RIGHT] = SDL_SCANCODE_D;
		p2map[INPUTACTION_FIRE] = SDL_SCANCODE_LCTRL;

		p1.AddBehavior(new Engine::PlayerBaseBehavior(p1, p1map));
		p2.AddBehavior(new Engine::PlayerBaseBehavior(p2, p2map));

		m1.AddBehavior(new Engine::MonsterBehavior(m1));
		m2.AddBehavior(new Engine::MonsterBehavior(m2));
		m3.AddBehavior(new Engine::MonsterBehavior(m3));
		m4.AddBehavior(new Engine::MonsterBehavior(m4));

		fclose(f);

		return result;
	}
	
}