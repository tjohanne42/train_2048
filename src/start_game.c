#include "train_2048.h"

static void			init_s_value(void)
{
	size_t			i = 0;
	SDL_Color		color = {0, 0, 0, 255};
	char			*str;

	str = NULL;
	while (i < 12)
	{
		game.s_value[i] = NULL;
		if (!(str = ft_itoa(ft_sqrt(2, i + 1))))
			ftmix_exit_error("ft_itoa");
		if (!(game.s_value[i] = TTF_RenderText_Blended(ftmix.font[30], str, color)))
			ftmix_exit_error("TTF_RenderText_Blended");
		free(str);
		str = NULL;
		i++;
		if (i == 2)
		{
			color.r = 255;
			color.g = 255;
			color.b = 255;
			color.a = 255;
		}
	}
}

static void			free_game(void)
{
	size_t			i = 0;

	if (game.cases)
	{
		free(game.cases);
		game.cases = NULL;
	}
	while (i < 12)
	{
		if (game.s_value[i])
		{
			SDL_FreeSurface(game.s_value[i]);
			game.s_value[i] = NULL;
		}
		i++;
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
		init_s_value();
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
