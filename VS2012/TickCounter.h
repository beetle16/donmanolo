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

		inline void Tick() { _counter++; }

		inline bool TargetReached() { return _counter >= _target; }

		inline void Reset() { _counter = 0; }

	};
}

#endif