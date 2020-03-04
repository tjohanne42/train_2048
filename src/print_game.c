#include "train_2048.h"

void		print_game(int x, int y)
{
	size_t	size = 75;
	size_t	i = 0;
	size_t	r = 0;
	size_t	g = 0;
	size_t	b = 0;
	int		surface;

	ftmix_FillRect(x, y, 5 * game.nb + 5 + game.nb * size, 5 * game.nb + 5 + game.nb * size, 0, 0, 0, 255);
	while (i < game.nb * game.nb)
	{
		if (game.cases[i] == 0)
		{
			r = 255;
			g = 255;
			b = 255;
			surface = -1;
		}
		else if (game.cases[i] == 2)
		{
			r = 123;
			g = 123;
			b = 123;
			surface = 0;
		}
		else if (game.cases[i] == 4)
		{
			r = 255;
			g = 165;
			b = 0;
			surface = 1;
		}
		else if (game.cases[i] == 8)
		{
			r = 205;
			g = 92;
			b = 92;
			surface = 2;
		}
		else if (game.cases[i] == 16)
		{
			r = 128;
			g = 128;
			b = 0;
			surface = 3;
		}
		else if (game.cases[i] == 32)
		{
			r = 128;
			g = 128;
			b = 0;
			surface = 4;
		}
		else if (game.cases[i] == 64)
		{
			r = 128;
			g = 128;
			b = 0;
			surface = 5;
		}
		else if (game.cases[i] == 128)
		{
			r = 128;
			g = 128;
			b = 0;
			surface = 6;
		}
		else if (game.cases[i] == 256)
		{
			r = 128;
			g = 128;
			b = 0;
			surface = 7;
		}
		else if (game.cases[i] == 512)
		{
			r = 128;
			g = 128;
			b = 0;
			surface = 8;
		}
		else if (game.cases[i] == 1024)
		{
			r = 128;
			g = 128;
			b = 0;
			surface = 9;
		}
		else if (game.cases[i] == 2048)
		{
			r = 128;
			g = 128;
			b = 0;
			surface = 10;
		}
		else if (game.cases[i] == 2048)
		{
			r = 128;
			g = 128;
			b = 0;
			surface = 10;
		}
		else if (game.cases[i] == 4096)
		{
			r = 128;
			g = 128;
			b = 0;
			surface = 11;
		}
		ftmix_FillRect(x + 5 + i % game.nb * (size + 5), y + 5 + i / game.nb * (size + 5), size, size, r, g, b, 255);
		if (surface >= 0 && surface <= 11)
			ftmix_PrintSurfaceCenterXY(game.s_value[surface], x + 5 + i % game.nb * (size + 5) + size / 2, y + 5 + i / game.nb * (size + 5) + size / 2);
		i++;
	}
}
