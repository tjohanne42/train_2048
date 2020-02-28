#include "train_2048.h"

static void		up_game(void)
{
	
}

void		event_game(SDL_Event event)
{
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_UP)
			up_game();
	}
}
