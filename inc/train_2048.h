#ifndef TRAIN_2048_H
 #define TRAIN_2048_H

#include "ftmix_lib.h"

#define NB_CASES 4

typedef	struct 		t_game
{
	unsigned int	*cases;
	size_t			nb;
	SDL_Surface		*s_value[12];
}					s_game;

s_game		game;

void		start_game(size_t size);
void		event_game(SDL_Event event);
void		print_game(int x, int y);

#endif