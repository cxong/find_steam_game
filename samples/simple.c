#include <stdio.h>
#include <find_steam_game.h>

int main(int argc, char *argv[])
{
	int ret = 0;
	if (argc < 2)
	{
		perror("Usage: program <name_of_game>");
		ret = 1;
		goto bail;
	}

	const char *game_name = argv[1];
	char buf[4096];
	fsg_get_steam_game_path(buf, game_name);
	printf("Steam: %s found at %s\n", game_name, buf);
	fsg_get_gog_game_path(buf, game_name);
	printf("GOG: %s found at %s\n", game_name, buf);

bail:
	return ret;
}
