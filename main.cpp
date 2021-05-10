#include "CloveceNezlobSe_Game.h"



int main()
{
    try
    {
        Game* const game = new Game();

        game->menu();
        game->run();
        game->results();
        game->reset();

        std::cin.clear();
        std::cin.sync();
        std::cout.flush();

        delete game;
    }

    catch (const std::exception& err)
    {
        std::cerr << err.what() << en;
        exit(EXIT_FAILURE);
    }


    return 0;
}