#ifndef __SCREEN_H__
#define __SCREEN_H__

#include "DonManolo.h"

#include <SDL.h>

namespace Game
{
	class DonManolo;
	class Level;

	class ScreenBase
	{
	protected:
		
		DonManolo* _parent;
	public:
		ScreenBase(DonManolo* parent);
		virtual ~ScreenBase();

		virtual void Render() = 0;
		virtual void Tick() = 0;
	};

	class ScreenMenu : public ScreenBase
	{
	private:
		SDL_Rect _background_rect;
		SDL_Rect _cursor_pos;
		int _cursor_pos_index;
	public:
		ScreenMenu(DonManolo* parent);
		virtual ~ScreenMenu();

		virtual void Render();
		virtual void Tick();
	};

	class ScreenLevelBase : public ScreenBase
	{
	protected:
		Level* _level;
		bool _ready;
	public:
		ScreenLevelBase(DonManolo* parent, Level* level);
		Level& GetLevel() const;

		virtual ~ScreenLevelBase();

		virtual void Render();
		virtual void Tick();
	};
}

#endif