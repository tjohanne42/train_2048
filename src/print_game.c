#include "train_2048.h"

void		print_game(int x, int y)
{
	size_t	size = 75;
	size_t	i = 0;
	size_t	r = 0;
	size_t	g = 0;
	size_t	b = 0;

	ftmix_FillRect(x, y, 5 * game.nb + 5 + game.nb * size, 5 * game.nb + 5 + game.nb * size, 0, 0, 0, 255);
	while (i < game.nb * game.nb)
	{
		if (game.cases[i] == 0)
		{
			r = 255;
			g = 255;
			b = 255;
		}
		else if (game.cases[i] == 2)
		{
			r = 123;
			g = 123;
			b = 123;
		}
		else if (game.cases[i] == 4)
		{
			r = 255;
			g = 165;
			b = 0;
		}
		else if (game.cases[i] == 8)
		{
			r = 205;
			g = 92;
			b = 92;
		}
		else if (game.cases[i] == 16)
		{
			r = 128;
			g = 128;
			b = 0;
		}
		else
		{
			r = rand() % 256;
			g = rand() % 256;
			b = rand() % 256;
		}
		ftmix_FillRect(x + 5 + i % game.nb * (size + 5), y + 5 + i / game.nb * (size + 5), size, size, r, g, b, 255);
		i++;
	}
}
