#include "train_2048.h"

int				main(int argc, char **argv)
{
	if (argc < 1)
		SDL_Log("my main %d %s", argc, argv[0]);

	// init FTMix
	wchar_t			name[] = L"¤ MusicMixer ¤";
	wchar_t			pic_path[] = L"../src/ftmix_lib/¤pic";
	wchar_t			music_path[] = L"../music";

	ftmix_init(name, 350 + 40, 325 + 150, music_path, pic_path);
	ftmix_load();
	ftmix_event_pause();
	start_game(4);
	return (EXIT_SUCCESS);
}
