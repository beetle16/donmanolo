#ifndef __BEHAVIOR_H__
#define __BEHAVIOR_H__

namespace Game 
{
	class DonManolo;
	class Level;
}

namespace Engine
{
	class IBehavior
	{
	public:
		virtual void Tick(Game::DonManolo& game, Game::Level& level) = 0;
	};

}


#endif
