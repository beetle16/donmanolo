#ifndef __GHOSTEDTICKCOUNTER_H__
#define __GHOSTEDTICKCOUNTER_H__

#include "TickCounter.h"

namespace Engine
{
	// Specialization of TickCounter for use with ghosted ghosts.
	// -> TargetReached -> if true, ghosts are normal, otherwise they are ghosted.
	// -> GhostedStatus -> if true, ghosted texture shall be active. This
	//			is used 
	class GhostedTickCounter : public TickCounter 
	{
	protected:
	public:
		GhostedTickCounter(int target) : TickCounter(target) {}
		GhostedTickCounter() : TickCounter() {}

		inline bool GhostedStatus() 
		{
			if (TargetReached()) { return false; }

			if (_target - _counter <= 120)
			{
				return (_counter / 20) % 2;
			}
			return true;
		}

	};
}

#endif