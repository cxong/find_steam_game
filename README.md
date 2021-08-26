# find_steam_game
Cross platform C library for finding games installed from platforms like steam

## Usage

```c
#include <find_steam_game.h>

char buf[4096];
fsg_get_steam_game_path(buf, "Wolfenstein 3D");
printf("Steam: %s found at %s\n", "Wolfenstein 3D", buf);

// Prints: Steam: Wolfenstein 3D found at c:/program files (x86)/steam/SteamApps/common/Wolfenstein 3D
 ```

## Support

| Store      | Windows | Linux | macOS |
| ----------- | ----------- |----------- |----------- |
| Steam      | ✔ (folder name) | ✔ |  ❌ | 
| GOG   |  ✔ (game id) | ❌ |  ❌ |
