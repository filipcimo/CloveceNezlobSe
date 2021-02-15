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
#define en '\n'


class Game
{
    public:
        Game() = default;
        ~Game() = default;

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


std::uint16_t Game::Player::aktualniHrac = 0;


void Game::reset()
{
    if (hraci != nullptr)
    {
        delete [] hraci;
        hraci = nullptr;
    }

    pocetHracu = 0;
}


void Game::menu()
{
    std::uint16_t pocet = 0;
    while (true)
    {
        std::cout << "Zadejte pocet hracu: ";
        std::cin >> pocet;
        std::cout << en;

        std::cin.clear();
        std::cin.sync();
        std::cout.flush();

        if (pocet < 2 || pocet > 4)
        {
            std::cerr << "Musi hrat 2 az 4 tymy!" << en << en;
            std::cerr.flush();
        }

        else if (pocet >= 2 && pocet <= 4)
        {
            pocetHracu = pocet;
            hraci = new Player[pocetHracu];

            for (std::uint16_t i = 1; i < pocetHracu; i++)
            {
                hraci[i].poziceSpawn = (i * 11);
            }

            break;
        }
    }
}


void Game::run()
{
    bool zacatek = true;
    Player* player = &hraci[rand() % pocetHracu];
    std::uint32_t kostka = rand() % 6 + 1;

    while (player->figurekDoma != 4)
    {
        if (zacatek == true)
        {
            zacatek = false;
        }

        else if (zacatek == false)
        {
            player = &hraci[hraci[0].aktualniHracPosun(*this)];
            kostka = rand() % 6 + 1;
        }

        if (player->panacekVPoli == false)
        {
            if (kostka < 6)
            {
                for (std::uint16_t i = 0; i < 2; i++)
                {
                    kostka = rand() % 6 + 1;

                    if (kostka == 6)
                    {
                        kostka = rand() % 6 + 1;
                        player->pozicePanacka += kostka;
                        player->panacekVPoli = true;

                        break;
                    }
                }
            }

            else if (kostka == 6)
            {
                kostka = rand() % 6 + 1;
                player->pozicePanacka += kostka;
                player->panacekVPoli = true;
            }
        }

        else if (player->panacekVPoli == true)
        {
            player->pozicePanacka += kostka;

            if (player->pozicePanacka >= 40)
            {
                if (player->pozicePanacka > 40)
                {
                    player->pozicePanacka -= (player->pozicePanacka - 40);
                }

                kostka = rand() % 6 + 1;

                if (kostka < 5)
                {
                    if (player->zaplnenePoziceDomecek[kostka - 1] == false)
                    {
                        player->zaplnenePoziceDomecek[kostka - 1] = true;
                        player->figurekDoma += 1;
                        player->pozicePanacka = 0;
                        player->panacekVPoli = false;
                    }
                }
            }

            for (std::uint16_t i = 0; i < pocetHracu; i++)
            {
                if (&hraci[i] != player)
                {
                    if ((hraci[i].pozicePanacka + hraci[i].poziceSpawn) == (player->pozicePanacka + player->poziceSpawn))
                    {
                        hraci[i].panacekVPoli = false;
                        hraci[i].pozicePanacka = 0;
                    }
                }
            }
        }
    }
}


void Game::results() const
{
    std::uint16_t pozice = 0;
    for (pozice = 0; pozice < pocetHracu; pozice++)
    {
        if (hraci[pozice].figurekDoma == 4) { break; }
    }

    std::cout << "Vyhral tym cislo: " << pozice + 1 << en << en;

    std::cout << "Ostatni hraci:" << en;
    for (std::uint16_t i = 0; i < pocetHracu; i++)
    {
        if (i != pozice)
        {
            std::cout << "Tym cislo: " << i + 1 << en;
            std::cout << "Panacku doma: " << hraci[i].figurekDoma << en << "Pozice posledniho panacka v hracim poli: " << hraci[i].pozicePanacka;
            if (hraci[i].pozicePanacka == 0) { std::cout << " (Panacek neni v hernim poli)"; }
            std::cout << en << en;

            std::cout.flush();
        }
    }
}


Game::Player::~Player()
{
    delete [] zaplnenePoziceDomecek;
}


std::uint16_t Game::Player::aktualniHracPosun(const Game& thisObj)
{
    if (aktualniHrac == (thisObj.pocetHracu - 1)) { aktualniHrac = 0; }
    else if (aktualniHrac < (thisObj.pocetHracu - 1)) { aktualniHrac += 1; }

    return aktualniHrac;
}


bool operator==(const std::string& s1, const std::string& s2)
{
    if (s1.size() != s2.size()) { return false; }

    for (std::uint64_t i = 0; i < s1.size(); i++)
    {
        if (s1[i] != s2[i]) { return false; }
    }

    return true;
}



int main()
{
    std::string* volba = new std::string("ano");
    Game* const game = new Game();

    while (*volba == "ano" || *volba == "ANO" || *volba == "Ano")
    {
        game->menu();
        game->run();
        game->results();
        game->reset();

        std::cout << en << "Dalsi hra ? (ano/ne)" << en;
        std::getline(std::cin, *volba);
        std::cout << en;

        std::cin.clear();
        std::cin.sync();
        std::cout.flush();
    }

    delete volba;
    delete game;

    return 0;
}
