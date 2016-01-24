#include <stdio.h>
#include "Server.h"
#include "Array.h"

int main(void)
{
    SDL_Init(0);
    SDLNet_Init();

    Server* server = Server_create(50825, 8);
    while(1)
    {
        Server_update(server);
    }

    Server_destroy(&server);
    SDLNet_Quit();
    SDL_Quit();
    return 0;
}
