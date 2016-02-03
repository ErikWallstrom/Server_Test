#include <stdio.h>
#include "Server.h"
#include "Array.h"

int main(void)
{
    if(SDL_Init(0) || SDLNet_Init())
    {
        return EXIT_FAILURE;
    }

    Server* server = Server_create(50825, 8);
    if(server)
    {
        while(1)
        {
            if(!Server_update(server))
            {
                return EXIT_FAILURE;
            }
        }
    }
    else
    {
        return EXIT_FAILURE;
    }

    Server_destroy(&server);
    SDLNet_Quit(), SDL_Quit();
    return EXIT_SUCCESS;
}
