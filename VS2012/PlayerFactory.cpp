#include "PlayerFactory.h"


// TODO move this out of level. This is game specific (app specific).
// pregenerate entites with its default textures.

namespace Game
{
	ETexture baseTextures[] = { TEXTURE_ALPHA_PLAYER1, TEXTURE_ALPHA_PLAYER2 };
	ETexture animationTextures[2][4] = { { TEXTURE_ALPHA_PLAYER1, TEXTURE_ALPHA_PLAYER1b, TEXTURE_ALPHA_PLAYER1c, TEXTURE_ALPHA_PLAYER1b },
		 { TEXTURE_ALPHA_PLAYER2, TEXTURE_ALPHA_PLAYER2b, TEXTURE_ALPHA_PLAYER2c, TEXTURE_ALPHA_PLAYER2b } };

	Player* PlayerFactory::Create(EEntityId id) 
	{
		int index = (id == ENTITYID_PLAYER1) ? 0 : 1;
		
		Player* e = new Player(baseTextures[index]);

		Engine::SimpleAnimationController* controller1 = new Engine::SimpleAnimationController(*e, 4);
		controller1->AddTexture(animationTextures[index][0]);
		controller1->AddTexture(animationTextures[index][1]);
		controller1->AddTexture(animationTextures[index][2]);
		controller1->AddTexture(animationTextures[index][3]);
		e->SetAnimationController(controller1);

		return e;
	}
}