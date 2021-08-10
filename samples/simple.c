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

	const bool exists = fsg_game_exists(game_name);
	printf("%s exists? %s\n", game_name, exists ? "yes" : "no");

bail:
	return ret;
}
