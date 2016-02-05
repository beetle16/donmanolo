#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include "DonManolo.h"

#include <stdlib.h>
#include <crtdbg.h>

// program entry
int main(int argc, char* argv[])
{
	{
		Game::DonManolo wnd;
		wnd.Run();
	}
	_CrtDumpMemoryLeaks();
	return 0;
}