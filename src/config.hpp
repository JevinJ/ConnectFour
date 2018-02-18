/*
 * config.hpp
 *
 *  Created on: Dec 27, 2017
 *      Author: Jevin
 */

#ifndef CONFIG_HPP_
#define CONFIG_HPP_
#include <SFML/Graphics.hpp>


//Custom colors.
namespace CustomColor {
    const sf::Color LightGrey = sf::Color(100, 100, 100);
    const sf::Color DarkGrey = sf::Color(70, 70, 70);
    const sf::Color Black = sf::Color(100, 100, 100);
    const sf::Color Red = sf::Color(255, 90, 90);
}

//Menu
enum Difficulty {Easy = 1, Medium, Hard=4};
enum PlayerCount {One = 1, Two};
const unsigned int MENU_WINDOW_WIDTH = 400;
const unsigned int MENU_WINDOW_HEIGHT = 420;

//Main/State
const unsigned int MAIN_WINDOW_WIDTH = 798;
const unsigned int MAIN_WINDOW_HEIGHT = 798;
const unsigned int MAIN_WINDOW_AA_LEVEL = 4;

//Token
const float TOKEN_RADIUS = 57.0;

//Board
const int DEFAULT_PREPLACE_X_POS = 3;
const unsigned int TOKEN_WALL_HEIGHT = 6;
const unsigned int TOKEN_WALL_WIDTH = 7;

//Player
const unsigned int MAX_PLAYER_TOKENS = 21;

//Negamax/Win checks
const unsigned int NEGAMAX_DEFAULT_DEPTH = 6;
const bool BOOL_HUMAN_COLOR = false;
const bool BOOL_AI_COLOR = true;


#endif /* CONFIG_HPP_ */
