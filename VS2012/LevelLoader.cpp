#include "LevelLoader.h"
#include "Level.h"
#include "BaseTypes.h"
#include "CMWC.h"
#include "PlayerBaseBehavior.h"
#include "MonsterBehavior.h"

namespace Game
{
	
	void LevelLoader::ReadMap(Level* result, FILE* f)
	{
		// load level map
		for (int y = 0; y < result->GetHeight(); y++)
		{
			for (int x = 0; x < result->GetWidth(); x++)
			{
				int m;
				if (fscanf(f, "%d", &m) == 1)
				{
					if (m >= 0)
					{
						if ((ETileId)(m) == ETileId::TILEID_WALL || (ETileId)(m) == ETileId::TILEID_STRONG_WALL || (ETileId)(m) == ETileId::TILEID_EATABLE_WALL)
						{
							result->SetTileId(x, y, (ETileId)(m), CMWC() % 4);
						}
						else
						{
							result->SetTileId(x, y, (ETileId)(m));
						}
					}
				}
				// read delimiter, omit at end of line
				if (x != 31)
				{
					fscanf(f, ",");
				}
			}
			fscanf(f, " ");	//newlines, whitespaces
		}
	}


	Point<int> LevelLoader::ReadPosition(FILE* fp)
	{
		Point<int> result;
		fscanf(fp, "%d,%d",&result._X, &result._Y);

		return result;
	}



	Level* LevelLoader::Create(std::vector<Player*>& players, char* filename, int id)
	{
		Level* result = new Level(players, 32,24, id);
		FILE* f = fopen(filename, "r");

		ReadMap(result, f);

		//read entity starting positions.
		for(int i = 0; i < 6; i++)
		{
			result->SetStartingPosition((EEntityId) i, ReadPosition(f));

			if (i >= 2) 
			{
				// adds the basic behavior (move on a field until reached) to entity
				Entity& entity = result->GetEntity((EEntityId)i);
				entity.AddBehavior(new Engine::BaseBehavior(entity));
			}
		}

		int gameSpeed;
		int enemySpeed;
		int ghostedTime;
		fscanf(f, "%d,%d,%d", &gameSpeed, &enemySpeed, &ghostedTime);
		result->SetGameSpeed(gameSpeed);
		result->SetEnemySpeed(enemySpeed);
		result->SetGhostedTime(ghostedTime);

		// TODO: keymappings are hardcoded here...
		// add special behaviors to entities.
		Entity& p1 = result->GetEntity(EEntityId::ENTITYID_PLAYER1);
		Entity& p2 = result->GetEntity(EEntityId::ENTITYID_PLAYER2);

		Entity& m1 = result->GetEntity(EEntityId::ENTITYID_ENEMY1);
		Entity& m2 = result->GetEntity(EEntityId::ENTITYID_ENEMY2);
		Entity& m3 = result->GetEntity(EEntityId::ENTITYID_ENEMY3);
		Entity& m4 = result->GetEntity(EEntityId::ENTITYID_ENEMY4);



		m1.AddBehavior(new Engine::MonsterBehavior(m1));
		m2.AddBehavior(new Engine::MonsterBehavior(m2));
		m3.AddBehavior(new Engine::MonsterBehavior(m3));
		m4.AddBehavior(new Engine::MonsterBehavior(m4));

		fclose(f);

		return result;
	}
	
}