/*
** EPITECH PROJECT, 2021
** B_OOP_400_STG_4_1_arcade_maxime_frechard
** File description:
** Created by arthur,
*/

#include "Core.hpp"
#include <time.h>
#include <fstream>

Arcade::Core::Core()
{
    _graphicLib = nullptr;
    _gameLib = nullptr;
}

Arcade::Core::~Core()
{
}

void Arcade::Core::setGraphicLib(Arcade::IGraphic *lib)
{
    _graphicLib = lib;
}

void Arcade::Core::setGameLib(Arcade::IGame *game_lib)
{
    _gameLib = game_lib;
}

Arcade::IGraphic *Arcade::Core::getGraphicLib() const
{
    return _graphicLib;
}

Arcade::IGame *Arcade::Core::getGameLib() const
{
    return _gameLib;
}

void Arcade::Core::set_game_name(const std::string &game_name)
{
    _gameName = game_name;
}

const std::string &Arcade::Core::get_game_name() const
{
    return _gameName;
}

void Arcade::Core::switchLib(Arcade::LibLoader &loader, Arcade::CommandType event)
{
    Arcade::CommandType libEvent[] = {
        Arcade::NUM0,
        Arcade::NUM1,
        Arcade::NUM2,
        Arcade::NUM3
    };

    if (std::find(libEvent, libEvent + 4, event) == libEvent + 4)
        return;
    if (event == Arcade::CommandType::NUM0) {
        delete _graphicLib;
        this->setGraphicLib(loader.loadNextGraphics(true));
    } else if (event == Arcade::CommandType::NUM1) {
        delete _graphicLib;
        this->setGraphicLib(loader.loadNextGraphics(false));
    } else if (event == Arcade::CommandType::NUM2) {
        delete _gameLib;
        this->setGameLib(loader.loadNextGame(true));
        getGameLib()->initPlayerName(_playerName);
    } else if (event == Arcade::CommandType::NUM3) {
        delete _gameLib;
        this->setGameLib(loader.loadNextGame(false));
        getGameLib()->initPlayerName(_playerName);
    }
}

bool Arcade::Core::runGame(LibLoader &loader, std::string &playerName)
{
    Arcade::CommandType cmd = NO_EVENT;
    clock_t start_t = 0;
    clock_t end_t = 0;
    double current_time = 0.0f;
    double dt = 0.0f;

    _gameLib->initPlayerName(playerName);
    while (cmd != Arcade::CommandType::CLOSE_WINDOW && cmd != Arcade::CommandType::ESC && cmd != Arcade::CommandType::SPACE) {
        start_t = clock();
        cmd = _graphicLib->getInput();
        _gameLib->getEvent(cmd, _graphicLib);
        switchLib(loader, cmd);
        if (dt >= double(1.0f / 25.0f)) {
            _graphicLib->myClear();
            _gameLib->draw(_graphicLib);
            _graphicLib->myRefresh();
            dt = 0.0f;
        }
        _gameLib->update(current_time);
        end_t = clock();
        current_time = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        dt += current_time;
    }
    if (cmd == Arcade::CommandType::ESC || cmd == Arcade::CommandType::CLOSE_WINDOW)
        return false;
    else
        return true;
}

std::string Arcade::Core::playerNameLoop(Arcade::LibLoader &loader, Arcade::IMenu *menu)
{
    Arcade::CommandType event = Arcade::NO_EVENT;
    std::string name;
    clock_t start_t;
    clock_t end_t;
    double current_time = 0.0f;
    double dt = 0.0f;

    while (event != Arcade::ESC && event != Arcade::ENTER && event != Arcade::CLOSE_WINDOW) {
        start_t = clock();
        event = getGraphicLib()->getInput();
        if (Core_KEY.find(event) != Core_KEY.end()) {
            name.push_back(Core_KEY.find(event)->second);
        }
        else if (event == Arcade::BACKSPACE) {
            name.pop_back();
        }
        switchLib(loader, event);
        if (dt >= double(1.0f / 25.0f)) {
            menu->setPlayerName(name);
            menu->displayBackground(getGraphicLib());
            menu->displayPlayerName(getGraphicLib());
            dt -= double(1.0f / 25.0f);
        }
        end_t = clock();
        current_time = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        dt += current_time;
    }
    _playerName = name;
    return name  == "" ? "Anonymous" : name;
}

void Arcade::Core::storeScore(const std::string game, const std::string playerName, int score)
{
    std::ofstream myfile(game + ".txt");
    if (myfile.is_open()) {
        myfile << playerName << ": " << score << "\n";
        myfile.close();
    } else
        std::cout << "Unable to store score" << std::endl;
}

std::vector<std::vector<std::string>> Arcade::Core::getScores() const
{
    std::vector<std::vector<std::string>> scores = { std::vector<std::string>(), std::vector<std::string>() };
    std::string line;
    std::ifstream nibblerFile("Nibbler.txt");
    std::ifstream pacmanFile("Pacman.txt");

    if (nibblerFile.is_open() && pacmanFile.is_open()) {
        while (getline(nibblerFile, line))
            scores[0].push_back(line);
        while (getline(pacmanFile, line))
            scores[1].push_back(line);
        nibblerFile.close();
        pacmanFile.close();
    } else
        std::cout << "Something went wrong while reading scores" << std::endl;
    return scores;
}

void Arcade::Core::deleteLibs()
{
    delete _gameLib;
    delete _graphicLib;
}
