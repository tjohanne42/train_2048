#include "train_2048.h"

static void		new_case_gen(void)
{
	int			nb;
	_Bool		done = SDL_FALSE;
	size_t		i = 0;

	while (i < game.nb * game.nb)
	{
		if (game.cases[i] == 0)
			i = game.nb * game.nb;
		i++;
	}
	if (i == game.nb * game.nb)
		done = SDL_TRUE;

	while (!done)
	{
		nb = rand() % (game.nb * game.nb);
		if (game.cases[nb] == 0)
		{
			if (rand() % 2 == 0)
				game.cases[nb] = 2;
			else
				game.cases[nb] = 4;
			done = SDL_TRUE;
		}
	}
}

static void		up_game(void)
{
	size_t		i;
	_Bool		action = SDL_FALSE;
	_Bool		stop;
	size_t		z;
	_Bool		unbreak[game.nb * game.nb];

	i = 0;
	while (i < game.nb * game.nb)
	{
		unbreak[i] = SDL_FALSE;
		i++;
	}
	i = game.nb;
	while (i < game.nb * game.nb)
	{
		if (game.cases[i] == 0)
			stop = SDL_TRUE;
		else
			stop = SDL_FALSE;
		z = 0;
		while (!stop)
		{
			if (i - z < game.nb)
				stop = SDL_TRUE;
			else if (game.cases[i - z - game.nb] == 0)
			{
				game.cases[i - z - game.nb] = game.cases[i - z];
				game.cases[i - z] = 0;
				action = SDL_TRUE;
			}
			else if (!unbreak[i - z - game.nb] && game.cases[i - z - game.nb] == game.cases[i - z])
			{
				game.cases[i - z - game.nb] *= 2;
				game.cases[i - z] = 0;
				unbreak[i - z - game.nb] = SDL_TRUE;
				action = SDL_TRUE;
				stop = SDL_TRUE;
			}
			else
				stop = SDL_TRUE;
			z += game.nb;
		}
		i++;
	}
	if (action == SDL_TRUE)
		new_case_gen();
}

static void		down_game(void)
{
	int			i;
	_Bool		action = SDL_FALSE;
	_Bool		stop;
	size_t		z;
	_Bool		unbreak[game.nb * game.nb];

	i = 0;
	while ((size_t)i < game.nb * game.nb)
	{
		unbreak[i] = SDL_FALSE;
		i++;
	}
	i = game.nb * (game.nb - 1);
	while (i >= 0)
	{
		if (game.cases[i] == 0)
			stop = SDL_TRUE;
		else
			stop = SDL_FALSE;
		z = 0;
		while (!stop)
		{
			if (i + z > game.nb * (game.nb - 1))
				stop = SDL_TRUE;
			else if (game.cases[i + z + game.nb] == 0)
			{
				game.cases[i + z + game.nb] = game.cases[i + z];
				game.cases[i + z] = 0;
				action = SDL_TRUE;
			}
			else if (!unbreak[i + z + game.nb] && game.cases[i + z + game.nb] == game.cases[i + z])
			{
				game.cases[i + z + game.nb] *= 2;
				game.cases[i + z] = 0;
				unbreak[i + z + game.nb] = SDL_TRUE;
				action = SDL_TRUE;
				stop = SDL_TRUE;
			}
			else
				stop = SDL_TRUE;
			z += game.nb;
		}
		i--;
	}
	if (action == SDL_TRUE)
		new_case_gen();
}

static void		left_game(void)
{
	size_t		i;
	_Bool		action = SDL_FALSE;
	_Bool		stop;
	size_t		z;
	_Bool		unbreak[game.nb * game.nb];

	i = 0;
	while (i < game.nb * game.nb)
	{
		unbreak[i] = SDL_FALSE;
		i++;
	}
	i = 1;
	while (i < game.nb * game.nb)
	{
		if (game.cases[i] == 0)
			stop = SDL_TRUE;
		else
			stop = SDL_FALSE;
		z = 0;
		while (!stop)
		{
			if ((i - z) % game.nb == 0)
				stop = SDL_TRUE;
			else if (game.cases[i - z - 1] == 0)
			{
				game.cases[i - z - 1] = game.cases[i - z];
				game.cases[i - z] = 0;
				action = SDL_TRUE;
			}
			else if (!unbreak[i - z - 1] && game.cases[i - z - 1] == game.cases[i - z])
			{
				game.cases[i - z - 1] *= 2;
				game.cases[i - z] = 0;
				unbreak[i - z - 1] = SDL_TRUE;
				action = SDL_TRUE;
				stop = SDL_TRUE;
			}
			else
				stop = SDL_TRUE;
			z++;
		}
		i++;
	}
	if (action == SDL_TRUE)
		new_case_gen();
}

static void		right_game(void)
{
	int			i;
	_Bool		action = SDL_FALSE;
	_Bool		stop;
	size_t		z;
	_Bool		unbreak[game.nb * game.nb];

	i = 0;
	while ((size_t)i < game.nb * game.nb)
	{
		unbreak[i] = SDL_FALSE;
		i++;
	}
	i = game.nb * game.nb - 2;
	while (i >= 0)
	{
		if (game.cases[i] == 0)
			stop = SDL_TRUE;
		else
			stop = SDL_FALSE;
		z = 0;
		while (!stop)
		{
			if ((i + z) % game.nb == game.nb - 1)
				stop = SDL_TRUE;
			else if (game.cases[i + z + 1] == 0)
			{
				game.cases[i + z + 1] = game.cases[i + z];
				game.cases[i + z] = 0;
				action = SDL_TRUE;
			}
			else if (!unbreak[i + z + 1] && game.cases[i + z + 1] == game.cases[i + z])
			{
				game.cases[i + z + 1] *= 2;
				game.cases[i + z] = 0;
				unbreak[i + z + 1] = SDL_TRUE;
				action = SDL_TRUE;
				stop = SDL_TRUE;
			}
			else
				stop = SDL_TRUE;
			z++;
		}
		i--;
	}
	if (action == SDL_TRUE)
		new_case_gen();
}

void		event_game(SDL_Event event)
{
	_Bool	action = SDL_FALSE;

	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_UP && (action = SDL_TRUE))
			up_game();
		else if (event.key.keysym.sym == SDLK_DOWN && (action = SDL_TRUE))
			down_game();
		else if (event.key.keysym.sym == SDLK_LEFT && (action = SDL_TRUE))
			left_game();
		else if (event.key.keysym.sym == SDLK_RIGHT && (action = SDL_TRUE))
			right_game();
	}
}
