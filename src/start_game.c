#include "train_2048.h"

static void			free_game(void)
{
	if (game.cases)
	{
		free(game.cases);
		game.cases = NULL;
	}
}

static void			init_game(size_t size)
{
	size_t		i = 0;

	if (!(game.cases = malloc(sizeof(*game.cases) * (size * size))))
		ftmix_exit_error("malloc");
	while (i < size * size)
	{
		game.cases[i] = 0;
		i++;
	}
	if (rand() % 2 == 0)
		game.cases[rand() % (size * size)] = 2;
	else
		game.cases[rand() % (size * size)] = 4;
	game.nb = size;
}

static SDL_Rect		print_frame(void)
{
	SDL_Rect	rect = {0, 0, 0, 0};
	size_t		tmp = 0;

	SDL_GetWindowSize(ftmix.window, &rect.w, &rect.h);
	if (rect.w < 390 && rect.h < 475)
	{
		rect.w = 390;
		rect.h = 475;
	}
	else if (rect.w < 390)
		rect.w = 390;
	else if (rect.h < 475)
		rect.h = 475;
	else
		tmp = 1;
	if (tmp == 0)
		SDL_SetWindowSize(ftmix.window, rect.w, rect.h);
	if (SDL_SetRenderDrawColor(ftmix.renderer, 255, 255, 255, 255) != 0)
		ftmix_exit_error("SDL_SetRenderDrawColor");
	if (SDL_RenderClear(ftmix.renderer) != 0)
		ftmix_exit_error("SDL_RenderClear");
	print_game(rect.w / 2 - (325 / 2), 130 * rect.h / 475);
	ftmix_print(rect.w / 2 - (350 / 2), 20 * rect.h / 475);
	return (rect);
}

static void		sync_for_ftmix(void)
{
	print_frame();
}

void		start_game(size_t size)
{
	static	_Bool	done = SDL_FALSE;
	SDL_bool		EXIT_VALUE = SDL_FALSE;
	SDL_Event		event;
	size_t			fps = 60;
	void			(*ptr)(void) = &sync_for_ftmix;
	unsigned int	last_count;
	unsigned int	current_count;

	if (!done)
	{
		atexit(free_game);
		done = SDL_TRUE;
	}
	else
		free_game();
	init_game(size);
	print_frame();
	last_count = SDL_GetTicks();
	SDL_RenderPresent(ftmix.renderer);
	while (!EXIT_VALUE)
	{
		event.type = 0;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				EXIT_VALUE = SDL_TRUE;
			else if (!ftmix_event(event, fps, ptr))
				event_game(event);
		}
		ftmix_auto_play_next();
		current_count = SDL_GetTicks();
		if (current_count - last_count >= 1000 / fps)
		{
			print_frame();
			last_count = current_count;
		}
		SDL_RenderPresent(ftmix.renderer);
	}
}
