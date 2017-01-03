#ifndef __TICKCOUNTER_H__
#define __TICKCOUNTER_H__

namespace Engine
{
	class TickCounter {
	protected:
		int _counter;
		int _target;

	public:
		


		TickCounter(int target) {
			_counter = 0;
			_target = target;
		}

		TickCounter() 
		{
			_counter = 0;
			_target = 0;
		}


		inline void Tick() { if (!TargetReached()) { _counter++; } }

		inline void SetTarget(int target) { _target = target; }

		inline bool TargetReached() { return _counter >= _target; }

		inline void Reset() { _counter = 0; }

	};
}

#endif