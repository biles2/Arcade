/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** Library loader header
*/

#ifndef B_OOP_400_STG_4_1_ARCADE_NICOLAS_SCHNEIDER_IMENU_HPP
#define B_OOP_400_STG_4_1_ARCADE_NICOLAS_SCHNEIDER_IMENU_HPP

#include <vector>
#include "../../utils/Text/Text.hpp"
#include "../../utils/Pixel/Pixel.hpp"
#include "../../LibGraphic/interface/IGraphic.hpp"

namespace Arcade {
    class IMenu {
    public:
        virtual void initLibAvailable(std::vector<std::pair<std::string, std::string>> libGame, std::vector<std::pair<std::string, std::string>> libGraph) = 0;
        virtual void displayText(IGraphic *lib) = 0;
        virtual void getEvent(Arcade::CommandType event, Arcade::IGraphic *lib) = 0;
        virtual std::string getLib(std::vector<std::pair<std::string, std::string>> libGame) = 0;
        virtual void initBackground(IGraphic *libGraph) = 0;
        virtual void displayBackground(IGraphic *libGraph) = 0;
    };
}

#endif //B_OOP_400_STG_4_1_ARCADE_NICOLAS_SCHNEIDER_IMENU_HPP

