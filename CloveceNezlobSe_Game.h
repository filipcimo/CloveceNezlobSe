#ifndef CLOVECENEZLOBSE_GAME_H
#define CLOVECENEZLOBSE_GAME_H
#include <stdio.h>
#include <stdlib.h>
#include <cctype>
#include <iostream>
#include <string.h>
#include <math.h>
#include <cmath>
#include <tuple>
#include <ios>
#include <limits>
#include <memory>
static const char en = '\n';



class Game
{
    public:
        Game() = default;
        ~Game();

        void menu();
        void run();
        void reset();
        void results() const;


    private:
        class Player
        {
            public:
                Player() = default;
                ~Player();

                static std::uint16_t aktualniHracPosun(const Game& thisObj);

                static std::uint16_t aktualniHrac;
                bool panacekVPoli = false;
                std::uint16_t poziceSpawn = 0;
                std::uint16_t figurekDoma = 0;
                std::uint16_t pozicePanacka = 0;
                bool* const zaplnenePoziceDomecek = new bool[4] {false, false, false, false};
        };

        Player* hraci = nullptr;
        std::uint16_t pocetHracu = 0;
};



#endif  // CLOVECENEZLOBSE_GAME_H
